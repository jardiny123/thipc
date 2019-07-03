#include <iostream>
#include <cstring>
#include <thread>
#include <unistd.h>
#include <mutex>
#include <condition_variable>
using namespace std;

static mutex m;
static pthread_mutex_t count_mutex;
static pthread_cond_t cond[2];
condition_variable cv;
int arr[20];
int count=0;
int arrsize = sizeof(arr)/sizeof(arr[0]);
   
void main_thread(int th_num)
{
    int thcount;
    while(count < arrsize)
    {
	// without sync between threads
       /* 
	m.lock();
    	cout <<  "th" << th_num << endl;
	if(count > arrsize-1)
		return;
    	arr[count++] = rand() % 20;
	m.unlock();
	std::this_thread::yield();
	usleep(100);
	*/	
	// with sync
	pthread_mutex_lock(&count_mutex);
	while(count%2 == th_num)
		pthread_cond_wait(&cond[th_num], &count_mutex);
    	cout <<  "th" << th_num << endl;
	if(count > arrsize-1)
		return;
    	arr[count++] = rand() % 20;
	pthread_cond_signal(&cond[(th_num+1)%2]);
	pthread_mutex_unlock(&count_mutex);
    }
}

void swap(int i, int j)
{
	arr[i] ^= arr[j];
	arr[j] ^= arr[i];
	arr[i] ^= arr[j];
}

int main ()
{
    thread th1(main_thread, 0);
    thread th2(main_thread, 1);
    th1.join();
    th2.join();
	
    // print unsorted array
    for(int i=0;i<arrsize;i++)
	cout << arr[i] << endl;
    cout << "sort start" << endl;
     //dubble sort
    for(int i=0;i<arrsize;i++)
    	for(int j=0;j<arrsize-i-1;j++)
		if(arr[j] > arr[j+1])
    			swap(j,j+1);
    // print sorted array
    for(int i=0;i<arrsize;i++)
	cout << arr[i] << endl;
	return 0;
}
