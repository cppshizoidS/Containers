#ifndef MY_STRCMP_HPP

inline int my_strcmp(const char* str1, const char* str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 < *str2) {
            return -1;
        } else if (*str1 > *str2) {
            return 1;
        }
        // Move to the next characters in both strings
        str1++;
        str2++;
    }

    if (*str1 == '\0' && *str2 != '\0') {
        return -1;
    } else if (*str1 != '\0' && *str2 == '\0') {
        return 1;
    }

    return 0;
}
#endif // MY_STRCMP_HPP