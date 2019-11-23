#include <iostream> 
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <climits>
#include <cstring>

#define LARGE 1000001

using namespace std;
/* function definitions */
void* sort(void *arg);
void* merge(void *arg);

struct merges{
	int cnt1;
	int cnt2;
	int **list;
	//int list2[LARGE/2];
};
struct lists{
	int *list;
	int cnt;
};

int main (void) 
{
	struct lists lwc0;	//list with count
	struct lists lwc1;
	struct lists lwc2;
	struct lists lwc3;
	struct merges mwc1;
	struct merges mwc2;
	struct merges mwc3;
	pthread_t t0, t1, t2, t3, t4, t5, t6;
	/* Use STDIN (e.g. scanf, cin) to take the input */
	int input = 0;
	int *list = new int[LARGE];
	int count[4] = {0};
	int cnt = 0;
	
	while(cin >> input){
		list[cnt] = input;
		cnt++;
	}
	for(int i = 0; i < 4; i++){
		count[i] = cnt*(i+1)/4 - cnt*i/4;
		//cout << count[i]<<" ";
	}
	lwc0.cnt = count[0];
	lwc1.cnt = count[1];
	lwc2.cnt = count[2];
	lwc3.cnt = count[3];
	
	lwc0.list = new int[cnt];
	lwc1.list = new int[cnt];
	lwc2.list = new int[cnt];
	lwc3.list = new int[cnt];
	//count[0] = cnt/4;		//each list size
	//cnt1 = cnt/2 - cnt0;
	//cnt2 = cnt*3/4 - cnt/2;
	//cnt3 = cnt - cnt*3/4;
	
	for(int i = 0; i < count[0]; i++){
		lwc0.list[i] = list[i];
	}
	for(int j = 0; j < count[1]; j++){
		lwc1.list[j] = list[count[0]+j];
	}
	for(int k = 0; k < count[2]; k++){
		lwc2.list[k] = list[count[0]+count[1]+k];
	}
	for(int l = 0; l < count[3]; l++){
		lwc3.list[l] = list[count[0]+count[1]+count[2]+l];
	}
	
	void *ret0, *ret1, *ret2, *ret3, *ret4, *ret5, *ret6;
	pthread_create(&t0, NULL, sort, (void *) &lwc0);	
	pthread_create(&t1, NULL, sort, (void *) &lwc1);	
	pthread_create(&t2, NULL, sort, (void *) &lwc2);
	pthread_create(&t3, NULL, sort, (void *) &lwc3);
	pthread_join(t0, &ret0);
	pthread_join(t1, &ret1);
	pthread_join(t2, &ret2);
	pthread_join(t3, &ret3);

	delete [] list;	//release space
	mwc1.cnt1 = count[0];
	mwc1.cnt2 = count[1];
	mwc2.cnt1 = count[2];
	mwc2.cnt2 = count[3];
	
	mwc1.list = new int*[2];	//2-D array with count
	mwc1.list[0] = new int[cnt];
	mwc1.list[1] = new int[cnt];
	mwc2.list = new int*[2];
	mwc2.list[0] = new int[cnt];
	mwc2.list[1] = new int[cnt];
	
	mwc1.list[0] = (int *) ret0;
	mwc1.list[1] = (int *) ret1;
	mwc2.list[0] = (int *) ret2;
	mwc2.list[1] = (int *) ret3;

	pthread_create(&t4, NULL, merge, (void *) &mwc1);
	pthread_create(&t5, NULL, merge, (void *) &mwc2);
    	
	pthread_join(t4, &ret4);
	pthread_join(t5, &ret5);
	delete [] mwc1.list[0];
	delete [] mwc1.list[1];
	delete [] mwc1.list;
	delete [] mwc2.list[0];
	delete [] mwc2.list[1];
	delete [] mwc2.list;

	int half1 = count[0] + count[1];
	int half2 = count[2] + count[3];

	mwc3.cnt1 = half1;
	mwc3.cnt2 = half2;
	
	mwc3.list = new int*[2];
	mwc3.list[0] = new int[cnt];
	mwc3.list[1] = new int[cnt];
	
	mwc3.list[0] = (int *) ret4;
	mwc3.list[1] = (int *) ret5;
	
	pthread_create(&t6, NULL, merge, (void *) &mwc3);
	pthread_join(t6, &ret6);
	delete [] mwc3.list[0];
	delete [] mwc3.list[1];
	delete [] mwc3.list;
	int *list_final = new int[cnt];
	list_final = (int *) ret6;
	for(int i = 0; i < cnt; i++){
		cout << list_final[i] <<" ";
	}
	delete [] list_final;
	return 0;
}

void* sort(void *arg)
{
	struct lists lwc = *(lists *) arg;
	int cntt = lwc.cnt;
	int *list = new int[cntt];
	list = lwc.list;

	for(int i = 0; i < cntt; i++){
		for(int j = i+1; j < cntt; j++){
			if(list[i] > list[j]){
				int tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;	
			}
		}
	}
	pthread_exit((void *) list);

	// Sorting algorithm can be brute‐force methods, e.g., bubble sort 
	/*
		your code here
	*/
}
void* merge(void *arg){
	struct merges mwc = *(merges *) arg;
	int cnt1 = mwc.cnt1;
	int cnt2 = mwc.cnt2;
	int **list = new int*[2];
	list[0] = new int[cnt1];	//first array
	list[1] = new int[cnt2];	//second array
	list = mwc.list;
	list[0][cnt1] = INT_MAX;
	list[1][cnt2] = INT_MAX;
	int *ret_list = new int[cnt1+cnt2];
	
	int i = 0, j = 0, check = 0;
	while(1){
		if(list[0][i] < list[1][j]){
			ret_list[check] = list[0][i];
			i++;
			check++;
		}
		else if(list[0][i] >= list[1][j]){
			ret_list[check] = list[1][j];
			j++;
			check++;
		}
		if(i == cnt1 && j == cnt2) break;
	}
	pthread_exit((void *) ret_list);
}
