# FSM makefile.
# Author: 11 Jan 2017
# Author: 11 Jan 2017

TARGETNAME=fsm.exe
TARGETTYPE=APP
#TARGETTYPE=LIB

CXXSOURCES=$(wildcard *.cpp)
CXXSOURCES+=$(patsubst %.cxx,%.cpp, $(wildcard *.cxx))
CXXSOURCES+=$(patsubst %.cc,%.cpp,  $(wildcard *.cc))

CSOURCES=$(wildcard *.c)

HEADERS=$(wildcard *.h)
HEADERS+=$(patsubst %.hxx,%.h, $(wildcard *.hxx))
HEADERS+=$(patsubst %.hpp,%.h, $(wildcard *.hpp))


# COMMON COMMON COMMON COMMON COMMON COMMON COMMON COMMON
ARCH=x64

ifeq (CONFIG, Debug)
SUBDIR=debug
elif (CONFIG, Release)
SUBDIR=release
else
CONFIG=Debug
SUBDIR=debug
endif

# Specify files to be included
INCDIR=-I./
BLDDIR=./$(ARCH)/$(SUBDIR)
OBJDIR=$(BLDDIR)/obj/
LIBDIR=$(BLDDIR)/lib/
APPDIR=$(BLDDIR)/bin/

LDDIR=-L$(LIBDIR)

GCC=/usr/bin/gcc
GXX=/usr/bin/g++
LD=/usr/bin/g++
AR=/usr/bin/ar
RM=/usr/bin/rm -f
AS=/usr/bin/as
GDB=/usr/bin/gdb
MKDIR=/usr/bin/mkdir -p


ifeq (CONFIG, Debug)
GXXFLAGS= -g -DDEBUG
CFLAGS= -g -DDEBUG
endif
ifeq (CONFIG, Release)
GXXFLAGS= -O2
CFLAGS= -O2
endif

GXXFLAGS+=-c -std=c++14 -m64 -Wall -Werror
CFLAGS+=-c -m64 -Wall -Werror

ifdef MAP
GXXFLAGS+= -Wa,-aln=$(OBJDIR)$<.s
CFLAGS+= -Wa,-aln=$(OBJDIR)$<.s
endif


ASFLAGS=
LDFLAGS=-Wl,-Map=$(OBJDIR)$(TARGETNAME).map
ARFLAGS=crvs

OBJEXT=.o
LIBEXT=.a
APPEXT=.exe
# COMMON COMMON COMMON COMMON COMMON COMMON COMMON COMMON

TARGET=$($(TARGETTYPE)DIR)$(TARGETNAME)
#TARGET=$($(TARGETTYPE)DIR)$(TARGETNAME)$($(TARGETTYPE)EXT)
OBJECTS=$(patsubst %.cpp,$(OBJDIR)%$(OBJEXT), $(CXXSOURCES))
LIBS=

ifeq ($(TARGETTYPE),APP)
# Link the object files into a binary
$(TARGET) : $(OBJECTS) $(BLDDIR) $(APPDIR)
	$(LD) $(LDDIR) $(LIBS) $(LDFLAGS) -o $(TARGET) $(OBJECTS)
endif

# Archive objects into a library
ifeq ($(TARGETTYPE),LIB)
$(TARGET) : $(OBJECTS) $(BLDDIR) $(LIBDIR)
	$(AR) $(ARFLAGS) $(TARGET) $(OBJECTS)
endif

# Compile the source files into an object files
$(OBJDIR)%.o : %.c $(HEADERS) $(BLDDIR) $(OBJDIR)
	$(RM) $(OBJDIR)$<.s
	$(GCC) $(INCDIR) $(CFLAGS)$ $< -o $@
  
$(OBJDIR)%.o : %.cpp $(HEADERS) $(BLDDIR) $(OBJDIR)
	$(RM) $(OBJDIR)$<.s
	$(GXX) $(INCDIR) $(GXXFLAGS) $< -o $@
  
$(BLDDIR) :
	$(MKDIR) $(BLDDIR)

$(OBJDIR) : $(BLDDIR)
	$(MKDIR) $(OBJDIR)

$(LIBDIR) : $(BLDDIR)
	$(MKDIR) $(LIBDIR)

$(APPDIR) : $(BLDDIR)
	$(MKDIR) $(APPDIR)

.PHONY : all
all : $(TARGET)

.PHONY : clean
clean :
	echo $(RM) $(OBJECTS) $(TARGET) $(OBJDIR)*.cpp.s
	$(RM) $(OBJECTS) $(TARGET)
# bz debug	echo $(CXXSOURCES) $(HEADERS) $(CSOURCES)

