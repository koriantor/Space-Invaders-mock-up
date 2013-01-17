#include "State.h"



State::State(){}
 
State::State(bool* keys0, ALLEGRO_EVENT_QUEUE* event_queue0){
	keys = keys0;
	event_queue= event_queue0;

	done = false;
	render = true;
}

//*****************************************************
//basic outline for a state function with the loop
//*****************************************************
//int DoState{
//	//**GAME LOOP****GAME LOOP****GAME LOOP**
//	while(!done){
//		ALLEGRO_EVENT ev;
//		al_wait_for_event(*event_queue, &ev);
//
//		executeEvent(ev);
//
//	}
//
//	return next_state;
//}

//STATES State::StateFunction(){
//	return EXIT;
//}




//********************
//Function will call the appropriate function to handle the event handed to it
// (Does not necessarily need to be overloaded by shild class)
//
//********************

void State::executeEvent(ALLEGRO_EVENT ev0){
	
	//key down events
	if (ev0.type == ALLEGRO_EVENT_KEY_DOWN){
		keyDownEvents(ev0);
	}

	//key up events
	else if (ev0.type == ALLEGRO_EVENT_KEY_UP){
		keyUpEvents(ev0);
	}

	//timer events(frame refresh)
	else if (ev0.type == ALLEGRO_EVENT_TIMER){
		timerEvent();
	}
}


//********************
// Catch all function to store a key as pressed
// (Does not necessarily need to oveloaded by child class)
//
//********************

void State::keyDownEvents(ALLEGRO_EVENT ev0){

	switch(ev0.keyboard.keycode){
		
	case ALLEGRO_KEY_A		:keys[KEY_A] = true; break;
	case ALLEGRO_KEY_B		:keys[KEY_B] = true; break;
	case ALLEGRO_KEY_C		:keys[KEY_C] = true; break;
	case ALLEGRO_KEY_D		:keys[KEY_D] = true; break;
	case ALLEGRO_KEY_E		:keys[KEY_E] = true; break;
	case ALLEGRO_KEY_F		:keys[KEY_F] = true; break;
	case ALLEGRO_KEY_G		:keys[KEY_G] = true; break;
	case ALLEGRO_KEY_H		:keys[KEY_H] = true; break;
	case ALLEGRO_KEY_I		:keys[KEY_I] = true; break;
	case ALLEGRO_KEY_J		:keys[KEY_J] = true; break;
	case ALLEGRO_KEY_K		:keys[KEY_K] = true; break;
	case ALLEGRO_KEY_L		:keys[KEY_L] = true; break;
	case ALLEGRO_KEY_M		:keys[KEY_M] = true; break;
	case ALLEGRO_KEY_N		:keys[KEY_N] = true; break;
	case ALLEGRO_KEY_O		:keys[KEY_O] = true; break;
	case ALLEGRO_KEY_P		:keys[KEY_P] = true; break;
	case ALLEGRO_KEY_Q		:keys[KEY_Q] = true; break;
	case ALLEGRO_KEY_R		:keys[KEY_R] = true; break;
	case ALLEGRO_KEY_S		:keys[KEY_S] = true; break;
	case ALLEGRO_KEY_T		:keys[KEY_T] = true; break;
	case ALLEGRO_KEY_U		:keys[KEY_U] = true; break;
	case ALLEGRO_KEY_V		:keys[KEY_V] = true; break;
	case ALLEGRO_KEY_W		:keys[KEY_W] = true; break;
	case ALLEGRO_KEY_X		:keys[KEY_X] = true; break;
	case ALLEGRO_KEY_Y		:keys[KEY_Y] = true; break;
	case ALLEGRO_KEY_Z		:keys[KEY_Z] = true; break;

	case ALLEGRO_KEY_0		:keys[KEY_0] = true; break;
	case ALLEGRO_KEY_1		:keys[KEY_1] = true; break;
	case ALLEGRO_KEY_2		:keys[KEY_2] = true; break;
	case ALLEGRO_KEY_3		:keys[KEY_3] = true; break;
	case ALLEGRO_KEY_4		:keys[KEY_4] = true; break;
	case ALLEGRO_KEY_5		:keys[KEY_5] = true; break;
	case ALLEGRO_KEY_6		:keys[KEY_6] = true; break;
	case ALLEGRO_KEY_7		:keys[KEY_7] = true; break;
	case ALLEGRO_KEY_8		:keys[KEY_8] = true; break;
	case ALLEGRO_KEY_9		:keys[KEY_9] = true; break;

	case ALLEGRO_KEY_F1			:keys[KEY_F1] = true; break;
	case ALLEGRO_KEY_F2			:keys[KEY_F2] = true; break;
	case ALLEGRO_KEY_F3			:keys[KEY_F3] = true; break;
	case ALLEGRO_KEY_F4			:keys[KEY_F4] = true; break;
	case ALLEGRO_KEY_F5			:keys[KEY_F5] = true; break;
	case ALLEGRO_KEY_F6			:keys[KEY_F6] = true; break;
	case ALLEGRO_KEY_F7			:keys[KEY_F7] = true; break;
	case ALLEGRO_KEY_F8			:keys[KEY_F8] = true; break;
	case ALLEGRO_KEY_F9			:keys[KEY_F9] = true; break;
	case ALLEGRO_KEY_F10		:keys[KEY_F10] = true; break;
	case ALLEGRO_KEY_F11		:keys[KEY_F11] = true; break;
	case ALLEGRO_KEY_F12		:keys[KEY_F12] = true; break;

	case ALLEGRO_KEY_ESCAPE		:keys[KEY_ESCAPE] = true; break;
	case ALLEGRO_KEY_TILDE		:keys[KEY_TILDE] = true; break;
	case ALLEGRO_KEY_MINUS		:keys[KEY_MINUS] = true; break;
	case ALLEGRO_KEY_EQUALS		:keys[KEY_EQUALS] = true; break;
	case ALLEGRO_KEY_BACKSPACE	:keys[KEY_BACKSPACE] = true; break;
	case ALLEGRO_KEY_TAB		:keys[KEY_TAB] = true; break;
	case ALLEGRO_KEY_OPENBRACE	:keys[KEY_OPENBRACE] = true; break;
	case ALLEGRO_KEY_CLOSEBRACE	:keys[KEY_CLOSEBRACE] = true; break;
	case ALLEGRO_KEY_ENTER		:keys[KEY_ENTER] = true; break;
	case ALLEGRO_KEY_SEMICOLON	:keys[KEY_SEMICOLON] = true; break;
	case ALLEGRO_KEY_QUOTE		:keys[KEY_QUOTE] = true; break;
	case ALLEGRO_KEY_BACKSLASH	:keys[KEY_BACKSLASH] = true; break;
	case ALLEGRO_KEY_COMMA		:keys[KEY_COMMA] = true; break;
	case ALLEGRO_KEY_FULLSTOP	:keys[KEY_FULLSTOP] = true; break;
	case ALLEGRO_KEY_SLASH		:keys[KEY_SLASH] = true; break;
	case ALLEGRO_KEY_SPACE		:keys[KEY_SPACE] = true; break;

	case ALLEGRO_KEY_INSERT		:keys[KEY_INSERT] = true; break;
	case ALLEGRO_KEY_DELETE		:keys[KEY_DELETE] = true; break;
	case ALLEGRO_KEY_HOME		:keys[KEY_HOME] = true; break;
	case ALLEGRO_KEY_END		:keys[KEY_END] = true; break;
	case ALLEGRO_KEY_PGUP		:keys[KEY_PGUP] = true; break;
	case ALLEGRO_KEY_PGDN		:keys[KEY_PGDN] = true; break;
	case ALLEGRO_KEY_LEFT		:keys[KEY_LEFT] = true; break;
	case ALLEGRO_KEY_RIGHT		:keys[KEY_RIGHT] = true; break;
	case ALLEGRO_KEY_UP			:keys[KEY_UP] = true; break;
	case ALLEGRO_KEY_DOWN		:keys[KEY_DOWN] = true; break;

	}
}

