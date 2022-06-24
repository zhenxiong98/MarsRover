#include <iostream>
#include <iomanip> //for setw()
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime> //for time() in srand( time(NULL) );
#include <windows.h> //for Sleep()
#include "Rover.h"

using namespace std;
Rover::Rover(){
	x=0;
	y=0;
	life=true;
	goldCount=0;
}
void Rover::land(Map& mars){
	p_mars=&mars;
	mapper.resize(p_mars->getDimX(),p_mars->getDimY(),'?');
	mapper.setDimX(p_mars->getDimX());
	mapper.setDimY(p_mars->getDimY());
	char possibleHeading[]={'^','>','v','<'};
	x=(mapper.getDimX()-1)/2;
	y=(mapper.getDimY())/2;

	heading=Direction(rand()%4);
	mapper.setObject(x,y,possibleHeading[heading]);
	
	clearFront();
}
void Rover::clearFront(){
	if(y!=0&&x!=0&&y!=mapper.getDimY()-1&&x!=mapper.getDimX()-1){
		if(heading==Up){
			char object[]={p_mars->getObject(x-1,y-1),p_mars->getObject(x,y-1),p_mars->getObject(x+1,y-1)};
			mapper.setObject(x-1,y-1,object[0]);
			mapper.setObject(x,y-1,object[1]);
			mapper.setObject(x+1,y-1,object[2]);
		}
		else if(heading==Right){
			char object[]={p_mars->getObject(x+1,y-1),p_mars->getObject(x+1,y),p_mars->getObject(x+1,y+1)};	
			mapper.setObject(x+1,y-1,object[0]);
			mapper.setObject(x+1,y,object[1]);
			mapper.setObject(x+1,y+1,object[2]);
		}
		else if(heading==Left){
			char object[]={p_mars->getObject(x-1,y-1),p_mars->getObject(x-1,y),p_mars->getObject(x-1,y+1)};
			mapper.setObject(x-1,y-1,object[0]);
			mapper.setObject(x-1,y,object[1]);
			mapper.setObject(x-1,y+1,object[2]);
		}
		else if(heading==Down){
			char object[]={p_mars->getObject(x-1,y+1),p_mars->getObject(x,y+1),p_mars->getObject(x+1,y+1)};		
			mapper.setObject(x-1,y+1,object[0]);
			mapper.setObject(x,y+1,object[1]);
			mapper.setObject(x+1,y+1,object[2]);
		}
	}
}
bool Rover::turnLeft(){
	char possibleHeading[]={'^','>','v','<'};
	int temp=static_cast<int>(heading);
	temp=(temp+1)%4;
	heading=static_cast<Direction>(temp);
	mapper.setObject(x,y,possibleHeading[heading]);
	clearFront();
	return true;
}
bool Rover::turnRight(){
	char possibleHeading[]={'^','>','v','<'};
	int temp=static_cast<int>(heading);
	temp=(temp+3)%4;
	heading=static_cast<Direction>(temp);
	mapper.setObject(x,y,possibleHeading[heading]);
	clearFront();
	return true;
}

bool Rover::move(){
	char possibleHeading[]={'^','>','v','<'};
	int px=x;
	int py=y;
	if(heading==Up)
		py-=1;
	else if(heading==Right)
		px+=1;
	else if(heading==Left)
		px-=1;
	else if(heading==Down)
		py+=1;
		
	if(p_mars->isInsideMap(px,py)&&(p_mars->isEmpty(px,py)||p_mars->isTrap(px,py)||p_mars->isGold(px,py))){
		mapper.setObject(x,y,' ');
		objectUnderRover=p_mars->getObject(px,py);
		x=px;
		y=py;
		if(objectUnderRover=='#'){
			mapper.setObject(x,y,'@');	
			life=false;
		}
		else if(objectUnderRover=='*'){
			goldCount+=1;
			mapper.setObject(x,y,possibleHeading[heading]);
		}else{
		mapper.setObject(x,y,possibleHeading[heading]);
		}
		clearFront();
		return true;
	}else
		return false;
}
int Rover::getGoldCount(){
	return goldCount;
}
bool Rover::getLife(){
	return life;
}
bool Rover::executeCommand(char command){
	char fcommand=toupper(command);
	system("cls");
	displayMapper();
	cout<<"Executing command ["<<fcommand<<"] ..."<<endl;
	Sleep(1000);
	switch(fcommand){
		case 'M':	
			if(move()){
				system("cls");
				displayMapper();
				cout<<"Executed..."<<endl;
				Sleep(1000);
				if(!life){
					system("cls");
					displayMapper();
					cout<<"You hit the trap"<<endl;
					Sleep(1000);
					break;
				}
			}else{
				system("cls");
				displayMapper();
				cout<<"Failed to execute..."<<endl;	
				Sleep(1000);
			}
			return true;
		case'L':
			if(turnLeft()){
				system("cls");
				displayMapper();
				cout<<"Executed..."<<endl;
				Sleep(1000);
			}
			return true;
		case'R':
			if(turnRight()){
				system("cls");
				displayMapper();
				cout<<"Executed..."<<endl;
				Sleep(1000);
			}
			return true;
		case 'Q':
			life=false;
			break;
		default: 
			system("cls");
			displayMapper();
			cout<<"Failed to execute..."<<endl;	
			Sleep(1000);
			return true;
			
	}
	return true;
}
void Rover::displayMapper(){
	mapper.display();
}