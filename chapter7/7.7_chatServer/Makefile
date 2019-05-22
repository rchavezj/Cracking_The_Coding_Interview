# $Id: Makefile,v 1.7 2016-07-25 20:09:21-07 - - $

WARN     = -Wall -Wextra -Wold-style-cast
GPP      = g++ -std=gnu++14 -g -O0 ${WARN}

DEPFILE  = Makefile.dep
HEADERS  = sockets.h protocol.h logstream.h
CPPLIBS  = sockets.cpp protocol.cpp 
CPPSRCS  = ${CPPLIBS} cix.cpp cixd.cpp
LIBOBJS  = ${CPPLIBS:.cpp=.o}
CIXOBJS  = cix.o ${LIBOBJS}
CIXDOBJS = cixd.o ${LIBOBJS}
OBJECTS  = ${CIXOBJS} ${CIXDOBJS}
EXECBINS = cix cixd
LISTING  = Listing.ps cix cixd
SOURCES  = ${HEADERS} ${CPPSRCS} Makefile

all: ${DEPFILE} ${EXECBINS}

cix: ${CIXOBJS}
	${GPP} -o $@ ${CIXOBJS}

cixd: ${CIXDOBJS}
	${GPP} -o $@ ${CIXDOBJS}

%.o: %.cpp
	${GPP} -c $<
	- cpplint.py.perl $<

ci: ${SOURCES}
	- checksource ${SOURCES}
	- cpplint.py.perl ${CPPSRCS}
	- cid + ${SOURCES}

lis: all ${SOURCES} ${DEPFILE}
	mkpspdf ${LISTING} ${SOURCES} ${DEPFILE}

clean:
	- rm ${LISTING} ${LISTING:.ps=.pdf} ${OBJECTS} Makefile.dep

spotless: clean
	- rm ${EXECBINS}

dep:
	- rm ${DEPFILE}
	make --no-print-directory ${DEPFILE}

${DEPFILE}:
	${GPP} -MM ${CPPSRCS} >${DEPFILE}

again: ${SOURCES}
	make --no-print-directory spotless ci all lis

include ${DEPFILE}

