#ifndef COMMON_TYPES_HPP
#define COMMON_TYPES_HPP

#include <opencv2/core/core.hpp>

#include <cstdint>
#include <vector>
#include <map>

namespace obz
{

typedef std::vector<cv::Point2f>  pts_vec_t;

struct object_t {
  cv::Rect bb;
  object_t(): bb(cv::Rect(0,0,0,0)) {;}
  object_t(const cv::Rect& bb): bb(bb) {;}
};

// Used for low-level roi extraction from feature points
struct roi_t
{
  // Pass all tests? Size, motion ...
  bool valid;

  double motion_per_pixel;

  // Members of the ROI in image frame
  pts_vec_t curr_pts;

  // The position of the members in prev frame
  pts_vec_t prev_pts;

  // The minimu axis-aligned bounding box for curr_pts
  cv::Rect bb;

  roi_t(): valid(false), motion_per_pixel(0.0) {}

  void reset()
  {
    valid = false;
    curr_pts.clear();
    prev_pts.clear();
    bb = cv::Rect(0, 0, 0, 0);
  }
};

// Label -> ROI
typedef std::pair<std::int32_t, roi_t> roi_pair_t;
typedef std::map<std::int32_t, roi_t> roi_map_t;

}  // namespace obz
#endif
