#include "Pictura.h"

using namespace Pictura;
using namespace Pictura::Debug;
using namespace Pictura::Filesystem;

int main()
{
	FileInfo fi = FileInfo("C:\\testFile.txt");
	Log::Trace("File size is : " + Pictura::Types::ToString(fi.Size));
	Console::Pause();

	PString content = File::Read("C:\\testFile.txt");

	Log::Trace("Showing file content...");
	Log::Trace("-- BEGIN OF FILE\n" + content);
	Log::Trace("-- END OF FILE\n");

	Log::Success("Press [ENTER] to exit the program");
	std::getchar();
}