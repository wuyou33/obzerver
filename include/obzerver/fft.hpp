#ifndef FFT_HPP
#define FFT_HPP

#include "opencv2/core/core.hpp"

namespace obz
{

bool CalcVecDFT(const cv::Mat& vec_m,
                std::vector<float>& fft_power,
                const cv::Mat& win_m,
                const unsigned int remove_count = 0,
                const bool verbose = false);

class Periodicity {
protected:
  std::size_t hist_len;
  float fps;
  std::vector<float> freqs;
  std::vector<float> fft_power;
  cv::Mat hann_window;
  std::size_t average_counter;

public:
  Periodicity(const std::size_t hist_len, const float fps);
  void Update(const std::vector<float>& vec,
              const bool average = false,
              const bool verbose = false)
  {
    Update(cv::Mat(vec, false).t(), average, verbose);
  }

  // row vector
  void Update(const cv::Mat& vec, const bool average = false, const bool verbose = false);

  // At least get rid of DC Term
  float GetDominantFrequency(const std::size_t start_index = 1) const;
  bool IsPeriodic() const ;
  const std::vector<float>& GetSpectrum() const {return fft_power;}
};

}  // namespace obz
#endif
