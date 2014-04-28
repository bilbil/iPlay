src_files := $(wildcard ./src/*.cpp)
lib:= -lavcodec -lavformat -lavdevice -lavfilter -lswscale -lavutil
inc_dir:=./src
out := ./build

$(shell   mkdir -p $(out))

testX11Capture:
	g++ $(src_files) -o $(out)/capture -I$(inc_dir) $(lib) 
