#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "Vector.hpp"
#include "ScopedLocker.hpp"

using namespace std;

void *writer(void* ID); //Prototyper

Vector data; //Opretter global variabel
pthread_mutex_t lock;

int main()
{
  int numberThreads;
  
  if(pthread_mutex_init(&lock, NULL) != 0)
  {
    cout << "Mutex init fail!" << endl;
    cout << "Termination.." << endl;
    return 1;
  }
  
  while(numberThreads > 100 || numberThreads < 1)
  {
    cout << "Enter the number of threads you want (1-100): ";
    cin >> numberThreads;
    cout << endl;
  }
  
  pthread_t threads[numberThreads]; //Opretter objekter til threads
  
  cout << "Creating " << numberThreads << " threads!" << endl;
  for(int i=0; i<numberThreads; i++)
  {
    if(pthread_create(&threads[i], NULL, writer, (void*)i) != 0) //Opretter incrementer thread
    {
      cout << "Could not create thread: " << i << endl;
      cout << "Termination.." << endl;
      return 1;
    }
  }
  
  for(int i=0; i<numberThreads; i++)
  {
    pthread_join(threads[i], NULL);
  }
  
  if(pthread_mutex_destroy(&lock) != 0)
  {
    cout << "Mutex destroy fail!" << endl;
    cout << "Termination.." << endl;
    return 1;
  }

  return 0;
}

void *writer(void* ID) //incrementer shared
{
  int threadID = (int)(ID);
  int err;
  {
    ScopedLocker scopedLock(&lock);
    err = data.setAndTest(threadID);
  }

  if(err != 0)
    cout << threadID << ": All set!" << endl;
  else
    cout << threadID << ": Fail!" << endl;
    
  sleep(1);

  cout << "Terminating thread: " << threadID << endl;
  pthread_exit(NULL);
  
  return 0;
}