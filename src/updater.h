#ifndef UPDATER_H
#define UPDATER_H
#include <string>
#include <vector>

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