#include "DOJ_execute.h"

namespace DOJ {
	void execute(char* proID, char* subID){
		printf("[execute] running Proid #%s, SubID #%s\n", proID, subID);
	
		char input_file[255] = "./pro/";
		strcat(input_file, proID);
		strcat(input_file, "/input.txt");
	
		char output_file[255] = "./sub/";
		strcat(output_file, subID);
		strcat(output_file, "/output.txt");
	
		char exe_file[255] = "./sub/";
		strcat(exe_file, subID);
		strcat(exe_file, "/DOJ_SUB");
		strcat(exe_file, subID);
		strcat(exe_file, ".exe");
	
		char exe_name[255] = "DOJ_SUB";
		strcat(exe_name, subID);
		strcat(exe_name, ".exe");
	
		int fd_input = fileno(fopen(input_file, "r"));
		int fd_output = fileno(fopen(output_file, "w"));
	
		printf("[execute] execute=%s %s\n", exe_file, exe_name);
		printf("[execute] input=%s\n[execute]output=%s\n", input_file, output_file);
	
		dup2(fd_input, 0);
		dup2(fd_output, 1);
	
		if(execlp(exe_file, exe_name, NULL) == -1){
			puts("[execute] error executing submission program");
			exit(1);
		}
	}
}