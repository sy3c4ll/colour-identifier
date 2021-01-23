#include<opencv2/opencv.hpp>
#include<iostream>
#define SCREEN1 "Image"
#define SCREEN2 "Thresholded"
using namespace cv;
Mat img,text;
int range[3][2]={{179,0},{255,0},{255,0}};
static void onMouse(int event,int x,int y,int f,void*){
    char str[]="";
    text=Mat::zeros(img.size(),CV_8UC3);
    if(event==EVENT_LBUTTONDOWN){
        Mat imgHSV;
        cvtColor(img,imgHSV,COLOR_BGR2HSV);
        Vec3b p=imgHSV.at<Vec3b>(y,x);
        if(p[0]<range[0][0])range[0][0]=p[0];
        if(p[0]>range[0][1])range[0][1]=p[0];
        if(p[1]<range[1][0])range[1][0]=p[1];
        if(p[1]>range[1][1])range[1][1]=p[1];
        if(p[2]<range[2][0])range[2][0]=p[2];
        if(p[2]>range[2][1])range[2][1]=p[2];
        sprintf(str,"H=%d, S=%d, V=%d",p[0],p[1],p[2]);
        fprintf(stdout,"%3d<=H<=%3d, %3d<=S<=%3d, %3d<=V<=%3d\n",range[0][0],range[0][1],range[1][0],range[1][1],range[2][0],range[2][1]);
    }else sprintf(str,"x=%d, y=%d",x,y);
    putText(text,str,Point(x,y),FONT_HERSHEY_PLAIN,1.0,Scalar(255,255,255,0));
}
int main(){
    VideoCapture cap(0);
    Mat imgHSV,imgThres;
    if(!cap.isOpened())exit(-1);
    namedWindow(SCREEN1);
    namedWindow(SCREEN2);
    setMouseCallback(SCREEN1,onMouse,0);
    if(!cap.read(img))exit(-1);
    text=Mat::zeros(img.size(),CV_8UC3);
    for(;;){
        if(!cap.read(img))exit(-1);
        imshow(SCREEN1,img+text);
        cvtColor(img,imgHSV,COLOR_BGR2HSV);
        inRange(imgHSV,Scalar(range[0][0],range[1][0],range[2][0]),Scalar(range[0][1],range[1][1],range[2][1]),imgThres);
        imshow(SCREEN2,imgThres);
        if(waitKey(1)=='q')break;
    }
    return 0;
}
