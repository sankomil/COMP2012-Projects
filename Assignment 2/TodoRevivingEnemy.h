/*
 * RevivingEnemy.h
 *
 *  Created on: Mar 15, 2019
 *      Author: kevinw
 */

#ifndef TODOREVIVINGENEMY_H_
#define TODOREVIVINGENEMY_H_
#include "Enemy.h"
using namespace std;

class TodoRevivingEnemy: public Enemy {
public:
	TodoRevivingEnemy(int, int, int);
	virtual ~TodoRevivingEnemy();
	char getSymbol() const override;
	string getName() const override;
	virtual void fired(int a);

private:
	bool revive=false;
};


#endif /* TODOREVIVINGENEMY_H_ */
