#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"

using namespace std;
using namespace cv;

Mat mask(Mat img)
{	
	Mat masked(img.rows,img.cols, CV_8UC1);
	Mat channel[3];

	split (img, channel);

	for(int i=0;i<img.rows;i++)
	{
		for(int j=0;j<img.cols;j++)
		{
			
			if(i%2==0 && (i+j)%2==1)
			{
				masked.at<uchar>(i,j) = channel[2].at<uchar>(i,j);
			} 
			if((i+j)%2==0)
			{
				masked.at<uchar>(i,j) = channel[1].at<uchar>(i,j);
			} 
			if(i%2==1 && (i+j)%2==1)
			{
				masked.at<uchar>(i,j) = channel[0].at<uchar>(i,j);
			}
		}
	}
	return masked;
}

Mat unmask(Mat img)
{
	Mat unmasked(img.rows, img.cols, CV_8UC3);

	for(int i=1;i<img.rows;i++)
	{
		for(int j=1;j<img.cols;j++)
		{	
			int color[3];
			if(i%2==0)
			{
				if((i+j)%2==1)
				{
					color[0] = img.at<uchar>(i,j);
					color[1] = img.at<uchar>(i+1,j)/4+img.at<uchar>(i,j+1)/4+img.at<uchar>(i-1,j)/4+img.at<uchar>(i,j-1)/4;
					color[2] = img.at<uchar>(i-1,j-1)/4+img.at<uchar>(i-1,j+1)/4+img.at<uchar>(i+1,j-1)/4+img.at<uchar>(i+1,j+1)/4;
				}
			}
			if(i%2==1)
			{
				if((i+j)%2==1)
				{
					color[2] = img.at<uchar>(i,j);
					color[1] = img.at<uchar>(i+1,j)/4+img.at<uchar>(i,j+1)/4+img.at<uchar>(i-1,j)/4+img.at<uchar>(i,j-1)/4;
					color[0] = img.at<uchar>(i-1,j-1)/4+img.at<uchar>(i-1,j+1)/4+img.at<uchar>(i+1,j-1)/4+img.at<uchar>(i+1,j+1)/4;
				}
			}
			unmasked.at<Vec3b>(i,j) = Vec3b(color[2],color[1],color[0]);
		}
	}
	return unmasked;
}

Mat detect(Mat img_o, Mat img, int multiplier, int threshold, bool erosion, bool dilation)
{
	cvtColor(img_o, img_o, CV_BGR2GRAY);
	cvtColor(img, img, CV_BGR2GRAY);
	
	img_o -= img;
	img_o *= multiplier;

	for(int i=0;i<img.rows;i++)
    {
        for(int j=0;j<img.cols;j++)
        {
            if(img_o.at<uchar>(i,j)<threshold)
            {
                img_o.at<uchar>(i,j)=0;
            }
            else
            {
             	img_o.at<uchar>(i,j)=255;   
            }
        }
    }

    if(erosion ==1)
    {
    	erode(img_o, img_o, 0, Point(-1, -1), 2, 1, 1);
    }
	if(dilation ==1)
    {
		 dilate(img_o, img_o, 0, Point(-1, -1), 2, 1, 1);
    }
	
	return img_o;
}

int main(int argc, char const *argv[])
{
	Mat img, img_o;

	img= imread(argv[1]);
	
	img_o = img;
	imshow("original image", img_o);

	img = mask(img);
	imshow("masked image", img);

	img = unmask(img);
	imshow("unmasked image", img);

	
    namedWindow("Control Window", 1);
  
    int multi = 15;
    createTrackbar("multiplier", "Control Window", &multi, 100);

    int thresh= 50;
    createTrackbar("threshold", "Control Window", &thresh, 255);

    int erods=1;
    createTrackbar("erode", "Control Window", &erods, 1);

    int dilates=1;
    createTrackbar("dilate", "Control Window", &dilates, 1);

	while(true)
	{
		Mat image;

		image = detect(img_o, img, multi, thresh, erods, dilates);
		imshow("edges", image);

		int iKey = waitKey(50);

    	if (iKey == 27)
    	{
        	break;
    	}

	}
	
	return 0;
}