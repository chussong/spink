# makefile for spink

#-------------------------------------------------------------------------------
# setup, declarations, options
#-------------------------------------------------------------------------------

# what version this is
VER_BREAKING := 0
VER_RELEASE := 1
VER_HOTFIX := 1
VER_MACRO := SPINK_VERSION=\"$(VER_BREAKING).$(VER_RELEASE).$(VER_HOTFIX)\"

# definitions of various targets
MAIN_EXEC := spink
TEST_EXEC := test_spink
LIB_STATIC := libspink.a
LIB_SHARED := libspink.so

# locations of various subdirectories within the build tree
SRCDIR := source
OBJDIR := objects
INCDIR := include
TESTDIR := tests
TARGET_LIB_DIR := libs
TARGET_LIB_STATIC := $(TARGET_LIB_DIR)/$(LIB_STATIC)
TARGET_LIB_SHARED := $(TARGET_LIB_DIR)/$(LIB_SHARED)

# compiler options
DEBUGFLAGS := -g -Werror -Wall -Wextra -pedantic -fsanitize=address,undefined
CXXFLAGS := -I$(INCDIR) -c -std=c++17 -D$(VER_MACRO) $(DEBUGFLAGS)
LDFLAGS := -lstdc++fs -lasan -lubsan

#-------------------------------------------------------------------------------
# find files in the build tree
#-------------------------------------------------------------------------------

HEADERS := $(wildcard $(INCDIR)/*.hpp)

LIB_SRCS := $(wildcard $(SRCDIR)/*.cpp)
TEST_SRCS := $(wildcard $(SRCDIR)/$(TESTDIR)/*.cpp)
LIB_SRCS := $(filter-out $(wildcard */main.cpp), $(LIB_SRCS))
LIB_SRCS := $(filter-out $(TEST_SRCS), $(LIB_SRCS))

LIB_DEPS := $(LIB_SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.d)
LIB_OBJS := $(LIB_SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

TEST_DEPS := $(TEST_SRCS:$(SRCDIR)/$(TESTDIR)/%.cpp=$(OBJDIR)/$(TESTDIR)/%.d)
TEST_OBJS := $(TEST_SRCS:$(SRCDIR)/$(TESTDIR)/%.cpp=$(OBJDIR)/$(TESTDIR)/%.o)

#-------------------------------------------------------------------------------
# meta targets
#-------------------------------------------------------------------------------

.PHONY: all, clean

all: $(TARGET_LIBS) $(MAIN_EXEC) $(TEST_EXEC)

clean:
	rm -f $(TARGET_LIBS) $(MAIN_EXEC) $(TEST_EXEC) \
	    $(LIB_DEPS) $(LIB_OBJS) $(TEST_DEPS) $(TEST_OBJS) \
	    $(OBJDIR)/main.o $(OBJDIR)/main.d

#-------------------------------------------------------------------------------
# final targets
#-------------------------------------------------------------------------------

$(TARGET_LIB_STATIC): $(LIB_OBJS)
	ar rcs $@ $^

$(TARGET_LIB_SHARED): $(LIB_OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) -shared

$(MAIN_EXEC): $(OBJDIR)/main.o $(TARGET_LIB_STATIC)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(TEST_EXEC): $(TEST_OBJS) $(TARGET_LIB_STATIC)
	$(CXX) -o $@ $^ $(LDFLAGS)

#-------------------------------------------------------------------------------
# intermediate dependency and object targets
#-------------------------------------------------------------------------------

# build dependency file first, then build object file
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -MM -MP -MT $(OBJDIR)/$(*F).o -MT $(OBJDIR)/$(*F).d $(CXXFLAGS) \
	    $< > $(OBJDIR)/$(*F).d
	$(CXX) -c $< $(CXXFLAGS) -o $@

$(OBJDIR)/$(TESTDIR)/%.o: $(SRCDIR)/$(TESTDIR)/%.cpp
	$(CXX) -MM -MP -MT $(OBJDIR)/$(TESTDIR)/$(*F).o \
	    -MT $(OBJDIR)/$(TESTDIR)/$(*F).d $(CXXFLAGS) $< \
	    > $(OBJDIR)/$(TESTDIR)/$(*F).d
	$(CXX) -c $< $(CXXFLAGS) -o $@

-include $(LIB_DEPS)
-include $(TEST_DEPS)

