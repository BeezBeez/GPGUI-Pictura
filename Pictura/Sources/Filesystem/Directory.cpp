#include "PicturaPCH.h"
#include "Directory.h"

namespace Pictura::Filesystem
{
	Directory::Directory()
	{

	}

	Directory::~Directory()
	{

	}

	bool Directory::Create(const char path[260])
	{
		return false;
	}

	bool Directory::Exist(const char path[260])
	{
		return false;
	}

	bool Directory::Rename(const char path[260])
	{
		return false;
	}

	bool Directory::Copy(const char sourceDirectory[260], const char destinationDirectory[260])
	{
		return false;
	}

	bool Directory::Copy(const char sourceDirectory[260], const char destinationDirectory[260], float* progress)
	{
		return false;
	}

	bool Directory::Delete(const char sourceDirectory[260], bool recursive)
	{
		return false;
	}

	/** Class DirectoryInfo methods **/

	DirectoryInfo::DirectoryInfo()
	{

	}

	DirectoryInfo::~DirectoryInfo()
	{

	}

}