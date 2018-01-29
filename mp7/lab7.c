
/* lab7.c
 * Wenkang Wei
 * wenkanw
 * ECE 2220, Fall 2017
 *
 * Purpose:
 *	This program is to generate four sub processes: 3 IT services and a monitor process.
 *	Then the parent process uses wait function to wait and collect all exit status of three IT services and 
 *  print a message about status of each service.
 *  After the program is waiting, the mointor process collects input commands from the parent's terminal
 *  and send corresponding signals to the IT services. The signals are SNMP request, reconfiguration request
 *  and alarm signals..
 *
 * Assumptions:
 *		The program should take 4 terminal numbers as input and the first number is the terminal
 *		of monitor and the other three numbers are IT service numbers
 *		Commands of Ops center should be sn , rn, kn to request SNMP report, reconfigure service and kill service
 *		respectively.
 *Command line argument
 *			Usage: ./lab7 1 2 3 4 
 *			where 1 is the tty terminal number of monitor and 2,3,4 are terminal numbers of three IT services
 *			Ops center Commands:
 *			sn:  Send SNMP request
 *			rn:  reconfiguration request
 *			kn:	 kill service n
 *			where n is the IT service number and n should be 1 to 3
 *
 * 
 * Bugs:
 *      unknown
 *
 *
 */


#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>
#define uchar unsigned char
#define NUMTTYS 4
#define SIGSNMP 16
#define SIGRECONFIG 17
#define EXCODE_SUCCESSIVE 1
#define EXCODE_COMPROMISED 2
#define EXCODE_CRASH 3

//type definition
typedef struct timeval TimeStruct;
//  global value 
struct timeval OldTime;
// function procotypes
int SubtractTimevals(TimeStruct *result, TimeStruct *x, TimeStruct *y);
int calc_threat( int threat);
char get_ServNum(int *Services,int ser_amt  ,int pid );
void get_ServStatus(int status_code, uchar *exit_code, uchar *signal );
void obtain_ttys( char *argv[] , char (*strDev)[50], int  *Terminal, int *term_cnt ); 
void Task_Monitor(int serv_pid[NUMTTYS]);
void Task_ITServ1(char *dev);
void Task_ITServ2(char *dev);
void Task_ITServ3(char *dev);

//gobal variables to store each IT service info
int Terminal[NUMTTYS], Service_ID[NUMTTYS];
int Parent_PID;
char strDev[NUMTTYS][50];


