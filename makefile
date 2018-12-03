# Source: http://web.engr.oregonstate.edu/~rookert/cs162/03.mp4

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS = main.o Brush.o Camp.o Clearing.o Game.o Item.o Menu.o Pack.o Peak.o Player.o Space.o
SRCS = main.cpp Brush.cpp Camp.cpp Clearing.cpp Game.cpp Item.cpp Menu.cpp Pack.cpp Peak.cpp Player.cpp Space.cpp
HEADERS = Brush.hpp Camp.hpp Clearing.hpp Game.hpp Item.hpp Menu.hpp Pack.hpp Peak.hpp Player.hpp Space.hpp

finalproject: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o finalproject

$(OBJS): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $(@:.o=.cpp)

clean:
	rm *.o finalproject
