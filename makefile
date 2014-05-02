src_files := $(wildcard ./src/*.cpp)
libav:= -lavcodec -lavformat -lavdevice -lavfilter -lswscale -lavutil
inc_dir:=./src
out := ./build

libcairo := -lX11 -lXcomposite -lXfixes -lcairo

libopencv := -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab

$(shell   mkdir -p $(out))

testX11Capture:
	g++ test/testCapture.cpp $(src_files) -o $(out)/testCapture -I$(inc_dir) $(libav) 

testdraw:
	g++ test/testdraw.cpp $(pkg-config --cflags cairo) $(libcairo) -o $(out)/testdraw

testmouse:
	g++ test/testmouse.cpp $(src_files) -I$(inc_dir) $(libav) -o $(out)/testmouse

testimread:
	g++ test/imreadtest.cpp $(src_files) -I$(inc_dir) $(pkg-config --cflags cairo) $(pkg-config --cflags opencv) $(libopencv) $(libcairo) $(libav) -o $(out)/testimread
