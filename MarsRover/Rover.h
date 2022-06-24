#ifndef ROVER_H
#define ROVER_H
#include <iostream>
#include <iomanip> //for setw()
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime> //for time() in srand( time(NULL) );
#include <windows.h> //for Sleep()
#include "Map.h"

using namespace std;
class Rover{
	private:
		enum Direction{Up,Right,Down,Left};
		int x,y;
		Direction heading;
		char objectUnderRover;
		Map* p_mars;
		Map mapper;
		bool life;
		int goldCount;
	public:
		Rover();
		void land(Map& mars);
		bool turnLeft();
		bool turnRight();
		void clearFront();
		bool move();
		void displayMapper();
		bool executeCommand(char command);
		int getGoldCount();
		bool getLife();
};

#endif