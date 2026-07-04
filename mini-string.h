#if !defined(MINI_STRING_H)
#define MINI_STRING_H
/**
 * @file   mini-string.h
 * @brief  Mini: Strings.
 * @author Alicia D. Amarilla (smushyaa@gmail.com)
 * @date   July 01, 2026
*/
#include <string.h>
#if !defined(MINI_CONTAINERS_H)
    static_assert(false,
        "mini-containers.h is a required dependency! include it before mini-string.h");
#endif /* check for dependency: mini-containers.h */

/// @brief UTF-8 String.
typedef Slice<char> String;

/// @brief UTF-16 String.
typedef Slice<wchar_t> WString;

/// @brief UTF-32 String.
typedef Slice<char32_t> UString;

/// @brief A rune is a UTF-32 encoded character.
typedef char32_t Rune;

/// @brief Strategy for splitting strings.
enum class StringSplitStrategy : int {
    /// @brief Do not keep split criteria (default).
    DISCARD,
    /// @brief Keep split criteria on left side of split.
    KEEP_LEFT,
    /// @brief Keep split criteria on right side of split.
    KEEP_RIGHT,

    /// @brief Default strategy.
    DEFAULT = DISCARD
};

/// @brief Streaming function prototype.
/// @param[in] target Target of streaming function.
/// @param     count  Number of bytes to stream.
/// @param[in] bytes  Bytes to stream.
/// @return Number of bytes that could not be streamed.
typedef size_t StreamFn(void *target, size_t count, const void *bytes);

/// @brief Create a string from a null-terminated string.
/// @param[in] cstr Null-terminated string.
/// @param     len  (optional) Length of string. If not provided, calls strlen on @c cstr.
/// @return String.
inline
String string(const char *cstr, size_t len = 0);

/// @brief Create a string from a string literal.
/// @param[in] cstr Null-terminated string literal.
/// @return String.
template<size_t N> constexpr inline
String string(const char (&cstr)[N]);

constexpr inline
size_t utf8_len(String str);

constexpr inline
const char& utf8_index(const String& str, size_t index);

constexpr inline
char& utf8_index(String& str, size_t index);

inline
Rune utf8_get_next(String str, size_t *out_len = nullptr);

/// @brief Compare two strings for equality.
/// @param a, b Strings to compare.
/// @return
///     - @c true  : @c a and @c b are equal in content and length.
inline
bool cmp(String a, String b);

/// @brief Search for item in string.
/// @param      str       String to search in.
/// @param      ch        Character rune to search for.
/// @param[out] out_index (nullable) Pointer to write index that first occurrence was found in.
/// @return
///     - @c true  : @c ch was found.
///     - @c false : @c ch was not found.
inline
bool find(String str, Rune ch, size_t *out_index = nullptr);

/// @brief Search for item in string.
/// @param      str       String to search in.
/// @param      substr    Substring to search for.
/// @param[out] out_index (nullable) Pointer to write index that first occurrence was found in.
/// @return
///     - @c true  : @c substr as found.
///     - @c false : @c substr was not found.
inline
bool find(String str, String substr, size_t *out_index = nullptr);

/// @brief Search for item in string.
/// @param      str       String to search in.
/// @param      set       Set of character runes to search for.
/// @param[out] out_index (nullable) Pointer to write index that first occurrence was found in.
/// @return
///     - @c true  : @c set as found.
///     - @c false : @c set was not found.
inline
bool find(String str, Slice<Rune> set, size_t *out_index = nullptr);

/// @brief Search for item in string in reverse.
/// @param      str       String to search in.
/// @param      ch        Character rune to search for.
/// @param[out] out_index (nullable) Pointer to write index that last occurrence was found in.
/// @return
///     - @c true  : @c ch was found.
///     - @c false : @c ch was not found.
inline
bool find_rev(String str, Rune ch, size_t *out_index = nullptr);

