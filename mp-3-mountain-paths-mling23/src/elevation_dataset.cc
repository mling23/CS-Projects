#include "elevation_dataset.hpp"
#include <fstream>
#include <iostream>

ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height) {
  width_ = width;
  height_ = height;
  data_ = std::vector<std::vector<int>>(height, std::vector<int>(width, 0)); //initializing size
  size_t check_elements = width * height;
  size_t count = 0;
  std::ifstream ifs{filename};  // binding stream
  int value = 0; //initializing values
  int min = 0;
  int max = 0;
  for (size_t h = 0; h < height; h++) {
    for (size_t w = 0; w < width; w++) {
      ifs >> value;
      if (ifs.fail()) {
        throw std::runtime_error("formatting error");
      } 
      count++;
      data_.at(h).at(w) = value;  // assigning value
      if (h == 0 && w == 0) {     // first value to init min and max
        min = value;
        max = value;
      }
      else if (value > max) {  // new max found
        max = value;
      }
      else if (value < min) {  // new min found
        min = value;
      }
    }
  }
  if (count != check_elements) {//not enough elements 
    throw std::invalid_argument("invalid data size");
  }
  ifs.ignore(1, '\n');
  ifs >> value; //looking ahead to future values
  if (ifs.good()) { //should reach end of file
    throw std::invalid_argument("too many elements"); //if good, then too many elements 
  }
  min_ele_ = min; //assigning global min and max
  max_ele_ = max;
}
size_t ElevationDataset::Width() const { return width_; }
size_t ElevationDataset::Height() const { return height_; }
int ElevationDataset::MaxEle() const { return max_ele_; }
int ElevationDataset::MinEle() const { return min_ele_; }
int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_.at(row).at(col);
}
const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}