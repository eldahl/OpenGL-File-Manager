#pragma once
#include <iostream>
#include <vector>
#include <gl\glut.h>

#include "Input.h"
#include "Window.h"
#include "Vector2.h"
#include "Browser.h"

Vector2 Window::size(-1, -1);
bool Window::buttonStates[5];


Window::Window(int argc, char *argv[], char *title, Vector2 _size)
{
	size = _size;

	// Initialize window. 
	glutInitWindowPosition(-1, -1);							// -1 means the windows manager decides the starting position.
	glutInitWindowSize((int)_size.x, (int)_size.y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// Create window
	glutCreateWindow(title);

	glutDisplayFunc(Browser::Draw);
	glutIdleFunc(Browser::Draw);
	
	// Setup glut callbacks
	glutReshapeFunc(ResizeWindow);
}


void Window::ResizeWindow(int sizeX, int sizeY)
{
	// This hacks will let the window be a fixed size :D
	glutReshapeWindow((int)(Window::GetSize().x), (int)(Window::GetSize().y));
}


void Window::DrawRect(Vector2 point1, Vector2 point2)
{
	DrawTri(point1, point2, Vector2(point2.x, point1.y));
	DrawTri(point1, point2, Vector2(point1.x, point2.y));
}
void Window::DrawRect(Vector2 point1, Vector2 point2, float r, float g, float b)
{
	glColor3f(r, g, b);
	DrawTri(point1, point2, Vector2(point2.x, point1.y));
	DrawTri(point1, point2, Vector2(point1.x, point2.y));
}


void Window::DrawTri(Vector2 point1, Vector2 point2, Vector2 point3)
{
	glBegin(GL_TRIANGLES);
		glVertex3f(point1.x, point1.y, 0.0);
		glVertex3f(point2.x, point2.y, 0.0);
		glVertex3f(point3.x, point3.y, 0.0);
	glEnd();
}


void Window::DrawTextField(Vector2 position, char* text, int textLength)
{
	glPushMatrix();
	glRasterPos2f(position.x, position.y);

	for (int i = 0; i < textLength; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);

	glPopMatrix();
}
void Window::DrawTextField(Vector2 position, const char* text, int textLength)
{
	glPushMatrix();   
	glRasterPos2f(position.x, position.y);
																	
	for (int i = 0; i < textLength; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);

	glPopMatrix();
}


bool Window::DrawFileEntry(Vector2 pos1, Vector2 pos2, char* text, int textLength, int buttonID)
{
	// For avoiding recursive function calls that will cause runtime stack overflows
	const char *text_ = text;
	
	if (DrawFileEntry(pos1, pos2, text_, textLength, buttonID))
		return true;
	return false;
}
bool Window::DrawFileEntry(Vector2 pos1, Vector2 pos2, const char* text, int textLength, int buttonID)
{
	// Dark blue 
	glColor3f(0.11f, 0.17f, 0.39f);
	DrawRect(pos1, pos2);
	
	glColor3f(1, 1, 0.5f);
	DrawTextField(Vector2(pos1.x + (std::abs(pos1.x - pos2.x) * 0.03f), pos1.y + std::abs(pos1.y - pos2.y) * 0.35f), text, textLength);

	Vector2 mouse = Input::GetMousePos();

	// Check if mouse is hovering
	if (mouse.x > pos1.x && mouse.y > pos1.y && mouse.x < pos2.x  && mouse.y < pos2.y)
	{
		// Check if clicked on button / file entry
		if (Input::GetMouseButton(0) == true)
		{
			buttonStates[buttonID] = true;
		}
		else if (buttonStates[buttonID] == true)
		{
			buttonStates[buttonID] = 0x00;
			return true;
		}
	}

	return false;
}

bool Window::DrawButton(Vector2 pos1, Vector2 pos2, const char* text, int textLength, float r, float g, float b, int buttonID)
{
	if (r == 0 && g == 0 && b == 0)
	{
		// Dark blue 
		glColor3f(0.11f, 0.17f, 0.39f);
	}
	else
		glColor3f(r, g, b);

	DrawRect(pos1, pos2);

	glColor3f(1, 1, 0.5f);
	DrawTextField(Vector2(pos1.x + (std::abs(pos1.x - pos2.x) * 0.3f), pos1.y + std::abs(pos1.y - pos2.y) * 0.35f), text, textLength);

	Vector2 mouse = Input::GetMousePos();

	// Check if mouse is hovering
	if (mouse.x > pos1.x && mouse.y > pos1.y && mouse.x < pos2.x  && mouse.y < pos2.y)
	{
		// Check if clicked on button / file entry
		if (Input::GetMouseButton(0) == true)
		{
			buttonStates[buttonID] = true;
		}
		else if (buttonStates[buttonID] == true)
		{
			buttonStates[buttonID] = 0x00;
			return true;
		}
	}

	return false;
}
bool Window::DrawButton(Vector2 pos1, Vector2 pos2, char* text, int textLength, int buttonID)
{
	// For avoiding recursive function calls that will cause runtime stack overflows
	const char *text_ = text;
	
	if (DrawButton(pos1, pos2, text_, textLength, buttonID))
		return true;
	return false;
}
bool Window::DrawButton(Vector2 pos1, Vector2 pos2, const char* text, int textLength, int buttonID)
{
	if (DrawButton(pos1, pos2, text, textLength, 0.0f, 0.0f, 0.0f, buttonID))
		return true;
	return false;
	
}


bool Window::DrawTextEdit(Vector2 pos1, Vector2 pos2, char* text, int textLength, int buttonID)
{
	if (DrawButton(pos1, pos2, text, textLength, buttonID))
		return true;
	return false;
}
bool Window::DrawTextEdit(Vector2 pos1, Vector2 pos2, const char* text, int textLength, int buttonID)
{
	// Dark blue 
	glColor3f(0.11f, 0.17f, 0.39f);
	DrawRect(pos1, pos2);

	glColor3f(1, 1, 0.5f);
	DrawTextField(Vector2(pos1.x + (std::abs(pos1.x - pos2.x) * 0.01f), pos1.y + std::abs(pos1.y - pos2.y) * 0.35f), text, textLength);

	Vector2 mouse = Input::GetMousePos();

	// Check if mouse is hovering
	if (mouse.x > pos1.x && mouse.y > pos1.y && mouse.x < pos2.x  && mouse.y < pos2.y)
	{
		// Check if clicked on button / file entry
		if (Input::GetMouseButton(0) == true)
		{
			buttonStates[buttonID] = true;
		}
		else if (buttonStates[buttonID] == true)
		{
			buttonStates[buttonID] = 0x00;
			return true;
		}
	}

	return false;
}


Vector2 Window::GetSize()
{
	return size;
}

