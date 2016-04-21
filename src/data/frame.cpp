#include "frame.h"

namespace FeatureExtraction {

  Frame::Frame(Frame&& other)
    : features(move(other.features))
  {
  }

} // namespace FeatureExtraction
