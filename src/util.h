#ifndef MYREGEX_UTIL_H_
#define MYREGEX_UTIL_H_

inline bool num(char c) { return '0' <= c && c <= '9'; }
inline bool alpha_upper(char c) { return 'A' <= c && c <= 'Z'; }
inline bool alpha_lower(char c) { return 'a' <= c && c <= 'z'; }
inline bool alpha(char c) { return alpha_lower(c) || alpha_upper(c); }
inline bool alphanum(char c) { return alpha(c) || num(c); }

#endif