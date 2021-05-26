
int yOffset;
int xOffset;
bool maskX;
bool maskY;
int maskXMin;
int maskXMax;
int maskYMin;
int maskYMax;


EmulatedScreen pixels = EmulatedScreen(8, 16);

class EmulatedScreen {
	public: EmulatedScreen(int width, int height)
{
}

}

;

void loop() {
	pixels .clear();
	xOffset = 0;
	yOffset = 0;
	readButton(0, 2);
	readButton(1, 3);
	readButton(2, 6);
	readButton(3, 7);
	if (gameNr == 0) menu_update();
	else if (gameNr == 1) racer_gameUpdate();
	else if (gameNr == 2) pong_gameUpdate();
	else if (gameNr == 3) Andreas_gameUpdate();
	else if (gameNr == 4) beer_gameUpdate();
	// Tests Button Inputs of all buttons (isDown, pressed, released)
	/*testButton(0, 1, 2, 0, pixels.Color(150, 0, 0));
	testButton(15, 14, 13, 1, pixels.Color(150, 150, 0));
	testButton(16, 17, 18, 2, pixels.Color(0, 150, 0));
	testButton(31, 30, 29, 3, pixels.Color(0, 0, 150));
  */
	pixels.show();
	// This sends the updated pixel color to the hardware. //delay(200);
}

void testButton(int LED_pressed, int LED_down, int LED_up, int buttonId, uint32_t color) {
	if (button_pressed[buttonId])

{
	pixels .setPixelColor(LED_pressed, color);
}

if (button_upEvent[buttonId]) {
	pixels .setPixelColor(LED_up, color);
}

if (button_downEvent[buttonId]) {
	pixels .setPixelColor(LED_down, color);
}

}

void readButton(int buttonID, int pin) {
	digitalWrite(pin, HIGH);
	bool wasPressed = button_pressed[buttonID];
	button_pressed [buttonID] = digitalRead(pin) != HIGH;
	button_upEvent [buttonID] = wasPressed && !button_pressed[buttonID];
	button_downEvent [buttonID] = !wasPressed && button_pressed[buttonID];
}

void ShowPixel(int X, int Y, uint32_t color) {
	Y = Y + yOffset;
	X = X + xOffset;
	/*
	  Y = 15-Y;
	  X = 7-X;
	*/

	if (maskX && (X < maskXMin || X > maskXMax)) return;
	if (maskY && (Y < maskYMin || Y > maskYMax)) return;
	int pixelPos = 0;
	if (Y % 2 == 0) // EVEN

{
	pixelPos = Y * 8 + X;
	Serial .print(pixelPos);
}

else {
	pixelPos = Y * 8 - (X + 1) + 8;
}

pixels.setPixelColor(pixelPos, color); // Moderately bright green color.
}

