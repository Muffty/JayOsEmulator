#ifndef __GAMES
#define __GAMES

#include <wx/wx.h>

#define color(r, g, b) (uint32_t)(r<<24|g<<16|b<<8)


class JayScreen
{
	wxImage* image;

public:
	JayScreen(wxImage* image) {
		this->image = image;
		this->yOffset = 0;
		this->xOffset = 0;
		this->maskX = false;
		this->maskY = false;
		this->maskXMin = 0;
		this->maskXMax = 0;
		this->maskYMin = 0;
		this->maskYMax = 0;
	}

	void ShowPixel(int x, int y, uint32_t color) {
		x += xOffset;
		y += yOffset;

		if (x < 0 || x > 7 || y < 0 || y > 15)
			return;

		unsigned char red = (color >> 24) & 0xff; // red
		unsigned char green = (color >> 16) & 0xff; // green
		unsigned char blue = (color >> 8) & 0xff; // blue
		image->SetRGB(x, 15 - y, red, green, blue);
	}

	void ClearPixels() {
		xOffset = 0;
		yOffset = 0;
	}

	int yOffset;
	int xOffset;
	bool maskX;
	bool maskY;
	int maskXMin;
	int maskXMax;
	int maskYMin;
	int maskYMax;

	void draw32code(int code, int width, int height, int x, int y, uint32_t color) {

		int d = 0;
		for (int yD = 0; yD < height; yD++)
			for (int xD = width - 1; xD >= 0; xD--)
			{
				{
					if ((code & 0x01) == 0x01) {
						ShowPixel(x + xD, y + yD, color);
					}
					code = code >> 1;
					if (code == 0)
						return;
				}
			}
	}

	void draw5x4Number(int nr, int x, int y, uint32_t color)
	{
		yOffset += y;
		xOffset += x;

		int code = 0;
		if (nr == 0) {
			code = 0b01101001100110010110;
		}
		else if (nr == 1) {
			code = 0b00100110101000100010;
		}
		else if (nr == 2) {
			code = 0b11100001011010000110;
		}
		else if (nr == 3) {
			code = 0b11000010010000101100;
		}
		else if (nr == 4) {
			code = 0b00100110111100100010;
		}
		else if (nr == 5) {
			code = 0b11101000110000101100;
		}
		else if (nr == 6) {
			code = 0b00100100011001010110;
		}
		else if (nr == 7) {
			code = 0b11100010010001000100;
		}
		else if (nr == 8) {
			code = 0b01101001011010010110;
		}
		else if (nr == 9) {
			code = 0b01101010011000100100;
		}
		draw32code(code, 4, 5, 0, 0, color);

		yOffset -= y;
		xOffset -= x;
	}
};
class OsGame {
public:
	virtual void HandleInput(bool button_pressed[4], bool button_downEvent[4], bool button_upEvent[4]) = 0;
	virtual void ResetState() = 0;
	virtual void Draw(JayScreen* screen) = 0;
};
#endif // GUARD