/* lab1.c
 * name: Wenkang Wei
 * username: wenkanw
 * ECE 2220, Section 1, Fall 2017
 * 
 * MP1
 *
 * Purpose:  
 *          machine problem1 is to detect the highest threat level in the packets
 *          The program will check the threat level from the packets until invalid
 *          data is input or other negative values are input
 * Assumptions:
 *          The inputs for minimum threat level must be value great than or equal to 
 *          the MINTHRESH(3) or -1 to exit. Otherwise, This process will repeat till v
 *          alid value input.
 *          false alarm count input must be a value great than 0.
 *          When inputing threat level data, the input must be value greater than -1
 *          Other kind of input are invalid and program will exit immediately if input
 *          is invalid
 *          
 * Bugs:  
 *      unknown
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//notice there is no semi-colon at the end of a #define
#define MAXLINE 100
#define MAXSAMPLES 500
#define MINTHRESH 3


/* function declarations*/
int get_SampleSet(char *buffer,int buffer_size,int *breach_level,int *breach_count, int *sample_set);
void selection_Sort(int *arr, int samples_count);
void get_ThreatLevel(int *samples,
                    int samples_count, 
                    int Min_ThreatLevel, 
                    int *threat, 
                    int *times, 
                    int false_alarm_cnt);


int main()
{
    char line[MAXLINE];
    int min_threat_level = -12345;
    int false_alarm_count = -137153163;
    int breach_level = -54321;              // if a breach, this is the threat level
    int breach_count = -99999;              // if a breach, how many times level found
    int SampleSet[MAXSAMPLES];              //array storing samples
    int samples_count=0;                    //amount of samples in a set

    // fgets takes input from stdin (standard input) and places
    // up to MAXLINE bytes into the array "line".  The size of 
    // the array must be equal to MAXLINE.
    //
    // sscanf looks at the array "line" to find the first integer (%d)
    // and puts it at the address of "min_threat_level"
    printf("What is the minimum threat level (or -1 to exit)? ");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &min_threat_level);


    while(min_threat_level < MINTHRESH)
    {
         if(min_threat_level==-1)
        {
            printf("Goodbye.\n");
            return 0;
        }
        // figure out if you exit the program and ask for a valid value
        printf("\nThe input is invalid, you entered: %d\n", min_threat_level);
        printf("What is the minimum threat level (or -1 to exit)? ");
        fgets(line, MAXLINE, stdin);
        sscanf(line, "%d", &min_threat_level);
    }

    printf("\nThe minimum threat level(>= 3) is %d\n", min_threat_level );


    // Next read the the false alarm count.
    printf("How many times must a threat level occur so not a false alarm? ");
    fgets(line, MAXLINE, stdin);
    sscanf(line, "%d", &false_alarm_count);
    //if a invalid false alarm count is entered
    while(false_alarm_count<=0)
    {
        // if it is -1, exit program
        if (false_alarm_count==-1)
        {
            printf("Goodbye.\n");
            return 0;   
        }
        printf("\nThe input is invalid, you entered: %d\n", false_alarm_count);
        printf("How many times must a threat level occur so not a false alarm? ");
        fgets(line, MAXLINE, stdin);
        sscanf(line, "%d", &false_alarm_count);
    }
    // if a valid false alarm count is entered then print this
    printf("\nA false alarm if the count is < %d\n", false_alarm_count);
 
    //start receiving sample sets
        do
        {
            //clear breach data for the next sample set
            breach_level=0;
            breach_count=0;
            // receive breach level samples until it is <0
            if( !get_SampleSet(line,MAXLINE,&breach_level,&breach_count,SampleSet)) break;
            // get sample amount in a set
            samples_count=breach_count; 

            //if the last input is -1, evaluate samples. Otherwise, break the loop
            if (breach_level==-1)
            {
                //sort the threat level set in increasing order
                selection_Sort(SampleSet,samples_count);
                //get the threat level and breach count after sorting
                get_ThreatLevel(SampleSet,
                                samples_count,
                                min_threat_level,
                                &breach_level,
                                &breach_count,
                                false_alarm_count);

                //judge whether a breach appears
                if(breach_count>=false_alarm_count&&breach_level>=min_threat_level)
                    {
                        printf("Threat detected with level %d and appears %d times\n", 
                                breach_level, breach_count);
                    }       

                else
                    {
                        printf("No threat detected\n");
                    }
                    
            }
                        
        }
        while(breach_level>=-1);
    // If there are no more sample sets print this
    printf("Goodbye\n");
    exit(0);
}




