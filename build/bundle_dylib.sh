#!/bin/bash
PATH_TO_PROJECT=~/nazar
cd "$PATH_TO_PROJECT/lib"

install_name_tool -id "@executable_path/lib/libopencv_calib3d.dylib" ./libopencv_calib3d.dylib
install_name_tool -id "@executable_path/lib/libopencv_contrib.dylib" ./libopencv_contrib.dylib
install_name_tool -id "@executable_path/lib/libopencv_core.dylib" ./libopencv_core.dylib
install_name_tool -id "@executable_path/lib/libopencv_features2d.dylib" ./libopencv_features2d.dylib
install_name_tool -id "@executable_path/lib/libopencv_flann.dylib" ./libopencv_flann.dylib
install_name_tool -id "@executable_path/lib/libopencv_gpu.dylib" ./libopencv_gpu.dylib
install_name_tool -id "@executable_path/lib/libopencv_highgui.dylib" ./libopencv_highgui.dylib
install_name_tool -id "@executable_path/lib/libopencv_imgproc.dylib" ./libopencv_imgproc.dylib
install_name_tool -id "@executable_path/lib/libopencv_legacy.dylib" ./libopencv_legacy.dylib
install_name_tool -id "@executable_path/lib/libopencv_ml.dylib" ./libopencv_ml.dylib
install_name_tool -id "@executable_path/lib/libopencv_nonfree.dylib" ./libopencv_nonfree.dylib
install_name_tool -id "@executable_path/lib/libopencv_objdetect.dylib" ./libopencv_objdetect.dylib
install_name_tool -id "@executable_path/lib/libopencv_photo.dylib" ./libopencv_photo.dylib
install_name_tool -id "@executable_path/lib/libopencv_stitching.dylib" ./libopencv_stitching.dylib
install_name_tool -id "@executable_path/lib/libopencv_superres.dylib" ./libopencv_superres.dylib
install_name_tool -id "@executable_path/lib/libopencv_ts.dylib" ./libopencv_ts.dylib
install_name_tool -id "@executable_path/lib/libopencv_video.dylib" ./libopencv_video.dylib
install_name_tool -id "@executable_path/lib/libopencv_videostab.dylib" ./libopencv_videostab.dylib


install_name_tool -id @executable_path/lib/libopencv_cuda.dylib ./libopencv_cuda.dylib
install_name_tool -id @executable_path/lib/libopencv_cudaarithm.dylib ./libopencv_cudaarithm.dylib
install_name_tool -id @executable_path/lib/libopencv_cudabgsegm.dylib ./libopencv_cudabgsegm.dylib
install_name_tool -id @executable_path/lib/libopencv_cudafeatures2d.dylib ./libopencv_cudafeatures2d.dylib
install_name_tool -id @executable_path/lib/libopencv_cudafilters.dylib ./libopencv_cudafilters.dylib
install_name_tool -id @executable_path/lib/libopencv_cudaimgproc.dylib ./libopencv_cudaimgproc.dylib
install_name_tool -id @executable_path/lib/libopencv_cudaoptflow.dylib ./libopencv_cudaoptflow.dylib
install_name_tool -id @executable_path/lib/libopencv_cudastereo.dylib ./libopencv_cudastereo.dylib
install_name_tool -id @executable_path/lib/libopencv_cudawarping.dylib ./libopencv_cudawarping.dylib
install_name_tool -id @executable_path/lib/libopencv_ocl.dylib ./libopencv_ocl.dylib
install_name_tool -id @executable_path/lib/libopencv_optim.dylib ./libopencv_optim.dylib
install_name_tool -id @executable_path/lib/libopencv_softcascade.dylib ./libopencv_softcascade.dylib


install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_core.dylib

