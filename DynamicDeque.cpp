#include<iostream>
#include<bits/stdc++.h>

#define EXPO_GROWTH_FACTOR 2
#define INIT_SIZE 10
using namespace std;

class DynamicDequeue {
private:
  	double *A; // the array used for implementing the dynamic dequeue
	int N; // the current size of array A
	int f; // index where first element of queue is present (if not empty)
   	int r;  	// index where next element will be inserted
	//increase size of array if needed
   	int nextSizeExponential() { return N*EXPO_GROWTH_FACTOR; }
public:
  	DynamicDequeue();
  	bool isEmpty();
  	bool isFull();
  	void grow();
   	int size();
  	void insertFront(double x);
  	void insertRear(double x);
 	double removeFront();
  	double removeRear();
  	double front();
  	double rear();
  	void erase();
  	double getPosition(int pos);
};

// default constructor
DynamicDequeue::DynamicDequeue()
{
  N = INIT_SIZE;
  f = 0;
  r = 0;
  A = new double[N];
}

//to check if dequeue is empty
bool DynamicDequeue::isEmpty(){
  return f==r;
}

//to check if dequeue is full
bool DynamicDequeue::isFull()
{
  return (r+1)%N==f;
}

// grow the queue to its next size
void DynamicDequeue::grow()
{
  double A_new[nextSizeExponential()];
  for( int i=0; i<N-1 ; i++){
    A_new[i] = A[(f+i)%N];
  }

  r = size();
  N = nextSizeExponential();
  A = A_new;
  f = 0;

}

// return the current number of elements in the queue
int DynamicDequeue::size()
{
  if(r>=f) return r-f;
  else return (N+r-f);
}

 // insert given value in front of the queue; grow array size as necessary
void DynamicDequeue::insertFront(double x)
{
  if(isFull()) grow();
  if (f == 0) f = N-1;
  else f = f-1;
  A[f] = x;
}

// insert given value in rear of the queue; grow array size as necessary
void DynamicDequeue::insertRear(double x)
{
  if(isFull()) grow();
  A[r] = x;
  r = (r+1)%N;
}

// remove the value in front of the queue and place it in *x; returns false if queue is empty, true otherwise
double DynamicDequeue::removeFront()
{
  if(isEmpty()) return 0;
  int f1 = f;
  f = (f+1)%N;
  return A[f1];
}

 // remove the value in rear of the queue and place it in *x
 // returns false if queue is empty, true otherwise
double DynamicDequeue::removeRear()
{
  if(isEmpty()) return 0;
  int r1 =r;
  if(r == 0) r = N-1;
  else r = r-1;
  return A[r1-1];
}

// place value in front of queue in *x; returns false if queue is empty, true otherwise
double DynamicDequeue::front()
{
  if(isEmpty()) return 0;
  return A[f];
}

// place value in rear of queue in *x; returns false if queue is empty, true otherwise
double DynamicDequeue::rear()
{
  if(isEmpty()) return 0;
  if(r == 0) return A[N-1];
  else return A[r-1];
}

//reset the dequeue
void DynamicDequeue::erase()
{
	//change all variables back to initial state
	N = INIT_SIZE;
	A = new double[N];
	f =0;
	r =0;
}

//give value of item at the given position from front
double DynamicDequeue::getPosition(int pos)
{
	int t = (f+pos-1)%N;
	return A[t];
}
