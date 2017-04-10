BIN  = kmeans
CC   = g++
SRCS = $(BIN).cpp mat.cpp rand.cpp readfile.cpp compute.cpp
OBJS = $(BIN).o mat.o rand.o readfile.o compute.o
LIBS = -lm
CCFLAGS = -g -std=c++11


$(BIN): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o kmeans

$(BIN).o: $(BIN).cpp
	$(CC) $(CCFLAGS) -c $(BIN).cpp

rand.o: rand.cpp rand.h
	$(CC) $(CCFLAGS) -c rand.cpp

readfile.o: readfile.cpp readfile.h
	$(CC) $(CCFLAGS) -c readfile.cpp

compute.o: compute.cpp compute.h
	$(CC) $(CCFLAGS) -c compute.cpp

all:
	touch $(SRCS)
	make

clean:
	rm -f $(OBJS) $(BIN) rand.o randf.o randmt.o $(BIN).tar *~ *.output

tar:
	make
	tar -cvf $(BIN).tar $(SRCS) rand.h mat.h readfile.h compute.h makefile

submit:
	curl -F student=daniel -F assignment="CS504 S17 Assignment 4" -F "submittedfile=@kmeans.tar" "http://ec2-52-89-93-46.us-west-2.compute.amazonaws.com/cgi-bin/fileCapture.py"
