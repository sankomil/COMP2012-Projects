/*
 * Object.cpp
 *
 *  Created on: Feb 26, 2019
 *      Author: kevinw
 */

#include "Object.h"
#include <string>
using std::string;


void Object::getXY(int& ax, int& ay) const {
	ax = x;   ay = y;
}

void Object::writeToStream(ostream& os) const {
	os << getName() << "(" << getSymbol() << ")" << endl
			<< "State: ";
	switch (state) {
	case ObjectState::NORMAL: os << "Normal" << endl; break;
	case ObjectState::FROZEN: os << "Frozen" << endl; break;
	case ObjectState::DEAD: os << "Dead" << endl; break;
	}
}

void Object::setXY(int ax, int ay) {
	x = ax;   y = ay;
}

ostream& operator<< (ostream&os, const Object& o) {
	o.writeToStream(os);
	return os;
}

ObjectState Object::getState() const {
	return state;
}

void Object::setState(ObjectState enumObjectState) {
	state =  enumObjectState;
}
