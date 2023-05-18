
#ifndef REGASSIST_REGASSIST_H
#define REGASSIST_REGASSIST_H

#include <iostream>
#include <regex>
#include <memory>
#include "RangeTools.h"

#define BOTH_POS 0
#define MIN_NEG 1
#define BOTH_NEG 2

class RegAssist
{
public:

    RegAssist() = default;
    RegAssist(std::string subject);

//    struct RangeFormat
//    {
//        std::vector<std::string> subExps;
//
//        void addSubExp(std::string& numStr, char bracketLow, char bracketHigh)
//        {
//            subExps.push_back(numStr + '[' + bracketLow + '-' + bracketHigh + ']');
//        }
//
//        std::string join(std::string& dCount)
//        {
//            std::string joined = "(";
//
//            for (auto& sub : subExps)
//                joined += sub + '|';
//
//            subExps.clear();
//
//            joined.pop_back();
//            joined += ')' + dCount;
//
//            return joined;
//        }
//
//        void operator()(std::string& numStr, char bracketLow, char bracketHigh)
//        {
//            addSubExp(numStr, bracketLow, bracketHigh);
//        }
//    };

    struct RangeTools
    {
        RangeTools(std::string& boundStr, char bracketFirst, char bracketSecond) :
                   boundStr(boundStr), bracket(bracketFirst, bracketSecond)
        {

        };

        std::string& boundStr;
        std::pair<char, char> bracket;

        void bracketNext()
        {
            bracket.first = boundStr.back();
            boundStr.pop_back();
        }
    };



    std::string buildRangeExpression(std::string min, std::string max);
    std::string buildRangeExpNegatives(std::string min, std::string max);

    std::vector<std::string>& match(std::string regexQuery, std::string tempSubject);

    std::vector<std::string>& rangeMatch(int min, int max);

    void setQuery(std::string newQuery);
    std::string getQuery() const;

    void setSubject(std::string newSubject);
    std::string getSubject() const;

//std::vector<std::string>& range(int min, int max);

    std::vector<std::string>& operator[](int i);
    void operator()(std::string subject);

private:

    std::string subject;
    std::string query;
    std::regex re;

    std::vector<std::shared_ptr<std::vector<std::string>>> log;

    void increment(std::string& numStr, std::string::reverse_iterator currentIt);
    void decrement(std::string& numStr, std::string::reverse_iterator currentIt);




//void updateRe();
//void updateRe(std::string regexQuery);

};


#endif //REGASSIST_REGASSIST_H
