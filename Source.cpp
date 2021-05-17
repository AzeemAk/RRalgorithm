#include<iostream>
#include<fstream>
using namespace std;
void rr(int numOfProcesses, int pid[], int arrivalTime[], int burstTime[], int tq);
bool allComplete(bool complete[], int numOfProcesses);
int main() {
	int numOfProcesses, tq;
	cout << "Enter Time Quantum for Round Robin algorithm: ";
	cin >> tq;
	ifstream read;
	read.open("input.txt");
	read >> numOfProcesses;
	int pid[50];
	int arrivalTime[50];
	int burstTime[50]; 
	
	if (read.is_open()) {        //initializing arrays
		for (int i = 0; i < numOfProcesses; i++)
		{
			read >> pid[i];
			read >> arrivalTime[i];
			read >> burstTime[i];
		}
	}
	else
		cout << "Error. File Couldn't Be Found." << endl;
	
	
	rr(numOfProcesses, pid, arrivalTime, burstTime, tq);

	
}
bool allComplete(bool complete[], int numOfProcesses) {
	int count = 0;
	for (int i = 0; i < numOfProcesses; i++)
	{
		if (complete[i] == true)
		{
			count++;
		}
	}
	if (count == numOfProcesses) {
		cout << "\nROUND ROBIN COMPLETE.\n" << endl;
		return true;
	}
	return false;
}
void rr(int numOfProcesses, int pid[], int arrivalTime[], int burstTime[], int tq) {
	int burstTimeLeft[50], waitTime[50], completionTime[50], turnAroundTime[50], serviceTime[50];
	int order, timer = 0, temp1 = 0, temp2 = 0, sumWait = 0, switchTime = 5, totalSwitch = 0;
	float avgWait = 0, avgTAT = 0, cpuEff = 0;
	bool complete[50];
	for (int i = 0; i < numOfProcesses; i++) {
		burstTimeLeft[i] = burstTime[i];
		complete[i] = false;
		waitTime[i] = 0;
	}
	cout << "Before Sort: " << endl;
	for (int i = 0; i < numOfProcesses; i++)
	{
		cout << pid[i] << "\t" << arrivalTime[i] << "\t" << burstTime[i] << endl;
	}
	for (int i = 0; i < numOfProcesses; i++)                     //find order of procceses
	{
		for (int k = 0; k < numOfProcesses; k++)
		{
			if (arrivalTime[i] == arrivalTime[k]) {
				if (burstTime[i] < burstTime[k])
				{

					order = arrivalTime[i];
					arrivalTime[i] = arrivalTime[k];
					arrivalTime[k] = order;

					temp1 = pid[i];
					pid[i] = pid[k];
					pid[k] = temp1;

					temp2 = burstTime[i];
					burstTime[i] = burstTime[k];
					burstTime[k] = temp2;
				}
			}
			if (arrivalTime[i] < arrivalTime[k]) {
				order = arrivalTime[i];
				arrivalTime[i] = arrivalTime[k];
				arrivalTime[k] = order;

				temp1 = pid[i];
				pid[i] = pid[k];
				pid[k] = temp1;

				temp2 = burstTime[i];
				burstTime[i] = burstTime[k];
				burstTime[k] = temp2;
			}
		}
	}
	cout << "After Sort: " << endl;
	for (int i = 0; i < numOfProcesses; i++)
	{
		cout << pid[i] << "\t" << arrivalTime[i] << "\t" << burstTime[i] << endl;
	}

	int cycle = 1;

	while (!allComplete(complete, numOfProcesses)) {
		
		cout << "-----------------------" << endl;
		cout << "Cycle " << cycle << ":" << endl;
		for (int i = 0; i < numOfProcesses; i++)
		{
			if (complete[i] == false)
			{
				if (burstTimeLeft[i] < tq) {
					timer += burstTimeLeft[i];
					for (int j = 0; j < numOfProcesses; j++)
					{
						if (!j == i)      //adding to wait time if process is not being run
						{
							waitTime[j] += burstTimeLeft[i];
						}
					}
					burstTimeLeft[i] -= burstTimeLeft[i];
					totalSwitch += switchTime;
					
					
				}
				else {
					burstTimeLeft[i] -= tq;
					timer += tq;
					totalSwitch += switchTime;
					for (int j = 0; j < numOfProcesses; j++)
					{
						if (!j == i)
						{
							waitTime[j] += tq;
						}
					}
				}

				if (burstTimeLeft[i] == 0)    // checking if process is finished after this cycle of rr.
				{
					complete[i] = true;
					completionTime[i] = timer;
					cout << "Process " << pid[i] << " completed" << " at time " << completionTime[i] << "." << endl;
				}
				if (burstTimeLeft[i] < 0) {
					cout << "Error. BurstTimeLeft was a negative number. " << endl;
				}
			}
			
		}
		
		for (int i = 0; i < numOfProcesses; i++)         //checking status after every instance
		{
			if (complete[i] == false) {
				cout << pid[i] << "\t" << arrivalTime[i] << "\t" << burstTimeLeft[i] << endl;
			}
		}
		
		cycle++;
	}

	
	for (int i = 0; i < numOfProcesses; i++)  //calculating output values
	{
		turnAroundTime[i] = completionTime[i] - arrivalTime[i];
		sumWait += waitTime[i];

	}
	
	avgWait = (sumWait / numOfProcesses);
	
	
	

	for(int i = 0; i < numOfProcesses; i++)
	{
		cout << "Process " << pid[i] << ":" << endl;
		cout << "Service Time = " << burstTime[i] << endl;
		cout << "Turnaround Time = " << turnAroundTime[i] << endl << endl;

	}
	cout << "Total Time Running = " << timer << endl;
	cout << "Average waiting time is " << avgWait << " time units " << endl;
	cout << "Total switching time is " << totalSwitch << endl;
	cout << "CPU Efficiency is " << "%" << cpuEff * 100 << endl;
	cout << "timer = " << timer << " totalSwitch = " << totalSwitch << endl;

}