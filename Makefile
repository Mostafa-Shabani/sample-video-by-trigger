APP := Webcam_unit_test

SRCS := \
	Webcam_unit_test.cpp\
	Webcam.cpp
	

#OBJS := $(SRCS:.cpp=.o)
OBJS := $(patsubst %.cpp, ./build/%.o,$(SRCS)) 
CPP := g++ -std=c++11 -g -pthread
LDFLAGS:=`pkg-config --libs opencv` 
#~ LDFLAGS+= 'lpthread'
INCLUDE:= -I./myHeaderFiles\
		  

CPPFLAGS:=

all: $(APP)

./build/%.o: %.cpp
	$(CPP) $(INCLUDE) $(LDFLAGS) $(CPPFLAGS) -c $< -o $@

$(APP): $(OBJS)
	$(CPP) -o ./build/$@ $(OBJS) $(CPPFLAGS) $(INCLUDE) $(LDFLAGS)

clean:
	rm -rf ./build/* 
