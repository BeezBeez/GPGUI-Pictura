#include "Pictura.h"

using namespace Pictura;
using namespace Pictura::Debug;
using namespace Pictura::Filesystem;

int main()
{
	const char* FileSrc = "C:\\Windows\\cTest.txt";

	File::Create(FileSrc, "Test content\nTest text");

	Log::Success("Press [ENTER] to exit the program");

	std::getchar();
}