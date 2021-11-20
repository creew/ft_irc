#include "StringUtils.h"

std::vector<char *> StringUtils::splitMessage(std::vector<char *> &words, const char *message) {
    const char *s, *d;
    do {
        s = skipSpaces(message);
        d = skipNonSpaces(s);
        if (d == s) {
            break;
        }
        if (*s == ':') {
            words.push_back(duplicateString(++s));
            break;
        }
        words.push_back(duplicateString(s, d - s));
        message = d;
    } while (true);
    return words;
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
