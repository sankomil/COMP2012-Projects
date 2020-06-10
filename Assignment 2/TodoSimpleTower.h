/*
 * LazyTower.h
 *
 *  Created on: Mar 11, 2019
 *      Author: kevinw
 */

#ifndef TODOSIMPLETOWER_H_
#define TODOSIMPLETOWER_H_
#include <iostream>
#include "Tower.h"
using namespace std;

class TodoSimpleTower: public Tower
{
public:
	TodoSimpleTower(int x, int y);
	TodoSimpleTower(int a, int b, int c);
	virtual ~TodoSimpleTower();
	virtual bool isInRange(int x, int y) const;
	virtual char getSymbol() const;
	virtual string getName() const;

};

#endif /* TODOSIMPLETOWER_H_ */
