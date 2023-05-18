
#include "RegAssist.h"


RegAssist::RegAssist(std::string subject) : subject(subject)
{}

void RegAssist::setQuery(std::string newQuery)
{
    this->query = newQuery;
}

std::string RegAssist::getQuery() const
{
    return query;
}

void RegAssist::setSubject(std::string newSubject)
{
    this->subject = newSubject;
}

std::string RegAssist::getSubject() const
{
    return subject;
}


std::string RegAssist::buildRangeExpression(std::string min, std::string max)
{
    RangeFormat format;
    std::string dCount;
    char tempMin, tempMax;
    std::string::reverse_iterator minIt, maxIt;

    std::string rangeExp = "\\b(";

    while (true)
    {
        // PULL OUT
        tempMin = min.back(); tempMax = max.back();
        min.pop_back(); max.pop_back();

        // CHECK MAX EMPTY
        if (max.empty() || min == max)
        {
            format(max, tempMin, tempMax);
            return rangeExp + format.join(dCount) + ")\\b";
        }

        // BUILD
        format(min, tempMin, '9');
        format(max, '0', tempMax);
        rangeExp += format.join(dCount) + '|';

        // CHECK MIN EMPTY
        if (min.empty())
            min = "0";

        // INC/DEC FOR NEXT LOOP
        minIt = min.rbegin(); maxIt = max.rbegin();
        increment(min, minIt); decrement(max, maxIt);

        // ++DCOUNT FOR NEXT LOOP
        dCount += "\\d";
    }
}

// SEE IF ADDING EMPTY STRING FUCKS THINGS UP
// IF NOT, JUST USE BACKET_MAX()

// TOP LEVEL FUNCTION ASSIGNS OPENING/CLOSING '\\b'

// pass decrement/increment as functional?
// then would need a "top level" function to consolidate

// THIS MIGHT ONLY WORK IF MAX HAS MORE DIGIT PLACES!!!!!!!!! check plz
std::string RegAssist::makeRangeMax(std::string max, size_t minSize)
{

    if (max.front() == '0')
        throw std::invalid_argument("Numbers cannot begin with '0'");


    std::string formattedRange;
    std::string dCountMax;
    char tempMax;
    char bottomBound = '0';

    int dCount = 0;
    auto addDs = [&dCount]() { std::string d; for (int i = 0; i < dCount; i++) { d += "\\d"; } return d; };

    tempMax = max.back();
    max.pop_back();
    formattedRange += max + '[' + bottomBound + '-' + tempMax + "]|";

    std::string::reverse_iterator rIt;
    while (dCount != minSize && bottomBound != '1')
    {
        if (max.empty())
        {
            --dCount;
            formattedRange += "[1-9]" + addDs() + '|';

        }
        else
        {
            rIt = max.rbegin();
            decrement(max, rIt);

            tempMax = max.back();
            max.pop_back();

            ++dCount;

            if (max.empty())
                bottomBound = '1';

            formattedRange += max + '[' + bottomBound + '-' + tempMax + ']' + addDs() + '|';

        }
    }

    formattedRange.pop_back();
    return formattedRange;
}


std::string RegAssist::makeRangeMin(std::string min)
{

    if (min.front() == '0')
        throw std::invalid_argument("Numbers cannot begin with '0'");


    std::string formattedRange;
    std::string dCountMin;
    char tempMin;

    tempMin = min.back();
    min.pop_back();
    formattedRange += min + '[' + tempMin + "-9]|";

    std::string::reverse_iterator rIt;
    while (!min.empty())
    {

        rIt = min.rbegin();
        increment(min, rIt);

        tempMin = min.back();
        min.pop_back();

        dCountMin += "\\d";

        formattedRange += min + '[' + tempMin + "-9]" + dCountMin + '|';
    }

    return formattedRange;
}



//std::string RegAssist::makeRanges(std::string min, std::string max)
//{
//
//    auto rtMin = RTMin(min);
//    auto rtMax = RTMax(max);
//
//    std::string dCount;
//    auto formatLayer = [&]() { return '(' + rtMin.format() + '|' + rtMax.format() + ')' + dCount; };
//
//    std::string formattedRange = formatLayer() + '|';
//
//    std::string::reverse_iterator rIt;
//    while (!rtMin.bound.empty() && !rtMax.bound.empty())
//    {
//        if (max.empty())
//        {
//            --dCount;
//            formattedRange += "[1-9]" + addDs() + '|';
//
//        }
//        else
//        {
//            rIt = max.rbegin();
//            decrement(max, rIt);
//
//            tempMax = max.back();
//            max.pop_back();
//
//            ++dCount;
//
//            if (max.empty())
//                bottomBound = '1';
//
//            formattedRange += max + '[' + bottomBound + '-' + tempMax + ']' + addDs() + '|';
//
//        }
//    }
//
//    formattedRange.pop_back();
//    return formattedRange;
//}


// performs new match using supplied regexQuery argument 
// matches against "this->subject" by default; Optional argument tempSubject performs match on a newly-supplied subject string instead. Does NOT update "this->subject"
// stores match inside log as new shared_ptr and returns a reference to the match
std::vector<std::string>& RegAssist::match(std::string regexQuery, std::string tempSubject)
{
//if (tempSubject.empty()) // set default
// tempSubject = this->subject;

    re = std::regex(regexQuery); // update regex with new query

    log.emplace_back(std::make_shared<std::vector<std::string>>()); // create new match vector inside log

    auto itBegin = std::sregex_iterator(tempSubject.begin(), tempSubject.end(), re);
    auto itEnd = std::sregex_iterator();
    std::smatch m;

    for (std::sregex_iterator i = itBegin; i != itEnd; i++) // populate new match vector
    {
        m = *i;
        log.back()->push_back(m.str());
    }

    return *(log.back().get()); // return new match vector as reference
}

//std::vector<std::string>& RegAssist::range(int min, int max)
//{
//    std::string minStr = std::to_string(min), maxStr = std::to_string(max);
//
//}


std::vector<std::string>& RegAssist::operator[](int i)
{
    if (i > log.size() - 1)
        throw std::out_of_range("Index exceeds log size");

    return *(log[i].get());
}

void RegAssist::operator()(std::string subject)
{
    setSubject(subject);
}

void RegAssist::increment(std::string& numStr, std::string::reverse_iterator currentIt)
{
    if (*currentIt == '9')
    {
        *currentIt = '0';

        if (currentIt == numStr.rend() - 1)
        {
            numStr.insert(0, "1");
            return;
        }
        else
            increment(numStr, std::next(currentIt));
    }
    else
        *currentIt += 1;
}

void RegAssist::decrement(std::string& numStr, std::string::reverse_iterator currentIt)
{
    if (*currentIt == '0')
    {
        *currentIt = '9';

        if (currentIt == numStr.rend() - 1)
        {
            numStr.erase(0, 1);
            return;
        }
        else
            decrement(numStr, std::next(currentIt));
    }
    else
        *currentIt -= 1;
}

std::vector<std::string> &RegAssist::rangeMatch(int min, int max) {
    std::string minStr = std::to_string(min);
    std::string maxStr = std::to_string(max);

    std::string rangeQuery = buildRangeExpression(minStr, maxStr);

    return match(rangeQuery, subject);
}
