#include "path_image.hpp"
#include <fstream>
#include <iostream>
void OptimalDirectionNormal(const ElevationDataset& dataset, size_t& height, size_t width, Path& path) {
  int current = dataset.DatumAt(height, width);
 
    int north_east = std::abs(dataset.DatumAt(height - 1, width + 1) - current);
    int east = std::abs(dataset.DatumAt(height, width + 1) - current);
    int south_east = std::abs(dataset.DatumAt(height + 1, width + 1) - current);
    if (north_east < east && north_east < south_east) {  // north_east is best option
      height--;
      path.IncEleChange(north_east);
    } else if (south_east < east && south_east <= north_east) {  // south_east is best option
      height++;
      path.IncEleChange(south_east);
    } else if (east <= south_east && east <= north_east) {  // east is best option, or is tied with one of the others
      path.IncEleChange(east);
    } 
  }
  void OptimalDirectionTop(const ElevationDataset& dataset, size_t& height, size_t width, Path& path) {
    int current = dataset.DatumAt(height, width);
    int east = std::abs(dataset.DatumAt(height, width + 1) - current);
    int south_east = std::abs(dataset.DatumAt(height + 1, width + 1) - current);
    if (east > south_east) {  // moving east not good
      height++;                    // want to decrease elevation
      path.IncEleChange(south_east);
    } else {  // east was better or tie 
      path.IncEleChange(east);
    }
  }
  void OptimalDirectionBot( const ElevationDataset& dataset,size_t& height, size_t width, Path& path) {
    int current = dataset.DatumAt(height, width);
    int north_east = std::abs(dataset.DatumAt(height - 1, width + 1) - current);
    int east = std::abs(dataset.DatumAt(height, width + 1) - current);
    if (east > north_east) {  // moving east not good
      height--;                    // increasing elevation
      path.IncEleChange(north_east);
    } else {  // moving east was better or tie 
      path.IncEleChange(east);
    }
  }
  void FillPathImage(size_t best_row, std::vector<Path> paths, size_t width, std::vector<std::vector<Color>>& path_image, Color best_path, Color other_path) {
    for (size_t i = 0; i < paths.size(); i++) {  // iterating through paths
      Path path = paths.at(i);                // path at index i
      if (i != best_row) {               // other rows
        Color color = other_path;      // red color
        for (size_t w = 0; w < width; w++) {     // iterate through the paths path
          size_t row = path.GetPath().at(w);   // row it was at for each step
          path_image.at(row).at(w) = color;          // fill data with the color
        }
      } 
      }
      Path best = paths.at(best_row); //need to layer the green path last so its over the red ones
      Color color = best_path;             // green
      for (size_t w = 0; w < width; w++) {  // iterate through the paths path
      size_t row = best.GetPath().at(w);    // row it was at for each step
      path_image.at(row).at(w) = color;
      }
  }

  PathImage::PathImage(const GrayscaleImage& image, const ElevationDataset& dataset) {
    height_ = image.Height();
    width_ = image.Width();
    unsigned int min_elevation = 0;
    for (size_t h = 0; h < height_; h++) {  // creating paths
      Path path = Path(width_, h);       // creating path, starting with each row
      size_t index = h;                    // used to keep track of index
      size_t w = 0;                        //width, starts at first column
      path.SetLoc(w, h); //setting initial starting location wth index is h
      while (w < width_ - 1) {  // not at eastmost column yet
        if (h == 0) {  // at top of map
          OptimalDirectionTop(dataset, h, w, path);
        } else if (h == height_ - 1) {  // at bottom
          OptimalDirectionBot(dataset, h, w, path);
        } else {  // normal case
          OptimalDirectionNormal(dataset, h, w, path);
        }
        //height has now been updated
        w++;  // moving on to next column
        path.SetLoc(w, h);
      }
      paths_.push_back(path);  // adding path to paths
      h = index;  // need to restart h back to what it was originally
      if (h == 0) { //initialize min path to first one
        min_elevation = path.EleChange(); 
      } 
      if (path.EleChange() < min_elevation) { //found a strictly better path, if tied, keep the lower one 
        min_elevation = path.EleChange();
        best_path_row_ = h;
    } 
    }
    path_image_ = image.GetImage(); //set to grayscale image first
    FillPathImage(best_path_row_, paths_, width_, path_image_, Green_, Red_);  //layer the paths on top of image
  }
size_t PathImage::Width() const { return width_; }
size_t PathImage::Height() const { return height_; }
unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }
const std::vector<Path>& PathImage::Paths() const { return paths_; }
const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}
void PathImage::ToPpm(const std::string& name) const { 
  std::ofstream ofs{name};
  ofs << "P3" << std::endl;
  ofs << width_ << " " << height_ << std::endl;
  ofs << kMaxColorValue << std::endl;
  //now writing to the file
  for (size_t h = 0; h < height_; h++) {
    for (size_t w = 0; w < width_; w++) {
      Color color = path_image_.at(h).at(w);
      ofs << color.Red() << " " << color.Green() << " "
          << color.Blue() << " ";
    }
    ofs << std::endl;
    }
  }
