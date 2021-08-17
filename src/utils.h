#ifndef UTILS_H
#define UTILS_H
#include <string>
inline void openWebLink(std::string url)
{
    std::string op;
#ifdef _WIN32
    op = std::string("start ").append(url);
#else
    op = std::string("xdg-open ").append(url);
#endif
    system(op.c_str());
}

template <typename T> int min(T value1, T value2)
{
    return value1 < value2 ? value1 : value2;
}
#endif