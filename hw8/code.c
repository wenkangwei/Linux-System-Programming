#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
// int main(int argc, char const *argv[])
// {
// 	system("sort code.c > sorted-code");
// 	return 0;
// }

// int main(void)
// {
// int i = 5, pid;
// printf("1:%d\n", i);
// pid = fork();
// i++; printf("2:%d\n", i);
// wait(NULL);
// if (pid == 0) {
// sleep(1);
// i--; printf("3:%d\n", i);
// sleep(1);
// i += 4; printf("4:%d\n", i);
// } else {
// i++; printf("5:%d\n", i);
// i = i+3;
// printf("6:%d\n", i);
// sleep(6);
// i = 0; printf("7:%d\n", i);
// }
// i += 2; printf("8:%d\n", i);
// }


// void SigHandler(int signum)
// {
// 	static char switch_on=0;
// 	//switch on/off when receiving user signal 1
// 	if(signum== SIGUSR1){
// 		switch_on= switch_on==0? 1:0;
// 	}
// 	if(signum== SIGALRM && switch_on==1)
// 	{
// 		// print text each 1s if switch is on
// 		printf("Go Tigers\n");
// 		alarm(1);	
// 	}

// 	if (signum== SIGUSR2)
// 	{
// 			printf("Beat sCar\n");
// 			exit(0);

// 	}
// }

// int main(int argc, char const *argv[])
// {
// 	char command[10];
// 	int pid=getpid();
// 	signal(SIGUSR1,SigHandler);
// 	signal(SIGUSR2,SigHandler);
// 	signal(SIGALRM,SigHandler);

// 	while(1)
// 	{
// 		scanf("%s",command);//receive commands
// 		if(strcmp(command,"poke")==0 )
// 		{//send control signal
// 			kill(pid,SIGUSR1);
// 			alarm(1);
// 		}
// 		if (strcmp(command,"quit")==0)
// 			kill(pid,SIGUSR2);

// 	}	
// 	return 0;
// }



void SignalHandler(int signum)
{
	static FILE *fpt;
	static unsigned char toggle_cnt=0;
	static unsigned char is_inTimeInterv=0;//flag to judge if 60s elapse
	static char is_fileOpened=0;
	if(is_fileOpened==0 )
	{
		if((fpt=fopen("joblog.txt","w"))==NULL)
			exit(0);
		is_fileOpened=1;
	}
	if (signum==SIGALRM)
	{
			if(((toggle_cnt+2)%2)==0) {
				fprintf(fpt, "Clemson\n");
			}
			else{
				fprintf(fpt, "ECE\n");
			}
		
		alarm(60);//print text each 60s
		is_inTimeInterv=1;
	}
	else if(signum== SIGINT)
	{
		//check if it is the first toggle in 60s
		if(is_inTimeInterv==1)
			{
				toggle_cnt++;
				is_inTimeInterv=0;
				printf("toggle count: %d \n", (int)(toggle_cnt));
									
			}
			if(toggle_cnt== 8){
				fprintf(fpt, "Graduated\n");
				fclose(fpt);
				exit(0);
			}

	}
	 else if(signum== SIGKILL){
	 	if(fpt!=NULL)
			fclose(fpt);
			exit(0);
			}
}

int main(int argc, char const *argv[])
{
	signal(SIGALRM,SignalHandler );
	signal(SIGINT,SignalHandler );
	signal(SIGKILL,SignalHandler);
	alarm(60);
	while(1) {	//wait for signal
			pause();
		}

	return 0;
}

