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
	int priority = 0;
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
		pc[i]->priority = 0;
	}
	pair <int, pair<int, int>> arr[n];
	for(int i = 0; i < n; i++){
		cin >> arr[i].first;	//arrive time
		arr[i].second.second = i;		//number
		pc[i]->arrive = arr[i].first;
	}
	for(int i = 0; i < n; i++){
		cin >> pc[i]->burst;
	}
	for(int i = 0; i < n; i++){
		cin >> pc[i]->priority;
		arr[i].second.first = pc[i]->priority;
	}
	sort(arr, arr + n);
	int now = arr[0].first;	//arrive time
	pc[arr[0].second.second]->wait = 0;
	now += pc[arr[0].second.second]->burst;
	for(int i = 1; i < n; i++){
		//cout << arr[i].first << " " << arr[i].second.first << " "<< arr[i].second.second << endl;
		int tmp_prior = INT_MAX;
		pair <int, pair<int, int>> tmp;
		for(int j = i; j < n; j++){
			if(pc[arr[j].second.second]->arrive < now && pc[arr[j].second.second]->priority < tmp_prior){
				tmp_prior = pc[arr[j].second.second]->priority;		//change the highest priority pc ahead to 
				tmp = arr[j];										//be execute first
				arr[j] = arr[i];
				arr[i] = tmp;
			}
		}
		pc[arr[i].second.second]->wait = now - pc[arr[i].second.second]->arrive;
		now += pc[arr[i].second.second]->burst;
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