#libopencv_nonfree.dylib:
#	@executable_path/lib/libopencv_nonfree.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_nonfree.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_nonfree.dylib
install_name_tool -change lib/libopencv_flann.dylib @executable_path/lib/libopencv_flann.dylib libopencv_nonfree.dylib
install_name_tool -change lib/libopencv_highgui.dylib @executable_path/lib/libopencv_highgui.dylib libopencv_nonfree.dylib
install_name_tool -change lib/libopencv_features2d.dylib @executable_path/lib/libopencv_features2d.dylib libopencv_nonfree.dylib
install_name_tool -change lib/libopencv_calib3d.dylib @executable_path/lib/libopencv_calib3d.dylib libopencv_nonfree.dylib
install_name_tool -change lib/libopencv_objdetect.dylib @executable_path/lib/libopencv_objdetect.dylib libopencv_nonfree.dylib
install_name_tool -change lib/libopencv_video.dylib @executable_path/lib/libopencv_video.dylib libopencv_nonfree.dylib
install_name_tool -change lib/libopencv_photo.dylib @executable_path/lib/libopencv_photo.dylib libopencv_nonfree.dylib
install_name_tool -change lib/libopencv_ml.dylib @executable_path/lib/libopencv_ml.dylib libopencv_nonfree.dylib
install_name_tool -change lib/libopencv_legacy.dylib @executable_path/lib/libopencv_legacy.dylib libopencv_nonfree.dylib
install_name_tool -change lib/libopencv_gpu.dylib @executable_path/lib/libopencv_gpu.dylib libopencv_nonfree.dylib 
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_nonfree.dylib
install_name_tool -change lib/libopencv_cudaarithm.dylib  @executable_path/lib/libopencv_cudaarithm.dylib libopencv_nonfree.dylib
install_name_tool -change lib/libopencv_ocl.dylib @executable_path/lib/libopencv_ocl.dylib libopencv_nonfree.dylib


#libopencv_contrib.dylib
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_contrib.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_contrib.dylib
install_name_tool -change lib/libopencv_flann.dylib @executable_path/lib/libopencv_flann.dylib libopencv_contrib.dylib
install_name_tool -change lib/libopencv_highgui.dylib @executable_path/lib/libopencv_highgui.dylib libopencv_contrib.dylib
install_name_tool -change lib/libopencv_features2d.dylib @executable_path/lib/libopencv_features2d.dylib libopencv_contrib.dylib
install_name_tool -change lib/libopencv_calib3d.dylib @executable_path/lib/libopencv_calib3d.dylib libopencv_contrib.dylib
install_name_tool -change lib/libopencv_ml.dylib @executable_path/lib/libopencv_ml.dylib libopencv_contrib.dylib
install_name_tool -change lib/libopencv_video.dylib @executable_path/lib/libopencv_video.dylib libopencv_contrib.dylib
install_name_tool -change lib/libopencv_objdetect.dylib @executable_path/lib/libopencv_objdetect.dylib libopencv_contrib.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_contrib.dylib

#libopencv_calib3d.dylib:
#	@rpath/lib/libopencv_calib3d.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_calib3d.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_calib3d.dylib
install_name_tool -change lib/libopencv_flann.dylib @executable_path/lib/libopencv_flann.dylib libopencv_calib3d.dylib
install_name_tool -change lib/libopencv_highgui.dylib @executable_path/lib/libopencv_highgui.dylib libopencv_calib3d.dylib
install_name_tool -change lib/libopencv_features2d.dylib @executable_path/lib/libopencv_features2d.dylib libopencv_calib3d.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_calib3d.dylib

#libopencv_features2d.dylib:
#	@rpath/lib/libopencv_features2d.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_features2d.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_features2d.dylib
install_name_tool -change lib/libopencv_flann.dylib @executable_path/lib/libopencv_flann.dylib libopencv_features2d.dylib
install_name_tool -change lib/libopencv_highgui.dylib @executable_path/lib/libopencv_highgui.dylib libopencv_features2d.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_features2d.dylib
#libopencv_flann.dylib:#
#	@rpath/lib/libopencv_flann.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_flann.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_flann.dylib

