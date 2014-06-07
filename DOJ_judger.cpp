#include "DOJ_judger.h"

namespace DOJ {
	namespace judger {
		
		bool TLE = false;
		pid_t pid;
		pid_t exec_pid;
		
		void catch_alarm(int signum){
			TLE = true;
			kill(exec_pid, SIGABRT);
		}
		
		void judge(int pro_id, int sub_id){
			TLE = false;
			int status;
			
			char pro_str[255];
			char sub_str[255];
			
			sprintf(pro_str, "%d", pro_id);
			sprintf(sub_str, "%d", sub_id);
			
			printf("[judger] judging ProID=%s, SubID=%s\n", pro_str, sub_str);
			
			char bin[255] = "./sub/";
			strcat(bin, sub_str);
			strcat(bin, "/DOJ_SUB");
			strcat(bin, sub_str);
			strcat(bin, ".exe");
			
			remove(bin);
			
			pid = fork();
			if(pid == 0){
				compile(sub_str);
				exit(0);
			}
			
			pid = wait(&status);
			
			puts("[judger] compile complete");
			
			if(access(bin, F_OK) == -1){
				// CE, binary file does not exist
				puts("[judger] Result: CE - no executable file");
				return;
			}
			
			exec_pid = fork();
			if(exec_pid == 0){
				execute(pro_str, sub_str);
				exit(0);
			}
			
			printf("[judger] executing - Waiting for process %d\n", exec_pid);
			
			void (*prev_handler)(int);
			prev_handler = signal(SIGALRM, catch_alarm);
			
			alarm(5);
			
			exec_pid = wait(&status);
			
			puts("[judger] execute complete");
			
			if(!TLE){
			
				char output_txt[255] = "./sub/";
				strcat(output_txt, sub_str);
				strcat(output_txt, "/output.txt");
				
				char answer_txt[255] = "./pro/";
				strcat(answer_txt, pro_str);
				strcat(answer_txt, "/output.txt");
				
				FILE* output_file = fopen(output_txt, "r");
				FILE* answer_file = fopen(answer_txt, "r");
				
				if(output_file == NULL){
					puts("[judger] Result: WA - no output");
					return;
				}
				
				bool ok = true;
				
				char output_line[65535];
				char answer_line[65535];
				while(fgets(output_line, 65535, output_file) != NULL){
					if(fgets(answer_line, 65535, answer_file) == NULL){
						ok = false;
						break;
					}
					
					char* answer = strtok(answer_line, "\r");
					answer = strtok(answer, "\r\n");
					char* output = strtok(output_line, "\r");
					output = strtok(output, "\r\n");
					
					if(strcmp(answer, output) != 0){
						ok = false;
						break;
					}
				}
				if(fgets(answer_line, 65535, answer_file) != NULL) ok = false;
				if(ok){
					puts("[judger] Result: AC");
				} else {
					puts("[judger] Result: WA");
				}
			}
		}
	}
}
