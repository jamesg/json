first:	all

CPPFLAGS=-std=c++0x -O3 -g0 -Iinclude/
LIBS=-lboost_regex

OBJDIR=objs

OBJS=\
	${OBJDIR}/parsers/json_number.o \
	${OBJDIR}/parsers/json_object.o \
	${OBJDIR}/parsers/quoted_string.o \
	${OBJDIR}/serialisers/set.o \
	${OBJDIR}/serialisers/string.o \
	${OBJDIR}/serialisers/vector.o \
	${OBJDIR}/convert.o \
	${OBJDIR}/json.o \
	${OBJDIR}/list.o \
	${OBJDIR}/log.o \
	${OBJDIR}/serialise_json.o

clean:
	rm -f ${OBJS}

all:	bin/main

libjson.a:	${OBJS}
	ar rvs libjson.a ${OBJS}

bin/main:	${OBJS} src/main.cpp
	${CXX} ${CPPFLAGS} ${OBJS} ${LIBS} src/main.cpp -o $@

${OBJDIR}/%.o : src/%.cpp
	${CXX} ${CPPFLAGS} -Isrc $< -c -o $@

