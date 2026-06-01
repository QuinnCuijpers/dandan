#ifndef DANDAN_UTIL_H
#define DANDAN_UTIL_H

#include <array>
#include <string>

// taken from https://www.geeksforgeeks.org/dsa/convert-number-to-words/
namespace dandan::utils
{

    static const int THOUSAND = 1000;
    static const int HUNDRED = 100;
    static const int TWENTY = 20;
    static const int TEN = 10;

    // Words for numbers 0 to 19
    static constexpr std::array<const char *, 20> units = {
        "",        "One",     "Two",       "Three",    "Four",
        "Five",    "Six",     "Seven",     "Eight",    "Nine",
        "Ten",     "Eleven",  "Twelve",    "Thirteen", "Fourteen",
        "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

    // Words for numbers multiple of 10
    static constexpr std::array<const char *, 10> tens = {
        "",      "",      "Twenty",  "Thirty", "Forty",
        "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

    static constexpr std::array<const char *, 4> multiplier = {
        "", "Thousand", "Million", "Billion"};

    inline std::string convertToWords(int n)
    {
        if (n == 0)
        {
            return "Zero";
        }

        std::string res{};
        int group{};

        // Process number in group of 1000s
        while (n > 0)
        {
            if (n % THOUSAND != 0)
            {

                int value = n % THOUSAND;
                std::string temp{};

                // Handle 3 digit number
                if (value >= HUNDRED)
                {
                    temp = std::string(units.at(value / HUNDRED)) + " Hundred ";
                    value %= HUNDRED;
                }

                // Handle 2 digit number
                if (value >= TWENTY)
                {
                    temp += std::string(tens.at(value / TEN)) + " ";
                    value %= TEN;
                }

                // Handle unit number
                if (value > 0)
                {
                    temp += std::string(units.at(value)) + " ";
                }

                // Add the multiplier according to the group
                temp += std::string(multiplier.at(group)) + " ";

                // Add this group result to overall result
                res += temp;
            }
            n /= THOUSAND;
            group++;
        }

        // Remove trailing space
        return res.substr(0, res.find_last_not_of(' ') + 1);
    }
} // namespace dandan::utils

#endif