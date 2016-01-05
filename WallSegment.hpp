/**
 * @file WallSegment.hpp
 * @ingroup Map
 * @author Amaury Nègre, CNRS, Inria
 * @copyright All right reserved.
 */

#ifndef WALL_SEGMENT_HPP
#define WALL_SEGMENT_HPP

#include <opencv2/opencv.hpp>

/**
 * @class WallSegment WallSegment.cpp WallSegment.hpp
 * @brief Class to segment walls of map
 *
 * @author Amaury Nègre, CNRS, Inria
 */
class WallSegment
{
public:
	/** @brief constructor.
	 * @param p0 [in] first point of the segment.
	 * @param p1 [in] second point of the segment.
	 */ 
	WallSegment( const cv::Vec2d& p0, const cv::Vec2d& p1);

	/** @brief Copy constructor.
	 * @param ws [in] Wall segment to copy.
	 */
	WallSegment( const WallSegment& ws);

  	/** @brief virtual destructor. Empty.
	 */
	virtual ~WallSegment() {}
  
	/** @brief Check if a point than dmin distance from the segment. Return true if yes (dmin contains the new distance).
	 *
	 * @param p [in] input point.
	 * @param dmin [in,out] actual distance of the previous nearest point. Would be modified if a nearest point is found.
	 * @param np [in,out] actual nearest point distance. Would be modified if a new point is found
	 * @return true e if p is nearer that dmin, update dmin and update nearest point.
	 */
	bool nearestPoint(const cv::Vec2d& p, double& dmin, cv::Vec2d& np) const;

	
  	/** @brief return the bouding box of the segment
	 */
	cv::Rect_<double> boundingBox() const ;

	cv::Vec2d p0, p1;	/*!< @brief first and second point of the segment */
	cv::Vec2d d, n;		/*!< @brief normalized vectors for the segment */
	double length;		/*!< @brief length of the segment */

};

#endif //WALL_SEGMENT_HPP
