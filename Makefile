all: EdgeDetection

EdgeDetection: 
	g++ `pkg-config --cflags opencv` edge_detect.cpp -lopencv_highgui -lopencv_core -lopencv_imgproc `pkg-config --libs opencv` -o edge 

clean:
	rm *o a -f
