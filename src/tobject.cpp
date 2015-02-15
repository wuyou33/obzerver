#include "obzerver/tobject.hpp"
#include "glog/logging.h"

namespace obz
{

TObject::TObject(const std::size_t hist_len, const float fps)
  :
    hist_len(hist_len),
    fps(fps),
    obj_hist(hist_len),
    self_similarity(hist_len, false), // TODO
    periodicity(hist_len, fps)
{
  ;
}

void TObject::Reset() {
  obj_hist.clear();
  self_similarity.Reset();
}

void TObject::Update(const object_t &obj,
                     const cv::Mat &frame,
                     const bool calc_self_similarity,
                     const bool reset) {
  if (reset) Reset();
  LOG(INFO) << "[TObj] Updating with: " << obj.bb << " | Reset: " << reset;
  obj_hist.push_front(obj);

  // Only calculate the self similarity matrix when:
  // 1) The caller explicitly asked us to
  self_similarity.Update(frame(obj.bb).clone());
  if (self_similarity.IsFull()) {
    for (int i = 0; i < self_similarity.GetSimMatrix().cols; i+=1) {
      // First time, reset the spectrum, then add up the power
      periodicity.Update(self_similarity.GetSimMatrix().row(i), i != 0, false);
    }
    LOG(INFO) << "Avg Spectrum: " << cv::Mat(periodicity.GetSpectrum(), false).t();
  }
}

void TObject::Update(const cv::Rect &bb,
                     const cv::Mat &frame,
                     const bool calc_self_similarity,
                     const bool reset) {
  object_t obj(bb);
  Update(obj, frame, calc_self_similarity, reset);
}

}  // namespace obz
