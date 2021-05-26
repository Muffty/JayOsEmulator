#ifndef __RACER
#define __RACER

#include "Games.cpp"

class Racer : public OsGame
{

	uint32_t racer_playerColorA = color(251, 242, 54); // yellowish
	uint32_t racer_playerColorB = color(172, 50, 50);  // redish

	byte racer_playerA_X[32] = { 5, 5, 5, 5, 5, 5, 4, 3, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6 };
	byte racer_playerA_Y[32] = { 8, 9, 10, 11, 12, 13, 13, 13, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7 };

	byte racer_playerB_X[32] = { 6, 6, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 4, 5, 5, 5, 5, 5, 5 };
	byte racer_playerB_Y[32] = { 8, 9, 10, 11, 12, 13, 14, 14, 14, 14, 14, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 2, 2, 2, 3, 4, 5, 6, 7 };

	byte racer_playerA_pos;
	byte racer_playerB_pos;
	bool racer_playerA_1key;
	bool racer_playerB_1key;
	byte racer_playerA_laps;
	byte racer_playerB_laps;
	byte racer_playerA_lapsPenalty;
	byte racer_playerB_lapsPenalty;

public:
	virtual void ResetState()
	{
		racer_playerA_pos = 0;
		racer_playerB_pos = 0;
		racer_playerA_1key = false;
		racer_playerB_1key = false;
		racer_playerA_laps = 0;
		racer_playerB_laps = 0;
		racer_playerA_lapsPenalty = 0;
		racer_playerB_lapsPenalty = 0;
	}
	virtual void Draw(JayScreen* screen)
	{

		// Map
		uint32_t frameColor = color(10, 15, 24); // Blueish
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 16; y++)
			{
				if (y == 0 || y == 15 || x == 0 || x == 7 || ((x == 3 || x == 4) && (y >= 3 && y <= 12)))
					screen->ShowPixel(x, y, frameColor);
			}
		}

		screen->ShowPixel(racer_playerA_X[racer_playerA_pos], racer_playerA_Y[racer_playerA_pos], racer_playerColorA);

		screen->ShowPixel(racer_playerB_X[racer_playerB_pos], racer_playerB_Y[racer_playerB_pos], racer_playerColorB);

		for (int i = 0; i < racer_playerA_laps; i++)
		{
			screen->ShowPixel(0, i, racer_playerColorA);
		}
		for (int i = 0; i < racer_playerB_laps; i++)
		{
			screen->ShowPixel(7, i, racer_playerColorB);
		}
	}

	virtual void HandleInput(bool button_pressed[4], bool button_downEvent[4], bool button_upEvent[4])
	{
		HandleInputForPlayer(racer_playerA_1key, racer_playerA_pos, racer_playerA_laps, racer_playerA_lapsPenalty, 0, 1, button_pressed, button_downEvent, button_upEvent);
		HandleInputForPlayer(racer_playerB_1key, racer_playerB_pos, racer_playerB_laps, racer_playerB_lapsPenalty, 2, 3, button_pressed, button_downEvent, button_upEvent);
		
		/*
		//Players
		if (!racer_playerA_1key && button_downEvent[0])
		{ //Incorrect
			racer_playerA_pos--;
		}
		else if (racer_playerA_1key && button_downEvent[1])
		{ //Incorrect
			racer_playerA_pos--;
		}
		else if (racer_playerA_1key && button_downEvent[0])
		{ //Correct
			racer_playerA_pos++;
			racer_playerA_1key = !racer_playerA_1key;
		}
		else if (!racer_playerA_1key && button_downEvent[1])
		{ //Correct
			racer_playerA_pos++;
			racer_playerA_1key = !racer_playerA_1key;
		}
		if (racer_playerA_pos > 32)
		{
			racer_playerA_pos = 31;
			racer_playerA_lapsPenalty++;
		}
		if (racer_playerA_pos == 32)
		{
			if (racer_playerA_lapsPenalty > 0)
				racer_playerA_lapsPenalty--;
			else
				racer_playerA_laps++;
			racer_playerA_pos = 0;
		}

		if (!racer_playerB_1key && button_downEvent[2])
		{ //Incorrect
			racer_playerB_pos--;
		}
		else if (racer_playerB_1key && button_downEvent[3])
		{ //Incorrect
			racer_playerB_pos--;
		}
		else if (racer_playerB_1key && button_downEvent[2])
		{ //Correct
			racer_playerB_pos++;
			racer_playerB_1key = !racer_playerB_1key;
		}
		else if (!racer_playerB_1key && button_downEvent[3])
		{ //Correct
			racer_playerB_pos++;
			racer_playerB_1key = !racer_playerB_1key;
		}
		if (racer_playerB_pos > 32)
		{
			racer_playerB_pos = 31;
			racer_playerB_lapsPenalty++;
		}
		if (racer_playerB_pos == 32)
		{

			if (racer_playerB_lapsPenalty > 0)
				racer_playerB_lapsPenalty--;
			else
				racer_playerB_laps++;
			racer_playerB_pos = 0;
		}*/
	}
	void HandleInputForPlayer(bool& AsTurn, byte& positon, byte& lap, byte& penalty, byte playerA, byte playerB, bool button_pressed[4], bool button_downEvent[4], bool button_upEvent[4]) {
		if (!AsTurn && button_downEvent[playerA])
		{ //Incorrect
			positon--;
		}
		else if (AsTurn && button_downEvent[playerB])
		{ //Incorrect
			positon--;
		}
		else if (AsTurn && button_downEvent[playerA])
		{ //Correct
			positon++;
			AsTurn = !AsTurn;
		}
		else if (!AsTurn && button_downEvent[playerB])
		{ //Correct
			positon++;
			AsTurn = !AsTurn;
		}
		if (positon > 32)
		{
			positon = 31;
			penalty++;
		}
		if (positon == 32)
		{
			if (penalty > 0)
				penalty--;
			else
				lap++;
			positon = 0;
		}
	}
};

#endif // GUARD