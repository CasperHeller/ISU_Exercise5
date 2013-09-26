#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "Vector.hpp"

using namespace std;

void *writer(void* ID); //Prototyper

Vector data;; //Opretter global variabel

int main()
{
  int numberThreads;
  
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

  return 0;
}

void *writer(void* ID) //incrementer shared
{
  int threadID = (int)(ID);
  
  if(data.setAndTest(threadID) != 0)
    cout << threadID << ": All set!" << endl;
  else
    cout << threadID << ": Fail!" << endl;
    
  sleep(1);

  cout << "Terminating thread: " << threadID << endl;
  pthread_exit(NULL);
  
  return 0;
}