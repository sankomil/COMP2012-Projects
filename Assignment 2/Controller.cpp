/*
 * Controller.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: kevinw
 *  Update: To fix the issue that cannot equip the fourth weapon, code updated
 */

#include "Controller.h"
#include <string>
#include <sstream>
#include <fstream>

#include "TodoSimpleTower.h"
using namespace std;

Controller::Controller() :
		state(NAVIGATE), selectObject(nullptr), cursor_x(0), cursor_y(0) {

	arena = new Arena();
	view = new View(arena);

	view->renderAll();
	ofstream file;
			file.open("test.txt");
			file<<"dfj"<<endl;
			file.close();


}

Controller::~Controller() {
	delete view;
	delete arena;
}

void Controller::run() {
	bool running = true;
	view->pause(
			"This is PA2. \nF1 or Q - exit; Arrow keys, space/enter to control.");
	while (running) {
		running = handleInput();
	}
}

bool Controller::handleInput() {
	int x = 0, y = 0;

	switch (state) {
	case NAVIGATE:
		if (arena->isGameOver()) {
			view->pause("Game Over");
			return false;
		}

		switch (view->handleNavigate(x, y)) {
		case EXIT:
			return false;
		case OKAY:
		default:
			Object* r = arena->getObjectAt(x, y);
			if (r != nullptr && r->getObjectType() == ObjectType::TOWER) {
				selectObject = r;
				state = TOWER_COMMAND;
			} else {

				int code = view->handleCommand(MENU_LIST);
				if (code == M_END_TURN) {
					view->pause(string("Enemy finish their move. Next round starts"));
					arena->nextRound();
				} else if (code == M_BUILD) {
					if (arena->getObjectAt(x,y) == nullptr) {
						state = BUILDING;
						cursor_x = x;
						cursor_y = y;
					}
				}

			}
		}
		break;

	case BUILDING:
	{
		int building = view->handleCommand(BUILD_LIST);
		if (building == CANCEL_T)
			state = NAVIGATE;
		else {
			view->pause("Build a Tower!");
			arena->addBuilding(building, cursor_x, cursor_y);
			state = NAVIGATE;
		}
	}
		break;

	case TOWER_COMMAND:
		switch (view->handleCommand(CMD_LIST)) {
		case EXIT:
			return false;
		case T_DESTROY:
			arena->removeObject(selectObject);
			selectObject = nullptr;
			state = NAVIGATE;
			break;
		case T_UPGRADE:
			state = NAVIGATE;
			if (!arena->upgrade(static_cast<Tower*>(selectObject)))
				view->displayMessage("Insufficient Money to upgrade");
			break;
		case T_CANCEL:
			state = NAVIGATE;
			selectObject = nullptr;
			break;
		}
		break;


	}

	return true;
}
