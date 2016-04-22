#include "frame.h"

namespace Common {

  Frame::Frame(Frame&& other)
    : features(move(other.features))
  {
  }

} // namespace FeatureExtraction
