#include <iostream> 
#include <stdlib.h>
#define LARGE 1000001
using namespace std;

//int list[LARGE];
int cnt = 0;
/* function definitions */
void sort(int list[]);

int main (int argc, const char * argv[]) 
{
	/* Use STDIN (e.g. scanf, cin) to take the input */
	int input = 0;
	int *list_tmp = new int[LARGE];
	
	while(cin >> input){
		list_tmp[cnt] = input;
		cnt ++;
	}
	
	sort(list_tmp);
	
	for(int i = 0; i < cnt; i++){
		cout << list_tmp[i] <<" ";
	}	
	delete [] list_tmp;
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

