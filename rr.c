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

char isIncluded(int* arr,int n,int val){
	for(int i=0;i<n;i++)
		if (arr[i]==val)
			return 1;

return 0;

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



	//Calculate total burst time
	int totalBurstTime = 0 ;
  
	for(int i=0;i<n;i++){
		totalBurstTime+=arr[i].burst_time;
	}

	int currentTime = 0;
	int ganttArr[totalBurstTime],m=0;
	int requestQueue[10000],k=0;
	int j=0,key;
   
	while(currentTime<totalBurstTime){
			//Start executing the first process
			if(m==0){
					if(arr[0].burst_time>quantum){
						//Update Gantt's array
						for(int i=0;i<quantum;i++){
							ganttArr[m]=arr[0].pid;
							m++;
						}
						//Update CurrentTime and BurstTime
						currentTime+=quantum;
						arr[0].burst_time -= quantum;

						//Update Request queue
						for(int i=1;i<n;i++){
							if(arr[i].arrival_time<=currentTime){
								requestQueue[k]=arr[i].pid;
								k++;
							}
						}
						requestQueue[k]=arr[0].pid;
						k++;
					}
					else{
						//Update Gantt's array
						for(int i=0;i<arr[0].burst_time;i++){
							ganttArr[m]=arr[0].pid;
							m++;
						}

						//Update CurrentTime and BurstTime
						currentTime+=arr[0].burst_time;
						arr[0].burst_time = 0;

						//Update Request queue
						for(int i=1;i<n;i++){
							if(arr[i].arrival_time<=currentTime){
								requestQueue[k]=arr[i].pid;
								k++;
							}
						}
					}
			}
			else{
				//Execute next process based on Request Queue

				//Find the index of the process to be executed
				for(int i=0;i<n;i++){
					if(requestQueue[j]==arr[i].pid)
						key=i;
				}
				
				//Add to Gannt's Array
				if(arr[key].burst_time>quantum){
					for(int i=0;i<quantum;i++){
						ganttArr[m]=arr[key].pid;
						m++;
					}
					currentTime+=quantum;
					arr[key].burst_time-=quantum;

					//Update Request queue
					for(int i=0 ; i<n ;i++){
						if(!isIncluded(requestQueue,k,arr[i].pid) && arr[i].arrival_time<=currentTime && arr[i].burst_time>0){
								requestQueue[k]=arr[i].pid;
								k++;
						}
					}
					requestQueue[k]=arr[key].pid;
					k++;

				}
				else{
					
					//Add to Gantt's array
					for(int i=0;i<arr[key].burst_time;i++){
						ganttArr[m]=arr[key].pid;
						m++;
					}
					currentTime+=arr[key].burst_time;
					arr[key].burst_time=0;

					//Update request queue
					for(int i=0 ; i<n ;i++){
						if(!isIncluded(requestQueue,k,arr[i].pid) && arr[i].arrival_time<=currentTime && arr[i].burst_time>0){
								requestQueue[k]=arr[i].pid;
								k++;
						}
					}
				}
          j++;
			}
	 }

  printArr(ganttArr,m);

	return 0; /* DO NOT EDIT THIS LINE */
}
