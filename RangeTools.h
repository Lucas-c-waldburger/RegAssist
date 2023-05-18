
#ifndef REGASSIST_RANGETOOLS_H
#define REGASSIST_RANGETOOLS_H

#include <iostream>
#include <utility>
#include <vector>


struct RangeFormat
{
    std::vector<std::string> subExps;

    void addSubExp(std::string& numStr, char bracketLow, char bracketHigh)
    {
        subExps.push_back(numStr + '[' + bracketLow + '-' + bracketHigh + ']');
    }

    std::string join(std::string& dCount)
    {
        std::string joined = "(";

        for (auto& sub : subExps)
            joined += sub + '|';

        subExps.clear();

        joined.pop_back();
        joined += ')' + dCount;

        return joined;
    }

    void operator()(std::string& numStr, char bracketLow, char bracketHigh)
    {
        addSubExp(numStr, bracketLow, bracketHigh);
    }
};

//class RangeTools
//{
//public:
//
//    RangeTools(std::string boundStr) : bound(std::move(boundStr)), bracket('0', '9') {};
//
//    std::string bound;
//    std::pair<char, char> bracket;
//
//    std::string format()
//    {
//        return bound + '[' + bracket.first + '-' + bracket.second + ']';
//    };
//
//};
//
//class RTMin : public RangeTools
//{
//public:
//
//    RTMin(std::string& boundStr) : RangeTools(boundStr)
//    {
//        bracketNext();
//    };
//
//    void bracketNext()
//    {
//        bracket.first = bound.back();
//        bound.pop_back();
//    }
//
//};
//
//class RTMax : public RangeTools
//{
//public:
//
//    RTMax(std::string& boundStr) : RangeTools(boundStr)
//    {
//        bracketNext();
//    };
//
//    void bracketNext()
//    {
//        bracket.second = boundStr.back();
//        boundStr.pop_back();
//    }
//};


#endif //REGASSIST_RANGETOOLS_H
