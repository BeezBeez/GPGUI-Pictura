#pragma once

namespace Pictura::Filesystem
{
	class File
	{
	public:
		File();
		~File();

	public:
		static bool Exist(char sourceFile[260]);
		static bool Move(char sourceFile[260], char destinationFile[260], bool Overwrite = false);
		static bool Copy(char sourceFile[260], char destinationFile[260], bool Overwrite = false);
		static bool Delete(char targetFile[260]);

		static bool Create(char targetFile[260], char data[]);
		static PString Read(char targetFile[260]);
		static PString* ReadLines(char targetFile[260]);

		static bool Encrypt(char sourceFile[260], char destinationFile[260], PString key);
		static bool Decrypt(char sourceFile[260], char destinationFile[260], PString key);

	};

	class FileInfo
	{
	public:
		FileInfo(char path[260]);
		~FileInfo();

	public:
		PString Name;
		PString FullName;
		PString ParentDirectory;
		PString Extension;
		long Size;
		bool StillExist;
	};
}


