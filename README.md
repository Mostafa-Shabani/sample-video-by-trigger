# sample-video-by-trigger
Using openCV in C++: Capturing images from a video stream once a trigger is activated 

webcam::lookForCamTrig is called within a thread and looks for a trigger to capture images from the video stream
This function plays a wait and notify game with the main function. 
The user can change the Webcam::lookForCamTrig function to implement a certain triggering method. Current implementation either captures on a fixed time interval basis or waits for the Return key to be pressed. 


## Prerequisites
Requires OpenCV 2.4.13 To use with OpenCV 3.x.x some changes should be done according to https://docs.opencv.org/3.2.0/db/dfa/tutorial_transition_guide.html

## Usage
cd [directory]

mkdir build

make

./build/Webcam_unit_test

## Contributing
1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D
## History

## Credits

## License
This project is licensed under the MIT License