int main(int argc, char *argv[])
{ 
    int  service_pid;
    int term_cnt = 0, process_cnt=0, Server_status=0;
	uchar exit_code=0, return_signal=0;
 	uchar service_num=-1;   	
 	uchar ret_status[NUMTTYS-1];

    if (argc != NUMTTYS+1) {
        printf("Usage: ./lab7 1 2 3 4, where the numbers are the terminal pts values\n");
        exit(1);
    }

    // determine which ttys are open and available to this user
  
    obtain_ttys( argv ,strDev, Terminal, &term_cnt ); 
	//obtain parent pid
	Parent_PID=getpid();
   //create IT services 1
   process_cnt=1;
   Service_ID[process_cnt]=fork();//obtain IT Serv 1 pid
   if(Service_ID[process_cnt] !=0 )
	{
		process_cnt++;
		Service_ID[process_cnt]=fork();//create IT service 2
	   if(Service_ID[process_cnt] !=0 )
		{
		process_cnt++;
		Service_ID[process_cnt]=fork();//create IT service 3
		   if(Service_ID[process_cnt] !=0 )
			{
				process_cnt++;
		  		Service_ID[0]=fork();//create IT service monitor in parent process
			   if(Service_ID[0] !=0 )
				{
				//parent task
				for(;process_cnt>1;process_cnt-- )
				{
		
					service_pid=wait(&Server_status );//obtain service pid
					service_num=get_ServNum(Service_ID,NUMTTYS,service_pid );//obtain service number
					get_ServStatus(Server_status,&exit_code,&return_signal );//obtain returned exit codeand signal.
					if(return_signal!=SIGKILL)
						ret_status[service_num-1]=exit_code;
					else ret_status[service_num-1]=SIGKILL;
				}
				// print message of each IT service status after collecting status of all IT services
					for(service_num=1;service_num<NUMTTYS;service_num++ )
					{
						exit_code=ret_status[service_num-1];
						switch(exit_code )
						{
							case EXIT_SUCCESS:
							printf("Job well done IT specialist %d. Prepare for new attack\n", service_num);
									break;
							case EXCODE_CRASH:
							printf("Call HR, we need a cybersecurity expert for service %d\n",service_num);
									break;
							case EXCODE_COMPROMISED:
							printf("IT service %d compromised, we are going to out of business\n", service_num);
									break;
							 case SIGKILL:
							 printf("Terminated IT serivce %d\n", service_num);// when service was killed by user
									break;
						}
					
					
					}
					//Close monitor service after finishing missions
					kill(Service_ID[0],SIGKILL);	
				}
				else{
				Service_ID[0]=getpid();// get monitor pid for monitor itself
				sprintf(strDev[0],"/dev/pts/%d",Terminal[0] );
				Task_Monitor(Service_ID );//pass terminal dev to monitor
				}
			}
			else{
				sprintf(strDev[process_cnt],"/dev/pts/%d",Terminal[process_cnt] );
				Task_ITServ3(strDev[process_cnt]);//pass terminal dev to service 3
			}
		}
		else{	
			sprintf(strDev[process_cnt],"/dev/pts/%d",Terminal[process_cnt] );
			Task_ITServ2(strDev[process_cnt]);//pass terminal dev to service 2
		}
	}
	else{
		sprintf(strDev[process_cnt],"/dev/pts/%d",Terminal[process_cnt] );
		Task_ITServ1(strDev[process_cnt]);//pass terminal dev to servie 1		
    }

    exit(EXIT_SUCCESS);
}

/**
*	brief: get_ServStatus
*			It is to parse the status code return by the Services to
*			get the exit code and signal.
*	@para status_code:
*			status code returned by wait() function
*	@para *exit_code:
*			return the exit code parsed from status code returned by services
*	@para signal:
*			return the signal in the services' status code
*
*/

void get_ServStatus(int status_code, uchar *exit_code, uchar *signal )
{
	*exit_code=(uchar)(status_code>>8);
	*signal=(uchar)(status_code&0x7F);
}

/**
* brief: get_SerNum
*			It is to return the IT service number (1~3) based on
*			the pid given.If not found, return -1;
* @para *Service:
*			array storing services' pid used to look for service number
* @para serv_amt:
*			the number of IT services
* @para pid:
*		pid of service used to find its corresponding service number
*/

char get_ServNum(int *Services,int ser_amt  ,int pid )
{
	int service_index;
	for(service_index=0; service_index<ser_amt;service_index++ )
		if(pid== Services[service_index]) return (char)(service_index);
	//	return -1 if not found
	return -1;
}


/*
* brief obtain_ttys:
*		It is to obtain the tty terminal numbers and store their dev names in a 2D array
* @para *argv[]
*		terminal numbers from the terminal input
* @para (*strDev)[]
*		2D array used to store names of all terminal devices
* @para *Terminal
*		array used to store each terminal number
* @para *term_cnt
*		return terminal count
*
*/

