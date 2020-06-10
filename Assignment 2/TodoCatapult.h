/*
 * Catapult.h
 *
 *  Created on: Mar 12, 2019
 *      Author: kevinw
 */

#ifndef TODOCATAPULT_H_
#define TODOCATAPULT_H_
#include <iostream>
#include "Tower.h"
using namespace std;

class TodoCatapult: public Tower{
public:
	TodoCatapult(int x, int y);
	TodoCatapult(int a, int b, int c);
	virtual ~TodoCatapult();
	virtual bool isInRange(int x, int y) const;
	virtual char getSymbol() const;
	virtual string getName() const;
};



#endif /* TODOCATAPULT_H_ */
