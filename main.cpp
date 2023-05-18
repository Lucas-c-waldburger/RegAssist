#include <iostream>
#include "RangeTools.h"
#include "RegAssist.h"

void increment(std::string& min) {}
void decrement(std::string& max) {}
void changeBuildPattern() {}
std::string build(std::string& dCount) { return "built";}








int main() {

    std::string subject;

    for (int i = 0; i <= 10000; i++)
        subject += std::to_string(i) + ' ';

    RegAssist rgx(subject);

//    std::string minStr = "53", maxStr = "107", formattedRange;
//
//    formattedRange = rgx.buildRangeExpression(minStr, maxStr);

    std::vector<std::string> matches = rgx.rangeMatch(4, 8000);

    for (auto& match : matches)
        std::cout << match << '\n';

    return 0;
}