void obtain_ttys( char *argv[] , char (*strDev)[50], int  *Terminal, int *term_cnt ) 
{
    int  ttyindex, term_count=*term_cnt ;
	FILE *fpt;
    for (term_count = 0;term_count < NUMTTYS; term_count++)
    { 
        ttyindex = -1;
        ttyindex = atoi(argv[term_count+1]);
        if (ttyindex < 1) {
            printf("invalid terminal number %s\n", argv[term_count+1]);
            exit(1);
        }
        //obtain terminal device's name
		sprintf(strDev[term_count], "/dev/pts/%d", ttyindex);
	if ((fpt = fopen(strDev[term_count],"w")) != NULL) {//test tty terminals
	    Terminal[term_count] = ttyindex;
		printf("Terminal[%d] = %d\n", term_count, ttyindex);
        fprintf(fpt, "IT Service terminal %d, Service num: %d\n",
                ttyindex, term_count);
	    fclose(fpt);
	} else {
            printf("failed to open terminal %s\n", strDev[term_count]);
            exit(1);
        }
  }
    printf("This program can write to %d terminals\n", term_count);
	*term_cnt=term_count;

}
/**
* brief: calc_threat 
*		it is to calculate the new threat level to reconfigure services
* @para threat
*		former threat level
* @return 
*		the new threat level
*/
int calc_threat( int threat)
{
    if(drand48()<0.5){
	threat++;
    }
    else if(threat>1 && drand48()<0.6){
	threat--;
    }

return threat;
}



/*
* @brief SubtractTimevals
*			This function is to return the difference between the time of last SNMP request
*			and the time of next SNMP request
*
* @para *result
*			return the difference of time
*
* @para *x
*			time of new SNMP request
*
* @para *y
*			time of last SNMP request
*/
int SubtractTimevals(TimeStruct *result, TimeStruct *x, TimeStruct *y)
{
    /* Perform the carry for the later subtraction by updating y. */
    if (x->tv_usec < y->tv_usec) {
        int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
        y->tv_usec -= 1000000 * nsec;
        y->tv_sec += nsec;
    }
    if (x->tv_usec - y->tv_usec > 1000000) {
        int nsec = (x->tv_usec - y->tv_usec) / 1000000;
        y->tv_usec += 1000000 * nsec;
        y->tv_sec -= nsec;
    }

    /* Compute the time remaining to wait. tv_usec is certainly positive. */
    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_usec = x->tv_usec - y->tv_usec;

    /* Return 1 if result is negative. */
    return x->tv_sec < y->tv_sec;
}


/*
* @brief IT1_SigHandler
*		 Singal handler for IT service 1. This handler is to 
*		 deal with three signals: reconfiguration, SNMP, alarm.
* @signum:
*		signal number to identify which signal the handler received	
*/
void IT1_SigHandler(int signum)
{
	FILE *fpt;
	static uchar is_reconfig=0;
	static uchar threat=1;
	static uchar threat_color=0;//red: 2, yellow: 1 green:0
	static struct timeval NewTime, diff_time;
	static char is_firstSNMP=1;//flag to identify whether it is the first SNMP request

	//deal with reconfiguration signal
	fpt=fopen(strDev[1],"w" );
	if(signum==SIGRECONFIG){
		if(is_reconfig==0 && threat_color==2 ){
		is_reconfig=1;
		//reconfigure parameters for IT service1
		fprintf(fpt,"Reconfiguring system to thwart attack- this may take a few seconds\n" );
		}
		else if(is_reconfig==1) {
		fprintf(fpt,"Cannot reconfigure more than once.You are fired!\n" );
		fclose(fpt);
		exit(EXCODE_CRASH);
		}
		else if(threat_color<2){
		fprintf(fpt,"Threat level is not critical.You are fired!\n" );
		fclose(fpt);
		exit(EXCODE_CRASH);
		}
	}

	// deal with SNMP request  signal
	if(signum==SIGSNMP){
		if( diff_time.tv_sec<5 && !is_firstSNMP) {
		fprintf(fpt,"Load too high.Threat is increased\n " );
		threat++;
		//update threat color
		}
		else{
		//print threat color
		threat_color= (threat>=10)? 2: ((threat>=5)? 1:0);
		if(threat_color==0)			fprintf(fpt,"Theat color is Green\n");
		else if(threat_color==1)		fprintf(fpt,"Theat color is Yellow\n");
		else if(threat_color==2)		fprintf(fpt,"Theat color is Red\n");
		gettimeofday(&OldTime,NULL);//update time of the last SNMP request
		is_firstSNMP=0;
		}
	}

	//deal with alarm signal
	if(signum==SIGALRM){
		//tracking the time since the last SNMP request
			if (!is_firstSNMP)
			{
			gettimeofday(&NewTime,NULL);
			SubtractTimevals(&diff_time, &NewTime, &OldTime);
			}
		
		//update threat level
		if(is_reconfig==1){
			threat--;
			if(threat<10){
			fprintf(fpt,"Attack averted. Mission complete\n");
			fclose(fpt);
			exit(EXIT_SUCCESS);
			}
		}
		else{
		//calc new threat level.
		     threat=calc_threat(threat);
		}
		//alarm time of avaliable SNMP request
		if(diff_time.tv_sec<5 && !is_firstSNMP ){
		fprintf(fpt,"Next report avaliabe in %d seconds.\n",4-(int)(diff_time.tv_sec) );
		
		}
		//check if data stolen
		if(threat>15){
		fprintf(fpt,"Intruder!Data stolen... \n");
		fclose(fpt);
		exit(EXCODE_COMPROMISED);
		}
		// set next alarm
		alarm(1);
	}
	fclose(fpt);
}


