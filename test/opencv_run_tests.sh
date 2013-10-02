#!/bin/bash
PATH_TO_PROJECT=~/nazar
OPEN_CV_NAME="opencv-2.4.5"
DYLD_PRINT_LIBRARIES="ON"
export "DYLD_PRINT_LIBRARIES"
OPENCV_TEST_DATA_PATH="$PATH_TO_PROJECT/test/opencv_test_data"
export "OPENCV_TEST_DATA_PATH"
cd "$PATH_TO_PROJECT/3rdparty/build/$OPEN_CV_NAME/bin/Debug"
pwd
env

./opencv_test_video
./opencv_test_calib3d
./opencv_test_contrib
./opencv_test_core
./opencv_test_features2d
./opencv_test_flann
./opencv_test_gpu
./opencv_test_highgui
./opencv_test_imgproc
./opencv_test_legacy
./opencv_test_ml
#./opencv_test_nonfree
./opencv_test_objdetect
./opencv_test_photo
./opencv_test_stitching
./opencv_test_superres
./opencv_perf_calib3d
./opencv_perf_core
./opencv_perf_features2d
./opencv_perf_gpu
./opencv_perf_highgui
./opencv_perf_imgproc
./opencv_perf_nonfree
./opencv_perf_objdetect
./opencv_perf_photo
./opencv_perf_stitching
./opencv_perf_superres
./opencv_perf_video
./opencv_performance

