#include "updater.h"
#include "utils.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

enum CharType
{
    Number,
    Period,
    String
};

CharType getCharType(char c)
{
    if (c == '.')
        return Period;
    else if (c >= 0 && c <= 9)
        return Number;
    else
        return String;
}

std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out)
{
    const std::size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}

Updater::Updater(std::string url, struct curl_slist* headers)
{
    this->headers = headers;
    this->url = url;
}

Updater::~Updater()
{
    free(headers);
}

std::string Updater::getLatestVersion()
{
    CURL* curl = curl_easy_init();
    if (curl)
    {
        long satusCode(0);
        std::unique_ptr<std::string> response(new std::string());

        // Request
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, this->url.c_str());
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response.get());
        curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &satusCode);
        curl_easy_cleanup(curl);

        if (satusCode == 200)
        {
            json j = json::parse(response.get()->c_str(), nullptr, true);
            return j["tag_name"];
        }
    }
    return "";
}

int Updater::compareVersions(std::string v1, std::string v2)
{
    const std::vector<std::string> v1list = split(v1);
    const std::vector<std::string> v2list = split(v2);

    const size_t n = min(v1list.size(), v2list.size());

    for (size_t i = 0; i < n; i++)
    {
        const std::string& a = v1list[i];
        const std::string& b = v2list[i];
        const CharType typeA = getCharType(a[0]);
        const CharType typeB = getCharType(b[0]);
        if (typeA == typeB)
        {
            if (typeA == String)
            {
                int result = a.compare(b);
                if (result != 0)
                    return result;
            }
            else if (typeA == Number)
            {
                const int intA = atoi(a.c_str());
                const int intB = atoi(b.c_str());
                if (intA > intB)
                    return 1;
                else if (intA < intB)
                    return -1;
            }
        }
        else
        {
            if (typeA != String && typeB == String)
                return 1;
            else if (typeA == String && typeB != String)
                return -1;
            else
                return (typeA == Number) ? 1 : -1;
        }
    }
    return -1;
}

std::vector<std::string> Updater::split(const std::string& value)
{
    std::vector<std::string> list;

    if (value.empty())
        return list;
    std::string s;
    const size_t length = value.length();
    s = value[0];
    CharType prev = getCharType(value[0]);

    for (size_t i = 1; i < length; i++)
    {
        const char c = value[i];
        const CharType newType = getCharType(c);

        if (prev != newType || prev == Period)
        {
            list.push_back(s);
            s = c;
        }
        else
        {
            s += c;
        }
        prev = newType;
    }

    list.push_back(s);

    return list;
}