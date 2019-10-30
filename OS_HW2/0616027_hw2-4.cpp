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
	bool over = false;
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
	int time_qu;
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
		pc[i]->over = false;
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
	cin >> time_qu;
	sort(pc, pc + n, compare_arrive);
	int now = pc[0]->arrive;
	for(int i = 0; i < n; i ++){	//in Qo RR
		if(pc[i]->burst >= time_qu){
			pc[i]->burst -= time_qu;
			now += time_qu;
		}
		else{
			now += pc[i]->burst;
			pc[i]->burst = 0;
			pc[i]->complete = now;	//already over because burst too short
			pc[i]->over = true;
		}
	}
	sort(pc, pc + n, compare_priority);
	for(int i = 0; i < n; i++){
		if(pc[i]->over == false){
			now += pc[i]->burst;
			pc[i]->complete = now;
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
/*test
3
1 2 3			answer: 3 10 
7 8 1					7 15
3 5 7					2 3
2

3
3 5 6			3 7 0 1 2 11
4 1 9
2 3 6
2
*/
