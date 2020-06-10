/*
 * Object.h
 *
 *  Created on: Feb 26, 2019
 *      Author: kevinw
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>
#include <string>
#include "definition.h"
using namespace std;


class Object {
	friend ostream& operator<< (ostream& os, const Object& o);
public:

	virtual ~Object() = default;
	Object() = default;

	//Return a symbol of the object to be printed on screen. There is no specification on this function, you can decide what to return for each class.
	virtual char getSymbol() const = 0;

	//Return the name of the object to be printed on message box. There is no specification on this function, you can decide what to return for each class.
	virtual string getName() const = 0;

	//Return the coordinate of the object
	void getXY(int&, int&) const;

	//Return the type of the object, can be either ObjectType::TOWER or ObjectType::ENEMY
	virtual ObjectType getObjectType() const = 0;

	//Set the object State.
	void setState(ObjectState);

	//Return the object State
	ObjectState getState() const;
protected:

	//Set the coordinate of the object
	void setXY(int, int);

	//write the content to ostream e.g. cout << anObject << endl; 
	virtual void writeToStream(ostream& os) const;

private:
	int x = -1;
	int y = -1;
	ObjectState state = ObjectState::NORMAL;
};


#endif /* OBJECT_H_ */
