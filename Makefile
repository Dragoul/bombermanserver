##############################################################################
#
#  Sample Makefile for C++ applications
#    Works for single and multiple file programs.
#    written by Robert Duvall
#    modified by Owen Astrachan
#    and by Garrett Mitchener
# 
##############################################################################

##############################################################################
# Application-specific variables
# EXEC is the name of the executable file
# SRC_FILES is a list of all source code files that must be linked
#           to create the executable
##############################################################################

BUILD_DIR	= build
SOURCE_DIR	= src
INC_DIR		= include


EXEC		= $(BUILD_DIR)/bombermanserver
FILES		= main.cc src/player.cc
SRC_FILES	= $(SOURCE_DIR)/$(FILES)

##############################################################################
# Where to find course related files
# are found.  LIB_DIR is where various header files (.h) and library files (.so and .a) are kept.
LIB_DIR     = /usr/local/lib

##############################################################################
# Compiler specifications
# These match the variable names given in /usr/share/lib/make/make.rules
# so that make's generic rules work to compile our files.
# gmake prefers CXX and CXXFLAGS for c++ programs
##############################################################################
# Which compiler should be used
CXX = g++ #colorgcc
CC = $(CXX)

# What flags should be passed to the compiler

DEBUG_LEVEL     = -g
EXTRA_CCFLAGS   = -Wall -vvv
CXXFLAGS        = $(DEBUG_LEVEL) $(EXTRA_CCFLAGS)
CCFLAGS         = $(CXXFLAGS)

# What flags should be passed to the C pre-processor
#   In other words, where should we look for files to include - note,
#   you should never need to include compiler specific directories here
#   because each compiler already knows where to look for its system
#   files (unless you want to override the defaults)

CPPFLAGS        = -I. \
                  -I$(INC_DIR)

# What flags should be passed to the linker
#   In other words, where should we look for libraries to link with - note,
#   you should never need to include compiler specific directories here
#   because each compiler already knows where to look for its system files.

LDFLAGS	=	-L. \
		-R $(LIB_DIR)

# What libraries should be linked with.
# For example, -lm links with libm.so, the math library.
# If you make a library of your own, say, libscandir.a, you have to link it
# in by adding -lscandir here.
#LDLIBS          = -lscandir

# All source files have associated object files.
# This line sets `OFILES' to have the same value as `SRC_FILES' but
# with all the .cc's changed into .o's.

O_FILES         = $(SRC_FILES:%.cc=$(BUILD_DIR)/%.o)

###########################################################################
# Additional rules make should know about in order to compile our files
###########################################################################
# all is the default rule
all: $(EXEC)
	@echo "Building all: $(SRC_FILES) -> $(O_FILES)"
	mkdir -vp $(dir $(O_FILES))

	$(CXX) -c -o $(O_FILES) $(SRC_FILES)
	@find . -name *.o
	$(CXX) $(O_FILES) -o $(EXEC)

# exec depends on the object files
# It is made automagically using the LDFLAGS and LOADLIBES variables.
# The .o files are made automagically using the CXXFLAGS variable.
$(EXEC): $(O_FILES)


#$(objects): | obj
#
#obj:
#  @mkdir -p $@
#
#obj/%.o : %.cpp
#  @echo $< 
#  @$(CXX) $(CXXFLAGS) -c $< -o $@

#What does the "|" in the line $(objects): | obj stands for? 
#
#ezhaka, it means that the prerequisites that follow (in this case obj) are order-only prerequisites. This means that if any $(objects) must be built then obj must be built first, but if obj is out of date (or doesn't exist), that does not force $(objects) to be built.



# to use `makedepend', the target is `depend'
depend:
	makedepend -vm -- $(CXXFLAGS) -- -Y $(SRC_FILES) -p $(BUILD_DIR)/



# clean up after you're done
clean:
	$(RM) -v $(O_FILES) core *.rpo

very-clean: clean
	$(RM) -v $(EXEC)



# DO NOT DELETE

build/src/main.o: src/AIInterface.cc
# src/AIInterface.cc includes:
#	../include/log.h
#	player.h
build/src/main.o: include/log.h src/player.h
# src/player.h includes:
#	board.h
build/src/main.o: src/board.h
build/src/player.o: include/log.h
