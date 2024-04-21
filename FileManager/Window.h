#pragma once

#include "Vector2.h"

class Window
{

private:
	static Vector2 size;

public:
	Window(int argc, char* argv[], char* title, Vector2 size);

	static Vector2 GetSize();
	static bool buttonStates[5];


	// Glut callback funcs
	static void ResizeWindow(int sizeX, int sizeY);

	static Vector2 PixelToGLUTCord(Vector2 cord);

	// Shape drawing
	static void DrawRect(Vector2 point1, Vector2 point2);
	static void DrawRect(Vector2 point, Vector2 point2, float r, float g, float b);

	static void DrawTri(Vector2 point1, Vector2 point2, Vector2 point3);
	
	static void DrawTextField(Vector2 position, char* text, int textLength);
	static void DrawTextField(Vector2 position, const char* text, int textLength);
	
	static bool DrawFileEntry(Vector2 position, Vector2 size, char* text, int textLength, int buttonID);
	static bool DrawFileEntry(Vector2 position, Vector2 size, const char* text, int textLength, int buttonID);

	static bool DrawButton(Vector2 position, Vector2 size, char* text, int textLength, int buttonID);
	static bool DrawButton(Vector2 position, Vector2 size, const char* text, int textLength, int buttonID);
	static bool DrawButton(Vector2 position, Vector2 size, const char* text, int textLength, float r, float g, float b, int buttonID);

	static bool DrawTextEdit(Vector2 position, Vector2 size, char* text, int textLength, int buttonID);
	static bool DrawTextEdit(Vector2 position, Vector2 size, const char* text, int textLength, int buttonID);
};