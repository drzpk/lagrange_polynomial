#pragma once

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <locale.h>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string.h>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <sys/ioctl.h>
#endif


//jeśli zdefiniowane, wyświetlane są informacje debugowania
//#define DEBUG_INFO