//********************
// Catch-all fucntion to store a key as not pressed
// (Does not necessarily need to oveloaded by child class)
//
//********************

void State::keyUpEvents(ALLEGRO_EVENT ev0){

	switch(ev0.keyboard.keycode){

	case ALLEGRO_KEY_A		:keys[KEY_A] = false; break;
	case ALLEGRO_KEY_B		:keys[KEY_B] = false; break;
	case ALLEGRO_KEY_C		:keys[KEY_C] = false; break;
	case ALLEGRO_KEY_D		:keys[KEY_D] = false; break;
	case ALLEGRO_KEY_E		:keys[KEY_E] = false; break;
	case ALLEGRO_KEY_F		:keys[KEY_F] = false; break;
	case ALLEGRO_KEY_G		:keys[KEY_G] = false; break;
	case ALLEGRO_KEY_H		:keys[KEY_H] = false; break;
	case ALLEGRO_KEY_I		:keys[KEY_I] = false; break;
	case ALLEGRO_KEY_J		:keys[KEY_J] = false; break;
	case ALLEGRO_KEY_K		:keys[KEY_K] = false; break;
	case ALLEGRO_KEY_L		:keys[KEY_L] = false; break;
	case ALLEGRO_KEY_M		:keys[KEY_M] = false; break;
	case ALLEGRO_KEY_N		:keys[KEY_N] = false; break;
	case ALLEGRO_KEY_O		:keys[KEY_O] = false; break;
	case ALLEGRO_KEY_P		:keys[KEY_P] = false; break;
	case ALLEGRO_KEY_Q		:keys[KEY_Q] = false; break;
	case ALLEGRO_KEY_R		:keys[KEY_R] = false; break;
	case ALLEGRO_KEY_S		:keys[KEY_S] = false; break;
	case ALLEGRO_KEY_T		:keys[KEY_T] = false; break;
	case ALLEGRO_KEY_U		:keys[KEY_U] = false; break;
	case ALLEGRO_KEY_V		:keys[KEY_V] = false; break;
	case ALLEGRO_KEY_W		:keys[KEY_W] = false; break;
	case ALLEGRO_KEY_X		:keys[KEY_X] = false; break;
	case ALLEGRO_KEY_Y		:keys[KEY_Y] = false; break;
	case ALLEGRO_KEY_Z		:keys[KEY_Z] = false; break;

	case ALLEGRO_KEY_0		:keys[KEY_0] = false; break;
	case ALLEGRO_KEY_1		:keys[KEY_1] = false; break;
	case ALLEGRO_KEY_2		:keys[KEY_2] = false; break;
	case ALLEGRO_KEY_3		:keys[KEY_3] = false; break;
	case ALLEGRO_KEY_4		:keys[KEY_4] = false; break;
	case ALLEGRO_KEY_5		:keys[KEY_5] = false; break;
	case ALLEGRO_KEY_6		:keys[KEY_6] = false; break;
	case ALLEGRO_KEY_7		:keys[KEY_7] = false; break;
	case ALLEGRO_KEY_8		:keys[KEY_8] = false; break;
	case ALLEGRO_KEY_9		:keys[KEY_9] = false; break;

	case ALLEGRO_KEY_F1			:keys[KEY_F1] = false; break;
	case ALLEGRO_KEY_F2			:keys[KEY_F2] = false; break;
	case ALLEGRO_KEY_F3			:keys[KEY_F3] = false; break;
	case ALLEGRO_KEY_F4			:keys[KEY_F4] = false; break;
	case ALLEGRO_KEY_F5			:keys[KEY_F5] = false; break;
	case ALLEGRO_KEY_F6			:keys[KEY_F6] = false; break;
	case ALLEGRO_KEY_F7			:keys[KEY_F7] = false; break;
	case ALLEGRO_KEY_F8			:keys[KEY_F8] = false; break;
	case ALLEGRO_KEY_F9			:keys[KEY_F9] = false; break;
	case ALLEGRO_KEY_F10		:keys[KEY_F10] = false; break;
	case ALLEGRO_KEY_F11		:keys[KEY_F11] = false; break;
	case ALLEGRO_KEY_F12		:keys[KEY_F12] = false; break;

	case ALLEGRO_KEY_ESCAPE		:keys[KEY_ESCAPE] = false; break;
	case ALLEGRO_KEY_TILDE		:keys[KEY_TILDE] = false; break;
	case ALLEGRO_KEY_MINUS		:keys[KEY_MINUS] = false; break;
	case ALLEGRO_KEY_EQUALS		:keys[KEY_EQUALS] = false; break;
	case ALLEGRO_KEY_BACKSPACE	:keys[KEY_BACKSPACE] = false; break;
	case ALLEGRO_KEY_TAB		:keys[KEY_TAB] = false; break;
	case ALLEGRO_KEY_OPENBRACE	:keys[KEY_OPENBRACE] = false; break;
	case ALLEGRO_KEY_CLOSEBRACE	:keys[KEY_CLOSEBRACE] = false; break;
	case ALLEGRO_KEY_ENTER		:keys[KEY_ENTER] = false; break;
	case ALLEGRO_KEY_SEMICOLON	:keys[KEY_SEMICOLON] = false; break;
	case ALLEGRO_KEY_QUOTE		:keys[KEY_QUOTE] = false; break;
	case ALLEGRO_KEY_BACKSLASH	:keys[KEY_BACKSLASH] = false; break;
	case ALLEGRO_KEY_COMMA		:keys[KEY_COMMA] = false; break;
	case ALLEGRO_KEY_FULLSTOP	:keys[KEY_FULLSTOP] = false; break;
	case ALLEGRO_KEY_SLASH		:keys[KEY_SLASH] = false; break;
	case ALLEGRO_KEY_SPACE		:keys[KEY_SPACE] = false; break;

	case ALLEGRO_KEY_INSERT		:keys[KEY_INSERT] = false; break;
	case ALLEGRO_KEY_DELETE		:keys[KEY_DELETE] = false; break;
	case ALLEGRO_KEY_HOME		:keys[KEY_HOME] = false; break;
	case ALLEGRO_KEY_END		:keys[KEY_END] = false; break;
	case ALLEGRO_KEY_PGUP		:keys[KEY_PGUP] = false; break;
	case ALLEGRO_KEY_PGDN		:keys[KEY_PGDN] = false; break;
	case ALLEGRO_KEY_LEFT		:keys[KEY_LEFT] = false; break;
	case ALLEGRO_KEY_RIGHT		:keys[KEY_RIGHT] = false; break;
	case ALLEGRO_KEY_UP			:keys[KEY_UP] = false; break;
	case ALLEGRO_KEY_DOWN		:keys[KEY_DOWN] = false; break;

	}
}

//********************
// Timer/Screen update function
// (DOES NEED to be implemented by child class)
//
//********************

void State::timerEvent(){}