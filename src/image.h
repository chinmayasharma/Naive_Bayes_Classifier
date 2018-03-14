#ifndef NAIVEBAYES_IMAGEDATA_H
#define NAIVEBAYES_IMAGEDATA_H

#include <string>
#include <vector>
using std::string;
class Image {
 private:
  std::vector<std::vector<bool>> pixels;
 public:
  explicit Image(std::vector<std::vector<bool>> pixels);
  std::vector<std::vector<bool> > &getPixels();
  void print_image();
};

#endif //NAIVEBAYES_IMAGEDATA_H
