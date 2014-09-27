/*****************************************************
 * FILE NAME: functionCall.cpp
 *
 * Created on: Sept 22 2014
 * Author: Yihong Dai
 * this function keeps all the fucntion call the other source fils required
 *****************************************************/
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


/* This function checks if the shell redirect command exist
 * Parameters:void
 * return: 0;
 */
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

/* This function adds string constant to the username
 * string constant appended can be ACL, meta which are used to 
 * create either fileACL or filemeta filename
 *
 * Parameters:
 *  temp: user name
 *  fileFlag: 1 or 0 indicate whether to append fileName
 *  ACL: 1 or 0 indicate whether to append ACL
 *  metaFlag: 1 or 0 indicate whether to append metaFlag
 *  return : 1
 *
 */
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

/* This function  checks if certain permission exist among the ACL
 * Parameters:
 *  c: permission to be check
 *  val: The ACL of a certain file
 *  return : 1 if such permission exist
 *	     -1 if such permission does not exist
 */
int checkPermission(char c, char *val)
{
	
	int loop;
	int Permission;
	int strlength;
	strlength = (int)strlen(val);
	Permission = -1 ;
	/* loop is used to check char c appear among the sting val
	 * if exists, then method immmediately gets returned
	 */
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
		return 1;
	}
	else
	{
		return -1;
	}
	return 1;
}

/* This function finds the ACL for a certain file
 *  filename: ACL file
 *  first: the username
 *  second: the group
 *  val: val written to be the permission list and returned back
 *  return : 0;
 */
int findPermission(string &filename, char *first, char * second, char **val)
{
	/* open the file and find the corresponding permission
	 * list for certain users and group
	 */
	 
	ifstream infile;
	infile.open(filename.c_str());
	
	if(infile.fail()){
		cout<<"file does not exist"<<endl;
		exit(EXIT_FAILURE);
	}
	
	
    	char *token;
	char *token2;
	char *insideToken1;
	char *insideToken2;
	char *array;
	char *delimiterInside;
	char * delimiter = (char *)" \t";
	string temp;
	int check;
	
	/* read the line by line to find the corresponding
	 * permission list for certain usr and group combinatin
	 */
	while(getline(infile,temp))
	{
		/* we assume that the format for each line is as follows
		 * u1.*  rwxpv
		 * we find the first topken and second token
		 * by using delimiter space or tab
		 */
		array = (char *)temp.c_str();
		token = strtok(array,delimiter);
		token2 =strtok(NULL,delimiter);
		
		printf("the arrays is %s \n", array);
		printf("the token is %s \n", token);
		printf("the toke2 is %s  \n" , token2);
		
		/* we pass the first token u1.* again to
		 * retrieve the user and group
		 */
		delimiterInside = (char *)".";
		insideToken1 =strtok(token,delimiterInside);
		printf("the insidetoke is %s \n",insideToken1);
		insideToken2 = strtok(NULL,delimiterInside);
		printf("the second toke is %s \n", insideToken2);
		/*  call the checkMatch to check if there is permission
		 *  list exist for usr and group combination
		 */
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


/* This function check if there is acl permission match
 * for certain usr and group
 *  first: the username
 *  second: the group
 *  std1: users in the ACL to be compared against
 *  std2: groups in the ACL to be compared against
 *  return : 1 if such combination is found;
 *	     0 if no such combination is found;
 */
int checkMatch ( char * first , char *second, char *std1, char *std2)
{
	if(strcmp(std1,first) == 0 || strcmp(std1,"*") == 0){
		if(strcmp(std2,"*")==0 || strcmp(std2, second) == 0)
			return 1;
		else
			return 0 ;
	}
	return  0;
}

/* This function checks if a character is among the rwx options
 *  a: character to be checked
 *  return : true if it is one of rwx
 *	     false if it is not
 */
bool isdefaultPermission(char a)
{
	if(a != 'r'&& a!='w' && a!='x')
		return false;
	return true;
}

/* This function checks if a certain gourp number alreadys exists in 
 * the meta file username groupname1 groupname2........
 *  stream: file keeps the usr info
 *  group: to be checked if a group exists
 *  return: true   if it exist
 *          false  if it does not exists
 */
bool checkGroupExist(FILE * stream, const char *group)
{
	
	/*  get the entire line to read
	 *  to find if group number exists
	 */
	size_t dum;
	int val;
	char *buffer;
	char *temp;
	char * delimiter = (char *)"  \t \n";
	buffer = NULL;
	val = (int)getline(&buffer, &dum, stream);
	
	if (val == -1)
		perror("error: something wrong happens\n");
	
	/* tokenized the string based on the tab space or new newline
	 */
	temp = strtok(buffer,delimiter);
	while(temp != NULL){
		if(strcmp(temp,group) == 0){
			if(buffer)
				free(buffer);
			return true;
		}
	 	temp = strtok(NULL,delimiter);
	}
	
	if(buffer){
		free(buffer);
	}	
	return false;
}


/* This function parse the commands passed in by using getopt and
 * set corresponding flag
 *  argc: the number of arguments
 *  command: the argument line
 *  uFlag: user name flag
 *  gFlag: gourp name flag
 *  aFlag: action flag
 *  lFlag: list flag 
 *  usr: usr to be assgined the usrname
 *  group: group to be assigned the groupname
 *  operation: option following the -a
 *  return 1;
 */
int parseCommand(int argc , const char ** command, int &uFlag,
		 int &gFlag,int &aFlag,
		 int &lFlag,string &usr , string & group, char &operation)
{
	/* c keeps the return value of getopt
	 * enter records if the we have entered the getopt loop
	 * if enter equals to one then loop has been exeucted
	 * if enter equals to -1 then loop has not been executed
	 */
	int c;
	int enter;
	enter = -1;
	
	/* set the corresponding flags
	 * if there is no option after -u -g or -a
	 * then we report errors and exit immediately
	 * if the option after -a is more than one character,
	 * then we report an error as well
	 */
	while ( (c = getopt(argc,(char * const *)command,"u:g:a:l")) != -1){
		enter = 1;
		switch(c)
		{
			case'a':
				aFlag = 1 ;
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
				usr.assign(optarg);
				break;
			case 'g':
				gFlag = 1 ;
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
				   optopt == 'u' || optopt == 'g' ||
				   optopt == 'l')
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
