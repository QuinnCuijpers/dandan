#ifndef DANDAN_STRSPLIT_H
#define DANDAN_STRSPLIT_H

#include <string>
#include <vector>

inline std::vector<std::string> strSplit(const std::string &str,
                                         char delim = ' ')
{
    std::vector<std::string> result;
    size_t begin = 0;
    while (true)
    {
        size_t end = str.find_first_of(delim, begin);
        result.push_back(str.substr(begin, end - begin));

        if (end == std::string::npos)
        {
            break;
        }

        begin = end + 1;
    }
    return result;
}

#endif // !DANDAN_STRSPLIT_H
