#include "Pictura.h"

using namespace Pictura;
using namespace Pictura::Debug;

int main()
{
	Console::WriteLine("Hello world");
	Log::Warning("Watch out!");
	Log::Error("EXCEPTION : Pictura.IOException");
	Log::Success("Lightmap baking completed !");
	std::getchar();
}