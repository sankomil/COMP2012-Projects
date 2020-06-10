/*
 * Arena.cpp
 *
 *  Created on: Feb 25, 2016
 *      Author: kevinw
 */

/*
 * Arena.cpp
 *
 *  Created on: Feb 25, 2016
 *      Author: kevinw
 */

#include "Arena.h"
#include <fstream>		//remove

#include "Enemy.h"
#include "TodoCatapult.h"
#include "TodoDiagonalEnemy.h"
#include "TodoIceTower.h"
#include "TodoLaserTower.h"
#include "TodoRevivingEnemy.h"
#include "TodoSimpleTower.h"

const int ARENA_W = 45;
const int ARENA_H = 5;
const int TOWER_X = 35;
const int ENEMY_X = 0;
const int LASER_COST = 3;
const int SIMPLE_TOWER_COST = 1;
const int TODO_ICE_TOWER_COST = 3;
const int TODO_CATAPULT_COST = 2;



Arena::~Arena() {
//TODO
	for(int x=0;x<num_objects;++x){
		delete objects[x];
	}
	delete[] objects;
}

//Perform shadow copying and add this object to the array objects.
//The ownership of this object is transfered to Arena.
void Arena::addObject(Object* newobj) {
//TODO

	if(objects!=nullptr){
		Object** temp=new Object*[this->num_objects+1];
		for(int x=0;x<num_objects;++x){
			temp[x]=objects[x];
		}
		temp[num_objects]=newobj;
		delete[] objects;
		objects=temp;
		temp=nullptr;
		++num_objects;
	}
	else{
		objects=new Object*[1];
		objects[0]=newobj;
		++num_objects;
	}
}

//To return a dynamic const Object array. You might treat the memory
//pointed by obj is garbage.
void Arena::getConstObjects(const Object**& obj, int& count) const {
//TODO
	const Object** ob=new const Object*[num_objects];
	for(int x=0;x<num_objects;++x){
		ob[x]=objects[x];
	}
	obj=ob;
	count=num_objects;
}

//Return the object in the array objects with the coordinate aX and aY.
//If there are more than one object is in this coordinate, return any
//one of them. If there are no object is in this coordinate, return nullptr 
Object* Arena::getObjectAt(int aX, int aY) const {
//TODO
	for(int x=0;x<this->num_objects;++x){
		int ax,ay;
		objects[x]->getXY(ax,ay);
		if(ax==aX && ay==aY){
			return objects[x];
			break;
		}
		else{continue;}
	}
	return nullptr;

}

//Return true if the game is over, false otherwise.
//The game is over when any not DEAD enemy reaches the end-zone - i.e., its
//x-coordinate >= the constant TOWER_X.
bool Arena::isGameOver() const {
//TODO
	for(int x=0;x<num_objects;++x){
		int ax,ay;
		objects[x]->getXY(ax,ay);
		if(ax>=TOWER_X && objects[x]->getObjectType()==ObjectType::ENEMY && objects[x]->getState()!=ObjectState::DEAD){
			return true;
		}
		else{continue;}
	}
	return false;
}


//Remove the object pointed by the pointer r from the array objects if it is 
//in the list. Do nothing if r is a nullptr or r is not in the array.
void Arena::removeObject(Object* r) {
//TODO
	if(r!=nullptr){
		int i=-1;
		for(;i<num_objects;++i){
			if(objects[i]==r){
				break;
			}
		}
		if(i!=-1){
			Object** temp=new Object*[num_objects-1];
			for(int x=0;x<i;++x){
				temp[x]=objects[x];
			}
			for(int x=i+1;x<num_objects;++x){
				temp[x-1]=objects[x];
			}
			delete objects[i];
			delete[] objects;
			objects=temp;
			temp=nullptr;
			--num_objects;
		}
	}
}