/*
* @brief IT1_SigHandler
*		 Singal handler for IT service 2. This handler is to 
*		 deal with three signals: reconfiguration, SNMP, alarm.
* @signum:
*		signal number to identify which signal the handler received	
*/
void IT2_SigHandler(int signum)
{
	FILE *fpt;
	static uchar is_reconfig=0;
	static uchar threat=1;
	static uchar threat_color=0;//red: 2, yellow: 1 green:0
	static struct timeval NewTime, diff_time;
	static char is_firstSNMP=1;//flag to identify whether it is the first SNMP request

	//deal with reconfiguration signal
	fpt=fopen(strDev[2],"w" );
	if(signum==SIGRECONFIG){
		if(is_reconfig==0 && threat_color==2 ){
		is_reconfig=1;
		//reconfigure parameters for IT service1
		fprintf(fpt,"Reconfiguring system to thwart attack- this may take a few seconds\n" );
		}
		else if(is_reconfig==1) {
		fprintf(fpt,"Cannot reconfigure more than once.You are fired!\n" );
		fclose(fpt);
		exit(EXCODE_CRASH);
		}
		else if(threat_color<2){
		fprintf(fpt,"Threat level is not critical.You are fired!\n" );
		fclose(fpt);
		exit(EXCODE_CRASH);
		}
	}

	// deal with SNMP request  signal
	if(signum==SIGSNMP){
		if( diff_time.tv_sec<5 && !is_firstSNMP) {
		fprintf(fpt,"Load too high.Threat is increased\n " );
		threat++;
		//update threat color
		}
		else{
		//print threat color
		threat_color= (threat>=10)? 2: ((threat>=5)? 1:0);
		if(threat_color==0)			fprintf(fpt,"Theat color is Green\n");
		else if(threat_color==1)		fprintf(fpt,"Theat color is Yellow\n");
		else if(threat_color==2)		fprintf(fpt,"Theat color is Red\n");
		gettimeofday(&OldTime,NULL);//update time of the last SNMP request
		is_firstSNMP=0;
		}
	}

	//deal with alarm signal
	if(signum==SIGALRM){
		//tracking the time since the last SNMP request
			if (!is_firstSNMP)
			{
			gettimeofday(&NewTime,NULL);
			SubtractTimevals(&diff_time, &NewTime, &OldTime);
			}
		
		//update threat level
		if(is_reconfig==1){
			threat--;
			if(threat<10){
			fprintf(fpt,"Attack averted. Mission complete\n");
			fclose(fpt);
			exit(EXIT_SUCCESS);
			}
		}
		else{
		//calc new threat level.
		     threat=calc_threat(threat);
		}
		//alarm time of avaliable SNMP request
		if(diff_time.tv_sec<5 && !is_firstSNMP ){
		fprintf(fpt,"Next report avaliabe in %d seconds.\n",4-(int)(diff_time.tv_sec) );
		
		}
		//check if data stolen
		if(threat>15){
		fprintf(fpt,"Intruder!Data stolen... \n");
		fclose(fpt);
		exit(EXCODE_COMPROMISED);
		}
		//set next alarm
		alarm(1);
	}
	fclose(fpt);
}




