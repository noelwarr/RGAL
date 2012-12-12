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
 * It returns all inwads offsets with a distance of @offsetStep 
 * 
 * Return type is Array of [Array of Polygon_2 (EPECK)]
 */


Array do_inward_offset_from_EPICK(Polygon_with_holes_EPICK poly, double offsetStep){
    
      double MAX_COUNTOURS = 100; //Limit variable in case something goes wrong
      double MIN_POLYGON_AREA = 0.00001; // Minimum area to consider an offset polygon
      
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
	    offset_collection.push_back(curr_offset_polygons);
	    Array newArray(currentOffsetPolygons);
	    outputCollection.push(newArray);
	  } else {
	    cout << "inward_offset warning: offset ignored due to area smaller than MIN_POLYGON_AREA" << endl;
	  }
	}
	offset += offsetStep; // Increase offset for next contour
	count++;
      } while (!curr_offset_polygons.empty() && count<MAX_COUNTOURS);
      
      if (count==MAX_COUNTOURS) {
	  cout << "inward_offset error: max number of contours generated, aborting generation." << endl;
	  cout << "Verify points are given in CCW order for the outer boundary, and CW for holes." << endl;
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
 * It returns all inwads offsets with a distance of @offsetStep 
 * Return type is Array of [Array of Polygon_2]
 * 
 */

Array inward_offset_polygon(Array polygon_points, double offsetStep){
  
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
      for (unsigned int i = 0; i < outerPoints.size(); ++i){
	      pt = from_ruby<Point_2>( currHolePoints[i] );
	      EPICK::Point_2 pE(CGAL::to_double(pt.x()), CGAL::to_double(pt.y()));
	      holePolygon.push_back(pE);
      }
      finalPolygon.add_hole(holePolygon);
    }
    
    outputArray = do_inward_offset_from_EPICK(finalPolygon,offsetStep); 
    
  } else {
    
    cout << "inward_offset error: polygon_points empty" << endl;
    
  }
  return outputArray;

}