//Depends on the value of the variable building, construct a tower at the coordinate x, y when money is larger than the building cost.
// if building is SIMPLE_TOWER - construct a TodoSimpleTower
// if building is CATAPUL_TOWER - construct a TodoCatapult
// if building is LASER_TOWER - construct a TodoLaserTower
// if building is ICE_TOWER - construct a TodoIceTower
// otherwise - do nothing.
// After building the tower, deduct the money by the building cost of the tower
void Arena::addBuilding(int building, int x, int y) {
//TODO
	bool empty=true;
	for(int a=0;x<num_objects;++a){
		int ax,ay;
		objects[a]->getXY(ax,ay);
		if(ax!=x && ay!=y && empty==true){empty=true;}
		else{empty=false;}
	}

	if(empty){

		switch(building){
		case (SIMPLE_TOWER):
			if(money>=SIMPLE_TOWER_COST){
				TodoSimpleTower* temp=new TodoSimpleTower(x,y);
				this->addObject(temp);
				money-=SIMPLE_TOWER_COST;
			}
			break;
		case(CATAPULT_TOWER):
				if(money>=TODO_CATAPULT_COST){
					TodoCatapult* temp=new TodoCatapult(x,y);
					this->addObject(temp);
					money-=TODO_CATAPULT_COST;
				}
			break;
		case(LASER_TOWER):
			if(money>=LASER_COST){
				TodoLaserTower* temp=new TodoLaserTower(x,y);
				this->addObject(temp);
				money-=LASER_COST;
			}
			break;
		case(ICE_TOWER):
			if(money>=TODO_ICE_TOWER_COST){
				TodoIceTower* temp=new TodoIceTower(x,y);
				this->addObject(temp);
				money-=TODO_ICE_TOWER_COST;

			}
			break;
		}

	}

}


