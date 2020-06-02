/**
 * Author: Asger Hautop Drewsen
 * Date: 2018-11-15
 * License: CC0
 * Source: https://wwwf.imperial.ac.uk/~rn/centroid.pdf
 * Description: Returns six times the volume of a polyhedron.
 *  Points in faces can be given in either cw or ccw order.
 * Status: Tested with Kattis problem threedprinter
 */
#pragma once

#include "Point3D.h"

template<class T>
T polyhedronVolume6(const vector<vector<Point3D<T>>> & faces) {
	T volume = 0;
	Point3D<T> center;
	set<Point3D<T>> vertices;
	for(auto& face : faces) for(auto& p : face) {
		if (!vertices.count(p)) {
			center = center + p;
			vertices.insert(p);
		}
	}
	center = center / sz(vertices);
	for(auto& f : faces) {
		rep(i, 1, sz(f) - 1) {
			auto normal = (f[i] - f[0]).cross(f[i+1] - f[0]);
			T s = normal.dot(center - f[0]) < 0? 1: -1;
			volume += f[0].dot(normal) * s;
		}
	}
	return volume;
}
