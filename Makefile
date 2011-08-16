#
# Makefile for comp project
#
# Created on: May 27, 2011
#     Author: norton
#

YACC    = bison
LEX     = flex
CXX     = g++
CFLAGS  = -g -Wall -O2 -std=c++0x -lboost_program_options
INCPATH = -I.
EXE     = Bones

OBJS = node.o            \
       visitor.o         \
       parser.o          \
       lexer.o           \
       basic_visitor.o   \
       symtable.o        \
       scope.o           \
       pool.o            \

HEAD = Makefile          \
       basic_visitor.hpp \

all: $(EXE)
$(EXE): $(OBJS) $(EXE).cpp $(HEAD)
	$(CXX) $(INCPATH) $(CFLAGS) $@.cpp $(OBJS) -o $@

parser.cpp: parser.y $(HEAD)
	$(YACC) $< -o $@ -d

lexer.cpp: lexer.lex parser.y $(HEAD)
	$(LEX) --nounput -I -o $@ $<

node.cpp: astgen.py nodes.in $(HEAD)
	./astgen.py

visitor.cpp: astgen.py nodes.in $(HEAD)
	./astgen.py

$(OBJS): %.o: %.cpp $(HEAD)
	$(CXX) -c $(INCPATH) $(CFLAGS) $<

clean:
	rm -f $(EXE) *.o parser.cpp parser.hpp lexer.cpp *.dot *.png
	rm -f TestCases/*.png TestCases/*.ast TestCases/*.sym
	rm -f node.cpp node.hpp visitor.cpp visitor.hpp
