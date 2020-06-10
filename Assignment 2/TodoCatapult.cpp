/*
 * Catapult.cpp
 *
 *  Created on: Mar 12, 2019
 *      Author: kevinw
 */

#include "TodoCatapult.h"

const int TODO_CATAPULT_COST = 2;
const int TODO_CATAPULT_UPGRADE_COST = 2;
const int TODO_CATAPULT_POWER = 5;
const int TODO_CATAPULT_RANGE = 5;

TodoCatapult::TodoCatapult(int x, int y): Tower(TODO_CATAPULT_COST,TODO_CATAPULT_UPGRADE_COST,TODO_CATAPULT_POWER){this->setXY(x,y);}
TodoCatapult::TodoCatapult(int a, int b, int c): Tower(a,b,c){}

TodoCatapult::~TodoCatapult(){
	int x,y;
	x=y=-1;
	setXY(x,y);
}


bool TodoCatapult::isInRange(int x, int y) const{
	int ax,ay;
	this->getXY(ax,ay);
	return ((abs(ax-x) + abs(ay-y))==TODO_CATAPULT_RANGE);
}

char TodoCatapult::getSymbol() const{return 'C';}
string TodoCatapult::getName() const{return "Catapult";}
