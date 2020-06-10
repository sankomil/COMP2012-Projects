#ifndef ARENA_H_
#define ARENA_H_

extern const int ARENA_W;
extern const int ARENA_H;
extern const int TOWER_X;

#include "Object.h"
#include "Tower.h"
/**
 * The Arena class
 * The Arena class is a model class that contains the Robot on it.
 * It also manages the coordinate of the game board and maintains the
 * size of the Arena (ARENA_W / ARENA_H) as defined in Arena.cpp
 *
 * Please find the specification of the function in TodoArena.cpp
 */

class Arena {
public:
	Arena();
	virtual ~Arena();

	bool isGameOver() const;

	void removeObject(Object*);
	void addObject(Object*);

	void getConstObjects(const Object**&, int&) const;

	Object* getObjectAt(int aX, int aY) const;

	void nextRound();

	void addBuilding(int, int, int);

	bool upgrade(Tower*);

	int getMoney() const {return money;}

	int getEnemyKill() const {return enemy_kill;}


private:
	void generateEnemy();
	Object** objects;
	int num_objects;
	int money;
	int enemy_kill;
};

#endif /* ARENA_H_ */
