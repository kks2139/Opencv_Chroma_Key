#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>

using namespace cv;
using namespace std;

int main()
{
	Mat img, bg; // Chroma key

	img = imread("D:\\opencv\\sources\\doc\\girl.jpg");
	bg = imread("D:\\opencv\\sources\\doc\\bg.jpg");

	cvtColor(img, img, CV_BGR2YCrCb);
	cvtColor(bg, bg, CV_BGR2YCrCb);

	FILE *f;

	int Bsum = 0;
	int Rsum = 0;
	int Ysum = 0;
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 60; j++) {
			Bsum += img.at<Vec3b>(i, j)[1];
			Rsum += img.at<Vec3b>(i, j)[2];
		}
	}
	for (int i = 1; i < img.rows; i++) {
		for (int j = 1; j < img.cols; j++) {
			Ysum += img.at<Vec3b>(i, j)[0];
		}
	}
	Bsum /= 3600;
	Rsum /= 3600;
	Ysum /= (img.rows - 1)*(img.cols - 1);
	int BR = (Bsum + Rsum) / 2;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {

			//printf("%d  %d\n",img.at<Vec3b>(i, j)[1], img.at<Vec3b>(i, j)[2]);

			if (abs(BR - (img.at<Vec3b>(i, j)[1] + img.at<Vec3b>(i, j)[2])) < 110) {
				for (int k = 0; k < 3; k++) {
					img.at<Vec3b>(i, j)[k] = bg.at<Vec3b>(i, j)[k];
				}
			}
		}
	}
	printf("%d  %d\n", Bsum, Rsum);

	cvtColor(img, img, CV_YCrCb2BGR);
	imshow("Original", img);

	waitKey(0);
	return 0;

}