/// @brief Search for item in string in reverse.
/// @param      str       String to search in.
/// @param      substr    Substring to search for.
/// @param[out] out_index (nullable) Pointer to write index that last occurrence was found in.
/// @return
///     - @c true  : @c substr as found.
///     - @c false : @c substr was not found.
inline
bool find_rev(String str, String substr, size_t *out_index = nullptr);

/// @brief Search for item in string in reverse.
/// @param      str       String to search in.
/// @param      set       Set of character runes to search for.
/// @param[out] out_index (nullable) Pointer to write index that last occurrence was found in.
/// @return
///     - @c true  : @c set as found.
///     - @c false : @c set was not found.
inline
bool find_rev(String str, Slice<Rune> set, size_t *out_index = nullptr);

/// @brief Split string.
/// @param str   String to split.
/// @param index Index to split at.
/// @return Left and right sides of split.
template<StringSplitStrategy Strategy = StringSplitStrategy::DEFAULT> inline
Tuple<String,String> split_at(String str, size_t index);

/// @brief Split string at first instance of character.
/// @param str String to split.
/// @param ch  Character to search for.
/// @return Left and right sides of split.
template<StringSplitStrategy Strategy = StringSplitStrategy::DEFAULT> inline
Tuple<String,String> split(String str, Rune ch);

/// @brief Split string at first instance of substring.
/// @param str    String to split.
/// @param substr Substring to search for.
/// @return Left and right sides of split.
template<StringSplitStrategy Strategy = StringSplitStrategy::DEFAULT> inline
Tuple<String,String> split(String str, String substr);

/// @brief Split string at first instance of set.
/// @param str String to split.
/// @param set Set to search for.
/// @return Left and right sides of split.
template<StringSplitStrategy Strategy = StringSplitStrategy::DEFAULT> inline
Tuple<String,String> split(String str, Slice<Rune> set);

/// @brief Split string at last instance of character.
/// @param str String to split.
/// @param ch  Character to search for.
/// @return Left and right sides of split.
template<StringSplitStrategy Strategy = StringSplitStrategy::DEFAULT> inline
Tuple<String,String> split_rev(String str, Rune ch);

/// @brief Split string at last instance of substring.
/// @param str    String to split.
/// @param substr Substring to search for.
/// @return Left and right sides of split.
template<StringSplitStrategy Strategy = StringSplitStrategy::DEFAULT> inline
Tuple<String,String> split_rev(String str, String substr);

/// @brief Split string at last instance of set.
/// @param str String to split.
/// @param set Set to search for.
/// @return Left and right sides of split.
template<StringSplitStrategy Strategy = StringSplitStrategy::DEFAULT> inline
Tuple<String,String> split_rev(String str, Slice<Rune> set);

/// @brief Split string by character into buffer.
/// @param[in] b            Buffer of strings.
/// @param     str          String to split.
/// @param     ch           Character to split at.
/// @param     can_allocate If buffer is allowed to reallocate.
/// @return If can allocate, how many strings added. If cannot, how many strings were not added.
template<StringSplitStrategy Strategy = StringSplitStrategy::DEFAULT> inline
size_t split(Buffer<String>& b, String str, Rune ch, bool can_allocate = true);

/// @brief Split string by substring into buffer.
/// @param[in] b            Buffer of strings.
/// @param     str          String to split.
/// @param     substr       Substring to split at.
/// @param     can_allocate If buffer is allowed to reallocate.
/// @return If can allocate, how many strings added. If cannot, how many strings were not added.
template<StringSplitStrategy Strategy = StringSplitStrategy::DEFAULT> inline
size_t split(Buffer<String>& b, String str, String substr, bool can_allocate = true);

/// @brief Trim leading whitespace.
/// @param str String to trim.
/// @return Trimmed.
inline
String trim_whitespace_lead(String str);

/// @brief Trim trailing whitespace.
/// @param str String to trim.
/// @return Trimmed.
inline
String trim_whitespace_trail(String str);

