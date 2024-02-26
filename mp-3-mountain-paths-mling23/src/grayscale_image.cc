#include "grayscale_image.hpp"
#include <cmath>
#include <iostream>
#include <fstream>
GrayscaleImage::GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();
  int max_ele = dataset.MaxEle();
  int min_ele = dataset.MinEle();
  image_ = std::vector<std::vector<Color>>(height_, std::vector<Color>(width_));
  if (max_ele == min_ele) { //max == min, makes whole thing grey 
    int pixel_value = 0;
    Color color = Color(pixel_value, pixel_value, pixel_value);  // creating color
    for (size_t h = 0; h < height_; h++) {
      for (size_t w = 0; w < width_; w++) {  // iterating through all parts of dataset
        image_.at(h).at(w) = color;             // assigning color
      }
    }
  } else {
    for (size_t h = 0; h < height_; h++) { //max != min
      for (size_t w = 0; w < width_;w++) {  // iterating through all parts of dataset
        int elevation_point = dataset.DatumAt(h, w);  // finding elevation at point
        double pixel_value = 0;
        if (max_ele != min_ele) {
          pixel_value = std::round(((double)(elevation_point - min_ele) / (double)(max_ele - min_ele)) * kMaxColorValue);
        }
        Color color = Color((int)pixel_value, (int)pixel_value, (int)pixel_value);  // creating color
        image_.at(h).at(w) = color;             // assigning color
      }
    }
  }  
}
GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) {
  ElevationDataset dataset = ElevationDataset(filename, width, height); //creating new dataset then same as previous
  width_ = dataset.Width();
  height_ = dataset.Height();
  int max_ele = dataset.MaxEle();
  int min_ele = dataset.MinEle();
  image_ = std::vector<std::vector<Color>>(height_, std::vector<Color>(width_));
  if (max_ele == min_ele) {  // max == min, makes whole thing grey
    int pixel_value = 0;
    Color color =
        Color(pixel_value, pixel_value, pixel_value);  // creating color
    for (size_t h = 0; h < height_; h++) {
      for (size_t w = 0; w < width_;
           w++) {                    // iterating through all parts of dataset
        image_.at(h).at(w) = color;  // assigning color
      }
    }
  } else {
    for (size_t h = 0; h < height_; h++) {  // max != min
      for (size_t w = 0; w < width_;
           w++) {  // iterating through all parts of dataset
        int elevation_point =
            dataset.DatumAt(h, w);  // finding elevation at point
        double pixel_value = 0;
        if (max_ele != min_ele) {
          pixel_value = std::round(((double)(elevation_point - min_ele) /
                                    (double)(max_ele - min_ele)) *
                                   kMaxColorValue);
        }
        Color color = Color((int)pixel_value,
                            (int)pixel_value,
                            (int)pixel_value);  // creating color
        image_.at(h).at(w) = color;             // assigning color
      }
    }
  }
}
size_t GrayscaleImage::Width() const { return width_; }
size_t GrayscaleImage::Height() const { return height_; }
unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }
const Color& GrayscaleImage::ColorAt(int row, int col) const { return image_.at(row).at(col); }
const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}
void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs{name};
  ofs << "P3" << std::endl;
  ofs << width_ << " " << height_ << std::endl;
  ofs << kMaxColorValue << std::endl;
  for (size_t h = 0; h < height_; h++) {
    for (size_t w = 0; w < width_; w++) {
      ofs << ColorAt((int)h, (int)w).Red() << " " << ColorAt((int)h, (int)w).Green() << " " << ColorAt((int)h, (int)w).Blue() << " ";
    }
    ofs << std::endl;
  }
}