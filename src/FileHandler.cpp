//*************************************************************
//  File: FileHandler.cpp
//  Date created: 1/13/2016
//  Date edited: 1/14/2016
//  Author: Nathan Martindale
//  Copyright © 2016 Digital Warrior Labs
//  Description: Cross-platform file handling library
//*************************************************************

#ifndef FILE_HANDLER_CPP
#define FILE_HANDLER_CPP

#include "FileHandler.h"

using namespace std;

namespace dwl
{
	// private functions
	#ifdef _WIN32
		FileListing* FileHandler::getFileListing(WIN32_FIND_DATA data)
		{
			FileListing* file = new FileListing();
			string fullName(data.cFileName);
			int index = fullName.find_last_of(".");

			file->FullName = fullName;
			if (index != -1) 
			{ 
				file->Name = fullName.substr(0, index); 
				file->Extension = fullName.substr(index); // NOTE: includes .
			}
			else // either no extension or directory
			{ 
				file->Name = file->FullName; 
				file->Extension = "";
			}

			file->Path = m_currentPath;

			// check whether dir or not (checks if directory attribute flag set)
			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { file->isDirectory = true; }
			else { file->isDirectory = false; }

			return file;
			
		}
	#endif // _WIN32




	// construction
	FileHandler::FileHandler() 
	{ 
		m_currentPath = "";
		m_currentPath = this->getCWD();
	}
	FileHandler::~FileHandler() { }

	// path/directory stuff
	string FileHandler::getCWD()
	{
		#ifdef _WIN32
			char curDir[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, curDir);
			string path(curDir);
			return path;
		#endif // _WIN32
		
		#ifdef linux
		#endif // linux

		return "";
	}

	string FileHandler::getApplicationPath()
	{
		#ifdef _WIN32
			char appPath[MAX_PATH];
			GetModuleFileName(NULL, appPath, MAX_PATH); // NULL means that it uses current executable
			
			// take of the executable name and just use path
			string path(appPath);
			int indexOfLast = path.find_last_of("/\\");
			path = path.substr(0, indexOfLast);
			return path;
		#endif // _WIN32

		#ifdef linux
		#endif // linux
		
		return "";
	}

	string FileHandler::getCurrentPath() { return m_currentPath; }
	void FileHandler::setCurrentPath(string path) 
	{ 
		#ifdef _WIN32
			char* currentPath = (char*)path.c_str();
			char newPath[MAX_PATH];

			// check that valid path (and resolve if relative path was passed
			if (_fullpath(newPath, currentPath, MAX_PATH) == NULL) { throw FileHandlerPathNotFound(); }

			string finalPath(newPath);
			m_currentPath = finalPath;

			if (!this->isDirectory(m_currentPath)) { throw FileHandlerNotDirectory(); }
		#endif // _WIN32
		
		#ifdef linux
		#endif // linux
	}

	bool FileHandler::isDirectory(string path)
	{
		#ifdef _WIN32
			DWORD attributes = GetFileAttributes(path.c_str());
			if (attributes == INVALID_FILE_ATTRIBUTES) { return false; }
			if (attributes & FILE_ATTRIBUTE_DIRECTORY) { return true; }
			return false;
		#endif // _WIN32

		#ifdef linux
		#endif // linux
	}
	
	bool FileHandler::isFile(string path)
	{
		#ifdef _WIN32
			DWORD attributes = GetFileAttributes(path.c_str());
			if (attributes == INVALID_FILE_ATTRIBUTES) { return false; }
			if (attributes & FILE_ATTRIBUTE_DIRECTORY) { return false; }
			return true;
		#endif // _WIN32

		#ifdef linux
		#endif // linux
	}
	
	bool FileHandler::exists(string path)
	{
		#ifdef _WIN32
			DWORD attributes = GetFileAttributes(path.c_str());
			if (attributes == INVALID_FILE_ATTRIBUTES) { return false; }
			return true;
		#endif // _WIN32

		#ifdef linux
		#endif // linux
	}

	// TODO: NEVER ANY TRAILING BACKSLASHES 
	
	vector<FileListing>* FileHandler::getDirectoryListing()
	{
		vector<FileListing>* list = new vector<FileListing>();
		
		#ifdef _WIN32
			WIN32_FIND_DATA FindFileData;
			HANDLE hFind;

			// define what to search for
			string strSearchPath = m_currentPath + "\\*.*";
			LPCSTR searchPath = strSearchPath.c_str();

			// get first file
			hFind = FindFirstFile(searchPath, &FindFileData);
			FileListing* firstFileListing = getFileListing(FindFileData);
			list->push_back(*firstFileListing);

			// list all the rest
			while (FindNextFile(hFind, &FindFileData))
			{
				FileListing* nextFileListing = getFileListing(FindFileData);
				list->push_back(*nextFileListing);
			}
		#endif // _WIN32
		
		#ifdef linux
		#endif // linux

		return list;
	}
}

#endif // FILE_HANDLER_CPP
