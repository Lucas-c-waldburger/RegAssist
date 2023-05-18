#include <iostream>
#include "RangeTools.h"
#include "RegAssist.h"

void increment(std::string& min) {}
void decrement(std::string& max) {}
void changeBuildPattern() {}
std::string build(std::string& dCount) { return "built";}








int main() {

    std::string subject;

    for (int i = -1000; i < 0; i++)
        subject += std::to_string(i) + ',';
    for (int j = 0; j <= 1000; j++)
        subject += std::to_string(j) + ',';

    RegAssist rgx(subject);

//    std::string minStr = "53", maxStr = "107", formattedRange;
//
//    std::string formattedRange = rgx.buildRangeExpression("0", "20");
//    std::cout << formattedRange;


    std::vector<std::string> matches = rgx.rangeMatch(-77, 124);
//
    for (auto& match : matches)
        std::cout << match << '\n';

    return 0;
}