/*
* @brief IT1_SigHandler
*		 Singal handler for IT service 3. This handler is to 
*		 deal with three signals: reconfiguration, SNMP, alarm.
* @signum:
*		signal number to identify which signal the handler received	
*/
void IT3_SigHandler(int signum)
{

	FILE *fpt;
	static uchar is_reconfig=0;
	static uchar threat=1;
	static uchar threat_color=0;//red: 2, yellow: 1 green:0
	static struct timeval NewTime, diff_time;
	static char is_firstSNMP=1;//flag to identify whether it is the first SNMP request

	//deal with reconfiguration signal
	fpt=fopen(strDev[3],"w" );
	if(signum==SIGRECONFIG){
		if(is_reconfig==0 && threat_color==2 ){
		is_reconfig=1;
		//reconfigure parameters for IT service1
		fprintf(fpt,"Reconfiguring system to thwart attack- this may take a few seconds\n" );
		}
		else if(is_reconfig==1) {
		fprintf(fpt,"Cannot reconfigure more than once.You are fired!\n" );
		fclose(fpt);
		exit(EXCODE_CRASH);
		}
		else if(threat_color<2){
		fprintf(fpt,"Threat level is not critical.You are fired!\n" );
		fclose(fpt);
		exit(EXCODE_CRASH);
		}
	}

	// deal with SNMP request  signal
	if(signum==SIGSNMP){
		if( diff_time.tv_sec<5 && !is_firstSNMP) {
		fprintf(fpt,"Load too high.Threat is increased\n " );
		threat++;
		//update threat color
		}
		else{
		//print threat color
		threat_color= (threat>=10)? 2: ((threat>=5)? 1:0);
		if(threat_color==0)			fprintf(fpt,"Theat color is Green\n");
		else if(threat_color==1)		fprintf(fpt,"Theat color is Yellow\n");
		else if(threat_color==2)		fprintf(fpt,"Theat color is Red\n");
		gettimeofday(&OldTime,NULL);//update time of the last SNMP request
		is_firstSNMP=0;
		}
	}

	//deal with alarm signal
	if(signum==SIGALRM){
		//tracking the time since the last SNMP request
			if (!is_firstSNMP)
			{
			gettimeofday(&NewTime,NULL);
			SubtractTimevals(&diff_time, &NewTime, &OldTime);
			}
		
		//update threat level
		if(is_reconfig==1){
			threat--;
			if(threat<10){
			fprintf(fpt,"Attack averted. Mission complete\n");
			fclose(fpt);
			exit(EXIT_SUCCESS);
			}
		}
		else{
		//calc new threat level.
		     threat=calc_threat(threat);
		}
		//alarm time of avaliable SNMP request
		if(diff_time.tv_sec<5 && !is_firstSNMP ){
		fprintf(fpt,"Next report avaliabe in %d seconds.\n",4-(int)(diff_time.tv_sec) );
		
		}
		//check if data stolen
		if(threat>15){
		fprintf(fpt,"Intruder!Data stolen... \n");
		fclose(fpt);
		exit(EXCODE_COMPROMISED);
		}
		//set next alarm
		alarm(1);
	}
	fclose(fpt);
}



/*
* @brief Monitor_SignHandler
*			It is to handler the signal received by the monitor
*			process. When the monitor process received ctr+c or kill
*			signal, it will kill all service process and parent process
*			to force the program to stop.
*/
void Monitor_SigHandler(int signum)
{
	int i;
	//kill all children 
	for(i=1;i<NUMTTYS;i++)
	 	kill(Service_ID[i],SIGKILL);
	kill(Parent_PID,SIGKILL);
	exit(0);
}

/*
* @brief Task_ITServ1:
*		It is the task function of IT service 1.
*		All work done by IT service 1 should be put here.
*		It waits for signals using pause() function and keep 
*		working until the service satifies the requirements of exiting
* @para *dev		
*		It passes the terminal string name to the function
*/

