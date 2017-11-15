/**
 * Author: Asger Hautop Drewsen
 * Date: 2017-11-15
 * License: CC0
 * Description: Makes a POD-like type hashable
 * Usage: struct P { int x, y; }; MAKE_HASHABLE(P, t.x, t.y);
 */
#pragma once

size_t hash_combine(size_t s) { return s; }
template <typename T, typename... Ts>
size_t hash_combine(size_t s, const T & v, Ts... vs) {
    return hash_combine(hash<T>{}(v) + 0x9e3779b9 +
           (s<<6) + (s>>2), vs...);
}
#define MAKE_HASHABLE(T, ...) \
    namespace std {\
        template<> struct hash<T> {\
            size_t operator()(const T &t) const {\
                return hash_combine(0, __VA_ARGS__);\
            } }; }

