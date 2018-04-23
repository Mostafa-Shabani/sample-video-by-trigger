#ifndef WEBCAM_H_
#define WEBCAM_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

static void PressEnterToContinue()
{
  std::cout << "Press ENTER to continue... " << std::flush;
  std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
}

enum trigger_method
{
	TRIGGER_BY_FIXED_TIME_INTERVAL=1,
	TRIGGER_BY_USER_DEFINED_METHOD=2,
};
class Webcam
{
	private:
		std::thread t;
		std::atomic_flag flag= ATOMIC_FLAG_INIT;
		bool if_terminate_capture;
        std::string portName;
		cv::VideoCapture capture;
		static Webcam* instance;

	public:
		Webcam();
		void Initialise();
		void Start();
		void Stop();
		void Finalise();
		void getImage(cv::Mat&);
        void lookForCamTrig(std::mutex&, std::condition_variable&, trigger_method, bool&);
		static void static_quit_handler( int);
		void quit_handler (int);
        

};


  
  
  #endif //WEBCAM_H_
