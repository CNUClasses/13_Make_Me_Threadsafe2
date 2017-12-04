//============================================================================
// Name        : 13_Make_Me_Threadsafe2.cpp
// Author      : 
// Version     :
// Copyright   : Steal this code!
// Description : make it so usually only 
//				1 thread can run at a time
//				2 threads can run at a time
//				3 threads can run at a time
//              you will find that the total amount of work accomplished
//				(as evidenced by iG1+iG2+iG3) is greater when using more threads
//				at a time
//				demo system monitor-resources view watch threads spike
//============================================================================

#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>
#include <mutex>
#include <atomic>
using namespace std;

//globals
bool bDoWork = true;
int iG1 = 0;
int iG2 = 0;
int iG3 = 0;

mutex m1;
mutex m2;
mutex m3;

void f1() {
	while (bDoWork) {
		lock_guard<mutex> m(m1);
		iG1++;
	}
}
void f2() {
	while (bDoWork) {
		lock_guard<mutex> m(m2);
		iG2++;
	}
}
void f3() {
	while (bDoWork) {
		lock_guard<mutex> m(m3);
		iG3++;
	}
}

int main() {
	thread t1(f1); 	//f1 - 2 threads
	thread t2(f1);
	thread t3(f2);	//f2 - 2 threads
	thread t4(f2);
	thread t5(f3);	//f3 - 2 threads
	thread t6(f3);
	
//	thread t7(f1); 	//f1 - 3 threads
//	thread t8(f2);	//f2 - 3 threads
//	thread t9(f3);	//f3 - 3 threads
		
	//delay long enough for threads to start and get some work done 
	std::this_thread::sleep_for(std::chrono::microseconds(1000000)); //add a 0 to examine system monitor resources view
	bDoWork = false;

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
//	t7.join();
//	t8.join();
//	t9.join();

	cout << "iG1=" << iG1 << endl;
	cout << "iG2=" << iG2 << endl;
	cout << "iG3=" << iG3 << endl;

	cout << "TOTALS=" << iG1 + iG2 + iG3 << endl;
}
