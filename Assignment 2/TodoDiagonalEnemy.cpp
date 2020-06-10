/*
 * DiagonalEnemy.cpp
 *
 *  Created on: Mar 13, 2019
 *      Author: kevinw
 */

#include "TodoDiagonalEnemy.h"
#include <iostream>
using namespace std;

TodoDiagonalEnemy::TodoDiagonalEnemy(int a, int b, int c): Enemy(a,b,c){}
TodoDiagonalEnemy::~TodoDiagonalEnemy(){}
char TodoDiagonalEnemy::getSymbol() const {return 'D';}
string TodoDiagonalEnemy::getName() const {return "Diagonal Enemy";}
void TodoDiagonalEnemy::move(){
	int x,y;
	getXY(x,y);
	if(up && y<0){
		setXY(x+1,y+1);
	}
	else if(!up){
		setXY(x+1,y-1);
	}
}

void TodoDiagonalEnemy::set_up(const bool value){up=value;}
bool TodoDiagonalEnemy::get_up() const{return up;}
