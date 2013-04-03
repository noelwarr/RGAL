#include <CGAL/intersections.h>

#include "defs.h"

using namespace std;
using namespace Rice;

/*
 * Returns
 * 		0 if the segments do not intersect
 * 		1 if the two segments intersect at one single point
 * 		2 if the two segments overlap
 */
// TODO: Use constants for return value
int segments_intersect(Point_2 p1, Point_2 p2, Point_2 q1, Point_2 q2){

	int result = 0;

    typedef Kernel::Segment_2         Segment_2;

    Segment_2 segment_1(p1,p2), segment_2(q1,q2);

    CGAL::Object obj = intersection(segment_1, segment_2);

    if (CGAL::object_cast<Point_2>(&obj)) {
    	result = 1;
    } else if (CGAL::object_cast<Segment_2>(&obj)) {
    	result = 2;
    }
    return result;
}

/*
 * Returns an intersection point of the segments p1p2 and q1q2.
 * WARNING: the intersection point must exists, use segments_intersect before calling this method, to make sure they do intersect.
 *
 * If the segments overlap and there is more than one intersection point, it returns the first point of the overlap segment
 *
 */
Point_2 intersect_segments(Point_2 p1, Point_2 p2, Point_2 q1, Point_2 q2){

    typedef Kernel::Segment_2         Segment_2;

    Segment_2 segment_1(p1,p2), segment_2(q1,q2);

    CGAL::Object obj = intersection(segment_1, segment_2);

    if (const Point_2 * point = CGAL::object_cast<Point_2>(&obj)) {
        /* do something with *point */
    	return Point_2(point->x(), point->y());
    } else if (const Segment_2 * segment = CGAL::object_cast<Segment_2>(&obj)) {
        /* do something with *segment*/
    	return segment->source();
    } else {
    	/* there was no intersection, return an ugly point... this case should actually throw an error */
    	return Point_2(-6666666, -6666666);
    }
}

