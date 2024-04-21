#pragma once
#include <stdlib.h>
#include <iostream>
#include <gl\glut.h>
#include <vector>
#include <string>

#include "Window.h"
#include "Browser.h"
#include "Input.h"

int main(int argc, char *argv[])
{
	// Debug stuff
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	
	// Initialize glut
	glutInit(&argc, argv);

	Browser browser(argc, argv, "File Manager", Vector2(600, 800));
	Input::Init();

	glutMainLoop();
	return 0;
}