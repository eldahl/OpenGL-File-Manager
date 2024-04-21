#pragma once
#include "Vector2.h"

class Input
{

private:
	static Vector2 mousePos;

public:
	
	static bool mouseButtons[5];

	static void Init();

	static Vector2 GetMousePos();
	static bool GetMouseButton(int button);


	// Glut callbacks
	static void SetMousePos(int x, int y);
	static void SetMouseButton(int button, int state, int x, int y);

	static void ProcessNormalKeys(unsigned char key, int x, int y);
	static void ProcessSpecialKeys(int key, int x, int y);
};