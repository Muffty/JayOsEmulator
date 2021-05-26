#ifndef __MAINOS
#define __MAINOS
#include <wx/wx.h>
#include "Games.cpp"
#include "Racer.cpp"
#include "Pong.cpp"

class InputSystem {


	void Pressed(int button);
	void Released(int button);
public:
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);
	void Reset();

	bool button_pressed[4];
	bool button_downEvent[4];
	bool button_upEvent[4];
};


class JayOS
{
	JayScreen* screen;
	OsGame* currentGame;
	int gameNr = 0;
	byte resetCounter;
	bool gameReset;

	void ReadButtons() {
	}

public:
	JayOS(JayScreen* screen):
		screen(screen),
		currentGame(new Pong())
	{}


	void Update(InputSystem* inputs)
	{
		screen->ClearPixels();
		ReadButtons();
		currentGame->HandleInput(inputs->button_pressed, inputs->button_downEvent, inputs->button_upEvent);
		currentGame->Draw(screen);
	}

};


#endif // __MAINOS