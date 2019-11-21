#include <iostream> 
#include <stdlib.h>
#define LARGE 1000000
using namespace std;

int list[LARGE];
int cnt = 0;
/* function definitions */
void sort(int list[]);

int main (int argc, const char * argv[]) 
{
	/* Use STDIN (e.g. scanf, cin) to take the input */
	int input = 0;
	//int list[LARGE] = {0};
	while(cin >> input){
		list[cnt] = input;
		cnt ++;
	}
	
	sort(list);
	
	for(int i = 0; i < cnt; i++){
		cout << list[i] <<" ";
	}	
    return 0;
}

void sort(int list[])
{
	for(int i = 0; i < cnt; i++){
		for(int j = i+1; j < cnt; j++){
			if(list[i] > list[j]){
				int tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;	
			}
		}
	}
}

