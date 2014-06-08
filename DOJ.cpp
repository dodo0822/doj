#include "DOJ.h"

using namespace DOJ;

int main(int argc, char** argv){
	int sock_fd, newsock_fd, portnum = 22022;
	socklen_t clilen;
	char buf[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd < 0){
		puts("[main] error opening socket");
		exit(1);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portnum);
	if(bind(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		puts("[main] error binding");
		exit(1);
	}
	listen(sock_fd, 5);
	clilen = sizeof(cli_addr);
	while((newsock_fd = accept(sock_fd, (struct sockaddr *) &cli_addr, &clilen))){
		bzero(buf, 256);
		n = read(newsock_fd, buf, 255);
		char a[255];
		char b[255];
		char c[255];
		sscanf(buf, "%s %s %s", a, b, c);
		printf("[main] recv cmd judge(%s, %s)\n", b, c);
		pid_t judge_pid = fork();
		if(judge_pid == 0){
			judger::judge(atoi(b), atoi(c));
		}	
	}
}
