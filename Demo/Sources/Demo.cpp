#include "Pictura.h"

using namespace Pictura;
using namespace Pictura::Debug;
using namespace Pictura::Filesystem;

int main()
{
	const char* FileSrc = "C:\\Windows\\test.txt";

	Log::Trace("File size is " + std::to_string(FileInfo(FileSrc).Size) + " bytes"); 
	Log::Success("Press [ENTER] to exit the program");

	std::getchar();
}