#libopencv_gpu.dylib:
#	@rpath/lib/libopencv_gpu.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_gpu.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_gpu.dylib
install_name_tool -change lib/libopencv_flann.dylib @executable_path/lib/libopencv_flann.dylib libopencv_gpu.dylib
install_name_tool -change lib/libopencv_highgui.dylib @executable_path/lib/libopencv_highgui.dylib libopencv_gpu.dylib
install_name_tool -change lib/libopencv_features2d.dylib @executable_path/lib/libopencv_features2d.dylib libopencv_gpu.dylib
install_name_tool -change lib/libopencv_calib3d.dylib @executable_path/lib/libopencv_calib3d.dylib libopencv_gpu.dylib
install_name_tool -change lib/libopencv_objdetect.dylib @executable_path/lib/libopencv_objdetect.dylib libopencv_gpu.dylib
install_name_tool -change lib/libopencv_video.dylib @executable_path/lib/libopencv_video.dylib libopencv_gpu.dylib
install_name_tool -change lib/libopencv_photo.dylib @executable_path/lib/libopencv_photo.dylib libopencv_gpu.dylib
install_name_tool -change lib/libopencv_ml.dylib @executable_path/lib/libopencv_ml.dylib libopencv_gpu.dylib
install_name_tool -change lib/libopencv_legacy.dylib @executable_path/lib/libopencv_legacy.dylib libopencv_gpu.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_gpu.dylib

#libopencv_highgui.dylib:
#	@rpath/lib/libopencv_highgui.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_highgui.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_highgui.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_highgui.dylib

#libopencv_imgproc.dylib:
#	@rpath/lib/libopencv_imgproc.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_imgproc.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_imgproc.dylib

#libopencv_legacy.dylib:
#	@rpath/lib/libopencv_legacy.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_legacy.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_legacy.dylib
install_name_tool -change lib/libopencv_flann.dylib @executable_path/lib/libopencv_flann.dylib libopencv_legacy.dylib
install_name_tool -change lib/libopencv_highgui.dylib @executable_path/lib/libopencv_highgui.dylib libopencv_legacy.dylib
install_name_tool -change lib/libopencv_features2d.dylib @executable_path/lib/libopencv_features2d.dylib libopencv_legacy.dylib
install_name_tool -change lib/libopencv_calib3d.dylib @executable_path/lib/libopencv_calib3d.dylib libopencv_legacy.dylib
install_name_tool -change lib/libopencv_video.dylib @executable_path/lib/libopencv_video.dylib libopencv_legacy.dylib
install_name_tool -change lib/libopencv_ml.dylib @executable_path/lib/libopencv_ml.dylib libopencv_legacy.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_legacy.dylib

#libopencv_ml.dylib:
#	@rpath/lib/libopencv_ml.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_ml.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_ml.dylib

#libopencv_objdetect.dylib:
#	@rpath/lib/libopencv_objdetect.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_objdetect.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_objdetect.dylib
install_name_tool -change lib/libopencv_highgui.dylib @executable_path/lib/libopencv_highgui.dylib libopencv_objdetect.dylib
install_name_tool -change lib/libopencv_ml.dylib @executable_path/lib/libopencv_ml.dylib libopencv_objdetect.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_objdetect.dylib

#libopencv_photo.dylib:
#	@rpath/lib/libopencv_photo.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_photo.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_photo.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_photo.dylib
install_name_tool -change lib/libopencv_cudaarithm.dylib @executable_path/lib/libopencv_cudaarithm.dylib libopencv_photo.dylib 
install_name_tool -change lib/libopencv_cudafilters.dylib @executable_path/lib/libopencv_cudafilters.dylib libopencv_photo.dylib
install_name_tool -change lib/libopencv_cudaimgproc.dylib @executable_path/lib/libopencv_cudaimgproc.dylib libopencv_photo.dylib

