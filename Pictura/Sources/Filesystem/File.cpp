#include "PicturaPCH.h"
#include "File.h"

namespace Pictura::Filesystem
{
	File::File()
	{
	}


	File::~File()
	{
	}

	bool File::Exist(const char sourceFile[260])
	{
		std::filesystem::path p = std::filesystem::path(sourceFile);
		return std::filesystem::exists(p);
	}

	bool File::Move(const char sourceFile[260], const char destinationFile[260], bool Overwrite)
	{
		if (!File::Exist(sourceFile))
		{
			return false;
		}

		if (Overwrite || File::Exist(destinationFile))
		{
			File::Delete(destinationFile);
	    }
		else if (File::Exist(destinationFile))
		{
			return false;
		}

		return std::rename(sourceFile, destinationFile) == 0;
	}

	bool File::Copy(const char sourceFile[260], const char destinationFile[260], bool Overwrite)
	{
		std::filesystem::path from = std::filesystem::path(sourceFile);
		std::filesystem::path to = std::filesystem::path(destinationFile);

		std::filesystem::copy_options cOptions = Overwrite ? std::filesystem::copy_options::overwrite_existing : std::filesystem::copy_options::none;

		std::filesystem::copy_file(from, to, cOptions);
		return File::Exist(destinationFile);
	}

	bool File::Delete(const char targetFile[260])
	{
		return std::filesystem::remove(targetFile);
	}

	bool File::Create(const char targetFile[260], const char data[])
	{
		std::ofstream ofs(std::filesystem::path(targetFile));
		
		return false;
	}

	/** Class FileInfo methods**/

	FileInfo::FileInfo(const char path[260])
	{
		std::filesystem::path p = std::filesystem::path(path);
		Name = p.filename().generic_string();
		Extension = p.extension().generic_string();
		ParentDirectory = p.parent_path().string();
		FullName = p.string();
		Size = -1;
	}

	FileInfo::~FileInfo()
	{
		
	}
}

