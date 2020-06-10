/*
 * definition.h
 *
 */

#ifndef DEFINITION_H_
#define DEFINITION_H_

#define _DEBUG_
/**
 * enum classes that are related to your implementation.
 */
enum class ObjectType {ENEMY, TOWER};

enum class ObjectState {NORMAL, DEAD, FROZEN, LAST=FROZEN};


/**
 * enum that used in Controller and View class only.
 *
 */

enum gamestate {NAVIGATE, BUILDING, TOWER_COMMAND};

enum {T_DESTROY, T_UPGRADE, T_CANCEL, LAST_OPTION=T_CANCEL, FIRST_OPTION=T_DESTROY};
enum {ABORT = -2, EXIT = -1, OKAY};
enum {CMD_LIST, MENU_LIST, BUILD_LIST};
enum {M_END_TURN, M_BUILD, M_CANCEL, M_LAST_OPTION=M_CANCEL, M_FIRST_OPTION=M_END_TURN};
enum {SIMPLE_TOWER, CATAPULT_TOWER, LASER_TOWER, ICE_TOWER, CANCEL_T, T_FIRST_OPTION=SIMPLE_TOWER, T_LAST_OPTION=CANCEL_T};


enum class Command {
	ERROR = -1,
	SPACE_BUILD, END_TURN,
	TOWER_UPGRADE, TOWER_DESTROY, TOWER_REPAIR,
	ENEMY_CHEAT_DESTROY
};



#endif /* DEFINITION_H_ */
