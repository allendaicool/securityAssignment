
All: objget   objput  objlist objsetcal

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


objsetcal : objsetacl.o functionCall.o
	g++ -Wall -o objsetacl objsetacl.o functionCall.o
	g++ -Wall -c objsetacl.cpp 
	g++ -Wall -c functionCall.cpp 

clean:
	rm *.o

	