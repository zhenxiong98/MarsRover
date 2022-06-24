#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <iomanip> //for setw()
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime> //for time() in srand( time(NULL) );
#include <windows.h> //for Sleep()

using namespace std;

class Map{
	private:
		vector< vector<char> >map;
		int dimX, dimY,noOfGold;

	public:
		Map(){dimX=0;
			dimY=0;}
		Map(int dimx,int dimy,int g);
		void resize(int dimx,int dimy,char ch);
		void display();
		void setObject(int x,int y,char ch);
		char getObject(int x,int y);
		bool isEmpty(int x,int y);
		bool isHill(int x,int y);
		bool isTrap(int x,int y);
		bool isGold(int x,int y);
		bool isInsideMap(int x,int y);
		int getDimX();
		int getDimY();
		void setDimX(int x);
		void setDimY(int y);
};
#endif