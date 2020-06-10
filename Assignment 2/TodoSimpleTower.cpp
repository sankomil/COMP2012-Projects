/*
 * LazyTower.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: kevinw
 */

#include "TodoSimpleTower.h"

const int SIMPLE_TOWER_COST = 1;
const int SIMPLE_TOWER_UPGRADE_COST = 1;
const int SIMPLE_TOWER_POWER = 3;

TodoSimpleTower::TodoSimpleTower(int x,int y): Tower(SIMPLE_TOWER_COST,SIMPLE_TOWER_UPGRADE_COST,SIMPLE_TOWER_POWER){this->setXY(x,y);}
TodoSimpleTower::TodoSimpleTower(int a, int b, int c): Tower(a,b,c){}


bool TodoSimpleTower::isInRange(int x, int y) const{
	int ax, ay;
	this->getXY(ax,ay);
	if((ax==x+1 || ax==x+2) && (ay==y)){return true;}
	else{return false;}
}


char TodoSimpleTower::getSymbol() const{return 'S';}

string TodoSimpleTower::getName() const{return "Simple Tower";}


TodoSimpleTower::~TodoSimpleTower(){
	int x,y;
	x=-1;
	y=-1;
	setXY(x,y);

}
