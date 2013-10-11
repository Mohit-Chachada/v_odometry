#include <iostream>
#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "mono_odometry.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    // class input parameters - feature options
    MonoVisualOdometry::parameters param;
    param.option.feature=4;
    param.option.extract=2;
    param.option.match=1;
    param.option.outlier=1;
    param.option.solver=1; 
    
    // call image from ROS
    Mat frame_old,frame;
    frame_old=imread("1.png"); // for testing
    frame=imread("2.png"); // for testing
    
    if(frame_old.empty() || frame.empty())
    {
        cout<<"Can't read one of the images\n";
        return -1;
    }
    
    MonoVisualOdometry odom(param);               
    odom.nframes=1; // keeps track of overall frames count
//    odom.nframes=0; // shud be intitialised with =0; for testing =1;
    
//    while(!flag){	//actual
    for(int i=0 ;i<1 ;i++ ){	// for(;;) testing
	// get new frame from ROS
        //cin>>frame;  
        odom.nframes++;

        if(odom.nframes>=2) {
  	  // run odometry
  	  odom.img1=frame_old;
  	  odom.img2=frame;
   	  odom.run(); 	// run the main odometry calculations
   	  MonoVisualOdometry::pose position; //output struct
	  odom.output(position);  // get output parameters
	  cout<<position.N<<"\n"; // no of good_matches
	  cout<<position.x_net<<"\n"; // net x-translation
	  cout<<position.y_net<<"\n"; // net y-translation
	  cout<<position.heading_net<<"\n"; // net heading
	  cout<<position.Z_avg1<<"\n"; // avg Z estimation 1
	  cout<<position.Z_avg2<<"\n"; // avg Z estimation 2
	  cout<<position.iteration<<"\n"; // no of solver iterations
  	  cout<<position.run_time<<"\n"; // .run() time
    	}
	
	//copy the frame to frame_old
	frame_old=frame.clone();    	
    }
    
    // ROS Plot x_net, y_net, heading_net wrt time
    
    return 0;
}