/**
 * Author: Asger Hautop Drewsen
 * Date: 2017-10-06
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection
 * Description: Given a line with point l0 and direction l and a plane with point p0 and normal vector n returns the intersection and the distance.
 */
#pragma once

#include "Point3D.h"

typedef Point3D<double> P;
int lpIntersection(P l0, P l, P p0, P n, P & r, double & d) {
	auto x = (p0 - l0).dot(n), ln = l.dot(n);
	if (ln == 0) {
		if (x == 0) { // Line lies in plane
			d = 0, r = l0;
			return 2;
		}
		return 0; // No intersection
	}
	d = x / ln, r = l * d + l0;
	return 1;
}
