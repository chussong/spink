# makefile for spink

#-------------------------------------------------------------------------------
# setup, declarations, options
#-------------------------------------------------------------------------------

# what version this is
VER_BREAKING := 0
VER_RELEASE := 1
VER_HOTFIX := 1
VER_MACRO := SPINK_VERSION=\"$(VER_BREAKING).$(VER_RELEASE).$(VER_HOTFIX)\"

# locations of various subdirectories within the build tree
SRCDIR := source
OBJDIR := objects
INCDIR := include
TESTDIR := tests

# definitions of various targets
MAIN_EXEC := spink

# compiler options
DEBUGFLAGS := -g -Werror -Wall -Wextra -pedantic -fsanitize=address,undefined
CXXFLAGS := -I$(INCDIR) -c -std=c++17 -D$(VER_MACRO) $(DEBUGFLAGS)
LDFLAGS := -lstdc++fs -lasan -lubsan

#-------------------------------------------------------------------------------
# find files in the build tree
#-------------------------------------------------------------------------------

HEADERS := $(wildcard $(INCDIR)/*.hpp)

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
DEPFILES := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.d)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

TEST_SRCS := $(wildcard $(TESTDIR)/*.cpp)
TEST_DEPS := $(TEST_SRCS:$(TESTDIR)/%.cpp=$(TESTDIR)/$(OBJDIR)/%.d)
TEST_OBJS := $(TEST_SRCS:$(TESTDIR)/%.cpp=$(TESTDIR)/$(OBJDIR)/%.o)

#-------------------------------------------------------------------------------
# meta targets
#-------------------------------------------------------------------------------

.PHONY: all, clean

all: $(MAIN_EXEC)

clean:
	rm -f $(MAIN_EXEC) $(DEPFILES) $(OBJECTS)

#-------------------------------------------------------------------------------
# final targets
#-------------------------------------------------------------------------------

$(MAIN_EXEC): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

#-------------------------------------------------------------------------------
# intermediate dependency and object targets
#-------------------------------------------------------------------------------

# build dependency file first, then build object file
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) -MM -MP -MT $(OBJDIR)/$(*F).o -MT $(OBJDIR)/$(*F).d $(CXXFLAGS) \
	    $< > $(OBJDIR)/$(*F).d
	$(CXX) -c $< $(CXXFLAGS) -o $@

$(OBJDIR):
	mkdir $@

-include $(DEPFILES)

