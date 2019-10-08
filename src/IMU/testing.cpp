//Testing threading

#include <iostream>
#include <thread>
#include <unistd.h>
#include <mutex>
#include <condition_variable>


std::mutex mtx;
std::condition_variable cv;
bool ready = false;
int current= 0;

void print_me(int num){

	mtx.lock();
	current++;
	std::cout<< num + 1;// << " / "<< max;
	std::cout<< "Current count is:" << current <<std::endl;
	mtx.unlock();

}

void run(){

	std::unique_lock<std::mutex> lck(mtx);
	ready = true;
	cv.notify_all();
}

int main(){

	int id = 0;
	while(1){

		id++;
		std::thread thread = std::thread(print_me,id);
		thread.detach();
		usleep(5000);

	}
	std::cout<<"\nDone\n";
	return 0;

}
