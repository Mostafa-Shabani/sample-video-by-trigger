#include "Webcam.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <atomic>
#include <thread>
#include <iostream>


  
Webcam* Webcam::instance;

Webcam::Webcam()
{
	Initialise();
}
void Webcam::Initialise()
{
	if_terminate_capture= false;
	instance=this;

}
void Webcam::Start()
{	
	int counter=0;
	while(counter<10 && !capture.isOpened())
	{	
		capture.open(counter);
		
		std::cout<<counter<<std::endl;
		++counter;
	}
	CV_Assert(capture.isOpened());
	t= std::thread([&](){
		cv::Mat temp_frame;
		int counter=0;
		while(!if_terminate_capture)
		{
			 ++counter;
	 		 while (flag.test_and_set()) {}
			capture >> temp_frame;
			//~ cv::imshow("stream",temp_frame);
			//~ cv::waitKey(10);
			flag.clear();

			//~ if(counter%10 == 0) std::cout<<"counter =" <<counter<<std::endl;
			//~ std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	});
	
	

}

void Webcam::Stop()
{
	if_terminate_capture=true;
	t.join();
	capture.release();
}

void Webcam::Finalise()
{ }

void Webcam::getImage(cv::Mat& frame)
{	
	std::thread tg([&](){
		 while (flag.test_and_set()) {}
		capture >> frame;
		flag.clear();

	});
	tg.join();
}

 void Webcam::lookForCamTrig(std::mutex& m, std::condition_variable& cv, trigger_method _trigger_method, bool& session_active)
 {
	 bool trigger(false);
	 std::unique_lock<std::mutex> lk(m);

	 while (session_active)
	 {

		 switch(_trigger_method)
		 {
			 case TRIGGER_BY_FIXED_TIME_INTERVAL:
			 {
				 std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				 trigger = true;
				 break;
			 }
			 case TRIGGER_BY_USER_DEFINED_METHOD:
			 {

                PressEnterToContinue();
                trigger = true;
				break;
                
			 }
			 
			 default:
			{
					trigger = false;
					break;
			}
		 }
		 
	 if(trigger)
	 {
		lk.unlock();
		cv.notify_one();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		// you can add a fklag herethat the image is consumed
		lk.lock();
     }	
	}
 }
 
 
void
Webcam::
quit_handler( int sig )
{
	printf("\n");
	printf("TERMINATING AT USER REQUEST\n");
	printf("\n");
	if_terminate_capture = true; 
	//~ std::this_thread::sleep_for(std::chrono::milliseconds(200));	
	Stop();

	// end program here
	exit(0);

}

void
Webcam::
static_quit_handler(int signum)
{
    instance->quit_handler(signum);
}



