/*
 * Tower.cpp
 *
 *  Created on: Feb 26, 2019
 *      Author: kevinw
 */

#include "Tower.h"
#include "Enemy.h"


int Tower::getCost() const {
	return cost;
}

int Tower::getPower() const {
	return power;
}

Tower::Tower(int cost, int upgrade_cost, int power) : cost(cost), upgrade_cost(upgrade_cost), power(power) {
}

Tower::~Tower() {
}


void Tower::writeToStream(ostream& os) const {
	Object::writeToStream(os);
	os << "Power:" << getPower() << endl;
}


int Tower::getUpgradeCost() const {
	return upgrade_cost;
}


//Code updated at 1/4/2019. 
void Tower::fire(Enemy& enemy) {
    int x, y;
    enemy.getXY(x, y);
    bool isDeadYet = (enemy.getState() == ObjectState::DEAD);  //newly added
    if (isInRange(x, y)) {
	enemy.fired(getPower());
	//if (enemy.getState() == ObjectState::DEAD) //previous code
	if (!isDeadYet && enemy.getState() == ObjectState::DEAD)
	    money_earned++;
    }
}

int Tower::collectMoney() {
	int x = money_earned;
	money_earned = 0;
	return x;
}

void Tower::upgrade() {
	power++;
}