//This function would first make all tower fires (if there is 
//at least one enemy in its range). By default, the tower will select 
//the nearest enemy to shoot. If there are more than one nearest enemies,
//pick anyone of them (we would not test this case during grading).
//
//Next all enemies are going to move. Remember that an enemy in the state
//FROZEN or DEAD cannot move.  
//
//Next you need to generate one new Enemy by calling the function genereateEnemy(). The function generateEnemy has been written for you already.
//
//Finally you need to clean up all DEAD enemy and tower that was destroyed by enemy in this turn.
//
//The amount of money will be increased by the enemies killed in this turn.
//(*noted: if a RevivingEnemy revive, money will not be added) 
void Arena::nextRound() {
//TODO
	Tower* towers[num_objects];
	Enemy* enemies[num_objects];
	int num_towers=0;
	int num_enemies=0;
	for(int x=0;x<num_objects;++x){
		if(objects[x]->getObjectType()==ObjectType::TOWER){towers[num_towers]=static_cast<Tower*>(objects[x]);++num_towers;}
		else if(objects[x]->getObjectType()==ObjectType::ENEMY){enemies[num_enemies]=static_cast<Enemy*>(objects[x]);++num_enemies;}
	}
	for(int x=0;x<num_towers;++x){
		int tx,ty;
		towers[x]->getXY(tx,ty);
		Enemy* near=enemies[0];
		int ex,ey;
		enemies[0]->getXY(ex,ey);
		for(int y=0;y<num_enemies;++y){
			int a,b;
			enemies[y]->getXY(a,b);
			if(abs(tx-a)<abs(tx-ex)){
				near=enemies[y];
				ex=a;
				ey=b;
			}
		}
		towers[x]->fire(*near);
	}
	TodoDiagonalEnemy* diag[num_enemies];
	int num_diag=0;
	for(int x=0;x<num_enemies;++x){
		if(enemies[x]->getSymbol()!='D'){
			enemies[x]->move();
		}
		else{
			diag[num_enemies]=static_cast<TodoDiagonalEnemy*>(enemies[x]);
			int x,y;
			diag[num_diag]->getXY(x,y);
			if(y<=ARENA_H){
				diag[num_diag]->set_up(true);
			}
			else if(y<=0){diag[num_diag]->set_up(false);}
			diag[num_diag]->move();

		}

	}
	generateEnemy();
	for(int x=0;x<num_objects;++x){
		if(objects[x]->getState()==ObjectState::DEAD){
			this->removeObject(objects[x]);
		}
	}
	for(int x=0;x<num_towers;++x){
		money+=towers[x]->collectMoney();
	}
	/*Tower** towers=nullptr;
	Enemy** enemies=nullptr;
	int num_towers=0;
	int num_enemies=0;

	for(int x=0;x<num_objects;++x){       					//Separates everything into towers and enemies
		if(objects[x]->getObjectType()==ObjectType::TOWER){
			if(towers!=nullptr){
				Tower** temp=new Tower*[num_towers];
				for(int a=0;a<num_towers;++x){
					temp[x]=towers[x];
				}
				delete[] towers;
				towers=temp;
				towers[num_towers]=dynamic_cast<Tower*>(objects[x]);
				++num_towers;
				temp=nullptr;
			}
			else{
				towers=new Tower*[1];
				towers[num_towers]=dynamic_cast<Tower*>(objects[x]);
				++num_towers;

			}

		}
		else if(objects[x]->getObjectType()==ObjectType::ENEMY){
				if(enemies!=nullptr){
					Enemy** temp=new Enemy*[num_enemies];
					for(int a=0;a<num_enemies;++x){
						temp[x]=enemies[x];
					}
					delete[] enemies;
					enemies=temp;
					enemies[num_enemies]=dynamic_cast<Enemy*>(objects[x]);
					++num_enemies;
					temp=nullptr;
				}
				else{
					enemies=new Enemy*[1];
					enemies[num_enemies]=dynamic_cast<Enemy*>(objects[x]);
					++num_enemies;

				}
			}
	}

	for(int x=0;x<num_towers;++x){												//Fires at enemies, stops after hitting one enemy
		for(int y=0;y<num_enemies;++y){
			towers[x]->Tower::fire(*enemies[y]);
			int ax,ay;
			enemies[y]->getXY(ax,ay);
			if(towers[x]->isInRange(ax,ay)){
				break;
			}
		}
	}

	TodoDiagonalEnemy** diag=new TodoDiagonalEnemy*[1];							//Moves diagonal enemies
	int num_diag=0;
	for(int x=0;x<num_enemies;++x){
		if(enemies[x]->getSymbol()=='D' && enemies[x]->getState()==ObjectState::NORMAL){
			TodoDiagonalEnemy** temp=new TodoDiagonalEnemy*[num_diag+1];
			for(int a=0;a<num_diag;++a){
				temp[a]=diag[a];
			}
			temp[num_diag]=dynamic_cast<TodoDiagonalEnemy*>(enemies[x]);
			delete[] diag;
			diag=temp;
			++num_diag;
		}
	}

	for(int x=0;x<num_diag;++x){
		int ax,ay;
		diag[x]->getXY(ax,ay);
		if(ay<=ARENA_H){
			diag[x]->set_up(true);
			diag[x]->move();
		}
	}
	for(int x=0;x<num_enemies;++x){												//Moves normal enemies
		if(enemies[x]->getSymbol()!='D'&& enemies[x]->getState()==ObjectState::NORMAL){
			enemies[x]->move();
		}
		if(enemies[x]->getState()==ObjectState::FROZEN){						//Any frozen enemies are set to normal
			enemies[x]->setState(ObjectState::NORMAL);
		}
	}
	generateEnemy(); //Generates enemy

	for(int x=0;x<num_towers;++x){
		money+=towers[x]->collectMoney();								//collect money from towers
	}

	for(int x=0;x<num_objects;++x){   //Removes dead objects
		if(objects[x]->getState()==ObjectState::DEAD){
			this->removeObject(objects[x]);
		}
	}
	delete[] diag;
	delete[] enemies;
	delete[] towers;*/


}


//Completed
bool Arena::upgrade(Tower* t) {
	if (t == nullptr || money < t->getUpgradeCost())
		return false;
	money -= t->getUpgradeCost();
	t->upgrade();
	return true;
}

//Completed
void Arena::generateEnemy() {
	int i = rand() % ARENA_H;
	Enemy* e;
	switch (rand() % 3) {
	case 0: e = new Enemy(5, ENEMY_X, i); break;
	case 1: e = new TodoDiagonalEnemy(6, ENEMY_X, i); break;
	case 2: e = new TodoRevivingEnemy(10, ENEMY_X, i); break;
	}
	addObject(e);

}

//Completed
Arena::Arena() : objects(nullptr), num_objects(0), money(10), enemy_kill(0) {
	nextRound();

}