#libopencv_stitching.dylib:
#	@rpath/lib/libopencv_stitching.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_stitching.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_stitching.dylib
install_name_tool -change lib/libopencv_flann.dylib @executable_path/lib/libopencv_flann.dylib libopencv_stitching.dylib
install_name_tool -change lib/libopencv_highgui.dylib @executable_path/lib/libopencv_highgui.dylib libopencv_stitching.dylib
install_name_tool -change lib/libopencv_features2d.dylib @executable_path/lib/libopencv_features2d.dylib libopencv_stitching.dylib
install_name_tool -change lib/libopencv_calib3d.dylib @executable_path/lib/libopencv_calib3d.dylib libopencv_stitching.dylib
install_name_tool -change lib/libopencv_objdetect.dylib @executable_path/lib/libopencv_objdetect.dylib libopencv_stitching.dylib
install_name_tool -change lib/libopencv_video.dylib @executable_path/lib/libopencv_video.dylib libopencv_stitching.dylib
install_name_tool -change lib/libopencv_photo.dylib @executable_path/lib/libopencv_photo.dylib libopencv_stitching.dylib
install_name_tool -change lib/libopencv_ml.dylib @executable_path/lib/libopencv_ml.dylib libopencv_stitching.dylib
install_name_tool -change lib/libopencv_legacy.dylib @executable_path/lib/libopencv_legacy.dylib libopencv_stitching.dylib
install_name_tool -change lib/libopencv_gpu.dylib @executable_path/lib/libopencv_gpu.dylib libopencv_stitching.dylib
install_name_tool -change lib/libopencv_nonfree.dylib @executable_path/lib/libopencv_nonfree.dylib libopencv_stitching.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_stitching.dylib
install_name_tool -change lib/libopencv_cudaarithm.dylib @executable_path/lib/libopencv_cudaarithm.dylib libopencv_stitching.dylib 
install_name_tool -change lib/libopencv_cudawarping.dylib @executable_path/lib/libopencv_cudawarping.dylib libopencv_stitching.dylib 
install_name_tool -change lib/libopencv_cuda.dylib @executable_path/lib/libopencv_cuda.dylib libopencv_stitching.dylib 
install_name_tool -change lib/libopencv_cudafilters.dylib @executable_path/lib/libopencv_cudafilters.dylib libopencv_stitching.dylib 
install_name_tool -change lib/libopencv_cudafeatures2d.dylib @executable_path/lib/libopencv_cudafeatures2d.dylib libopencv_stitching.dylib 
install_name_tool -change lib/libopencv_ocl.dylib @executable_path/lib/libopencv_ocl.dylib libopencv_stitching.dylib 



#libopencv_superres.dylib:
#	@rpath/lib/libopencv_superres.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_superres.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_superres.dylib
install_name_tool -change lib/libopencv_video.dylib @executable_path/lib/libopencv_video.dylib libopencv_superres.dylib
install_name_tool -change lib/libopencv_flann.dylib @executable_path/lib/libopencv_flann.dylib libopencv_superres.dylib
install_name_tool -change lib/libopencv_highgui.dylib @executable_path/lib/libopencv_highgui.dylib libopencv_superres.dylib
install_name_tool -change lib/libopencv_features2d.dylib @executable_path/lib/libopencv_features2d.dylib libopencv_superres.dylib
install_name_tool -change lib/libopencv_calib3d.dylib @executable_path/lib/libopencv_calib3d.dylib libopencv_superres.dylib
install_name_tool -change lib/libopencv_objdetect.dylib @executable_path/lib/libopencv_objdetect.dylib libopencv_superres.dylib
install_name_tool -change lib/libopencv_photo.dylib @executable_path/lib/libopencv_photo.dylib libopencv_superres.dylib
install_name_tool -change lib/libopencv_ml.dylib @executable_path/lib/libopencv_ml.dylib libopencv_superres.dylib
install_name_tool -change lib/libopencv_legacy.dylib @executable_path/lib/libopencv_legacy.dylib libopencv_superres.dylib
install_name_tool -change lib/libopencv_gpu.dylib @executable_path/lib/libopencv_gpu.dylib libopencv_superres.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_superres.dylib
install_name_tool -change lib/libopencv_ocl.dylib  @executable_path/lib/libopencv_ocl.dylib libopencv_superres.dylib 
install_name_tool -change lib/libopencv_cudaarithm.dylib  @executable_path/lib/libopencv_cudaarithm.dylib libopencv_superres.dylib 
install_name_tool -change lib/libopencv_cudafilters.dylib  @executable_path/lib/libopencv_cudafilters.dylib libopencv_superres.dylib 
install_name_tool -change lib/libopencv_cudawarping.dylib  @executable_path/lib/libopencv_cudawarping.dylib libopencv_superres.dylib 
install_name_tool -change lib/libopencv_cudaimgproc.dylib  @executable_path/lib/libopencv_cudaimgproc.dylib libopencv_superres.dylib 
install_name_tool -change lib/libopencv_cudaoptflow.dylib  @executable_path/lib/libopencv_cudaoptflow.dylib libopencv_superres.dylib 

