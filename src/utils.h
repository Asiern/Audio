/**
 * @file utils.h
 * @author Asiern (https://github.com/Asiern)
 * @brief
 * @date 2021-08-27
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef UTILS_H
#define UTILS_H
#include <string>

/**
 * @brief Open url in default web browser
 * @param url web url
 * @return void
 */
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

/**
 * @brief Get min value
 * @param value1
 * @param value2
 * @return min{value1, value2}
 */
template <typename T> int min(T value1, T value2)
{
    return value1 < value2 ? value1 : value2;
}

/**
 * @brief Get filename from file path
 * @param path file path
 * @return filename
 */
inline std::string getFileName(const std::string& path)
{
    size_t lastIndex = path.find_last_of("\\/");
    std::string filename = path;
    if (std::string::npos != lastIndex)
    {
        filename.erase(0, lastIndex + 1);
    }

    // Remove file extension if present.
    const size_t periodIndex = filename.rfind('.');
    if (std::string::npos != periodIndex)
    {
        filename.erase(periodIndex);
    }
    return filename;
}
#endif