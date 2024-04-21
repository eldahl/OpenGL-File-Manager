#include <iostream>
#include <gl\glut.h>
#include <msclr\marshal_cppstd.h>

#include "Window.h"
#include "Browser.h"

Window Browser::*window;

std::string Browser::currentPath = "C:\\", Browser::displayModeText = "Files";

bool Browser::editPath = false, Browser::displayFiles = true;

std::vector<std::string> Browser::currentDirs(20);
std::vector<std::string> Browser::currentFiles(20);

Browser::Browser(int argc, char *argv[], char* title, Vector2 windowSize)
{
	*window = Window(argc, argv, title, windowSize);

	// Get directories and files in current location
	currentDirs = GetDirsInDirectory();
	currentFiles = GetFilesinDirectory();

	Draw();
}

void Browser::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// ALWAYS DRAW LOWER LEFTHAND CORNOR POINTS FIRST...
	
	if (currentPath == "exit ")
	{
		exit(0);
	}

	// Current Path
	if (Window::DrawTextEdit(Vector2(-0.98f, 0.9f), Vector2(0.69f, 0.99f), currentPath.c_str(), currentPath.length(), 1))
	{
		editPath = true;
	}

	if (editPath)
	{
		// Draw green rect to indicate editing of file path
		Window::DrawRect(Vector2(-0.98f, 0.88f), Vector2(0.69f, 0.89f), 0.5f, 1, 0.5f);
	}

	// GO button
	if (Window::DrawButton(Vector2(0.7f, 0.9f), Vector2(1, 0.99f), "GO", 2, 2))
	{
		GoToPath(currentPath);
		editPath = false;
	}
	
	if (Window::DrawButton(Vector2(-0.98f, 0.82f), Vector2(-0.30f, 0.88f), displayModeText.c_str(), displayModeText.length(), 0.15f, 0.21f, 0.09f, 3))
	{
		if (displayFiles)
		{
			displayFiles = false;
			displayModeText = "Directories";
		}
		else
		{
			displayFiles = true;
			displayModeText = "Files";
		}
	}

	for (int i = 0; i < 18; i++)
	{
		std::string buttonText, file, path;

		if (displayFiles)
		{
			if (currentFiles.size() > i)
				buttonText = currentFiles[i];
			else
				buttonText = "...";

			// Split string into file & path
			unsigned split = buttonText.find_last_of("/\\");

			// Get file & path of file
			file = buttonText.substr(split + 1);
			path = buttonText.substr(0, split);
		}
		else
		{
			if (currentDirs.size() > i)
				buttonText = currentDirs[i];
			else
				buttonText = "...";

			// Split string into file & path
			unsigned split = buttonText.find_last_of("/\\");

			// Get file & path of file
			file = buttonText.substr(split + 1);
			path = buttonText.substr(0, split);
		}

		// FILE ENTRIES
		if (Window::DrawFileEntry(Vector2(-0.98f, 0.71f - (i * 0.1f)), Vector2(0.49f, 0.8f - (i * 0.1f)), file.c_str(), file.length(), i + 100))
		{
			std::cout << "Opened " << buttonText << std::endl;

			FileOpen(buttonText);
		}
		// DEL
		if (Window::DrawButton(Vector2(0.5f, 0.71f - (i * 0.1f)), Vector2(0.75f, 0.8f - (i * 0.1f)), "DEL", 3, i + 200))
		{
			std::cout << "Deleted " << i << "." << std::endl;
			FileDelete(buttonText);
		}
		
		if (displayFiles)
		{
			// COPY
			if (Window::DrawButton(Vector2(0.76f, 0.71f - (i * 0.1f)), Vector2(1, 0.8f - (i * 0.1f)), "COPY", 4, i + 300))
			{
				// we need a seperate var, so currentPth does not get changed when appending below.
				std::string copyToPath = currentPath;

				if (!(currentPath.find_last_of("/\\") == currentPath.length()))
					copyToPath.append("\\");
				copyToPath.append(file);

				//   Or path.append(file);
				//            |
				FileCopy(buttonText, copyToPath);
			}
		}
	}
	
	
	glutSwapBuffers();
}


// Returns the current directory location
std::string Browser::GetDirectory()
{
	return currentPath;
}


