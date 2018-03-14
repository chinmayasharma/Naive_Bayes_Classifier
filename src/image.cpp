#include "image.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stoi;
using std::vector;
using std::ifstream;
using std::getline;
using std::istringstream;

/**
 * Constructor for image.
 * @param pixels_ setting value of 2-D array pixels
 */
Image::Image(std::vector<std::vector<bool>> pixels_) {
  pixels = move(pixels_);
}

/**
 *
 * @return 2-D vector of pixels
 */
std::vector<std::vector<bool> > &Image::getPixels() {
  return pixels;
}

/**
 * prints images with stars and spaces
 */
void Image::print_image() {
  for (int i = 0; i < 28; i++) {
    for (int j = 0; j < 28; j++) {
      if (pixels[i][j]) {
        cout << "*";
      } else {
        cout << " ";
      }
    }
    cout << endl;
  }
}