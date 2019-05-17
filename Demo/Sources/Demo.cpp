#include "Pictura.h"

using namespace Pictura;
using namespace Pictura::Debug;
using namespace Pictura::Filesystem;

int main()
{
	FileInfo fi = FileInfo("C:\\testFile.txt");
	Log::Trace("File size is : " + Pictura::Types::ToString(fi.Size));
	Console::Pause();
	for (auto &line : File::ReadLines(fi.FullName.c_str()))
	{
		Log::Trace("Line : " + line);
	}

	Log::Success("Press [ENTER] to exit the program");
	std::getchar();
}