#libopencv_ts.dylib:
#	@rpath/lib/libopencv_ts.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_ts.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_ts.dylib
install_name_tool -change lib/libopencv_flann.dylib @executable_path/lib/libopencv_flann.dylib libopencv_ts.dylib
install_name_tool -change lib/libopencv_highgui.dylib @executable_path/lib/libopencv_highgui.dylib libopencv_ts.dylib
install_name_tool -change lib/libopencv_features2d.dylib @executable_path/lib/libopencv_features2d.dylib libopencv_ts.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_ts.dylib

#libopencv_video.dylib:
#	@rpath/lib/libopencv_video.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_video.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_video.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_video.dylib

#libopencv_videostab.dylib:
#	@rpath/lib/libopencv_videostab.dylib (compatibility version 2.4.0, current version 2.4.6)
install_name_tool -change lib/libopencv_core.dylib @executable_path/lib/libopencv_core.dylib libopencv_videostab.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_videostab.dylib
install_name_tool -change lib/libopencv_flann.dylib @executable_path/lib/libopencv_flann.dylib libopencv_videostab.dylib
install_name_tool -change lib/libopencv_highgui.dylib @executable_path/lib/libopencv_highgui.dylib libopencv_videostab.dylib
install_name_tool -change lib/libopencv_features2d.dylib @executable_path/lib/libopencv_features2d.dylib libopencv_videostab.dylib
install_name_tool -change lib/libopencv_video.dylib @executable_path/lib/libopencv_video.dylib libopencv_videostab.dylib
install_name_tool -change lib/libopencv_photo.dylib @executable_path/lib/libopencv_photo.dylib libopencv_videostab.dylib
install_name_tool -change lib/libopencv_calib3d.dylib @executable_path/lib/libopencv_calib3d.dylib libopencv_videostab.dylib
install_name_tool -change lib/libopencv_objdetect.dylib @executable_path/lib/libopencv_objdetect.dylib libopencv_videostab.dylib
install_name_tool -change lib/libopencv_ml.dylib @executable_path/lib/libopencv_ml.dylib libopencv_videostab.dylib
install_name_tool -change lib/libopencv_legacy.dylib @executable_path/lib/libopencv_legacy.dylib libopencv_videostab.dylib
install_name_tool -change lib/libopencv_gpu.dylib @executable_path/lib/libopencv_gpu.dylib libopencv_videostab.dylib
install_name_tool -change libtbb.dylib @executable_path/lib/libtbb.dylib libopencv_videostab.dylib
install_name_tool -change lib/libopencv_cudaarithm.dylib @executable_path/lib/libopencv_cudaarithm.dylib  libopencv_videostab.dylib
install_name_tool -change lib/libopencv_cudafilters.dylib @executable_path/lib/libopencv_cudafilters.dylib libopencv_videostab.dylib 
install_name_tool -change lib/libopencv_cudaimgproc.dylib @executable_path/lib/libopencv_cudaimgproc.dylib libopencv_videostab.dylib 
install_name_tool -change lib/libopencv_cudawarping.dylib @executable_path/lib/libopencv_cudawarping.dylib libopencv_videostab.dylib 
install_name_tool -change lib/libopencv_cuda.dylib @executable_path/lib/libopencv_cuda.dylib libopencv_videostab.dylib 
install_name_tool -change lib/libopencv_cudaoptflow.dylib @executable_path/lib/libopencv_cudaoptflow.dylib libopencv_videostab.dylib 


#libopencv_cuda.dylib:
#	@executable_path/lib/libopencv_cuda.dylib (compatibility version 3.0.0, current version 3.0.0)
install_name_tool -change lib/libopencv_core.dylib  @executable_path/lib/libopencv_core.dylib libopencv_cuda.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_cuda.dylib
install_name_tool -change lib/libopencv_flann.dylib @executable_path/lib/libopencv_flann.dylib libopencv_cuda.dylib
install_name_tool -change lib/libopencv_highgui.dylib  @executable_path/lib/libopencv_highgui.dylib libopencv_cuda.dylib
install_name_tool -change lib/libopencv_features2d.dylib  @executable_path/lib/libopencv_features2d.dylib libopencv_cuda.dylib
install_name_tool -change lib/libopencv_calib3d.dylib  @executable_path/lib/libopencv_calib3d.dylib libopencv_cuda.dylib 
install_name_tool -change lib/libopencv_ml.dylib @executable_path/lib/libopencv_ml.dylib libopencv_cuda.dylib 
install_name_tool -change lib/libopencv_objdetect.dylib  @executable_path/lib/libopencv_objdetect.dylib libopencv_cuda.dylib 
install_name_tool -change lib/libopencv_cudaarithm.dylib  @executable_path/lib/libopencv_cudaarithm.dylib libopencv_cuda.dylib
install_name_tool -change lib/libopencv_cudawarping.dylib @executable_path/lib/libopencv_cudawarping.dylib libopencv_cuda.dylib

