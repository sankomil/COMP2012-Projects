/*
 * View.cpp
 *
 *  Created on: Feb 24, 2016
 *      Author: kevinw
 */

#include "View.h"
#include "Tower.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>

using namespace std;

/**
 * Reason for not moving the following parameters to definition.h is to allow
 * further extension of the view class. For example one may like to extend a GUI
 * view class using Qt!
 *
 * But the size of ARENA does matter as it is governing the logic of arena. So these
 * parameters are actually defined somewhere else.
 */

extern const int ARENA_W;
extern const int ARENA_H;
extern const int TOWER_X;

const int ARENA_BOX_W = ARENA_W + 2;
const int ARENA_BOX_H = ARENA_H + 2;


const int MSG_X = 0;
const int MSG_Y = 0; //ARENA_BOX_H + ARENA_Y;
const int MSG_W = ARENA_BOX_W;
const int MSG_H = 5;


const int ARENA_X = 0;
const int ARENA_Y = MSG_H;


const int STAT_X = 0;
const int STAT_Y = ARENA_Y + ARENA_BOX_H;
const int STAT_H = 8;
const int STAT_W = 25;

const int COMM_Y = STAT_Y;
const int COMM_X = STAT_X + STAT_W;
const int COMM_H = STAT_H;
const int COMM_W = ARENA_BOX_W - STAT_W;

const char* TOWER_COMMANDS[] = { "Destroy", "Upgrade", "Cancel" };
const char* MENUS[] = { "End Main Turns", "Build", "Cancel" };
const char* TOWERS[] = {"Simple Tower","Catapult", "Laser",  "Ice Tower", "Cancel"};
enum {UP, DOWN, LEFT, RIGHT};


View::View(Arena* aArena) : arena(aArena)
{
	initscr();
	clear();
	noecho();
	curs_set(0);
	cbreak(); /* Line buffering disabled. pass on everything */

	keypad(stdscr, TRUE);
	raw();
	nonl();

	cursor_x = 0;
	cursor_y = 0;

	refresh();

	msg_win_box = newwin(MSG_H, MSG_W, MSG_Y, MSG_X);
	box(msg_win_box, 0, 0);
	wrefresh(msg_win_box);
	arena_win_box = newwin(ARENA_BOX_H, ARENA_BOX_W, ARENA_Y, ARENA_X);
	box(arena_win_box, 0, 0);
	wrefresh(arena_win_box);
	stat_win_box = newwin(STAT_H, STAT_W, STAT_Y, STAT_X);
	box(stat_win_box, 0, 0);
	wrefresh(stat_win_box);
	comm_win_box = newwin(COMM_H, COMM_W, COMM_Y, COMM_X);
	box(comm_win_box, 0, 0);
	wrefresh(comm_win_box);

	msg_win = newwin(MSG_H - 2, MSG_W - 2, MSG_Y + 1, MSG_X + 1);
	wrefresh(msg_win);
	arena_win = newwin(ARENA_H, ARENA_W, ARENA_Y + 1, ARENA_X + 1);
	wrefresh(arena_win);
	stat_win = newwin(STAT_H - 2, STAT_W - 2, STAT_Y + 1, STAT_X + 1);
	wrefresh(stat_win);
	comm_win = newwin(COMM_H - 2, COMM_W - 2, COMM_Y + 1, COMM_X + 1);
	wrefresh(comm_win);

}

View::~View() {
	clrtoeol();
	refresh();
	endwin();
	delwin(msg_win);
	delwin(comm_win);
	delwin(stat_win);
	delwin(arena_win);
	delwin(msg_win_box);
	delwin(arena_win_box);
	delwin(stat_win_box);
	delwin(comm_win_box);
}

void View::renderArena() {
	const Object** objects;
	int num_objects;

	bool cursor_display = false;
	wclear(arena_win);

	arena->getConstObjects(objects, num_objects);

	for (int i = 0; i < num_objects; i++) {
		int x, y;

		const Object* r = objects[i];
		r->getXY(x, y);
		char c = r->getName().at(0);


		wattron(arena_win, A_BOLD);

		if (cursor_x == x && cursor_y == y) {
			wattron(arena_win, A_REVERSE);
			mvwaddch(arena_win, y, x, c);
			wattroff(arena_win, A_REVERSE);
			cursor_display = true;
		} else {
			mvwaddch(arena_win, y, x, c);
		}


		wattroff(arena_win, A_BOLD);
	}


	delete [] objects;
	if (!cursor_display) {
		wattron(arena_win, A_BLINK);
		mvwaddch(arena_win, cursor_y, cursor_x, '@');
		wattroff(arena_win, A_BLINK);
	}
	for (int i = 0; i < ARENA_H; i++)
		mvwaddch(arena_win, i, TOWER_X, '<' );

	mvwprintw(arena_win, 1, TOWER_X + 1, "End");
	mvwprintw(arena_win, 3, TOWER_X + 1, "Zone");
	wrefresh(arena_win);


}

