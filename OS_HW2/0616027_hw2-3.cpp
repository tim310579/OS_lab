#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

struct process{
	int arrive = 0;
	int number = 0;
	int wait = 0;
	int turnaround = 0;
	int burst = 0;
	int rem_burst = 0;
	int priority = 0;
	int complete = 0;
};
bool compare_arrive(process *a, process *b){
	return a->arrive < b->arrive;	//sort with arrive
}

bool compare_priority(process *a, process *b){
	return a->priority < b->priority;	//pri
}
bool compare_number(process *a, process *b){
	return a->number < b->number;	//num for output
}
int main(){
	int n;
	cin >> n;
	process *pc[n];
	for(int i = 0; i < n; i++){
		pc[i] = new process;
		pc[i]->arrive = 0;
		pc[i]->burst = 0;
		pc[i]->number = i;	// just numbering them as p0,p1,p2
		pc[i]->turnaround = 0;
		pc[i]->wait = 0;
		pc[i]->priority = 0;
		pc[i]->complete = 0;
		pc[i]->rem_burst = 0;
	}

	for(int i = 0; i < n; i++){
		cin >> pc[i]->arrive;
	}
	for(int i = 0; i < n; i++){
		cin >> pc[i]->burst;
		pc[i]->rem_burst = pc[i]->burst;
	}
	for(int i = 0; i < n; i++){
		cin >> pc[i]->priority;	
	}
	sort(pc, pc + n, compare_arrive);
	int now, j, pcom_num;
	now = 0;
	pcom_num = 0;	//process complete number
	while(pcom_num < n){
		for(j = 0; j < n; j++){
			if(pc[j]->arrive > now){
				break;
			}
		}
		sort(pc, pc + j, compare_priority);	//choose who first with priority
		if(j > 0){
			for(j = 0; j < n; j++)
			{
				if(pc[j]->burst != 0)
				break;
			}
			if(pc[j]->arrive > now){
				now += pc[j]->arrive - now;
			}
			pc[j]->complete = now + 1;	//one step by one step
			pc[j]->burst--;
		}
		now++;
		pcom_num = 0;
		for(j = 0; j < n; j++)
		{
			if(pc[j]->burst == 0){
				pcom_num ++;	//count which is complete
			}
		}
	}
	sort(pc, pc + n, compare_number);
	int total_wait = 0;
	int total_turn = 0;
	for(int i = 0; i < n; i++){
		pc[i]->turnaround = pc[i]->complete - pc[i]->arrive;
		pc[i]->wait = pc[i]->turnaround - pc[i]->rem_burst;
		total_wait += pc[i]->wait;
		total_turn += pc[i]->turnaround;
		cout << pc[i]->wait << " " << pc[i]->turnaround << endl;
	}
	
	cout << total_wait << endl;
	cout << total_turn << endl;
	return 0;
} 
