//
//  functionCall.cpp
//  
//
//  Created by yihong dai on 9/20/14.
//
//
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "functionCall.h"

using namespace std;



/*int checkMatch ( char *  , char *, char *, char *);
int findPermission(string & ,char *,char  *, char **);*/


int checkShellRedirect()
{
    
	if (isatty(fileno(stdin))){
		puts("stdin is connected to a terminal");
		return 1;
	}	
	else
    		puts("stdin is NOT connected to a terminal");
  	return 0;
}


int addPathName(string &temp, char * fileName, int FileFlag, int ACL,int metaFlag)
{
	if(FileFlag){
		temp.append("+");
		temp.append(fileName);
	}
	if(ACL){
		temp.append("+");
		temp.append("ACL");
	}
	if(metaFlag){
		temp.append("+");
		temp.append("meta");
	}
	return 1;
	
}

int checkPermission(char c, char *val)
{
	int loop;
	int Permission;
	int strlength;
	strlength = (int)strlen(val);
	Permission = -1 ;
	for(loop = 0; loop < strlength;loop++)
	{
		if(val[loop] == c)
		{
			Permission = 1;
			break;
		}
	}
	if(Permission == 1)
	{
		/*printf("we have permission");*/
		return 1;
	}
	else
	{
		/*perror("we dont have  permssion");*/
		return -1;
	}
	return 1;
}
int findPermission(string &filename, char *first, char * second, char **val)
{
	ifstream infile;
	infile.open(filename.c_str());
	
	if(infile.fail()){
		cout<<"file does not exist"<<endl;
		exit(EXIT_FAILURE);
	}
	
	// insert code here...
    	char *token;
	char *token2;
	char *insideToken1;
	char *insideToken2;
	char *array;
	char *delimiterInside;
	char * delimiter = (char *)" \t";
	//char *delimiterInside = (char *)".";
	string temp;
	int check;
	while(getline(infile,temp))
	{
		
		array = (char *)temp.c_str();
		token = strtok(array,delimiter);
		token2 =strtok(NULL,delimiter);
		
		printf("the arrays is %s \n", array);
		printf("the token is %s \n", token);
		printf("the toke2 is %s  \n" , token2);
		delimiterInside = (char *)".";
		insideToken1 =strtok(token,delimiterInside);
		printf("the insidetoke is %s \n",insideToken1);
		insideToken2 = strtok(NULL,delimiterInside);
		printf("the second toke is %s \n", insideToken2);
		check = checkMatch(first,second,insideToken1,insideToken2);
		if(check)
		{
			infile.close();
			*val = (char *)malloc(sizeof(char)*(strlen(token2)+1));
			strcpy(*val,token2);
			return 1;
		}
		
	}
	infile.close();
	return 0;
}

int checkMatch ( char * first , char *second, char *std1, char *std2)
{
	if(strcmp(std1,first) ==0 || strcmp(std1,"*") == 0)
	{
		if(strcmp(std2,"*")==0 || strcmp(std2, second) == 0 )
			return 1;
		else
			return 0 ;
	}
	return  0;
	
}
bool isdefaultPermission(char a)
{
	if(a!='r'&&a!='w'&&a!='x')
		return false;
	return true;
	
}


bool checkGroupExist(FILE * stream, const char *group)
{
	cout<<"get inside the check function"   <<endl;
	size_t dum;
	int val;
	char *buffer;
	char *temp;
	char * delimiter = (char *)"  \t \n";
	buffer = NULL;
	cout<<"get inside second time"   <<endl;
	val = (int)getline(&buffer, &dum, stream);
	
	cout<<"get inside third time"   <<endl;
	if (val == -1)
		perror("error: something wrong happens\n");
	temp = strtok(buffer,delimiter);
	cout<<"debug is "   <<endl;
	cout<< temp<<endl;
	while(temp!= NULL){
		if(strcmp(temp,group)==0){
			if(buffer)
				free(buffer);
			return true;
		}
	 	temp = strtok(NULL,delimiter);
		if(temp != NULL){		
			cout<<"debug XXXXXis "   <<endl;
			cout<< temp<<endl;
		}	
	}
	cout<<"outside while loop"<<endl;
	if(buffer == NULL)
		cout<<"buffer points to null"<<endl;
	if(buffer){
		cout<<"buffer has been freed"<<endl;
		free(buffer);
	}	
	return false;
}

int parseCommand(int argc , const char ** command, int &uFlag,
		 int &gFlag,int &aFlag,
		 int &lFlag,string &usr , string & group, char &operation)
{
	int c;
	int enter;
	enter = -1;
	while ( (c = getopt(argc,(char * const *)command,"u:g:a:l")) != -1){
		printf("%c is answer  \n", c);
		enter = 1;
		switch(c)
		{
			case'a':
				aFlag = 1 ;
				/*(*operation)  = (char *)malloc(strlen(optarg)+1);
				 strcpy((*operation), optarg);*/
				if(strlen(optarg)>1){
					perror(
				"permission check only need one character");
					exit(EXIT_FAILURE);

				}
				operation = optarg[0];
				if(!isdefaultPermission(operation)){
					perror(
					       "permission invalid");
					exit(EXIT_FAILURE);
				}

				break;
			case 'u':
				uFlag = 1;
				/*(*usr)  = (char *)malloc(strlen(optarg)+1);
				 strcpy(*usr, optarg);*/
				usr.assign(optarg);
				//printf("user is %s \n" , *usr );
				break;
			case 'g':
				gFlag = 1 ;
				/*(*group)  = (char *)malloc(strlen(optarg)+1);
				 strcpy((*group), optarg);
				 printf("group is %s \n" , *group );*/
				if(strcmp(optarg,command[argc-1])==0){
					perror("no group found");
					exit(EXIT_FAILURE);
				}
				group.assign(optarg);
				
				break;
			case 'l':
				lFlag = 1;
				break;
				
			case '?':
				if(optopt == 'a' ||
				   optopt == 'u' || optopt == 'u')
					fprintf (stderr,
						 "Option -%c requires an argument.\n"
						 , optopt);
				else if (isprint (optopt))
					fprintf (stderr,
						 "Unknown option `-%c'.\n", optopt);
				
				else
					fprintf (stderr,
						 "werid character `\\x%x'.\n",
						 optopt);
				return 1;
				
			default:
				abort ();
		}
	}
	if(enter == -1){
		perror("the wrong input format");
		exit(EXIT_FAILURE);
	}
	return 1;
}
