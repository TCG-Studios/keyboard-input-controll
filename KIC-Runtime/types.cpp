#include "types.h"
#include "iWin.h"
#include "typedefs.h"

const wchar_t* StringToLPCWSTR(const char* msg) {
    int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, msg, -1, nullptr, 0);
    std::wstring wideStr(wideStrLen, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, msg, -1, &wideStr[0], wideStrLen);
    return wideStr.c_str();
}

/*
*
* types of functions
*
*/
template <typename T>
std::vector<std::string_view>* get_argument_types() {
    using ArgsTuple = typename argument_types<T>::types;
    auto result = new std::vector<std::string_view>();
    std::apply([result](const auto&... args) {
        ((result->emplace_back(type_name<decltype(args)>())), ...);
        }, ArgsTuple{});
    return result;
}

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