#include <iostream>
#include <thread>
#include <memory>
#include <csignal>
#include "Webcam.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <sys/stat.h>



int main(int argc, const char *argv[])
{
	cv::Mat frame;
	std::mutex m;
	std::condition_variable cv;
	bool session_active(true);
	
	trigger_method tmethod=TRIGGER_BY_USER_DEFINED_METHOD;
	//~ trigger_method tmethod=TRIGGER_BY_FIXED_TIME_INTERVAL;
	
	std::unique_ptr<Webcam> webcam(new Webcam());
	signal(SIGINT,webcam->static_quit_handler);
	
	webcam->Start();
	std::thread td_trig([&](){
							  
								webcam->lookForCamTrig(m, cv, tmethod, session_active);

							 });
	
	int i = 0;
	std::unique_lock<std::mutex> lk(m);
	while(session_active)
	{
		std::stringstream ss;
        ss<<"Image"<<i<<".jpg";
        std::string cur_img_filename=ss.str();
        std::cout<<"waiting for trigger ..."<<std::endl;
		cv.wait(lk);
		
		webcam->getImage(frame);
		if(!frame.empty())
		{
            
            // do image processing			
			cv::imwrite(cur_img_filename,frame);
		}
		
		
		
		std::cout<<"image num "<<i<<" captured"<<std::endl;
		
		++i;
        
        // limit the number of images to 5:
		if(i>5) session_active=false;
		lk.unlock();
		cv.notify_one();
		lk.lock();

	}
	lk.unlock();
	td_trig.join();
	webcam->Stop();

    return 1;
}
