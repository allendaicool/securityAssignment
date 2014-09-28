CC=g++
CFLAGS=-g -Wall

build: objget   objput  objlist objsetacl objgetacl objtestacl

objget :  objget.o  functionCall.o
	$(CC) $(CFLAGS) -o objget    objget.cpp functionCall.cpp

	

objput	: help.o functionCall.o
	$(CC) $(CFLAGS) -o objput     help.cpp functionCall.cpp

	

objlist : objlist.o functionCall.o
	$(CC) $(CFLAGS)  -o objlist    objlist.cpp functionCall.cpp

	
objsetacl : objsetacl.o functionCall.o
	$(CC) $(CFLAGS)  -o objsetacl    objsetacl.cpp functionCall.cpp



objgetacl : objgetacl.o functionCall.o
	$(CC) $(CFLAGS)  -o objgetacl   objgetacl.cpp functionCall.cpp



objtestacl : objtestacl.o functionCall.o
	$(CC) $(CFLAGS)  -o objtestacl  objtestacl.cpp functionCall.cpp

	
ARG=testfile.txt

exec:	build
	cat $(ARG) > user+group
test: 	build
	./objput -u u1 -g g1 doc < haha
	./objget -u u1 -g g1 doc
	./objlist -u u1
	./objgetacl -u u1 -g g1 doc
	./objsetacl -u u1 -g g1 doc < newacl
	./objtestacl -u u1 -g g3 -a r doc
	./objtestacl -u u1 -g g3 -a x doc
clean:
	rm *.o   objtestacl objgetacl objsetacl objlist objput objget *.core
	rm u*

	
