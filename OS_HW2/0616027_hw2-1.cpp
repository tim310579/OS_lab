#include <iostream>
#include <algorithm>

using namespace std;

struct process{
	int arrive = 0;
	int number = 0;
	int wait = 0;
	int turnaround = 0;
	int burst = 0;
};

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
	}
	pair<int, int> arr[n];
	for(int i = 0; i < n; i++){
		cin >> arr[i].first;	//arrive time
		arr[i].second = i;		//number
		//cin >> pc[i]->arrive;
		pc[i]->arrive = arr[i].first;
	}
	for(int i = 0; i < n; i++){
		cin >> pc[i]->burst;
	}
	sort(arr, arr + n);
	int now = arr[0].first;	//arrive time
	for(int i = 0; i < n; i++){
		if(now < pc[arr[i].second]->arrive) now = pc[arr[i].second]->arrive;
		pc[arr[i].second]->wait = now - pc[arr[i].second]->arrive;
		now += pc[arr[i].second]->burst;
	}
	int total_wait = 0;
	int total_turn = 0;
	for(int i = 0; i < n; i++){
		pc[i]->turnaround = pc[i]->burst + pc[i]->wait;
		total_wait += pc[i]->wait;
		total_turn += pc[i]->turnaround;
		cout << pc[i]->wait << " " << pc[i]->turnaround << endl;
	}
	
	cout << total_wait << endl;
	cout << total_turn << endl;
	return 0;
} 
