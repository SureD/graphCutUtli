#
#
#
#

CC = g++
CFLAGS = -g -w `pkg-config opencv --libs --cflags opencv`

all:\
	ImgTools.o
ImgTools.o:\
	Image_cv.cpp Image_cv.h
	$(CC) -c Image_cv.cpp  $(CFLAGS) 

