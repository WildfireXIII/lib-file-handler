//*************************************************************
//  File: FileHandler.h
//  Date created: 1/13/2016
//  Date edited: 1/13/2016
//  Author: Nathan Martindale
//  Copyright © 2016 Digital Warrior Labs
//  Description: Cross-platform file handling library
//*************************************************************

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
	#include <windows.h>
#endif // _WIN32

#ifdef linux
#endif // linux

using namespace std;

namespace dwl
{
	struct FileListing
	{
		string FullName; // full name, includes extension (if file)
		string Name;
		string Path;
		string Extension;
		bool isDirectory;
	};
	
	class FileHandler
	{
		private:
			string m_currentPath;
		
		public:
			FileHandler();
			~FileHandler(); // TODO: don't forget to close any open files here

			// path/directory stuff
			string getCWD(); 
			string getApplicationPath();
			/*string getCurrentPath();
			void setCurrentPath(string path); // NOTE: only sets virtual path
			vector<FileListing> getDirectoryListing();

			// file i/o
			vector<string> readFile(string fileName);
			void prepareFileWrite(string fileName, int mode);
			void fileWrite(string content);
			void finishWrite();
			void quickWrite(string content, string fileName, int mode); */
	};
}

#endif // FILE_HANDLER_H
