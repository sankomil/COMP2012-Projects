/*
 * Enemy.h
 *
 *  Created on: Feb 26, 2019
 *      Author: kevinw
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "Object.h"
#include "definition.h"

class Enemy: public Object {
public:
	Enemy(int, int, int);
	virtual ~Enemy();

        //Return a symbol of the Enemy to be printed on screen. There is 
        //no specification on this function, you can decide what to return 
        //for each class.
	char getSymbol() const override;

        //Return the name of the object to be printed on message box. There 
        //is no specification on this function, you can decide what to 
        //return for each class.
	std::string getName() const override;

	//move according to the specification - one steps to the right.
	virtual void move();

	//return the HP of the enemy
	int getHP() const;

	//the function to be executed when an enemy is being fired.
	virtual void fired(int);

	//return ObjectType::ENEMY to identify that is a ENEMY type.
	virtual ObjectType getObjectType() const override {return ObjectType::ENEMY; }
protected:

	//override base class function.
	virtual void writeToStream(ostream& os) const override;
	int hp; //health point

};

#endif /* ENEMY_H_ */
