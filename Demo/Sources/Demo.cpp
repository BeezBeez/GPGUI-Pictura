#include "Pictura.h"

using namespace Pictura;
using namespace Pictura::Debug;
using namespace Pictura::Filesystem;

int main()
{
	FileInfo fi = FileInfo("C:\\setup.log");
	Log::Trace("File size is : " + Pictura::Types::ToString(fi.Size));
	Console::Pause();

	PVector<PString> v = File::ReadLines(fi.FullName.c_str());

	for (size_t i = 0; i < v.size(); ++i)
	{
		Log::Trace("Line (" + Types::ToString(i) + ") : " + v[i]);
	}

	Log::Success("Press [ENTER] to exit the program");
	std::getchar();
}