void Task_ITServ1( char *dev)
{
	FILE *fpt;
	int seed =time(NULL);
	//set pesudo random seed
	srand48(seed);
	//set alarm
	alarm(1);
	if((fpt=fopen(dev,"w"))!=NULL){
	fprintf(fpt,"Here is IT Service 1\n");
	fclose(fpt);
	}
	//install signal handler
	signal(SIGRECONFIG,IT1_SigHandler);
	signal(SIGSNMP,IT1_SigHandler);
	signal(SIGALRM,IT1_SigHandler);
	//waiting for signal
	while(1) pause();


}


/*
* @brief Task_ITServ2:
*		It is the task function of IT service 2.
*		All work done by IT service 2 should be put here.
*		It waits for signals using pause() function and keep 
*		working until the service satifies the requirements of exiting
* @para *dev		
*		It passes the terminal string name to the function
*/
void Task_ITServ2(char *dev  )
{
	FILE *fpt;
	int seed =time(NULL);
	//set pesudo random seed
	srand48(seed);
	//set alarm
	alarm(1);
	
	if((fpt=fopen(dev,"w"))!=NULL){
	fprintf(fpt,"Here is IT Service 2\n");
	fclose(fpt);
	}
	//install signal handler
	signal(SIGRECONFIG,IT2_SigHandler);
	signal(SIGSNMP,IT2_SigHandler);
	signal(SIGALRM,IT2_SigHandler);
	//waiting for signal
	while(1) pause();

}

/*
* @brief Task_ITServ3:
*		It is the task function of IT service 3.
*		All work done by IT service 3 should be put here.
*		It waits for signals using pause() function and keep 
*		working until the service satifies the requirements of exiting
* @para *dev		
*		It passes the terminal string name to the function
*/
void Task_ITServ3(char *dev )
{

	FILE *fpt;
	int seed =time(NULL);
	alarm(1);
	srand48(seed);
	if((fpt=fopen(dev,"w"))!=NULL){
	fprintf(fpt,"Here is IT Service 3\n");
	fclose(fpt);
	}
	
	//install signal handler
	signal(SIGRECONFIG,IT3_SigHandler);
	signal(SIGSNMP,IT3_SigHandler);
	signal(SIGALRM,IT3_SigHandler);
	//waiting for signal
	while(1) pause();
}


/*
* @brief Task_Monitor:
*		It is the task function of monitor.
*		All work done by monitor should be put here.
*		It collects the input of parent's terminal
*		and send signals to each IT service based on commands
* @para serv_pid[]
*		it passes the info of process IDs of all IT services to monitor
*		to control each IT service		
*/
void Task_Monitor( int serv_pid[NUMTTYS]  )
{
	char command[10]; 
	uchar serv_num;
	//kill all children if crtl+c signal or kill signal is sent
	signal(SIGINT,Monitor_SigHandler);
	signal(SIGKILL,Monitor_SigHandler);
	//print text
	printf("Here is monitor\n");
	while(1)
	{
		scanf("%s",command);	
		printf("%s\n", command );
			//check valid commands
			serv_num=(int)atoi((const char *) &command[1] );
			if(strlen(command)!=2 ){
			printf("\nInvalid command. command length should be 2\n\n");
			}
			else if(command[0]!='s'&& command[0]!='r' && command[0]!='k'  ){
			printf("\nInvalid command. command should be one of following:\n" );
			printf("sn rn kn\n\n");
			}
			else if(serv_num>NUMTTYS-1 || serv_num<1 ){
			printf("\nThe IT Service num should be between %d and %d. You input %c\n\n",1,NUMTTYS-1,command[1] );
			}
			else{
			//send signal here
				switch(command[0])
				{
					case 's':
						kill(serv_pid[serv_num ],SIGSNMP );
						break;
					case 'r':
						kill(serv_pid[serv_num ],SIGRECONFIG );
						break;
					case 'k':
						kill(serv_pid[serv_num ],SIGKILL );
						printf("\nTerminate IT Service %d\n\n",serv_num);
						break;
					default : break;
				}
			}
	}
	exit(0);
}



