#ifndef FT_IRC_STRINGUTILS_H
#define FT_IRC_STRINGUTILS_H

#include <vector>

class StringUtils {
private:
    StringUtils() {};
public:
    static const char *skipSpaces(const char *s);
    static char *duplicateString(const char *s, size_t length);
    static char *duplicateString(const char *s);
    static const char *skipNonSpaces(const char *s);
    static std::vector<char *> splitMessage(std::vector<char *> &words, const char *message);
    static bool isEmpty(const char *s);
    static char toLower(char c);
    static int strcmpNoCase(const char *s1, const char *s2);
};


#endif //FT_IRC_STRINGUTILS_H
