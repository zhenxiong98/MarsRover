#include <iostream>
#include <iomanip> //for setw()
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime> //for time() in srand( time(NULL) );
#include <windows.h> //for Sleep()
#include "Map.h"

using namespace std;

Map::Map(int dimx,int dimy,int g){
	dimX=dimx;
	dimY=dimy;
	noOfGold=g;
	int px,py;
	int counter;
	char hill=178;
	
	char object[]={' ',' ',' ',' ',' ',' ','#',hill};
	int sizeOfObject=sizeof(object);
	
	map.resize(dimY);
		for(int i=0;i<dimY;++i){
			map[i].resize(dimX);
		}
		
		do{
			px=rand()%dimX;
			py=rand()%dimY;
			if(!isEmpty(px,py)){
				map[py][px]='*';
				--noOfGold;
			}
			
		}while(noOfGold!=0);

		for(int i=0;i<dimY;++i){
			for(int j=0;j<dimX;++j){
				int noOfObj=rand()%sizeOfObject;
				if(map[i][j]!='*'){
					map[i][j]=object[noOfObj];
				}
			}
		}
		if(map[dimY/2][(dimX-1)/2]='*'){
			map[dimY/2][(dimX-1)/2]=' ';
			px=rand()%dimX;
			py=rand()%dimY;
			map[py][px]='*';
			
		}
		map[dimY/2][(dimX-1)/2]=' ';
	
}

void Map::resize(int dimx,int dimy,char ch){
	map.resize(dimy);
		for(int i=0;i<dimy;++i){
			map[i].resize(dimx);
		}
	for(int i=0;i<dimy;++i){
		for(int j=0;j<dimx;++j){
			map[i][j]=ch;
		}
	}
}
int Map::getDimX(){
	return dimX;
}
int Map::getDimY(){
	return dimY;
}
void Map::setDimX(int x){
	dimX=x;
}
void Map::setDimY(int y){
	dimY=y;
}
void Map::setObject(int x,int y,char ch){
	map[y][x]=ch;
}
char Map::getObject(int x,int y){
	return map[y][x];
}
bool Map::isEmpty(int x,int y){
	if(map[y][x]==' ')
		return true;
	return false;
}
bool Map::isGold(int x,int y){
	if(map[y][x]=='*')
		return true;
	return false;
}
bool Map::isHill(int x,int y){
	char hill=178;
	if(map[y][x]==hill)
		return true;
	return false;
}
bool Map::isTrap(int x,int y){
	if(map[y][x]=='#')
		return true;
	return false;
}
bool Map::isInsideMap(int x,int y){
	if(x<dimX&&x>-1&&y<dimY&&y>-1)
		return true;
	return false;
}
void Map::display(){
	for(int i=0;i<dimY;++i){
		cout<<setw(5);
		for(int j=0;j<dimX;++j){
			cout<<"+-";
		}
	cout<<"+"<<endl;
	cout<<setw(3)<<i+1;
	
		for(int j=0;j<dimX;++j){
			cout<<"|"<<map[i][j];
		}
			cout<<"|"<<endl;
			
	}
	cout<<setw(5);
	for(int i=0;i<dimX;++i){
		cout<<"+-";
	}
	cout<<"+"<<endl;
	
	cout << "   ";
	for (int j=0; j<dimX; ++j){
		int digit = (j+1)/10;
		cout << " ";
			if (digit==0)
				cout << " ";
			else
				cout << digit;
	}
	cout << endl;

	cout << "   ";
	for (int j=0; j<dimX; ++j){
		cout << " " << (j+1)%10;
	}
	cout << endl << endl;	
}
