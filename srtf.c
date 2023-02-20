#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pid;
	int arrival_time;
	int burst_time;
} process;

void printArr(int* arr,int n){
	for(int i=0;i<n;i++ )
		printf("%d\n",arr[i]);
}

int main() {

	/* read in data - DO NOT EDIT (START) */
	int n;
	int quantum;
	scanf("%d", &n);
	scanf("%d", &quantum);
	process *arr;
	arr = malloc(n * sizeof(process));
	for (int i = 0; i < n ; ++i) {
		scanf("%d", &arr[i].pid);
		scanf("%d", &arr[i].arrival_time);
		scanf("%d", &arr[i].burst_time);
	}
	/* read in data - DO NOT EDIT (END) */

int currentTime = 0;
int totalBurstTime = 0;
int minBurstTime;
int key;

// Calculate total burst time
for(int i=0;i<n;i++){
	totalBurstTime+=arr[i].burst_time;
}

int gantArr[totalBurstTime],m=0;

while(currentTime<totalBurstTime){

	// Start executing the first process
	if(m==0){
		gantArr[m]=arr[m].pid;
		arr[m].burst_time--;
	}
	else{
		// find next process to execute for next time unit
		 minBurstTime = 10000000;

		// Find smallest remaining time 
		for(int i=0;i<n;i++){
			if(arr[i].arrival_time<=currentTime && arr[i].burst_time<minBurstTime && arr[i].burst_time>0){
				minBurstTime = arr[i].burst_time;
				key=i;
			}
		}

		// Update gant array
		gantArr[m]=arr[key].pid;

		//Update remaining burst time 
		arr[key].burst_time--;

	}

   currentTime++;
   m++;
}	

	printArr(gantArr,m);

	return 0; /* DO NOT EDIT THIS LINE */
}
