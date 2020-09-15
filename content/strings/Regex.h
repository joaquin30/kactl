/**
 * Author: Asger Hautop Drewsen
 * Date: 2017-09-29
 * License: CC0
 * Description: You can use the following special characters: \texttt{\^{}\$.*?|()\{\}}
 * Time: O(NM)
 */
#pragma once

#include <regex.h> /** keep-include */

struct Regex {
	regex_t re;
	Regex(const string & p) {
		assert(regcomp(&re, p.data(), REG_EXTENDED) == 0);
	}
	~Regex() { regfree(&re); }
	bool search(const string & s, pii & res) {
		regmatch_t m;
		if (regexec(&re, s.data(), 1, &m, 0)) return false;
		res.first = m.rm_so; res.second = m.rm_eo;
		return true;
	}
};
