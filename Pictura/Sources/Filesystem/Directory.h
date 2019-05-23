#pragma once

namespace Pictura::Filesystem
{
	class PICTURA_API Directory
	{
	public:
		Directory();
		~Directory();

	public:
		bool Create(const char path[260]);
		bool Exist(const char path[260]);
		bool Rename(const char path[260]);
		bool Copy(const char sourceDirectory[260], const char destinationDirectory[260]);
		bool Copy(const char sourceDirectory[260], const char destinationDirectory[260], float* progress);
		bool Delete(const char sourceDirectory[260], bool recursive);
	};

	class PICTURA_API DirectoryInfo
	{
	public:
		DirectoryInfo();
		~DirectoryInfo();
	};
}