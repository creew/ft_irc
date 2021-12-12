#ifndef FT_IRC_STRINGUTILS_H
#define FT_IRC_STRINGUTILS_H

#include <vector>
#include <string>

using namespace std;

class StringUtils {
private:
    StringUtils() {};
public:
    static const char *skipSpaces(const char *s);
    static char *duplicateString(const char *s, size_t length);
    static char *duplicateString(const char *s);
    static const char *skipNonSpaces(const char *s);
    static bool isEmpty(const char *s);
    static char toUpper(char c);
    static int strcmpNoCase(const char *s1, const char *s2);
    static void splitMessage(vector<string> &words, const char *message);
};


#endif //FT_IRC_STRINGUTILS_H
