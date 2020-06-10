/*
 * Laser.h
 *
 *  Created on: Mar 14, 2019
 *      Author: kevinw
 */

#ifndef TODOLASERTOWER_H_
#define TODOLASERTOWER_H_
#include <iostream>
#include "Tower.h"
using namespace std;

class TodoLaserTower: public Tower {
public:
	TodoLaserTower(int x, int y);
	TodoLaserTower(int a, int b, int c);
	virtual ~TodoLaserTower();
	virtual bool isInRange(int x, int y) const;
	virtual char getSymbol() const;
	virtual string getName() const;

};

#endif /* TODOLASERTOWER_H_ */
