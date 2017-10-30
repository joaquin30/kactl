/**
 * Author: Asger Hautop Drewsen
 * Date: 2017-09-29
 * License: CC0
 * Description: Negative return value means no match found.
 * Time: O(N + M)
 */
#pragma once

#include <regex.h> /** keep-include */

string pattern = "a*";
regex_t re{};
re.fastmap = (char *)malloc(256);
re_compile_pattern(pattern.data(), sz(pattern), &re);
string S = "aaa";
int matched = re_match(&re, S.data(), sz(S), 0, nullptr);
int i = re_search(&re, S.data(), sz(S), 0, sz(S), nullptr);
regfree(&re);
