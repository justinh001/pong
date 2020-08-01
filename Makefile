appname=pong
CXX=g++
CXXFLAGS= -std=c++17 -Wall -Werror -Wextra -O3
LDLIBS= -lSDL2 -lSDL2_ttf
srcfiles= src/main.cpp src/Game.cpp src/Paddle.cpp src/Ball.cpp src/Text.cpp
all:
	$(CXX) $(srcfiles) -o $(appname) $(CXXFLAGS) $(LDLIBS)
