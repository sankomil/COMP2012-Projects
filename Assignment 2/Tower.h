/*
 * Tower.h
 *
 *  Created on: Feb 26, 2019
 *      Author: kevinw
 */

#ifndef TOWER_H_
#define TOWER_H_

#include "Object.h"

class Enemy;

/**
 * Tower is an abstract base class of other type of towers. 
 * The member functions are explained as below.
 *
 */
class Tower : public Object {
public:
	//The first parameter is the building cost
	//The second parameter is the upgrade cost
	//The third parameter is the power
	Tower(int, int, int);
	
	virtual ~Tower();

	//Return the building cost of the tower.
	int getCost() const;
	//Return the power of the tower.
	int getPower() const;
	//Return the upgrade cost of the tower.
	virtual int getUpgradeCost() const;

	//Return true if the coordinate x, y is in the range of this tower.
	//i.e. a tower can fire an enemy only if it is in its range.
	virtual bool isInRange(int x, int y) const = 0;

	//Fire an enemy. A enemy will decrease its HP by the tower's power.
	//It earns money when the enemy is dead.
	virtual void fire(Enemy&);

	//To differentiate it is a Tower or an Enemy class.
	virtual ObjectType getObjectType() const override {return ObjectType::TOWER; };

	//To upgrade a tower. A tower will increase its power by the value 1 after each upgrade.
	//You need to pay the upgrade cost to upgrade an tower. 
	virtual void upgrade();

	//When an enemy is killed some money will be generated at the Tower. 
	//this function will return the money to and reset this value to 0.
	int collectMoney();

protected:
	//To output its details to an ostream. i.e. cout << aTowerObject << endl;
	virtual void writeToStream(ostream& os) const override;


private:
	int cost;
	int upgrade_cost;
	int power;
	int money_earned = 0;
};

#endif /* TOWER_H_ */
