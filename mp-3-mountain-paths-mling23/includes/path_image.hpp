#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>

#include "color.hpp"
#include "path.hpp"
#include<string>
#include "grayscale_image.hpp"
#include "elevation_dataset.hpp"

class PathImage {
public:
  // write behavior declarations here; define in path_image.cc.
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color>>& GetPathImage() const;
  void ToPpm(const std::string& name) const;

private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  size_t best_path_row_ = 0;
  static const int kGreenR = 31;
  static const int kGreenG = 253;
  static const int kGreenB = 13;
  static const int kRedR = 252;
  static const int kRedG = 25;
  static const int kRedB = 63;
  Color Green_ = Color(kGreenR,kGreenG,kGreenB);
  Color Red_ = Color(kRedR, kRedG, kRedB);
};

#endif