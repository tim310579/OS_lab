#include <stdio.h> 
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
// Defines precision for x and y values. More the 
// interval, more the number of significant digits 

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void* Pi_cnt(void *arg);
long long incircle[4]; 
struct thrown{
	int t_num;
	long long length;
};
int main() 
{
   	long long i;
	for(i = 0; i < 4; i++){
		incircle[i] = 0;
	}	
	srand(time(NULL)); 
   	long long num, length;
	printf("0616027\n");
	scanf("%lld", &num);
	scanf("%lld", &length);
	thrown* thr[num];
	long long count[num];
	for(i = 0; i < num; i ++){
		thr[i] = (thrown*)malloc(sizeof(thrown));
		count[i] = length*(i+1)/num - length*i/num;
		thr[i]->length = count[i];
		thr[i]->t_num = i;
	}
	pthread_t t[num];
	void *ret[num];
	for(i = 0; i < num; i++){
		pthread_create(&t[i], NULL, Pi_cnt, (void *) thr[i]);
	}
	for(i = 0; i < num; i++){
		pthread_join(t[i], &ret[i]);
	}
	long long all_in = 0;
	for(i = 0; i < num; i++){
		printf("Thread %lld, There are %lld points in the circle\n", i, incircle[i]); 
		all_in += incircle[i];
	}
    	double pi = 0;
    	pi = (double)(4*all_in)/(length); 
    // Final Estimated Value 
    //printf("%lld %lld", circle_points, square_points);
    	printf("Pi : %lf\n", pi); 
  
    	return 0; 
} 
void* Pi_cnt(void *arg){
	thrown* tmp = (thrown*) arg;
	int t_num = tmp->t_num;
	long long cnt = tmp->length;
	long long circle_points = 0, i = 0;
	double rand_x, rand_y, origin_dist; 
	for (i = 0; i < cnt; i++) {  
        // Randomly generated x and y values 
        	rand_x = (double)rand()/ (RAND_MAX); 
	        rand_y = (double)rand()/ (RAND_MAX); 
        	origin_dist = rand_x * rand_x + rand_y * rand_y; 
	        if (origin_dist <= 1) circle_points++; 
    	}
   	pthread_mutex_lock(&lock);
   	//printf("Thread %d, There are %lld points in the circle\n", t_num, circle_points); 
   	incircle[t_num] += circle_points;
   	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}
