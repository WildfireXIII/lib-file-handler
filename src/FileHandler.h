//*************************************************************
//  File: 
//  Date created: 1/13/2016
//  Date edited: 1/13/2016
//  Author: Nathan Martindale
//  Copyright © 2016 Digital Warrior Labs
//  Description: Cross-platform file handling library
//*************************************************************

#include <string>

#ifdef _WIN32
#endif

#ifdef linux
#endif


namespace dwl
{
	struct FileListing
	{
		string FullName; //full name, includes extension (if file)
		string Name;
		String Path;
		String Extension;
		bool isDirectory;
	};
	
	class FileHandler
	{
	private:
		
	public:
	
	}
}
