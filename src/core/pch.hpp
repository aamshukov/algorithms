//..............................
// UI Lab Inc. Arthur Amshukov .
//..............................
#ifndef __PCH_H__
#define __PCH_H__

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#include <cstddef>
#include <cctype>
#include <cassert>

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <exception>
#include <stdexcept>

#include <memory>
#include <new>

#include <typeindex>
#include <type_traits>

#include <optional>

#include <algorithm>
#include <numeric>
#include <functional>
#include <utility>
#include <limits>
#include <locale>

#include <string>
#include <charconv>
#include <array>
#include <valarray>
#include <bitset>
#include <tuple>
#include <list>
#include <stack>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>
#include <queue>

#include <variant>

#include <cfenv>
#include <codecvt>

#include <chrono>

#include <filesystem>

#include <string_view>
#include <source_location>

#ifdef _WIN32
#   define NOMINMAX
#   include <windows.h>
#   include <strsafe.h>
#endif

#include <experimental/coroutine>
#include <experimental/generator>

#define COMPANY uilab

#define BEGIN_NAMESPACE(__x__) namespace COMPANY { ## namespace __x__ {
#define END_NAMESPACE   }; };

#define USINGNAMESPACE(__x__) using namespace COMPANY::##__x__;

#define INVALID_VALUE (static_cast<uint32_t>(-1))

#ifdef interface
#   undef interface
#endif
#define interface struct

#define BYTE_SIZE (CHAR_BIT)

BEGIN_NAMESPACE(algorithms)

using bit = uint8_t;
using byte = uint8_t;

using codepoint = uint32_t;

using char_type = wchar_t;
using string_type = std::basic_string<char_type>;

END_NAMESPACE

#endif // __PCH_H__
