#include "defs.h"

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/create_straight_skeleton_from_polygon_with_holes_2.h>
#include<CGAL/create_offset_polygons_from_polygon_with_holes_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel EPICK ;
typedef CGAL::Polygon_2<EPICK>           Polygon_2_EPICK ;
typedef CGAL::Polygon_with_holes_2<EPICK> Polygon_with_holes_EPICK ;
typedef CGAL::Straight_skeleton_2<EPICK> Ss ;
typedef boost::shared_ptr<Ss> SsPtr ;
typedef std::vector< boost::shared_ptr<Polygon_2> > PolygonPtrVectorEPECK ;


using namespace std;
using namespace Rice;

/**
 * Methods to produce inward offsets based on straight skeleton.
 * 
 * inward_offset_polygon is the one supposed to be invoked from the outside
 * 
 */


/**
 *   
 * For do_inward_offset_from_EPICK the input polygon must be EPICK, but the output is EPECK.
 * 
 * Returns the first #countours inwards offsets with a distance of @offsetStep, if #contours is not specified o is 0, all contours all returned
 * 
 * Return type is Array of [Array of Polygon_2 (EPECK)]
 */


Array do_inward_offset_from_EPICK(Polygon_with_holes_EPICK poly, double offsetStep, int contours){
    
      int MAX_CONTOURS = 1000; //Limit variable in case something goes wrong
      double MIN_POLYGON_AREA = 1.0; // Minimum area to consider an offset polygon

      // If max number of contours unspecified, we assume all offsets need to be computed
      if (contours==0) {
    	  contours = MAX_CONTOURS;
      }

      SsPtr iss = CGAL::create_interior_straight_skeleton_2(poly);
      
      PolygonPtrVectorEPECK curr_offset_polygons; // Will store the polygons for one fixed offset
      vector<PolygonPtrVectorEPECK> offset_collection; //Stores the offset polygons for all offset_collection

      Array outputCollection; // The final array that will be output
     
      double offset = offsetStep;
      int count = 1;
      do {
			curr_offset_polygons  = CGAL::create_offset_polygons_2<Polygon_2>(offset,*iss, Kernel());
			if (!curr_offset_polygons.empty()) {
			  double totalPolygonArea = 0;
			  Array currentOffsetPolygons; // Offset polygons for one fixed offset

			  for( typename PolygonPtrVectorEPECK::const_iterator pi = curr_offset_polygons.begin() ; pi != curr_offset_polygons.end() ; ++ pi ) {
				  Polygon_2 polygon2 = Polygon_2((*pi)->vertices_begin (), (*pi)->vertices_end());
				  currentOffsetPolygons.push(**pi);

				  totalPolygonArea += CGAL::to_double ( (*pi)->area() );
				}

			  if (totalPolygonArea>MIN_POLYGON_AREA) {
				offset_collection.push_back(curr_offset_polygons); //TODO Rodrigo: I dont think this is used
				Array newArray(currentOffsetPolygons);
				outputCollection.push(newArray);
			  } else {
				cout << "inward_offset.h warning: offset ignored due to area smaller than MIN_POLYGON_AREA" << endl;
			  }
			}
			offset += offsetStep; // Increase offset for next contour
			count++;
      } while (!curr_offset_polygons.empty() && count<=contours);
      
      if (count>=MAX_CONTOURS) {
	  cout << "inward_offset warning: max number of contours generated, aborting generation." << endl;
	  cout << "1) Verify points are given in CCW order for the outer boundary, and CW for holes." << endl;
	  cout << "2) Verify offset is not too small with respect to polygon size." << endl;
      }
	
	
      return outputCollection;
  
      // Alternative way
      
       // Instantiate the container of offset contours
      //std::vector< boost::shared_ptr< Polygon_2_EPICK > > offset_contours ;
      // Instantiate the offset builder with the skeleton
      //OffsetBuilder ob(*iss);
      // Obtain the offset contours
      //ob.construct_offset_contours(lOffset, std::back_inserter(offset_contours));
}



/**
 * Methods to produce inward offsets based on straight skeleton.
 * Input is a a list of points for a polygon with holes:
 * 	Array of Array of Point_2 (ruby)
 * 	The first array has polygons, the first position MUST have the points of the outer boundary, the rest, if any, the holes 
 * 
 * It returns the first #contours inwards offsets with a distance of @offsetStep (if contours=0, it returns them all)
 * Return type is Array of [Array of Polygon_2]
 * 
 */

Array inward_offset_polygon(Array polygon_points, double offsetStep, int contours){
  
  // Convert the points in polygon_points into a Polygon_with_holes_EPICK
  Array outputArray;
  if (polygon_points.size()>0) {
  
    // Outer face
    Array outerPoints = from_ruby<Array>(polygon_points[0]);
    Polygon_2_EPICK outerPolygon;
    Point_2 pt;
    for (unsigned int i = 0; i < outerPoints.size(); ++i){
	    pt = from_ruby<Point_2>(outerPoints[i]);
	    EPICK::Point_2 pE(CGAL::to_double(pt.x()), CGAL::to_double(pt.y()));
	    outerPolygon.push_back(pE);
    }
    
    Polygon_with_holes_EPICK finalPolygon (outerPolygon);
    
    // Holes
    for (unsigned int pol = 1; pol < polygon_points.size(); ++pol){
      Array currHolePoints = from_ruby<Array>(polygon_points[pol]);
      Polygon_2_EPICK holePolygon;
      Point_2 pt;
      for (unsigned int i = 0; i < currHolePoints.size(); ++i){
	      pt = from_ruby<Point_2>( currHolePoints[i] );
	      EPICK::Point_2 pE(CGAL::to_double(pt.x()), CGAL::to_double(pt.y()));
	      holePolygon.push_back(pE);
      }
      if (holePolygon.is_simple()) {
        finalPolygon.add_hole(holePolygon);
      }
    }
    if (outerPolygon.is_simple()) {
      outputArray = do_inward_offset_from_EPICK(finalPolygon, offsetStep, contours);
    }
    
  } else {
    
    cout << "inward_offset error: polygon_points empty" << endl;
    
  }
  return outputArray;

}

