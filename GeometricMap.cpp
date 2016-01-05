/**
 * @file GeometricMap.cpp
 * @ingroup Map
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @author Amaury Nègre, CNRS, Inria
 * @copyright All right reserved.
 */

#include "GeometricMap.hpp"

#include <fstream>
#include <iostream>

using namespace std;

/** @brief constructor.
 */ 
GeometricMap::GeometricMap()
{
}

/** @brief Copy constructor.
 */
GeometricMap::GeometricMap(const GeometricMap& gm)
  : segments(gm.segments)
{
}


/** @brief Load a map from a text file.
 *
 * @param filename [in] input file name
 * @return true if the file has been found and parsed.
 */	
bool GeometricMap::loadMap(const char* filename)
{
  char Line[10*1024];

  FILE * f = fopen( filename, "rb" );

  if(f == (FILE*)nullptr)
	return false;

  // Empty current map before loading new segments (Doms)
  segments.clear();

  while( fgets( Line, 10*1024, f ) != nullptr )
  {
	double x0, y0, x1, y1;
	if ( sscanf( Line, "%lf %lf %lf %lf", &x0, &y0, &x1, &y1 ) == 4 )
	{
		segments.push_back(WallSegment(cv::Vec2d(x0, y0),
								   cv::Vec2d(x1, y1)));
	}
  }

  fclose( f );

  cerr << segments.size() << " segments loaded" << endl;

  computeBoundingBox();
  
  cerr << "bounding Box : "
	   << boundingBox.tl().x << " "
	   << boundingBox.tl().y << " "
	   << boundingBox.br().x << " "
	   << boundingBox.br().y << endl;
  
  return true;
}

/** @brief Compute bounding box of the map.
 */	
void GeometricMap::computeBoundingBox()
{
  if(segments.empty())
  {
	boundingBox = cv::Rect_<double>(0.,0., 0., 0.);
	return;
  }
  
  boundingBox = segments[0].boundingBox();
  
  for(SegmentVector::const_iterator it=++segments.begin();
	  it!=segments.end();
	  ++it)
  {
	boundingBox |= it->boundingBox();
  }
}

/** @brief Search for a point on the map nearer than dmin distance. Return true if such a point is found.
 *
 * @param p [in] input point.
 * @param dmin [in,out] actual distance of the previous nearest point. Would be modified if a nearest point is found.
 * @param np [in,out] actual nearest point distance. Would be modified if a new point is found
 * @return true if a new point has been found.
 */
bool GeometricMap::nearestPoint(const cv::Vec2d& p, double& dmin, cv::Vec2d& np) const
{
  bool res = false;
  for(SegmentVector::const_iterator it=segments.begin();
	  it!=segments.end();
	  ++it)
  {
	res |= it->nearestPoint(p, dmin, np);
  }
  return res;
}