#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <iomanip>
#include <queue>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "chandtracker.h"
#include "feature.h"
#include "hog.h"
#include "processFeat.h"
#include "approxNNflann.h"
#include "cTemporalFilter.h"
#include "cPoselistMulti.h"

#include "handclass_config.h"
#include "typeDefinitions.h"

int main(int argc, char** argv) {
	std::vector<float> hogvals;
    cv::Mat img;
	std::pair<cv::Mat, cv::Mat> matAndMask;
	if (!boost::filesystem::exists(argv[1])) {
		exit(1);
	}
	boost::regex re("png");
	boost::filesystem::path p(argv[1]);
	std::cout << p << std::endl;
	boost::filesystem::recursive_directory_iterator end_itr;
	FILE* f = fopen("hog3.txt", "w");
	std::vector<std::string> v;
	for (boost::filesystem::recursive_directory_iterator it(p);
		 it != end_itr;
		 ++it) {
		 std::string s = it->path().string();
		 if (boost::regex_search(s, re)) {
			 v.push_back(s);
		 }
	}
	std::cout << "Size: " << v.size() << "\n";
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); ++i) {
		 img = cv::imread(v[i]);
		 std::cout << v[i] << std::endl;
         CHandTracker tracker;

         if (std::string(argv[2]) == "extract") {
             cv::Mat gray(img.size(),CV_8UC1);
             cv::Mat initgray(img.size(), CV_8UC1);
             cv::Mat c4(img.size(),CV_32FC3);
             img.convertTo(c4,CV_32FC3);
             cv::cvtColor(img,gray,CV_BGR2GRAY);
             cv::cvtColor(img,initgray, CV_BGR2GRAY);
             //cv::imshow("gray", gray);
             cv::threshold(gray, gray, 40, 255, cv::THRESH_TOZERO);
             cv::threshold(gray,gray,244,255,cv::THRESH_TOZERO_INV);

             //cv::imshow("threshold", gray);

             // compute contours to localize the hand
             std::vector<cv::Point> lAllContours;
             {
                 std::vector<std::vector<cv::Point> > lContours;
                 cv::Mat lTmp = gray.clone();
                 cv::findContours(lTmp, lContours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
                 for(int i=0;i<lContours.size();++i)
                     lAllContours.insert(lAllContours.end(),lContours[i].begin(),lContours[i].end());
             }

             // exit if there's no hand pixel; it would fail with a weird error when computing the hog
             if(lAllContours.empty())
             {
                 std::cerr << "There is no hand in the figure" << std::endl << 
                     "Run it again (to randomize the view point) or change the rendering parameters" << std::endl;
                 exit(1);
             }

             cv::Rect lBBox=cv::boundingRect(cv::Mat(lAllContours));
             cv::threshold(initgray, initgray, 244, 255, cv::THRESH_TOZERO_INV);
             initgray = (initgray > 0);
             //cv::imshow("initgray", initgray);
             std::pair<cv::Mat,cv::Mat> lTstMaskCrop=std::make_pair(c4(lBBox),initgray(lBBox));
             //cv::imshow("lbbox", c4(lBBox));
             Hog<float> hog;
             hogvals = hog.compute(lTstMaskCrop,99999999);

             cv::rectangle(img, lBBox.tl(), lBBox.br(), cv::Scalar(255, 0, 0));
             //cv::imshow("title", img);
             cv::waitKey();
         } else if (std::string(argv[2]) == "gethand") {
            cv::Rect rect = tracker.getHand(img, matAndMask);
            cv::rectangle(img, rect.tl(), rect.br(), cv::Scalar(255, 0, 0));
            cv::imshow("title", img);
            cv::waitKey();
            Hog<float> hog;
            hogvals = hog.compute(matAndMask, INVPROBDEFAULT);
         }
		 for (int i = 0; i < hogvals.size(); ++i) {
			 fprintf(f, "\t%.04f", hogvals[i]);
		 }
		 fprintf(f, "\n");
	}
		return 0;
}