/// @brief Trim leading and trailing whitespace.
/// @param str String to trim.
/// @return Trimmed.
inline
String trim_whitespace(String str);

// NOTE(alicia): implementation

inline
String string(const char *cstr, size_t len) {
    if(!len) {
        len = strlen(cstr);
    }
    return slice<char>(len, cstr);
}

template<size_t N> constexpr inline
String string(const char (&cstr)[N]) {
    return slice<char>(N-1, cstr);
}

inline
bool cmp(String a, String b) {
    return (a.len == b.len) && (memcmp(a.ptr, b.ptr, a.len) == 0);
}

inline
bool find(String str, Rune ch, size_t *out_index) {
    String substr = str;
    while(substr.len) {
        size_t len = 0;
        Rune current = utf8_get_next(substr, &len);

        if(current == ch) {
            if(out_index) {
                *out_index = substr.ptr - str.ptr;
            }
            return true;
        }

        substr += len ? len : 1;
    }

    return false;
}

inline
bool find(String str, String substr, size_t *out_index) {
    for(size_t i = 0; i < str.len; ++i) {
        if(str[i] != substr[0]) {
            continue;
        }

        String potential = str + i;
        if(potential.len < substr.len) {
            return false;
        }

        potential.len = substr.len;

        if(cmp(potential, substr)) {
            if(out_index) {
                *out_index = potential.ptr - str.ptr;
            }
            return true;
        }
    }

    return false;
}

inline
bool find(String str, Slice<Rune> set, size_t *out_index) {
    String substr = str;
    while(substr.len) {
        size_t len = 0;
        Rune current = utf8_get_next(substr, &len);

        for(size_t i = 0; i < set.len; ++i) {
            if(current == set[i]) {
                if(out_index) {
                    *out_index = substr.ptr - str.ptr;
                }
                return true;
            }
        }

        substr += len ? len : 1;
    }

    return false;
}

inline
bool find_rev(String str, Rune ch, size_t *out_index) {
    for(size_t i = str.len; i-- > 0;) {
        size_t len = 0;
        Rune rune = utf8_get_next(str + i, &len);
        if(!len) {
            continue;
        }

        if(rune == ch) {
            if(out_index) {
                *out_index = i;
            }
            return true;
        }
    }

    return false;
}

inline
bool find_rev(String str, String substr, size_t *out_index) {
    if(substr.len > str.len) {
        return false;
    }

    for(size_t i = str.len; i-- > 0;) {
        String chunk = str + i;

        if(chunk.len < substr.len) {
            continue;
        }

        chunk.len = substr.len;

        if(cmp(chunk, substr)) {
            if(out_index) {
                *out_index = i;
            }
            return true;
        }
    }

    return false;
}

inline
bool find_rev(String str, Slice<Rune> set, size_t *out_index) {
    for(size_t i = str.len; i-- > 0;) {
        size_t len = 0;
        Rune rune = utf8_get_next(str + i, &len);
        if(!len) {
            continue;
        }

        for(size_t j = 0; j < set.len; ++j) {
            if(rune == set[j]) {
                if(out_index) {
                    *out_index = i;
                }
                return true;
            }
        }
    }

    return false;
}

template<StringSplitStrategy Strategy> inline
Tuple<String,String> split_at(String str, size_t index) {
    if constexpr (Strategy == StringSplitStrategy::KEEP_LEFT) {
        return tuple(truncate(str, index + 1), advance(str, index + 1));
    } else if constexpr (Strategy == StringSplitStrategy::KEEP_RIGHT) {
        return tuple(truncate(str, index), advance(str, index));
    }

    return tuple(truncate(str, index), advance(str, index + 1));
}

template<StringSplitStrategy Strategy> inline
Tuple<String,String> split(String str, Rune ch) {
    size_t index = 0;
    if(find(str, ch, &index)) {
        return split_at<Strategy>(str, index);
    } else {
        return tuple(str, string("", 0));
    }
}

