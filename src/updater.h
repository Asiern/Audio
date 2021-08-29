/**
 * @file updater.h
 * @author Asiern (https://github.com/Asiern)
 * @brief
 * @date 2021-08-27
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef UPDATER_H
#define UPDATER_H
#include <string>
#include <vector>

/**
 * @brief Github releases update checker
 * @author Asiern
 * @since Fri Aug 27 2021
 */
class Updater
{
  public:
    Updater(std::string url, struct curl_slist* headers);
    ~Updater();
    std::string getLatestVersion();
    int compareVersions(std::string v1, std::string v2);

  private:
    std::vector<std::string> split(const std::string& value);
    std::string url;
    struct curl_slist* headers;
};

#endif