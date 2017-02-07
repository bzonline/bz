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
else
CONFIG=Release
SUBDIR=release
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

#GXXFLAGS=-c -std=c++11 -m64 -Wall -Werror -fpermissive
GXXFLAGS=-c -std=c++17 -m64 -Wall -Werror
CFLAGS=-c -m64 -Wall -Werror

ifeq (CONFIG, Debug)
GXXFLAGS+= -g -DDEBUG
CFLAGS+= -g -DDEBUG
endif
ifeq (CONFIG, Release)
GXXFLAGS+= -O2
CFLAGS+= -O2
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
	$(GCC) $(INCDIR) $(CFLAGS)$(OBJDIR)$<.s $< -o $@
  
$(OBJDIR)%.o : %.cpp $(HEADERS) $(BLDDIR) $(OBJDIR)
	$(RM) $(OBJDIR)$<.s
	$(GXX) $(INCDIR) $(GXXFLAGS)$(OBJDIR)$<.s $< -o $@
  
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

