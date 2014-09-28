
All: objget   objput  objlist objsetacl objgetacl objtestacl

objget :  objget.o  functionCall.o
	g++ -Wall -o objget -g   objget.cpp functionCall.cpp

	

objput	: help.o functionCall.o
	g++ -Wall -o objput  -g   help.cpp functionCall.cpp

	

objlist : objlist.o functionCall.o
	g++ -Wall -o objlist -g   objlist.cpp functionCall.cpp

	


objsetacl : objsetacl.o functionCall.o
	g++ -Wall -o objsetacl -g   objsetacl.cpp functionCall.cpp



objgetacl : objgetacl.o functionCall.o
	g++ -Wall -o objgetacl -g   objgetacl.cpp functionCall.cpp



objtestacl : objtestacl.o functionCall.o
	g++ -Wall -o objtestacl -g   objtestacl.cpp functionCall.cpp

	
ARG=testfile.txt

exec:	All
	cat $(ARG) > user+group
test: 	exec
	./objput -u u1 -g g1 doc < haha
	./objget -u u1 -g g1 doc
	./objlist -u u1
	./objgetacl -u u1 -g g1 doc
	./objsetacl -u u1 -g g1 doc < newacl
	./objtestacl -u u1 -g g3 -a r doc
	./objtestacl -u u1 -g g3 -a x doc
clean:
	rm *.o   objtestacl objgetacl objsetacl objlist objput objget
	rm u1+*
	
