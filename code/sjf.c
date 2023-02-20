#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int timePassed=0;	

typedef struct {
	int pid;
	int arrival_time;
	int burst_time;
} process;

// Function to print an array
void printArr(int* arr,int n){
	for(int i=0;i<n;i++ )
		printf("%d\n",arr[i]);
}

/*
 Function to check if a process has been executed
 Returns 1 if process has been executed, otherwise returns 0
*/
bool isExecuted(int* arr , int k , int id){
	bool flag = 0;
	for(int i=0;i<k;i++)
		if(arr[i]==id)
		  flag = 1;
	
  return flag;
}

// Function to calculate SJF
void calcSJF(process* arr,int n){

	int arrGantt[10000],k=0;
	int IDexecuted[10000],m=0;
	int nextId,p,min;

	
			// Execute the first process
				for(int i=0 ; i<arr[0].burst_time ; i++){
					arrGantt[i]=arr[0].pid;
					k++;
				}

			//Update total timePassed , add to executed processes
			timePassed+=arr[0].burst_time;
			IDexecuted[m]=arr[0].pid;
			m++;
			
		// Run for n-1 remaining processes 
    for(int j=0;j<n-1;j++){

			min=10000;

			for(int i=0;i<n;i++){
					if(!isExecuted(IDexecuted,m,arr[i].pid) && arr[i].arrival_time<=timePassed && arr[i].burst_time<min){
						min = arr[i].burst_time;
						nextId = arr[i].pid;
						p=i;
					}
			}

			//Add results to Gantt's array
			for(int v=0 ; v<arr[p].burst_time ; v++){
					     arrGantt[k]=nextId;
					     k++;
				}

				// Update executed processes and total time passed
				IDexecuted[m]=nextId;
				m++;
				timePassed+=arr[p].burst_time;

}
// printf("------------------------------\n");
printArr(arrGantt,k);
// printArr(IDexecuted,m);
}

// Function to print data
void printData(process* arr,int n){
	printf("----------------\n");
	for(int i=0;i<n;i++){
		if(i==0){
			printf("ID ArrTime BurstTime\n");
		}
		printf("%d    %d         %d \n",arr[i].pid,arr[i].arrival_time,arr[i].burst_time);
	}
	printf("----------------\n");
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

 calcSJF(arr,n);

	return 0; /* DO NOT EDIT THIS LINE */
}
