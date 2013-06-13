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
	cv::Mat img;
	std::pair<cv::Mat, cv::Mat> matAndMask;
	if (!boost::filesystem::exists(argv[1])) {
		exit(1);
	}
	boost::regex re("png");
	boost::filesystem::path p(argv[1]);
	std::cout << p << std::endl;
	boost::filesystem::recursive_directory_iterator end_itr;
	FILE* f = fopen("hog2.txt", "w");
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
		 tracker.getHand(img, matAndMask);
		 Hog<float> hog;
		 std::vector<float> v = hog.compute(matAndMask, INVPROBDEFAULT);
		 for (int i = 0; i < v.size(); ++i) {
			 fprintf(f, "\t%.04f", v[i]);
		 }
		 fprintf(f, "\n");
	}
		return 0;
}
