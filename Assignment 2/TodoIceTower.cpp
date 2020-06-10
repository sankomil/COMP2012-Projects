/*
 * IceTower.cpp
 *
 *  Created on: Mar 14, 2019
 *      Author: kevinw
 */

#include "TodoIceTower.h"
#include "Enemy.h"

const int TODO_ICE_TOWER_COST = 3;
const int TODO_ICE_TOWER_UPGRADE_COST = 0;
const int TODO_ICE_TOWER_POWER = 0;

TodoIceTower::TodoIceTower(int x, int y): Tower(TODO_ICE_TOWER_COST,TODO_ICE_TOWER_UPGRADE_COST,TODO_ICE_TOWER_POWER){this->setXY(x,y);}
TodoIceTower::TodoIceTower(int a, int b, int c): Tower(a,b,c){}
TodoIceTower::~TodoIceTower(){
	int ax,ay;
	ax=ay=-1;
	setXY(ax,ay);
}
bool TodoIceTower::isInRange(int x, int y) const{
	int ax,ay;
	getXY(ax,ay);
	if(ax<=x){return true;}
	else{return false;}
}
void TodoIceTower::fire(Enemy& enemy){
    int x, y;
    enemy.getXY(x, y);
    if (isInRange(x, y)) {
    	enemy.setState(ObjectState::FROZEN);
	//if (enemy.getState() == ObjectState::DEAD) //previous code
    }
}

void TodoIceTower::upgrade(){}
char TodoIceTower::getSymbol() const{return 'I';}
string TodoIceTower::getName() const{return "Ice Tower";}
