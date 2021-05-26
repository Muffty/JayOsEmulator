#ifndef __Pong
#define __Pong

#include "Games.cpp"

class Pong : public OsGame
{


	int pong_playerA_X = 3;
	int pong_playerB_X = 3;
	float pong_ballY = 8;
	float pong_ballX = 3;
	float pong_ballYD = 0.05;
	float pong_ballXD = 0;
	int pong_scoreA;
	int pong_scoreB;
	int playerHits;


public:
	void ResetState()
	{
		//Reset game variables
		pong_scoreA = 0;
		pong_scoreB = 0;
		pong_resetBall();
	}
	void pong_resetBall()
	{
		pong_ballX = 3;
		pong_ballY = 8;
		pong_ballYD = 0.05;
		pong_ballXD = 0;
		pong_playerA_X = 3;
		pong_playerB_X = 3;
		playerHits = 0;
	}

	void Draw(JayScreen* screen)
	{
		//Score
		uint32_t lightGray = color(20, 20, 20); // redish
		screen->draw5x4Number(pong_scoreA, 2, 2, lightGray);
		screen->draw5x4Number(pong_scoreB, 2, 9, lightGray);

		uint32_t white = color(100, 100, 100); // redish

		//Ball
		screen->ShowPixel(round(pong_ballX), round(pong_ballY), white);

		//PlayerA
		for (int i = -1; i <= 1; i++)
		{
			screen->ShowPixel(pong_playerA_X + i, 0, white);
		}

		//PlayerB
		for (int i = -1; i <= 1; i++)
		{
			screen->ShowPixel(pong_playerB_X + i, 15, white);
		}
	}

	void HandleInput(bool button_pressed[4], bool button_downEvent[4], bool button_upEvent[4])
	{


		pong_ballY += pong_ballYD;
		pong_ballX += pong_ballXD;

		if (pong_ballX < 0)
		{
			pong_ballXD = -pong_ballXD;
			pong_ballX = pong_ballXD;
		}
		if (pong_ballX > 7)
		{
			pong_ballXD = -pong_ballXD;
			pong_ballX = 7 - pong_ballXD;
		}

		int ballX = round(pong_ballX);
		int ballY = round(pong_ballY);

		if (ballY == 0)
		{
			//At 0
			if (abs(ballX - pong_playerA_X) <= 1)
			{
				//Hit player
				pong_ballYD = -pong_ballYD;
				playerHits++;
				if (playerHits > 5 && pong_ballYD < 1)
					pong_ballYD += 0.01;
				pong_ballY = pong_ballY + 2 * pong_ballYD;
				pong_ballXD = (ballX - pong_playerA_X) * 0.01;
			}
			else
			{
				//Score B
				pong_scoreB++;
				pong_resetBall();
			}
		}

		if (ballY == 15)
		{
			//At 0
			if (abs(ballX - pong_playerB_X) <= 1)
			{
				//Hit player
				pong_ballYD = -pong_ballYD;
				playerHits++;
				if (playerHits > 5 && pong_ballYD > -1)
					pong_ballYD -= 0.01;
				pong_ballY = pong_ballY + 2 * pong_ballYD;
				pong_ballXD = (ballX - pong_playerB_X) * 0.01;
			}
			else
			{
				//Score A
				pong_scoreA++;
				pong_resetBall();
			}
		}

		if (button_downEvent[0])
		{
			if (pong_playerA_X > -1)
				pong_playerA_X--;
		}
		if (button_downEvent[1])
		{
			if (pong_playerA_X < 8)
				pong_playerA_X++;
		}
		if (button_downEvent[2])
		{
			if (pong_playerB_X > -1)
				pong_playerB_X--;
		}
		if (button_downEvent[3])
		{
			if (pong_playerB_X < 8)
				pong_playerB_X++;
		}
	}
};

#endif // GUARD