#libopencv_cudaarithm.dylib:
#	@executable_path/lib/libopencv_cudaarithm.dylib (compatibility version 3.0.0, current version 3.0.0)
install_name_tool -change lib/libopencv_core.dylib  @executable_path/lib/libopencv_core.dylib libopencv_cudaarithm.dylib

#libopencv_cudabgsegm.dylib:
#	@executable_path/lib/libopencv_cudabgsegm.dylib (compatibility version 3.0.0, current version 3.0.0)
install_name_tool -change lib/libopencv_core.dylib  @executable_path/lib/libopencv_core.dylib libopencv_cudabgsegm.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_cudabgsegm.dylib
install_name_tool -change lib/libopencv_video.dylib @executable_path/lib/libopencv_video.dylib libopencv_cudabgsegm.dylib
install_name_tool -change lib/libopencv_flann.dylib @executable_path/lib/libopencv_flann.dylib libopencv_cudabgsegm.dylib
install_name_tool -change lib/libopencv_highgui.dylib @executable_path/lib/libopencv_highgui.dylib libopencv_cudabgsegm.dylib
install_name_tool -change lib/libopencv_features2d.dylib  @executable_path/lib/libopencv_features2d.dylib libopencv_cudabgsegm.dylib
install_name_tool -change lib/libopencv_calib3d.dylib  @executable_path/lib/libopencv_calib3d.dylib libopencv_cudabgsegm.dylib
install_name_tool -change lib/libopencv_ml.dylib  @executable_path/lib/libopencv_ml.dylib libopencv_cudabgsegm.dylib
install_name_tool -change lib/libopencv_legacy.dylib  @executable_path/lib/libopencv_legacy.dylib libopencv_cudabgsegm.dylib
install_name_tool -change lib/libopencv_cudaarithm.dylib  @executable_path/lib/libopencv_cudaarithm.dylib libopencv_cudabgsegm.dylib
install_name_tool -change lib/libopencv_cudafilters.dylib  @executable_path/lib/libopencv_cudafilters.dylib libopencv_cudabgsegm.dylib
install_name_tool -change lib/libopencv_cudaimgproc.dylib @executable_path/lib/libopencv_cudaimgproc.dylib libopencv_cudabgsegm.dylib

#libopencv_cudafeatures2d.dylib:
#	@executable_path/lib/libopencv_cudafeatures2d.dylib (compatibility version 3.0.0, current version 3.0.0)
install_name_tool -change lib/libopencv_core.dylib  @executable_path/lib/libopencv_core.dylib libopencv_cudafeatures2d.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_cudafeatures2d.dylib
install_name_tool -change lib/libopencv_flann.dylib  @executable_path/lib/libopencv_flann.dylib libopencv_cudafeatures2d.dylib
install_name_tool -change lib/libopencv_highgui.dylib  @executable_path/lib/libopencv_highgui.dylib libopencv_cudafeatures2d.dylib
install_name_tool -change lib/libopencv_features2d.dylib  @executable_path/lib/libopencv_features2d.dylib libopencv_cudafeatures2d.dylib
install_name_tool -change lib/libopencv_cudaarithm.dylib  @executable_path/lib/libopencv_cudaarithm.dylib libopencv_cudafeatures2d.dylib
install_name_tool -change lib/libopencv_cudafilters.dylib  @executable_path/lib/libopencv_cudafilters.dylib libopencv_cudafeatures2d.dylib
install_name_tool -change lib/libopencv_cudawarping.dylib @executable_path/lib/libopencv_cudawarping.dylib libopencv_cudafeatures2d.dylib