void View::renderRange(const Tower* r) {
	wattron(arena_win, A_REVERSE);

	for (int i = 0; i < ARENA_W; i++)
		for (int j = 0; j < ARENA_H; j++) {
			//print the highlighted map except for existing Object, cursor, and unreachable area
			if (arena->getObjectAt(i, j) == nullptr && r->isInRange(i, j)
					&& !(i == cursor_x && j == cursor_y)) {
				mvwaddch(arena_win, j, i, ' ');
			}
		}

	wattroff(arena_win, A_REVERSE);
	wrefresh(arena_win);
}

void View::displayMessage(string message) {
	wclear(msg_win);
	mvwprintw(msg_win, 0, 0, message.c_str());
	wrefresh(msg_win);
}

void View::renderStat(const Object* obj) {
	wclear(stat_win);
	wrefresh(stat_win);
	int line = 1;
	stringstream m;

	if (obj == nullptr && (obj = arena->getObjectAt(cursor_x, cursor_y)) == nullptr) {
		m << "Current Money: " << arena->getMoney() << endl;
		m << "Enemy Kill: " << arena->getEnemyKill();
		mvwprintw(stat_win, line++, 0, m.str().c_str());
	} else {
		m << "Name: " << obj->getName();
		mvwprintw(stat_win, line++, 0, m.str().c_str());
		m.str("");
		m.clear();

		m << (*obj);
		mvwprintw(stat_win, line++, 0, m.str().c_str());
		m.str("");
		m.clear();

		if (obj->getObjectType() == ObjectType::TOWER)
			renderRange(static_cast<const Tower*>(obj));
	}

	wrefresh(stat_win);
}

void View::renderCommand(int cmd, int opt) {
	wclear(comm_win);
	int lastopt;
	const char** cmdText;

	switch (cmd) {
	case CMD_LIST:
		lastopt = LAST_OPTION;
		cmdText = TOWER_COMMANDS;
		break;
	case MENU_LIST:
		lastopt = M_LAST_OPTION;
		cmdText = MENUS;
		break;
	case BUILD_LIST:
		lastopt = T_LAST_OPTION;
		cmdText = TOWERS;
		break;
	}

	for (int i = 0; i <= lastopt; i++) {
		if (opt == i) { //highlight that one
			wattron(comm_win, A_REVERSE);
			mvwprintw(comm_win, i, 0, cmdText[i]);
			wattroff(comm_win, A_REVERSE);
		} else
			mvwprintw(comm_win, i, 0, cmdText[i]);
	}

	wrefresh(comm_win);
}



void View::renderAll() {
	renderArena();
	const Object* r = arena->getObjectAt(cursor_x, cursor_y);

	if (r != nullptr)
		renderStat(r);
}

/*************************************************************************
 *
 * Input handlers
 *
 *
 *************************************************************************/

void View::pause(string message) {
	message += "\nHit any key to continue..";
	displayMessage(message);
	getch();
	wclear(msg_win);
	wrefresh(msg_win);
}



int View::handleCommand(int cmd) {

	int ch;

	int lastopt;
	switch (cmd) {
	case CMD_LIST: lastopt = LAST_OPTION; break;
	case MENU_LIST: lastopt = M_LAST_OPTION; break;
	case BUILD_LIST: lastopt = T_LAST_OPTION; break;
	}
	int option = 0; // to return this value after all;

	renderCommand(cmd, option);
	displayMessage(string("Use Up/Down arrows and Enter/Space to select"));
	while ((ch = getch()) != KEY_F(1) && ch != 'q' && ch != 'Q') {
		switch (ch) {
		case KEY_UP:
			option--;
			if (option == -1)
				option = lastopt;
			break;
		case KEY_DOWN:
			option++;
			if (option > lastopt)
				option = 0;
			break;
		case '\n':case KEY_ENTER: case '\r':
		case ' ':
			return option;
		}

		renderCommand(cmd, option);
	}

	return EXIT;
}


void View::moveCursor(int d) {
	switch (d) {
	case UP:
		if (cursor_y > 0)
			cursor_y--;
		break;
	case DOWN:
		if (cursor_y < ARENA_H - 1)  // from 0 to ARENA_H - 1, height = ARENA_H
			cursor_y++;
		break;
	case LEFT:
		if (cursor_x > 0)
			cursor_x--;
		break;
	case RIGHT:
		if (cursor_x < ARENA_W - 1)
			cursor_x++;
		break;
	}
}

int View::handleNavigate(int& x, int&y) {
	string message = "Use Up/Down/Left/Right arrows to navigate and Enter/Space to select. Press F1 or Q to exit";
	int ch;

	displayMessage(message);
	renderStat();
	renderArena();
	wclear(comm_win);
	wrefresh(comm_win);

	while ((ch = getch()) != KEY_F(1) && ch != 'q' && ch != 'Q') {
		switch (ch) {

		case KEY_UP:
			message += "UP KEY";
			moveCursor(UP);
			break;
		case KEY_DOWN:
			message += "DOWN KEY";
			moveCursor(DOWN);
			break;
		case KEY_LEFT:
			message += "LEFT KEY";
			moveCursor(LEFT);
			break;
		case KEY_RIGHT:
			message += "RIGHT KEY";
			moveCursor(RIGHT);
			break;
		case '\n':case KEY_ENTER: case '\r':
		case ' ':
			x = cursor_x;
			y = cursor_y;
			return OKAY;
		}

		renderArena();
		renderStat();
	}

	return EXIT;
}


