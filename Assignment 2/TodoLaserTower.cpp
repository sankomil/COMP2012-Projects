/*
 * Laser.cpp
 *
 *  Created on: Mar 14, 2019
 *      Author: kevinw
 */

#include "TodoLaserTower.h"

const int LASER_COST = 3;
const int LASER_UPGRADE_COST = 2;
const int LASER_POWER = 10;

TodoLaserTower::TodoLaserTower(int x, int y): Tower(LASER_COST,LASER_UPGRADE_COST,LASER_POWER){this->setXY(x,y);}
TodoLaserTower::TodoLaserTower(int a, int b, int c): Tower(a,b,c){}
TodoLaserTower::~TodoLaserTower() {
	int x,y;
	x=y=-1;
	setXY(x,y);
}
bool TodoLaserTower::isInRange(int x, int y) const{
	int ax,ay;
	this->getXY(ax,ay);
	return (ax==x || ay==y);
}
char TodoLaserTower::getSymbol() const{return 'L';}
string TodoLaserTower::getName() const{return "Laser";}
