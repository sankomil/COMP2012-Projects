/**
 * View.h
 *
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "Arena.h"
#ifdef _WIN_
#include "./ncurses_lib/curses.h"
#else
#include <curses.h>
#endif
#include <string.h>

#include "Object.h"
#include "Enemy.h"
#include "Tower.h"
#include "definition.h"

/**
 * This is the View class is the MVC model. It is responsible for rendering screen and to do
 * simple interaction with the user. A sequence of key strokes will be turned to a command or option
 * and return to its caller - the controller.
 *
 * In order to display correct information, the View class also has some model class with it.
 */
class View {
public:

	/**
	 * Constructor.
	 */
	View(Arena*);
	/**
	 * Destructor
	 */
	virtual ~View();
	/**
	 * To display certain message on the screen
	 */
	virtual void displayMessage(std::string);

	/**
	 * During the Navigate state, the View class asks the user to freely navigate on the arena and
	 * select a cell, which can be empty or with a robot. When the cursor moves on a Robot,
	 * it will also render the statistics of the robot.
	 *
	 */
	virtual int handleNavigate(int&, int&);

	/**
	 * During the Command state and the Menu state, the View class asks the user to pick one of the commands
	 * from the command box. It triggers the next stage.
	 */
	virtual int handleCommand(int);

	/**
	 * To display a message and pause for a key stroke
	 *
	 */
	virtual void pause(std::string = "");

	/**
	 * To render all windows
	 */
	virtual void renderAll();

private:
	/**
	 * To render the Arean windows;
	 */ 
	virtual void renderArena();

	/**
	 * To render the fire Range of a Tower.
	 */ 	
	virtual void renderRange(const Tower*);

	/**
	 * To render the Stat windows with the selected object
	 */ 
	virtual void renderStat(const Object* = nullptr);

	/**
	 * To render the command list.
	 */
	virtual void renderCommand(int, int);

	/**
	 * The arena model.
	 */
	Arena* arena;

	void moveCursor(int);
	int cursor_x, cursor_y;
	WINDOW *msg_win, *arena_win, *stat_win, *comm_win;
	WINDOW *msg_win_box, *arena_win_box, *stat_win_box, *comm_win_box;
};

#endif /* VIEW_H_ */
