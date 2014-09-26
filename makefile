
All: objget   objput  objlist objsetacl objgetacl objtestacl

objget :  objget.o  functionCall.o
	g++ -Wall -o objget  objget.o functionCall.o
	g++ -Wall -c objget.cpp
	g++ -Wall -c functionCall.cpp




objput	: help.o functionCall.o
	g++ -Wall -o objput help.o functionCall.o
	g++ -Wall -c help.cpp 
	g++ -Wall -c functionCall.cpp 

objlist : objlist.o functionCall.o
	g++ -Wall -o objlist objlist.o functionCall.o
	g++ -Wall -c objlist.cpp 
	g++ -Wall -c functionCall.cpp  


objsetacl : objsetacl.o functionCall.o
	g++ -Wall -o objsetacl objsetacl.o functionCall.o
	g++ -Wall -c objsetacl.cpp 
	g++ -Wall -c functionCall.cpp 

objgetacl : objgetacl.o functionCall.o
	g++ -Wall -o objgetacl objgetacl.o functionCall.o
	g++ -Wall -c objgetacl.cpp 
	g++ -Wall -c functionCall.cpp 

objtestacl : objtestacl.o functionCall.o
	g++ -Wall -o objtestacl objtestacl.o functionCall.o
	g++ -Wall -c objtestacl.cpp 
	g++ -Wall -c functionCall.cpp 

ARG = -u u1 -g g3 -a x doc
exec:
	./objtestacl $(ARG)
test: 
	./objput -u u1 -g g1 doc < haha
	./objget -u u1 -g g1 doc
	./objlist -u u1
	./objgetacl -u u1 -g g1 doc
	./objsetacl -u u1 -g g1 doc < newacl
	./objtestacl -u u1 -g g3 -a r doc
	./objtestacl -u u1 -g g3 -a x doc
clean:
	rm *.o   objtestacl objgetacl objsetacl objlist objput objget

	