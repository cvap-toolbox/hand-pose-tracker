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
#include <iostream>
#include <boost/timer.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/numeric/functional/vector.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/framework/features.hpp>
#include <boost/accumulators/statistics/weighted_sum.hpp>
#include <boost/accumulators/statistics/weighted_mean.hpp>
#include <boost/accumulators/statistics/weighted_variance.hpp>
#include <boost/accumulators/statistics/min.hpp>

//#include <Eigen/Dense>
#include <eigen3/Eigen/Dense>
#include "cPose.h"
#include "cDB.h"
#include "cTemporalFilter.h"
#include "constants.h"

std::ostream& operator << ( std::ostream& pOut, const CTemporalFilter& pTempF)
{
  const tPoseVP& lPlist = pTempF.mPoseList; 
  for(auto it=lPlist.begin();it!=lPlist.end();++it)
    pOut<<*it<<"\n";
  pOut << std::endl;
  return pOut;
}

const tPoseV& CTemporalFilter::interpolatePoses(const tPairV &lNNDist)
{
   //std::cout << lNNDist.size() << std::endl;
//   std::cout << mWPose << std::endl << std::endl;
  if(lNNDist.empty())
  {
    mWPose.setZero();
    throw EMPTYPOSELISTERROR;
  }
  reset(lNNDist);
  setWeights();
  computeWeightedPose();
  mPoseList.sort(cmpW);
  if(mPoseList.size()>MAXINFLUENCENN)
    reduceNNN(MAXINFLUENCENN);
  saveBestPoses();
  if(mPoseList.empty())
  {
    mWPose.setZero();
    throw EMPTYPOSELISTERROR;
  }
  mPoseW=(mPoseList.front().getWeight() < 0.05)?0.3:0.7;
  mWPose =  mPoseList.front().getPose(); // CONSIDERING BEST POSE AS WPOSE!!!
  return mWPose;
}

int CTemporalFilter::reset(const tPairV& pNNlist)
{
  mAccFeatD = tAcc_MinVar(); // clean acc
  mAccPoseD = tAcc_MinVar(); // clean acc
  mPoseList.clear(); // I assume this deletes the poses.
  tPairV::const_iterator itrpair;
  for(itrpair=pNNlist.begin();itrpair!=pNNlist.end();++itrpair) {
	//std::cout << "The index from the pnnlist: " << itrpair->first << std::endl;
    mPoseList.push_back(new CPose(*itrpair,mAccFeatD,mWPose,mAccPoseD,mDB));
  }
  return pNNlist.size();
}

void CTemporalFilter::computeWeightedPose()
{
  mWPose.setZero();
  for(auto itr=mPoseList.begin();itr!=mPoseList.end();++itr)
    mWPose+=(itr->getPose())*(itr->getWeight());
  mWPose/=mPoseList.size();
  //mPoseList.sort(cmpW);
}

void CTemporalFilter::reduceNNN(size_t pNNN)
{
  if(pNNN>mPoseList.size())
    return;
  //mPoseList.sort(cmpW);
  auto itr=mPoseList.begin();
  advance(itr,pNNN);
  mPoseList.erase(itr,mPoseList.end());
  
  mWPose.setZero();
  for(auto itr=mPoseList.begin();itr!=mPoseList.end();++itr)
    mWPose+=itr->getPose()*itr->getWeight();
  mWPose/=mPoseList.size();
}
