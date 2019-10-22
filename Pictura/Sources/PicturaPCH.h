#pragma once

#include <cstdio>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <filesystem>

#include <chrono>
#include <ctime>
#include <time.h>

#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include <typeinfo>
#include <thread>
#include <mutex>
#include <shared_mutex>

#include "Core/PlatformMacro.h"

#if PLATFORM_WINDOWS == 1
	#include <Windows.h>
#endif

using namespace std::chrono_literals;