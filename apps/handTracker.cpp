/***********************************************
This file is part of the Hand project (https://github.com/libicocco/Hand).

    Copyright(c) 2007-2011 Javier Romero
    * jrgn AT kth DOT se

    Hand is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Hand is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Hand.  If not, see <http://www.gnu.org/licenses/>.

**********************************************/
#include <boost/program_options.hpp>
#include "cPoseEstimator.h"
#include "cPoselistMulti.h"
#include "processFeat.h"
#include "feature.h"
#include "hog.h"
#include "nn.h"
#include "exactNN.h"
#include "approxNNflann.h"
#include "approxNNlshkit.h"

namespace po = boost::program_options;
int main(int argc,char* argv[])
{
  std::string lDBPath,lFeatPath,lIndexPath,lTestFolder,lTestPattern,lMetricPath,lNNChoice;
  unsigned lNNN,lDBsize,lFeatDim,lDimMetric;
  bool lTemporalSmoothing,lGUI;
  // Declare the supported options.
	std::cout << SCENEPATH << std::endl;
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "produce help message")
    ("dbpath,d", po::value<std::string>(&lDBPath)->default_value((std::string)SCENEPATH + (std::string)"/hands.db"),"Path to db file")
    ("nnalg,a", po::value<std::string>(&lNNChoice)->default_value("lsh"), "What algorithm to use for nearest neighbors")
    ("featpath,f", po::value<std::string>(&lFeatPath)->default_value((std::string)SCENEPATH + (std::string)"/hog.bin"),"Path to feature binary file")
    ("testfolder,t", po::value<std::string>(&lTestFolder)->default_value((std::string)SCENEPATH + (std::string)"/synthetic_test/test1/"),"Path to folder with test images")
    ("testpattern,p", po::value<std::string>(&lTestPattern)->default_value(".*.png"),"Test files common pattern")
    ("nnn,n", po::value<unsigned>(&lNNN)->default_value(16), "Number of NN to show")
    ("dbn", po::value<unsigned>(&lDBsize)->default_value(106920), "Number of db elements")
    ("fn", po::value<unsigned>(&lFeatDim)->default_value(512), "Dimensionality of the features")
    ("temporal", po::value<bool>(&lTemporalSmoothing)->default_value(true), "Should the temporal likelihood be used?")
    ("dimMetric", po::value<unsigned>(&lDimMetric)->default_value(0), "Dimensionality of the joint metric used")
    ("metric", po::value<std::string>(&lMetricPath)->default_value(""), "Matrix with features for different joint configurations (nnn x dimMetric)")
    ("gui", po::value<bool>(&lGUI)->default_value(true), "Should the results be shown in a GUI?")
    ;
  
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);    
  
  if (vm.count("help")) {
      std::cout << desc << "\n";
    return 1;
  }
  CPoselistMulti lPList(lDBPath,lTemporalSmoothing,lDimMetric,lMetricPath);
  nn<float> *lNNptr;
  if (lNNChoice == "lsh") {
    lFeatPath = LSH_BIN_PATH;
    lIndexPath = LSH_INDEX_PATH;
    lNNptr = new approxNNlshkit<float>(lNNN,lDBsize,lFeatDim,lFeatPath.c_str(), lIndexPath.c_str());
  } else if (lNNChoice == "flann"){
    lFeatPath = FLANN_BIN_PATH;
    lIndexPath = FLANN_INDEX_PATH;
    lNNptr = new approxNNflann<float>(lNNN,lDBsize,lFeatDim,lFeatPath.c_str(), lIndexPath.c_str());
  } else {
    lNNptr = new exactNN<float>(lNNN,lDBsize,lFeatDim,lFeatPath.c_str());
  }
  ProcessFeat<CPoselistMulti,float> lProcFeat(lNNptr,&lPList);
  Hog<float> lHog;
  Feature<float> *lFeat=&lHog;
  
  CPoseEstimator<CPoselistMulti,float> lTrackerHogExact(lFeat,&lProcFeat,lTestFolder,lTestPattern,lGUI);
  lTrackerHogExact.Run();
}