template<StringSplitStrategy Strategy> inline
Tuple<String,String> split(String str, String substr) {
    size_t index = 0;
    if(find(str, substr, &index)) {
        return split_at<Strategy>(str, index);
    } else {
        return tuple(str, string("", 0));
    }
}

template<StringSplitStrategy Strategy> inline
Tuple<String,String> split(String str, Slice<Rune> set) {
    size_t index = 0;
    if(find(str, set, &index)) {
        return split_at<Strategy>(str, index);
    } else {
        return tuple(str, string("", 0));
    }
}

template<StringSplitStrategy Strategy> inline
Tuple<String,String> split_rev(String str, Rune ch) {
    size_t index = 0;
    if(find_rev(str, ch, &index)) {
        return split_at<Strategy>(str, index);
    } else {
        return tuple(str, string("", 0));
    }
}

template<StringSplitStrategy Strategy> inline
Tuple<String,String> split_rev(String str, String substr) {
    size_t index = 0;
    if(find_rev(str, substr, &index)) {
        return split_at<Strategy>(str, index);
    } else {
        return tuple(str, string("", 0));
    }
}

template<StringSplitStrategy Strategy> inline
Tuple<String,String> split_rev(String str, Slice<Rune> set) {
    size_t index = 0;
    if(find_rev(str, set, &index)) {
        return split_at<Strategy>(str, index);
    } else {
        return tuple(str, string("", 0));
    }
}

template<StringSplitStrategy Strategy> inline
size_t split(Buffer<String>& b, String str, Rune ch, bool can_allocate) {
    size_t count = 0;

    Tuple<String, String> splt;
    String right = str;
    do {
        splt = split<Strategy>(right, ch);

        String left = get<0>(splt);
        if(left.len) {
            if(can_allocate) {
                push(b, left);
                count++;
            } else {
                if(!try_push(b, left)) {
                    count++;
                }
            }
        }

        right = get<1>(splt);
    } while(get<1>(splt).len);

    return count;
}

template<StringSplitStrategy Strategy> inline
size_t split(Buffer<String>& b, String str, String substr, bool can_allocate) {
    size_t count = 0;

    Tuple<String, String> splt;
    String right = str;
    do {
        splt = split<Strategy>(right, substr);

        String left = get<0>(splt);
        if(left.len) {
            if(can_allocate) {
                push(b, left);
                count++;
            } else {
                if(!try_push(b, left)) {
                    count++;
                }
            }
        }

        right = get<1>(splt);
    } while(get<1>(splt).len);

    return count;
}

inline
String trim_whitespace_lead(String str) {
    constexpr static char   WHITESPACE[]     = { ' ', '\r', '\t', '\n' };
    constexpr static size_t WHITESPACE_COUNT = sizeof(WHITESPACE) / sizeof(char);

    for(size_t i = 0; i < str.len; ++i) {
        bool is_whitespace = false;
        for(size_t j = 0; j < WHITESPACE_COUNT; ++j) {
            if(WHITESPACE[j] == str[i]) {
                is_whitespace = true;
                break;
            }
        }

        if(!is_whitespace) {
            return str + i;
        }
    }

    return str;
}

inline
String trim_whitespace_trail(String str) {
    constexpr static char   WHITESPACE[]     = { ' ', '\r', '\t', '\n' };
    constexpr static size_t WHITESPACE_COUNT = sizeof(WHITESPACE) / sizeof(char);

    for(size_t i = str.len; i-- > 0;) {
        bool is_whitespace = false;
        for(size_t j = 0; j < WHITESPACE_COUNT; ++j) {
            if(WHITESPACE[j] == str[i]) {
                is_whitespace = true;
                break;
            }
        }

        if(!is_whitespace) {
            return str + i;
        }
    }

    return str;
}

inline
String trim_whitespace(String str) {
    return trim_whitespace_lead(trim_whitespace_trail(str));
}

#endif /* header guard */
