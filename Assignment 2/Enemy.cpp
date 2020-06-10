/*
 * Enemy.cpp
 *
 *  Created on: Feb 26, 2019
 *      Author: kevinw
 */

#include "Enemy.h"

Enemy::Enemy(int hp, int x, int y) : hp(hp) {
	setXY(x, y);
}

Enemy::~Enemy() {
	// TODO Auto-generated destructor stub
}

void Enemy::writeToStream(ostream& os) const {
	Object::writeToStream(os);
	os << "HP:" << getHP() << endl;
}

void Enemy::move() {
	if (getState() == ObjectState::DEAD)
		return;
	if (getState() == ObjectState::FROZEN) {
		setState(ObjectState::NORMAL);
		return;
	}

	int x, y;
	getXY(x,y);
	setXY(x + 1, y);
}

char Enemy::getSymbol() const {
	return 'E';
}

std::string Enemy::getName() const {
	return "Enemy";
}

int Enemy::getHP() const {
	return hp;
}

void Enemy::fired(int power) {
	hp -= power;
	if (hp <= 0)
		setState(ObjectState::DEAD);
}
