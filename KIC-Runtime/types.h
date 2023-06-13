#pragma once

#include "win.h"

typedef uint16_t uint16; 
typedef uint8_t uint8;

typedef uint16_t u16;
typedef uint8_t u8;

// Function to convert std::string to LPCWSTR
LPCWSTR StringToLPCWSTR(const char* msg) {
    int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, msg, -1, nullptr, 0);
    std::wstring wideStr(wideStrLen, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, msg, -1, &wideStr[0], wideStrLen);
    return wideStr.c_str();
}

LPCWSTR StringToLPCWSTR(const std::string& msg) {
	return StringToLPCWSTR(msg);
}

// types of functions
#include <type_traits>
#include <string_view>
#include <vector>

template <typename T>
struct argument_types {};

template <typename Ret, typename... Args>
struct argument_types<Ret(Args...)> {
    using types = std::tuple<Args...>;
};

template <typename T>
std::vector<std::string_view> get_argument_types() {
    using ArgsTuple = typename argument_types<T>::types;
    std::vector<std::string_view> result;
    std::apply([&result](const auto&... args) {
        ((result.emplace_back(type_name<decltype(args)>())), ...);
        }, ArgsTuple{});
    return result;
}

// Type name retrieval using type traits (requires C++14 or later)
template <typename T>
constexpr std::string_view type_name() {
#ifdef __clang__
    std::string_view p = __PRETTY_FUNCTION__;
    return std::string_view(p.data() + 34, p.size() - 34 - 1);
#elif defined(__GNUC__)
    std::string_view p = __PRETTY_FUNCTION__;
#if __cplusplus < 201402
    return std::string_view(p.data() + 36, p.size() - 36 - 1);
#else
    return std::string_view(p.data() + 49, p.find(';', 49) - 49);
#endif
#elif defined(_MSC_VER)
    std::string_view p = __FUNCSIG__;
    return std::string_view(p.data() + 84, p.size() - 84 - 7);
#endif
    return "unknown";
}