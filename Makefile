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
FILES		= main.cc
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
CXX = colorgcc	
CC = $(CXX)

# What flags should be passed to the compiler

DEBUG_LEVEL     = -g
EXTRA_CCFLAGS   = -Wall
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

LDFLAGS         = -L.
#                  -R $(LIB_DIR)
#                  -R $(LIB_DIR):$(COURSE_DIR)

# What libraries should be linked with.
# For example, -lm links with libm.so, the math library.
# If you make a library of your own, say, libscandir.a, you have to link it
# in by adding -lscandir here.
#LDLIBS          = -lscandir

# All source files have associated object files.
# This line sets `OFILES' to have the same value as `SRC_FILES' but
# with all the .cc's changed into .o's.
O_FILES         = $(BUILD_DIR)/$(SRC_FILES:%.cc=%.o)

#O_FILES         = $(BUILD_DIR)/$(FILES:%.cc=%.o)


###########################################################################
# Additional rules make should know about in order to compile our files
###########################################################################
# all is the default rule
all: $(EXEC)
#	echo $(O_FILES)
#	g++ main.cc 2>&1 | sed -e "s/\(error:\)\(.*\)$/`echo -e '\033[31m\1\033[34;1m\2\033[0m'`/g" -e "s/^\([^:]*:\)\([ 0-9]*\)/`echo -e '\033[37;1m \1 \033[35;0m \2 \033[0m'`/g"


# exec depends on the object files
# It is made automagically using the LDFLAGS and LOADLIBES variables.
# The .o files are made automagically using the CXXFLAGS variable.
$(EXEC): $(O_FILES)

# to use `makedepend', the target is `depend'
depend:
	makedepend -- $(CXXFLAGS) -- -Y $(SRC_FILES) -p $(BUILD_DIR)/



# clean up after you're done
clean:
	$(RM) $(O_FILES) core *.rpo

very-clean: clean
	$(RM) $(EXEC)
# DO NOT DELETE

build/src/main.o: src/AIInterface.cc include/log.h