/*
*   @brief get_SampleSet:
*           This function is to receive the sample from a set. When the 
*           input data is valid, it continues to get input data until
*           the input is -1 or invalid data. It can update the breach level
*           and count by accessing their address
*   @para  *buffer:
*           used to store the data from stdin
*   @para  buffer_size:
*           the size of the buffer storing data from stdin
*   @para  *breach_level:
*           storing the new breach level input from the data
*   @para  *breach_count:
*           storing the amount of sample in a set
*   @para  *sample_set:
*           input the header address of the array storing a sample set
*   @return :
*           0:receive invalid input 
*           1:receive samples successfully
*/

int get_SampleSet(char *buffer,int buffer_size,int *breach_level,int *breach_count, int *sample_set)
{
    int returncode=0;
    while(*breach_level>=0)
        {
            fgets(buffer, buffer_size, stdin);
            returncode=sscanf(buffer, "%d", breach_level);
            // if input is invalid, break and return 0
            if (returncode!=1)
            {
                //when data is repeated
                if (returncode==-1) 
                    printf("\n The input data is repeated, this is invalid.\n");
                //when data is invalid characters
                if (returncode==0) 
                    printf("\n The input data is %s,this is invalid.\n",buffer);
                    
                    return 0;
            }
           
            // if count is over max samples, don't store threat level and break
            if(*breach_count>=MAXSAMPLES)
            {
                *breach_level=-1;
                printf("\n get maximum samples.\n");
                break;
            }

            if (*breach_level<0) break;
            sample_set[(*breach_count)++]=*breach_level;
            //stop inputing after max samples are received
        }

    return 1;
}


/*
*   @brief selection_Sort:
*           This function is to sort the threat level in 
*           the same set and restore samples in increasing 
*           order as index inceases
*   @para  *arr:
*           input the address of the array
*   @para  samples_count:
*           input amount of samples in the set
*/
void selection_Sort(int *arr, int samples_count)
{
    int temp;
    int min;
    int cur_count=0;    //the index of current location in the array     
    int rear_index=0;   //the index for checking the next element
    for (cur_count = 0; cur_count < samples_count; ++cur_count)
    {
        min=arr[cur_count];
        for (rear_index = cur_count+1; rear_index <samples_count ; ++rear_index)
        {
            if (arr[rear_index]<min)
            {
                temp=min;
                min=arr[rear_index];
                arr[rear_index]=temp;
                arr[cur_count]=min;
            }
        }
    }

}


/*
*   @brief get_ThreatLevel:
*           This function is used for get the breach level for the sample set
*           based on the false alarm count, minimum threat level the user input
*   @para  *samples:
*           input the address of the sample set array
*   @para  samples_count:
*           the amount of the samples in a set
*   @para  Min_ThreatLevel:
*           the minimum threat level set by the user
*   @para  *times:
*           input the address of the variable storing the breach count
*           output the total breach count to the address after processing the data
*   @para  *threat:
*           input the address of the variable storing the breach level
*           output the threat level of the breach after processsing the data
*/
void get_ThreatLevel(int *samples,int samples_count, int Min_ThreatLevel,int *threat_level,int *breach_cnt, int false_alarm_cnt)
{   
    int count=1;    //times that same sample appears in a set
 
    /*scanning threat level set from high threat level to low level*/
    for (samples_count--; samples_count>=0; samples_count--)
    {
        /*count plus 1 if same sample appear*/
        if (samples_count>0&&samples[samples_count]==samples[samples_count-1])
        {
            count++;
        }
        else
        {
            //return result and break if threat appears more than false alarm count
            if(count>=false_alarm_cnt) 
                {
                    *breach_cnt=count;
                    *threat_level=samples[samples_count];
                    break;
                }

                //reset the count if the next threat level is scanned
                count=1;
        }
    }

}

