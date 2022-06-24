#include <iostream>
#include <iomanip> //for setw()
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime> //for time() in srand( time(NULL) );
#include <windows.h> //for Sleep()
#include "Map.h"
#include "Rover.h"

using namespace std;

void displayMainMenu(Rover curiosity,int& csequenceCounter,int& commandCounter,int& noOfGold,int& score,string& command){
	char hill=178;
	system("cls");
	score=(curiosity.getGoldCount()*50)-(csequenceCounter*5)-(commandCounter*1);
	curiosity.displayMapper();
	cout<<"Mission: Get all the golds!!, Do not get trapped!!"<<endl;
	cout<<"L=Turn Left, R=Turn Right, M=Move, Q=Quit"<<endl;
	cout<<hill<<"=Hill"<<" #=Trap"<<" *=Gold"<<endl;
	cout<<endl;
	cout<<"Total Command Sequences = "<<csequenceCounter<<" [S]"<<endl;
	cout<<"Total Commands = "<<commandCounter<<" [C]"<<endl;
	cout<<"Total Golds =  "<<curiosity.getGoldCount()<<" [G] "<<"out of "<<noOfGold<<endl;
	cout<<"Total Score = [G] x 50 - [S] x 5 - [C] x 1 = "<<score<<endl;
	
	cout<<"Example Sequence: MRMRMLLMMRMRM"<<endl;
}

int main(){
	int dimx,dimy;
	int noOfGold;
	int csequenceCounter=0;
	int commandCounter=0;
	int score=0;
	bool counter=true;
	bool execution=true;
	bool b=false;
	string command;
	char temp,answer;
	srand(time(NULL));
	
	system("cls");
	cout<<"Mars Rover game"<<endl;
	cout<<"by zhenxiong 2019"<<endl;
	system("pause");
	

	do{
		system("cls");
		cout<<"Enter dimension X: ";
		cin>>dimx;
		cout<<"Enter dimension Y: ";
		cin>>dimy;
		cout<<"Enter amount of gold: ";
		cin>>noOfGold;
	
		system("cls");
		Map mars(dimx,dimy,noOfGold);
		Rover curiosity;
		curiosity.land(mars);
	
		do{
			displayMainMenu(curiosity,csequenceCounter,commandCounter,noOfGold,score,command);
			cout<<"Enter command sequence =>";
			cin>>command;
			csequenceCounter+=1;
			commandCounter+=command.length();
		
			for(int i=0;i<command.length();++i){
				curiosity.executeCommand(command[i]);
				if(curiosity.getGoldCount()==noOfGold){
					i=command.length();
					displayMainMenu(curiosity,csequenceCounter,commandCounter,noOfGold,score,command);
					execution=false;
					cout<<endl;
					cout<<"Congratulations! You have collect all the gold!"<<endl;
					cout<<"Your score is: "<<score<<endl;
				}
				if(curiosity.getLife()==false){
					i=command.length();
					displayMainMenu(curiosity,csequenceCounter,commandCounter,noOfGold,score,command);
					execution=false;
					cout<<endl;
					cout<<"Mission failed, Game over!"<<endl;
				}
			}
		}while(execution);
		
		do{
			cout<<"Do you want to see the map of mars?[Y/N]"<<endl;
			cin>>answer;
			temp=toupper(answer);
				if(temp=='Y'){
					system("cls");
					cout<<"==========Map of mars=========="<<endl;
					mars.display();
					b=false;
				}
				else if(temp=='N'){
					b=false;
				}else
					b=true;
		}while(b);
		
		do{
			cout<<"Do you want to explore mars again?[Y/N]"<<endl;
			cin>>answer;
			temp=toupper(answer);
				if(temp=='Y'){
					csequenceCounter=0;
					commandCounter=0;
					score=0;
					execution=true;
					b=false;
				}else if(temp=='N'){
					system("cls");
					b=false;
					counter=false;
				}else
					b=true;
		}while(b);
		
	}while(counter);
	
return 0;
}
