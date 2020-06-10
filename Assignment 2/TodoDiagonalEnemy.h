/*
 * DiagonalEnemy.h
 *
 *  Created on: Mar 13, 2019
 *      Author: kevinw
 */

#ifndef TODODIAGONALENEMY_H_
#define TODODIAGONALENEMY_H_
#include <iostream>
#include "Enemy.h"
using namespace std;

class TodoDiagonalEnemy: public Enemy {

public:
	TodoDiagonalEnemy(int, int, int);
	virtual ~TodoDiagonalEnemy();
	char getSymbol() const override;
	string getName() const override;
	virtual void move();
	void set_up(const bool value);
	bool get_up() const;
private:
	bool up=true;
};


#endif /* TODODIAGONALENEMY_H_ */
