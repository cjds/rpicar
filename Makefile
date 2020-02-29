CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=
LDFLAGS=
LDLIBS=

SRCS=src/main.cpp
OBJS=$(subst .cc,.o, $(SRCS))

all: tool

tool: $(OBJS)
	    $(CXX) $(LDFLAGS) -o tool $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	    $(RM) ./.depend
	        $(CXX) $(CPPFLAGS) -MM $^>>./.depend;

distclean: clean
	    $(RM) *~ .depend

include .depend

