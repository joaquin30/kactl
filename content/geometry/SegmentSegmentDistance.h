/**
 * Author: Asger Hautop Drewsen
 * Date: 2017-11-15
 * License: CC0
 * Description: Returns the shortest distance between two segments.
 * Status: tested
 */
#pragma once

#include "SegmentDistance.h"
#include "SegmentIntersection.h"

double segsegDist(P s1, P e1, P s2, P e2) {
	if (!segInter(s1, e1, s2, e2).empty()) return 0;
	return min(segDist(s1, e1, s2),
	       min(segDist(s1, e1, e2),
	       min(segDist(s2, e2, s1),
	           segDist(s2, e2, e1))));
}
