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

#include "cDB.h"
#include "cDBelement.h"

int main(int argc, char** argv) {
	CDB db("/home/dama/thesis/code/Hand/handpose/scene/hands.db");
    CDBelement elem = db.query(1620);
    std::vector<float> v = elem.getFeature();
    for (int i = 0; i < v.size(); ++i) {
        printf("%.4f ", v[i]);
    }

    return 0;
}
