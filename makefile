#
#
#
CC = g++
CFLAGS = -g -w `pkg-config opencv --libs --cflags opencv`
VL = -I/home/sured/lib/vlfeat/ -L/home/sured/lib/vlfeat/bin/glnx86/ -lvl


all:\
	grabCutTool.o main.o Image_cv.o Slic.o
	$(CC) -o testd main.o grabCutTool.o grabCutT.o GMM.o  Image_cv.o Slic.o $(VL) $(CFLAGS)
main.o:\
	Slic.o\
	main.cpp GrabCut/grabCutTool.h Slic/Slic.h
	$(CC) -c main.cpp $(VL) $(CFLAGS)
	
grabCutTool.o:\
	grabCutT.o
	$(CC) -c GrabCut/grabCutTool.cpp $(CFLAGS) 
grabCutT.o:\
	GMM.o\
	GraphCut/grabCutT.cpp GraphCut/grabCutT.h GraphCut/GCGraph.h
	$(CC) -c GraphCut/grabCutT.cpp $(CFLAGS)
GMM.o:\
	GraphCut/GMM.cpp GraphCut/GMM.hpp
	$(CC) -c GraphCut/GMM.cpp $(CFLAGS)

Image_cv.o:\
	ImgTool/Image_cv.cpp ImgTool/Image_cv.h
	$(CC) -c ImgTool/Image_cv.cpp $(CFLAGS)
Slic.o:\
	Slic/Slic.cpp Slic/Slic.h
	$(CC) -c Slic/Slic.cpp $(VL) $(CFLAGS)
 



	
