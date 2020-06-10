/*
 * IceTower.h
 *
 *  Created on: Mar 14, 2019
 *      Author: kevinw
 */

#ifndef TODOICETOWER_H_
#define TODOICETOWER_H_
#include "Tower.h"
using namespace std;

class TodoIceTower:public Tower{
public:
	TodoIceTower(int x, int y);
	TodoIceTower(int a, int b, int c);
	virtual ~TodoIceTower();
	virtual void upgrade();
	virtual bool isInRange(int x, int y) const;
	virtual void fire(Enemy&);
	virtual char getSymbol() const;
	virtual string getName() const;
};

#endif /* TODOICETOWER_H_ */
