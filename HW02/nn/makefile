BIN  = nn
CC   = g++
SRCS = $(BIN).cpp mat.cpp rand.cpp randf.cpp randmt.cpp readfile.cpp train.cpp util.cpp test.cpp
OBJS = $(BIN).o mat.o rand.o readfile.o train.o util.o test.o
LIBS = -lm 
CCFLAGS = -g -std=c++11 


$(BIN): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o nn

$(BIN).o: $(BIN).cpp $(BIN).h
	$(CC) $(CCFLAGS) -c $(BIN).cpp 

rand.o: rand.cpp rand.h
	$(CC) $(CCFLAGS) -c rand.cpp 

readfile.o: readfile.cpp readfile.h
	$(CC) $(CCFLAGS) -c readfile.cpp

train.o: train.cpp train.h
	$(CC) $(CCFLAGS) -c train.cpp

util.o: util.cpp util.h
	$(CC) $(CCFLAGS) -c util.cpp

test.o: test.cpp test.h
	$(CC) $(CCFLAGS) -c test.cpp
# randf.o: randf.cpp rand.h
# 	$(CC) $(CCFLAGS) -c randf.cpp 

# randmt.o: randmt.cpp rand.h
# 	$(CC) $(CCFLAGS) -c randmt.cpp 

all: 
	touch $(SRCS)
	make

clean:
	rm -f $(OBJS) $(BIN) rand.o randf.o randmt.o $(BIN).tar *~ *.output 

tar:
	make
	tar -cvf $(BIN).tar $(SRCS) nn.h rand.h mat.h readfile.h train.h util.h test.h makefile 

submit: 
	curl -F student=daniel -F assignment="CS504 S17 Assignment 2" -F "submittedfile=@nn.tar" "http://ec2-52-89-93-46.us-west-2.compute.amazonaws.com/cgi-bin/fileCapture.py"



