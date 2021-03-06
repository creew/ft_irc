#include "StringUtils.h"


void StringUtils::splitMessage(vector<string> &words, const char *message) {
    const char *s, *d;
    do {
        s = skipSpaces(message);
        d = skipNonSpaces(s);
        if (d == s) {
            break;
        }
        if (*s == ':') {
            words.push_back(++s);
            break;
        }
        string word = string(s, d - s);
        words.push_back(word);
        message = d;
    } while (true);
}

const char *StringUtils::skipSpaces(const char *s) {
    while (*s == ' ') {
        s++;
    }
    return s;
}

const char *StringUtils::skipNonSpaces(const char *s) {
    while (*s != ' ' && *s != '\0') {
        s++;
    }
    return s;
}

char *StringUtils::duplicateString(const char *s, size_t length) {
    char *d = new char[length + 1];
    strncpy(d, s, length);
    d[length] = '\0';
    return d;
}

char *StringUtils::duplicateString(const char *s) {
    size_t length = strlen(s);
    char *d = new char[length];
    strncpy(d, s, length);
    d[length] = '\0';
    return d;
}

bool StringUtils::isEmpty(const char *s) {
    return s == NULL || *s == '\0';
}

char StringUtils::toUpper(char c)
{
    if (c >= 'a' && c <= 'z')
        return (c - 'a' + 'A');
    return (c);
}

int	StringUtils::strcmpNoCase(const char *s1, const char *s2)
{
    unsigned char c1 = toUpper(*s1++);
    unsigned char c2 = toUpper(*s2++);
    while (c1 && c2)
    {
        if (c1 != c2)
            break;
        c1 = toUpper(*s1++);
        c2 = toUpper(*s2++);
    }
    return (c1 - c2);
}
