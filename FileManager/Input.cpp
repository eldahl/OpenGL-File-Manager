#include <iostream>
#include <stdlib.h>
#include <gl\glut.h>

#include "Vector2.h"
#include "Input.h"
#include "Window.h"
#include "Browser.h"

Vector2 Input::mousePos(-1, -1);
bool Input::mouseButtons[5];

Vector2 Input::GetMousePos()
{
	return mousePos;
}

void Input::Init()
{
	glutPassiveMotionFunc(SetMousePos);
	glutMouseFunc(SetMouseButton);

	glutKeyboardFunc(ProcessNormalKeys);
	glutSpecialFunc(ProcessSpecialKeys);
}

void Input::SetMousePos(int x, int y)
{
	// Reverse coordinate system y axis
	y = (int)(Window::GetSize().y - y);
	
	// Convert from screen size coords, to glut coord system
	mousePos.x = x / Window::GetSize().x * 2 - 1;
	mousePos.y = y / Window::GetSize().y * 2 - 1;
	
	// Debug
	//std::cout << "MousePosX: " << mousePos.x << " MousePosY: " << mousePos.y << std::endl;
}

void Input::SetMouseButton(int button, int state, int x, int y)
{
	if (state == GLUT_UP)
		mouseButtons[button] = false;
	else
		mouseButtons[button] = true;
}

bool Input::GetMouseButton(int button)
{
	return mouseButtons[button];
}

void Input::ProcessNormalKeys(unsigned char key, int x, int y)
{
	if (Browser::editPath)
	{
		if (key == 8)
		{
			Browser::currentPath.pop_back();
		}
		else if (key == 27 || key == 13)
		{
			Browser::editPath = false;
			Browser::GoToPath();
		}
		else
		{
			Browser::currentPath.push_back(key);
		}
			
	}
	else
	{
		// If ESC is pressed
		if (key == 27)
		{
			exit(0);
		}
	}
	
}

void Input::ProcessSpecialKeys(int key, int x, int y)
{
	/*
	switch (key)
	{
	case GLUT_KEY_F1:
		std::cout << "F1 pressed";
		break;
	}
	*/
}
