//
// Created by Edythe Klompus on 11/14/21.
//

#ifndef FT_IRC_STRINGUTILS_H
#define FT_IRC_STRINGUTILS_H

#include <vector>

class StringUtils {
private:
    StringUtils() {};
public:
    static std::vector<char *> *splitMessage(const char *message);
    static const char *skipSpaces(const char *s);
    static char *duplicateString(const char *s, size_t length);
    static char *duplicateString(const char *s);
    static const char *skipNonSpaces(const char *s);
    static std::vector<char *> *splitMessage(std::vector<char *> *words, const char *message);
};


#endif //FT_IRC_STRINGUTILS_H
