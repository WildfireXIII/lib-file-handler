//*************************************************************
//  File: FileLayer.h
//  Date created: 1/13/2016
//  Date edited: 2/19/2016
//  Author: Nathan Martindale
//  Copyright © 2016 Digital Warrior Labs
//  Description: Cross-platform file handling library
//*************************************************************

#ifndef FILE_LAYER_H
#define FILE_LAYER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <exception>

#ifdef _WIN32
	#include <windows.h>
#endif // _WIN32

#ifdef linux
#endif // linux

using namespace std;

// TODO: error numbering system, latest error variable (don't use exceptions)

namespace dwl
{

	// class list
	class FileListing;
	class FileLayer;
	class FileLayerPathNotFound;
	class FileLayerNotDirectory;

	class FileLayerPathNotFound : public exception
	{
		public:
			virtual const char* what() const throw() { return "The path wasn't found."; }
	};

	class FileLayerNotDirectory : public exception
	{
		public:
			virtual const char* what() const throw() { return "Path is not a directory."; }
	};
	
	class FileListing
	{
		public:
			string FullName; // full name, includes extension (if file)
			string Name;
			string Path;
			string Extension;
			bool isDirectory;
	};
	
	class FileLayer
	{
		private:
			string m_currentPath;
			ofstream m_openFile; // only opened by prepareFileWrite

			// private functions
			#ifdef _WIN32
				FileListing* getFileListing(WIN32_FIND_DATA data);
				void recursiveDelDir(string path);
			#endif // _WIN32
		
		public:
			FileLayer();
			~FileLayer(); // TODO: don't forget to close any open files here

			ofstream* getOFStream();

			// path/directory stuff
			
			void outputCWD(string path); // writes current path to a file _FILELAYER_CWD.dat in a specified path (for use in parent shell scripts etc)
			string getCWD(); 
			string getApplicationPath();
			string getCurrentPath();
			void setCurrentPath(string path); // NOTE: only sets virtual path
			bool isDirectory(string path);
			bool isFile(string path);
			bool exists(string path);
			vector<FileListing>* getDirectoryListing();

			// file i/o
			
			void createFile(string path);
			void createDirectory(string path);
			void deleteFile(string path); 
			void deleteDirectory(string path); // NOTE: recursive
			
			vector<string>* readFile(string fileName);
			void prepareFileWrite(string fileName, bool append);
			void fileWrite(string content);
			void finishWrite();
			void quickWrite(string content, string fileName, bool append);
	};
}

#endif // FILE_LAYER_H