std::vector<std::string> Browser::GetFilesinDirectory()
{
	// Convert currentDir std::string to System::String
	System::String^ directory = gcnew System::String(currentPath.c_str());
	
	// Get files in the directory
	array<System::String^>^ files = System::IO::Directory::GetFiles(directory);
	
	// Create std::vector instance (acts like a dynamic array, instead of static C++ arrays)
	std::vector<std::string> returnFiles(files->Length);

	for (int i = 0; i < files->Length; i++)
	{
		// Get single element from the array of files in directory
		System::String^ asd = files[i];

		// Convert element from System::String^ to std::string.
		returnFiles[i] = msclr::interop::marshal_as<std::string>(asd);
	}
	
	return returnFiles;
}
std::vector<std::string> Browser::GetFilesinDirectory(std::string path)
{
	// Convert path std::string to System::String
	System::String^ directory = gcnew System::String(path.c_str());

	// Get files in the directory
	array<System::String^>^ files = System::IO::Directory::GetFiles(directory);

	// Create std::vector instance (acts like a dynamic array, instead of static C++ arrays)
	std::vector<std::string> returnFiles(files->Length);

	for (int i = 0; i < files->Length; i++)
	{
		// Get single element from the array of files in directory
		System::String^ asd = files[i];

		// Convert element from System::String^ to std::string.
		returnFiles[i] = msclr::interop::marshal_as<std::string>(asd);
	}

	return returnFiles;
}

void Browser::GoToPath()
{
	GoToPath(currentPath);
}
void Browser::GoToPath(std::string path)
{
	// mabye add refreshing of current content in directory
	currentPath = path;

	// Update dirs and files
	currentDirs = GetDirsInDirectory();
	currentFiles = GetFilesinDirectory();
}

std::vector<std::string> Browser::GetDirsInDirectory()
{
	// Convert currentDir std::string to System::String
	System::String^ directory = gcnew System::String(currentPath.c_str());

	// Get files in the directory
	array<System::String^>^ files = System::IO::Directory::GetDirectories(directory);

	// Create std::vector instance (acts like a dynamic array, instead of static C++ arrays)
	std::vector<std::string> returnDirs(files->Length);

	for (int i = 0; i < files->Length; i++)
	{
		// Get single element from the array of files in directory
		System::String^ asd = files[i];

		// Convert element from System::String^ to std::string.
		returnDirs[i] = msclr::interop::marshal_as<std::string>(asd);
	}

	return returnDirs;
}
std::vector<std::string> Browser::GetDirsInDirectory(std::string path)
{
	// Convert path std::string to System::String
	System::String^ directory = gcnew System::String(path.c_str());

	// Get files in the directory
	array<System::String^>^ files = System::IO::Directory::GetDirectories(directory);

	// Create std::vector instance (acts like a dynamic array, instead of static C++ arrays)
	std::vector<std::string> returnDirs(files->Length);

	for (int i = 0; i < files->Length; i++)
	{
		// Get single element from the array of files in directory
		System::String^ asd = files[i];

		// Convert element from System::String^ to std::string.
		returnDirs[i] = msclr::interop::marshal_as<std::string>(asd);
	}

	return returnDirs;
}

void Browser::FileOpen(std::string path)
{
	System::String^ pathCLR = gcnew System::String(path.c_str());
	
	System::Diagnostics::Process::Start(pathCLR);
}

bool Browser::FileDelete(std::string path)
{
	// Get CLR string from supplied C++ string 
	System::String^ pathCLR = gcnew System::String(path.c_str());
	
	try
	{
		System::IO::File::Delete(pathCLR);
	}
	catch (System::Exception^ e)
	{
		std::cout << msclr::interop::marshal_as<std::string>(e->Message) << std::endl;

		return false;
	}

	return true;
}

void Browser::FileCopy(std::string file, std::string path)
{
	System::String^ fileCLR = gcnew System::String(file.c_str());
	System::String^ pathCLR = gcnew System::String(path.c_str());
	bool success = true;
	try
	{
		System::IO::File::Copy(fileCLR, pathCLR, true);
	}
	catch (System::Exception^ e)
	{
		std::cout << msclr::interop::marshal_as<std::string>(e->Message) << std::endl;
		std::cout << "Please run this application with elevated privilleges." << std::endl;
		success = false;
	}

	if (success)
	{
		std::cout << "Copied " << file << " to " << path << std::endl;
	}
}