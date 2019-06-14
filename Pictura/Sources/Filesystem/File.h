#pragma once
#include "Core/Core.h"

namespace Pictura::Filesystem
{
	class PICTURA_API File
	{
	public:
		File();
		~File();

	public:
		static bool Exist(const char sourceFile[260]);
		static bool Move(const char sourceFile[260], const char destinationFile[260], bool Overwrite = false);
		static bool Copy(const char sourceFile[260], const char destinationFile[260], bool Overwrite = false);
		static bool Delete(const char targetFile[260]);

		static bool Create(const char targetFile[260], const char data[]);
		static PString Read(const char targetFile[260]);
		static PVector<PString> ReadLines(const char targetFile[260]);

	};

	class PICTURA_API FileInfo
	{
	public:
		FileInfo(const char path[260]);
		~FileInfo();

	public:
		PString Name;
		PString FullName;
		PString ParentDirectory;
		PString Extension;
		long Size;
	};
}


