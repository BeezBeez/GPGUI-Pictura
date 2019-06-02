#include "PicturaPCH.h"
#include "File.h"
#include "Core/Exceptions/IOException.h"

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

		return std::filesystem::copy_file(from, to, cOptions);
	}

	bool File::Delete(const char targetFile[260])
	{
		return std::filesystem::remove(targetFile);
	}

	bool File::Create(const char targetFile[260], const char data[])
	{
		std::ofstream file(targetFile);
		file << data;
		file.close();

		return file.good();
	}

	PString File::Read(const char targetFile[260])
	{
		std::ifstream file(targetFile, std::ios::in | std::ios::binary | std::ios::ate);

		std::ifstream::pos_type fileSize = file.tellg();

		if (fileSize < 0) {
			throw IOException("Failed to allocate memory for the file! File size was unhandled by program!");
		}

		file.seekg(0, std::ios::beg);

		std::vector<char> bytes(fileSize);
		file.read(&bytes[0], fileSize);

		return PString(&bytes[0], fileSize);
	}

	PVector<PString> File::ReadLines(const char targetFile[260])
	{
		std::ifstream file(targetFile);
		std::string str;
		PVector<PString> r;
		
		while (std::getline(file, str))
		{
			if (str.size() > 0) {
				r.push_back(str);
			}
		}
		file.close();
		return r;
	}

	/** Class FileInfo methods**/

	FileInfo::FileInfo(const char path[260])
	{
		std::ifstream file(path, std::ifstream::in | std::ifstream::binary);

		if (file.is_open() || File::Exist(path))
		{
			file.seekg(0, std::ios::end);
			const auto end = file.tellg();
			file.close();
		
			Size = end;

			if (Size < 0)
			{
				Size = 0;
			}

			std::filesystem::path p = std::filesystem::path(path);
			Name = p.filename().generic_string();
			Extension = p.extension().generic_string();
			ParentDirectory = p.parent_path().string();
			FullName = p.string();			
		}
		else
		{
			throw IOException("File not found, check the path");
		}

	}

	FileInfo::~FileInfo()
	{
		
	}
}

