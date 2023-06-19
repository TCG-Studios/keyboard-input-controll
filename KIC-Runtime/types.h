#pragma once

#include <codecvt>
#include <locale>
#include <string>

// Function to convert std::string to LPCWSTR
const wchar_t* StringToLPCWSTR(const char* msg);

/*
* 
* types of functions
* 
*/
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
std::vector<std::string_view>* get_argument_types();

// Type name retrieval using type traits (requires C++14 or later)
template <typename T>
constexpr std::string_view type_name();