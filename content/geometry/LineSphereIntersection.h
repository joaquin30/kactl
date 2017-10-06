/**
 * Author: Asger Hautop Drewsen
 * Date: 2017-10-06
 * License: CC0
 * Description: Given a sphere with center s and radius r and a line with point l0 and direction l returns whether they intersect.
 */
#pragma once

#include "LinePlaneIntersection.h"

bool lsIntersects(P l0, P l, P s, double r) {
	P ip; double d;
	if (!lpIntersection(l0, l, s, l, ip, d))
		return false;
	if (d < 0) return false;
	return (s - ip).dist() <= r;
}
