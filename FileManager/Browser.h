#pragma once
#include <vector>
#include "Window.h"

class Browser
{
private:
	Window *window;
	
	static std::vector<std::string> currentDirs;
	static std::vector<std::string> currentFiles;


public:
	Browser(int argc, char *argv[], char* title, Vector2 windowSize);

	static std::string currentPath, displayModeText;
	static bool editPath, displayFiles;

	static void Draw();

	static std::string GetDirectory();

	static std::vector<std::string> GetFilesinDirectory();
	static std::vector<std::string> GetFilesinDirectory(std::string path);

	static void GoToPath(std::string path);
	static void GoToPath();

	static std::vector<std::string> GetDirsInDirectory();
	static std::vector<std::string> GetDirsInDirectory(std::string path);

	static void FileOpen(std::string path);
	static bool FileDelete(std::string path);
	static void FileCopy(std::string file, std::string path);
};