#libopencv_cudafilters.dylib:
#	@executable_path/lib/libopencv_cudafilters.dylib (compatibility version 3.0.0, current version 3.0.0)
install_name_tool -change lib/libopencv_core.dylib  @executable_path/lib/libopencv_core.dylib libopencv_cudafilters.dylib
install_name_tool -change lib/libopencv_imgproc.dylib  @executable_path/lib/libopencv_imgproc.dylib libopencv_cudafilters.dylib
install_name_tool -change lib/libopencv_cudaarithm.dylib  @executable_path/lib/libopencv_cudaarithm.dylib libopencv_cudafilters.dylib

#libopencv_cudaimgproc.dylib:
#	@executable_path/lib/libopencv_cudaimgproc.dylib (compatibility version 3.0.0, current version 3.0.0)
install_name_tool -change lib/libopencv_core.dylib  @executable_path/lib/libopencv_core.dylib libopencv_cudaimgproc.dylib
install_name_tool -change lib/libopencv_imgproc.dylib  @executable_path/lib/libopencv_imgproc.dylib libopencv_cudaimgproc.dylib
install_name_tool -change lib/libopencv_cudaarithm.dylib  @executable_path/lib/libopencv_cudaarithm.dylib libopencv_cudaimgproc.dylib
install_name_tool -change lib/libopencv_cudafilters.dylib  @executable_path/lib/libopencv_cudafilters.dylib libopencv_cudaimgproc.dylib

#libopencv_cudaoptflow.dylib:
#	@executable_path/lib/libopencv_cudaoptflow.dylib (compatibility version 3.0.0, current version 3.0.0)
install_name_tool -change lib/libopencv_core.dylib  @executable_path/lib/libopencv_core.dylib libopencv_cudaoptflow.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_cudaoptflow.dylib
install_name_tool -change lib/libopencv_video.dylib  @executable_path/lib/libopencv_video.dylib libopencv_cudaoptflow.dylib
install_name_tool -change lib/libopencv_flann.dylib @executable_path/lib/libopencv_flann.dylib libopencv_cudaoptflow.dylib
install_name_tool -change lib/libopencv_highgui.dylib @executable_path/lib/libopencv_highgui.dylib libopencv_cudaoptflow.dylib
install_name_tool -change lib/libopencv_features2d.dylib @executable_path/lib/libopencv_features2d.dylib libopencv_cudaoptflow.dylib
install_name_tool -change lib/libopencv_calib3d.dylib  @executable_path/lib/libopencv_calib3d.dylib libopencv_cudaoptflow.dylib
install_name_tool -change lib/libopencv_ml.dylib  @executable_path/lib/libopencv_ml.dylib libopencv_cudaoptflow.dylib
install_name_tool -change lib/libopencv_legacy.dylib  @executable_path/lib/libopencv_legacy.dylib libopencv_cudaoptflow.dylib
install_name_tool -change lib/libopencv_cudaarithm.dylib  @executable_path/lib/libopencv_cudaarithm.dylib libopencv_cudaoptflow.dylib
install_name_tool -change lib/libopencv_cudawarping.dylib  @executable_path/lib/libopencv_cudawarping.dylib libopencv_cudaoptflow.dylib
install_name_tool -change lib/libopencv_cudafilters.dylib  @executable_path/lib/libopencv_cudafilters.dylib libopencv_cudaoptflow.dylib
install_name_tool -change lib/libopencv_cudaimgproc.dylib @executable_path/lib/libopencv_cudaimgproc.dylib libopencv_cudaoptflow.dylib

#libopencv_cudastereo.dylib:
#	@executable_path/lib/libopencv_cudastereo.dylib (compatibility version 3.0.0, current version 3.0.0)
install_name_tool -change lib/libopencv_core.dylib  @executable_path/lib/libopencv_core.dylib libopencv_cudastereo.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_cudastereo.dylib
install_name_tool -change lib/libopencv_flann.dylib @executable_path/lib/libopencv_flann.dylib libopencv_cudastereo.dylib
install_name_tool -change lib/libopencv_highgui.dylib @executable_path/lib/libopencv_highgui.dylib libopencv_cudastereo.dylib
install_name_tool -change lib/libopencv_features2d.dylib @executable_path/lib/libopencv_features2d.dylib libopencv_cudastereo.dylib
install_name_tool -change lib/libopencv_calib3d.dylib @executable_path/lib/libopencv_calib3d.dylib libopencv_cudastereo.dylib

