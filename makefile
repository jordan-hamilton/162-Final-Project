# Source: http://web.engr.oregonstate.edu/~rookert/cs162/03.mp4

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS = main.o Menu.o Game.o Space.o
SRCS = main.cpp Menu.cpp Game.cpp Space.cpp
HEADERS = Menu.hpp Game.hpp Space.hpp

finalproject: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o finalproject

$(OBJS): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $(@:.o=.cpp)

clean:
	rm *.o finalproject
