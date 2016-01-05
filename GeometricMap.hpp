/**
 * @file GeometricMap.hpp
 * @ingroup Map
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @author Amaury Nègre, CNRS, Inria
 * @copyright All right reserved.
 */

#ifndef GEOMETRIC_MAP_HPP
#define GEOMETRIC_MAP_HPP

#include <vector>
#include "WallSegment.hpp"

/**
 * @class GeometricMap GeometricMap.cpp GeometricMap.hpp
 * @brief Class to manage map built from segments
 *
 * @author Dominique Vaufreydaz, Grenoble Alpes University, Inria
 * @author Amaury Nègre, CNRS, Inria
 */
class GeometricMap
{
public:
	/** @brief constructor.
	 */ 
	GeometricMap();

	/** @brief Copy constructor.
	 */
	GeometricMap(const GeometricMap& gm);

	/** @brief virtual destructor. Empty.
	 */
	virtual ~GeometricMap() {}
	
  	/** @brief Load a map from a text file.
	 *
	 * @param filename [in] input file name
	 * @return true if the file has been found and parsed.
	 */	
	bool loadMap(const char* filename);

	/** @brief Compute bounding box of the map.
	 */	
	void computeBoundingBox();

  	/** @brief Search for a point on the map nearer than dmin distance. Return true if such a point is found.
	 *
	 * @param p [in] input point.
	 * @param dmin [in,out] actual distance of the previous nearest point. Would be modified if a nearest point is found.
	 * @param np [in,out] actual nearest point distance. Would be modified if a new point is found
	 * @return true if a new point has been found.
	 */
	bool nearestPoint(const cv::Vec2d& p, double& dmin, cv::Vec2d& np) const;


	typedef std::vector<WallSegment> SegmentVector;			/*!< @brief type of vector containing map segments. */
    SegmentVector segments;									/*!< @brief Actual vector containing map segments. */
	cv::Rect_<double> boundingBox;							/*!< @brief Bouding box values. Only valid after a call to computeBoundingBox(). */
};

#endif // GEOMETRIC_MAP_HPP