#libopencv_cudawarping.dylib:
#	@executable_path/lib/libopencv_cudawarping.dylib (compatibility version 3.0.0, current version 3.0.0)
install_name_tool -change lib/libopencv_core.dylib  @executable_path/lib/libopencv_core.dylib libopencv_cudawarping.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_cudawarping.dylib

#libopencv_ocl.dylib:
#	@executable_path/lib/libopencv_ocl.dylib (compatibility version 3.0.0, current version 3.0.0)
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_ocl.dylib
install_name_tool -change lib/libopencv_video.dylib  @executable_path/lib/libopencv_video.dylib libopencv_ocl.dylib
install_name_tool -change lib/libopencv_flann.dylib @executable_path/lib/libopencv_flann.dylib libopencv_ocl.dylib
install_name_tool -change lib/libopencv_highgui.dylib @executable_path/lib/libopencv_highgui.dylib libopencv_ocl.dylib
install_name_tool -change lib/libopencv_features2d.dylib @executable_path/lib/libopencv_features2d.dylib libopencv_ocl.dylib
install_name_tool -change lib/libopencv_ml.dylib  @executable_path/lib/libopencv_ml.dylib libopencv_ocl.dylib
install_name_tool -change lib/libopencv_objdetect.dylib  @executable_path/lib/libopencv_objdetect.dylib libopencv_ocl.dylib
install_name_tool -change lib/libopencv_video.dylib  @executable_path/lib/libopencv_video.dylib libopencv_ocl.dylib
install_name_tool -change lib/libopencv_calib3d.dylib  @executable_path/lib/libopencv_calib3d.dylib libopencv_ocl.dylib
install_name_tool -change lib/libopencv_core.dylib  @executable_path/lib/libopencv_core.dylib libopencv_ocl.dylib

#libopencv_optim.dylib:
#	@executable_path/lib/libopencv_optim.dylib (compatibility version 3.0.0, current version 3.0.0)
install_name_tool -change lib/libopencv_core.dylib  @executable_path/lib/libopencv_core.dylib libopencv_optim.dylib

#libopencv_softcascade.dylib:
#	@executable_path/lib/libopencv_softcascade.dylib (compatibility version 3.0.0, current version 3.0.0)
install_name_tool -change lib/libopencv_core.dylib  @executable_path/lib/libopencv_core.dylib libopencv_softcascade.dylib
install_name_tool -change lib/libopencv_imgproc.dylib @executable_path/lib/libopencv_imgproc.dylib libopencv_softcascade.dylib
install_name_tool -change lib/libopencv_ml.dylib  @executable_path/lib/libopencv_ml.dylib libopencv_softcascade.dylib





otool -L libopencv_calib3d.dylib
otool -L libopencv_contrib.dylib
otool -L libopencv_core.dylib
otool -L libopencv_features2d.dylib
otool -L libopencv_flann.dylib
otool -L libopencv_gpu.dylib
otool -L libopencv_highgui.dylib
otool -L libopencv_imgproc.dylib
otool -L libopencv_legacy.dylib
otool -L libopencv_ml.dylib
otool -L libopencv_nonfree.dylib
otool -L libopencv_objdetect.dylib
otool -L libopencv_photo.dylib
otool -L libopencv_stitching.dylib
otool -L libopencv_superres.dylib
otool -L libopencv_ts.dylib
otool -L libopencv_video.dylib
otool -L libopencv_videostab.dylib

otool -L libopencv_cuda.dylib
otool -L libopencv_cudaarithm.dylib
otool -L libopencv_cudabgsegm.dylib
otool -L libopencv_cudafeatures2d.dylib
otool -L libopencv_cudafilters.dylib
otool -L libopencv_cudaimgproc.dylib
otool -L libopencv_cudaoptflow.dylib
otool -L libopencv_cudastereo.dylib
otool -L libopencv_cudawarping.dylib
otool -L libopencv_ocl.dylib
otool -L libopencv_optim.dylib
otool -L libopencv_softcascade.dylib


