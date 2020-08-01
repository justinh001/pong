appname=pong
CXX=g++
CXXFLAGS= -std=c++17 -Wall -Werror -Wextra -O3
LDLIBS= -lSDL2 -lSDL2_ttf
srcfiles= src/main.cpp src/Game.cpp src/Paddle.cpp src/Ball.cpp src/Text.cpp
all:
	$(CXX) $(srcfiles) -o $(appname) $(CXXFLAGS) $(LDLIBS)
install:
	$(CXX) $(srcfiles) -o $(appname) $(CXXFLAGS) $(LDLIBS)
	mkdir -p /usr/local/bin/
	mv $(appname) /usr/local/bin/
	chmod 755 /usr/local/bin/$(appname)
uninstall:
	rm -f /usr/local/bin/$(appname)
