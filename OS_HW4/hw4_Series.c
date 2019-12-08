#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

long long ans[10];
pthread_mutex_t lock;
struct ser{
	char* series;
	long long cnt;
};
void* count_num(void *arg);
int main(){
	int i, j;
	for(i = 0; i < 10; i ++){
		ans[i] = 0;
	}
	printf("0616027\n");
	int num, length;
	scanf("%d\n", &num);
	scanf("%d\n", &length);
	
	long long count[num];
	ser* series[num];

	for(i = 0; i < num; i++){
		series[i] = (ser*)malloc(sizeof(ser));
		count[i] = length*(i+1)/num - length*i/num;
		series[i]->cnt = count[i];
		series[i]->series = (char*)malloc(sizeof(char)*count[i]);
	}
	
	for(i = 0; i < num; i++){
		for(j = 0; j < count[i]; j++){
			scanf("%c", &series[i]->series[j]);
		}
	}
	
	pthread_t t[num];
	void *ret[num];
	for(i = 0; i < num; i++){
		pthread_create(&t[i], NULL, count_num, (void *) series[i]);
	}
	for(i = 0; i < num; i++){
		pthread_join(t[i], &ret[i]);
	}
	for(i = 0; i < 10; i++){
		printf("The total number of %d : %lld\n", i, ans[i]);
	}
	return 0;
}
void* count_num(void *arg){
	ser* tmp = (ser*) arg;
	long long cnt = tmp->cnt;
	char *series = (char*)malloc(sizeof(char)*cnt);
	series = tmp->series;
	long long i;
	long long ans_tmp[10] = {0};
	for(i = 0; i < cnt; i++){
		switch(series[i]){
			case '0': ans_tmp[0] ++; break;
			case '1': ans_tmp[1] ++; break;
			case '2': ans_tmp[2] ++; break;
			case '3': ans_tmp[3] ++; break;
			case '4': ans_tmp[4] ++; break;
			case '5': ans_tmp[5] ++; break;
			case '6': ans_tmp[6] ++; break;
			case '7': ans_tmp[7] ++; break;
			case '8': ans_tmp[8] ++; break;
			case '9': ans_tmp[9] ++; break;
			default: break;
		}
	}
	pthread_mutex_lock(&lock);
	for(i = 0; i < 10; i++){
		ans[i] += ans_tmp[i];
	}
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}
