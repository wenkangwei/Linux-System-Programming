/*-----------------------------------------------------

	Course: ECE2220
	Student: Wenkang Wei
	ID: C15485238
	MP:mp1

 Idea:
 	After collecting samples, sort the data set and scan the 
 	sample set from highest threat level to the lowest threat 
 	level. Once the high threat-level samples appear equal to 
 	or  more than 3 times, break the loop and return values.



--------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSAMPLES 500
#define MINTHRESH    3



void clean_SampleSet(int *samples,int len);
void bubble_Sort(int *arr, int len);
void selection_Sort(int *arr, int len);
int get_ThreatLevel(int *samples,int len, int Min_ThreatLevel,int *times, int false_alarm_cnt);


int main(int argc, char const *argv[])
{
	int min_threat_level=0;
	int false_alarm_count=0;
	int SampleSet[MAXSAMPLES];
	int sample=0;
	int samples_count=0;
	int len=0;
	int threat;
	int times;

	/*Input minimum threat level */
	printf("The minimum threat level is \n");
	while(1)
	{
		scanf("%d",&min_threat_level);
		if(min_threat_level>=MINTHRESH) break;
		else if(min_threat_level==-1)
		{
			printf("Exit program.\n");
			return 0;
		}

		printf("The minimum threat level(>= 3) is \n" );

	}


	/*Input false alarm count */
	printf("A False alarm if the count < \n");

	while(1)
	{
		scanf("%d",&false_alarm_count);
		if(false_alarm_count>0) break;
		else if(false_alarm_count==-1)
		{
			printf("Exit program.\n");
			return 0;
		}

		printf("A false alarm if the count < \n");

	}


	while(sample>=-1)
	{
		//clean data after each cycle
		clean_SampleSet(SampleSet,len);
		sample=0;
		samples_count=0;
		threat=0;
		times=0;


		while(sample>=0)
		{

			scanf("%d", &sample);
			SampleSet[samples_count++]=sample;
			/*Sample input complete after max samples are input*/
			if(samples_count>=MAXSAMPLES)break;

		}
		len=samples_count;

		/*	Evaluate samples */

		if (sample==-1)
		{
			/*sort the threat level set */
			selection_Sort(SampleSet,len);
			
			/*get the threat level and times*/
			threat=get_ThreatLevel(SampleSet,len,min_threat_level,&times,false_alarm_count);

			if(times>=false_alarm_count&&threat>=min_threat_level)
				{
					printf("Threat detected with level %d and appears %d times \n", threat,times);
				}		
				else
				{
					printf("No threat detected\n");
				}

					
		}

	}

		printf("Goodbye\n");
	


	return 0;

}


void selection_Sort(int *arr, int len)
{
	int temp;
	int min;
	for (int i = 0; i < len; ++i)
	{
		min=arr[i];
		for (int j = i+1; j <len ; ++j)
		{
			if (arr[j]<min)
			{
				temp=min;
				min=arr[j];
				arr[j]=temp;
				arr[i]=min;
			}
		}
	}



}

void bubble_Sort(int *arr, int len)
{
	int temp;
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < len-1; ++j)
		{
			if (arr[j]>=arr[j+1])
			{
				temp=arr[j+1];
				arr[j+1]=arr[j];
				arr[j]=temp;	
			}
		}
	}




}



void clean_SampleSet(int *samples,int len)
{

	for (int i = 0; i < len; ++i)
	{
		samples[i]=0;
	}
}

int get_ThreatLevel(int *samples,int len, int Min_ThreatLevel,int *times, int false_alarm_cnt)
{	
	int count=1;
	int threat;

	/*scanning threat level set from high threat level to low level*/
	for (len--; len>0; len--)
	{
		/*Get repeated times of the same threat level*/
		if (samples[len]==samples[len-1])
		{
			count++;

		}
		else
		{
			/*After geting the highest threat level, break and return value*/
			if(count>=false_alarm_cnt) 
				{
					*times=count;
					threat=samples[len];
					break;

				}

					count=1;
		}
	}




	return threat;

}