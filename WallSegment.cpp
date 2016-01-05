/**
 * @file WallSegment.cpp
 * @ingroup Map
 * @author Amaury Nègre, CNRS, Inria
 * @copyright All right reserved.
 */

#include "WallSegment.hpp"

using namespace cv;

/** @brief constructor.
 * @param p0 [in] first point of the segment.
 * @param p1 [in] second point of the segment.
 */ 
WallSegment::WallSegment( const cv::Vec2d& p0, const cv::Vec2d& p1)
  :p0(p0)
  ,p1(p1)
{
  Vec2d dx = p1-p0;
  length = norm(dx);
  d = dx / length;
  n = Vec2d(-dx[1], dx[0]);
}

/** @brief Copy constructor.
 * @param ws [in] Wall segment to copy.
 */
WallSegment::WallSegment( const WallSegment& ws)
  :p0(ws.p0)
  ,p1(ws.p1)
  ,d(ws.d)
  ,n(ws.n)
  ,length(ws.length)
{
}

/** @brief Check if a point than dmin distance from the segment. Return true if yes (dmin contains the new distance).
 *
 * @param p [in] input point.
 * @param dmin [in,out] actual distance of the previous nearest point. Would be modified if a nearest point is found.
 * @param np [in,out] actual nearest point distance. Would be modified if a new point is found
 * @return true e if p is nearer that dmin, update dmin and update nearest point.
 */
bool WallSegment::nearestPoint(const cv::Vec2d& p, double& dmin, cv::Vec2d& np) const
{
  Vec2d d0 = p-p0;
  double s = d0.dot(d);
  double dist;
  if(s<0)
  {
	dist = norm(d0);
	if(dist>=dmin)
	  return false;
	dmin = dist;
	np=p0;
  }else if(s>length)
  {
	Vec2d d1 = p-p1;
	dist = norm(d1);
	if(dist>=dmin)
	  return false;
	dmin = dist;
	np = p1;
  }else{
	// distance to line
	double r = d0.dot(n);
	double dl = fabs(r);
	
	if(dl >= dmin)
	  return false;
	dmin = dl;
	np = p0 + s*d;
  }
  return true;
}

/** @brief return the bouding box of the segment
 */
cv::Rect_<double> WallSegment::boundingBox() const
{
  return cv::Rect_<double> (p0, p1);
}
