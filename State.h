#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include "Keys.h"
#include "Constants.h"

#pragma once



class State{
protected:

	//******************
	// STATE VARIABLES
	//******************

	bool* keys;
	ALLEGRO_EVENT_QUEUE* event_queue;
	
	bool done;
	bool render;

	STATES next_state;
	
	//*******************

public:

	State();

	State(bool* keys0, ALLEGRO_EVENT_QUEUE* event_queue0);

	virtual STATES StateFunction() = 0;


	//********************************
	// EVENT-HANDLING FUNCTIONS
	//********************************

	void executeEvent(ALLEGRO_EVENT ev0);

	void keyDownEvents(ALLEGRO_EVENT ev0);
	void keyUpEvents(ALLEGRO_EVENT ev0);

	virtual void timerEvent();


	// Event for every key (other special keys found in keycodes.h)
	void Key_A_Events();
	void Key_B_Events();
	void Key_C_Events();
	void Key_D_Events();
	void Key_E_Events();
	void Key_F_Events();
	void Key_G_Events();
	void Key_H_Events();
	void Key_I_Events();
	void Key_J_Events();
	void Key_K_Events();
	void Key_L_Events();
	void Key_M_Events();
	void Key_N_Events();
	void Key_O_Events();
	void Key_P_Events();
	void Key_Q_Events();
	void Key_R_Events();
	void Key_S_Events();
	void Key_T_Events();
	void Key_U_Events();
	void Key_V_Events();
	void Key_W_Events();
	void Key_X_Events();
	void Key_Y_Events();
	void Key_Z_Events();

	void Key_0_Events();
	void Key_1_Events();
	void Key_2_Events();
	void Key_3_Events();
	void Key_4_Events();
	void Key_5_Events();
	void Key_6_Events();
	void Key_7_Events();
	void Key_8_Events();
	void Key_9_Events();

	void Key_F1_Events();
	void Key_F2_Events();
	void Key_F3_Events();
	void Key_F4_Events();
	void Key_F5_Events();
	void Key_F6_Events();
	void Key_F7_Events();
	void Key_F8_Events();
	void Key_F9_Events();
	void Key_F10_Events();
	void Key_F11_Events();
	void Key_F12_Events();


	void Key_ESCAPE_Events();
	void Key_TILDE_Events();
	void Key_MINUS_Events();
	void Key_EQUALS_Events();
	void Key_BACKSPACE_Events();
	void Key_TAB_Events();
	void Key_OPENBRACE_Events();
	void Key_CLOSEBRACE_Events();
	void Key_ENTER_Events();
	void Key_SEMICOLON_Events();
	void Key_QUOTE_Events();
	void Key_BACKSLASH_Events();
	void Key_COMMA_Events();
	void Key_FULLSTOP_Events();
	void Key_SLASH_Events();
	void Key_SPACE_Events();

	void Key_INSERT_Events();
	void Key_DELETE_Events();
	void Key_HOME_Events();
	void Key_END_Events();
	void Key_PGUP_Events();
	void Key_PGDN_Events();
	void Key_LEFT_Events();
	void Key_RIGHT_Events();
	void Key_UP_Events();
	void Key_DOWN_Events();

	//*******************************


};