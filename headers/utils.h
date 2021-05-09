#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>

#define \
array_length(type, array)               \
({                                      \
    type* m_arr;                        \
    int m_len;                          \
                                        \
    m_arr = (type*)array;               \
    m_len = 0;                          \
                                        \
    while (m_arr[m_len] != 0) {         \
        m_len += 1;                     \
    }                                   \
                                        \
    m_len+1;                            \
})

char* strToChar(std::string str);

#endif // __UTILS_H__
