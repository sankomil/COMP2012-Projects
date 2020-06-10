/*
 * RevivingEnemy.cpp
 *
 *  Created on: Mar 15, 2019
 *      Author: kevinw
 */

#include "TodoRevivingEnemy.h"

TodoRevivingEnemy::TodoRevivingEnemy(int a, int b, int c): Enemy(a,b,c){}
TodoRevivingEnemy::~TodoRevivingEnemy(){}
char TodoRevivingEnemy::getSymbol() const {return 'R';}
string TodoRevivingEnemy::getName() const {return "Reviving Enemy";}
void TodoRevivingEnemy::fired(int power){
	if(!revive){
		hp -= power;
		if (hp <= 0){
			hp=1;
			revive=true;
		}
	}
	else{
		hp -= power;
		if (hp <= 0)
			setState(ObjectState::DEAD);
	}
}
