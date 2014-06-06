#include "DOJ_compile.h"

void compile(char* subID){
	printf("compile: start to compile SubID #%s\n", subID);
	
	char src[255] = "./sub/";
	strcat(src, subID);
	strcat(src, "/submission.cpp");
	
	char bin[255] = "./sub/";
	strcat(bin, subID);
	strcat(bin, "/DOJ_SUB");
	strcat(bin, subID);
	strcat(bin, ".exe");
	
	char log[255] = "./sub/";
	strcat(log, subID);
	strcat(log, "/compile.txt");
	
	int fd = fileno(fopen(log, "w"));
	
	dup2(fd, 1);
	dup2(fd, 2);
	
	if(execlp("g++", "g++", src, "-o", bin, NULL) == -1){
		puts("Error calling g++ compiler");
		exit(1);
	}
}
