CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g
LDFLAGS=-g -pthread
LDLIBS=

SRCS=thipc.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: thipc

thipc: $(OBJS)
	    $(CXX) $(LDFLAGS) -o thipc $(OBJS) $(LDLIBS) 

thipc.o: thipc.cpp

clean:
	    $(RM) $(OBJS)

distclean: clean
	    $(RM) thipc
