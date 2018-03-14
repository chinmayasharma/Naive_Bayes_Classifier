#include "digit.h"
#include "image.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stoi;
using std::vector;
using std::ifstream;
using std::getline;
using std::istringstream;

const double k = 0.1;

/**
 *
 * @param digit_label label for digit
 * @param digit_images images corresponding to digit
 */
Digit::Digit(int digit_label, std::vector<Image> digit_images) {
  label = digit_label;
  images = std::move(digit_images);
  table.reserve(28);

  for (int row = 0; row < 28; row++) {
    std::vector<double> table_row;
    table_row.reserve(28);
    for (int col = 0; col < 28; col++) {
      table_row.push_back(0);
    }
    table.push_back(table_row);
  }

  probability_count();
}

/**
 *
 * @param image boolean 2-D vector to be evaluated
 */
void Digit::occurrence_count(Image image) {

  for (int i = 0; i < image.getPixels().size(); i++) {

    for (int j = 0; j < image.getPixels()[i].size(); j++) {

      if (image.getPixels()[i][j]) {
        table[i][j]++;
      }
    }
  }

}

/**
 *  Goes through all images and calculated probability of every pixel for a given digit
 */
void Digit::probability_count() {

  for (const Image &image: images) {
    occurrence_count(image);
  }

  for (auto &i : table) {

    for (double &j : i) {
      j = (j + k) / (images.size() + (2 * k));
    }
  }
}

int Digit::get_label() {
  return label;
}

/**
 *
 * @return table of probabilities
 */
std::vector<std::vector<double>> Digit::get_table() {
  return table;
}

/**
 *
 * @param set_table vector to set probabilities values to
 */
void Digit::set_table(std::vector<std::vector<double >> set_table) {
  table = move(set_table);
}

/**
 *
 * @param image image to be classified
 * @return label with highest probability
 */
double Digit::classify(Image image) {
  double total = log(images.size() / 5000.0);

  for (int i = 0; i < image.getPixels().size(); i++) {

    for (int j = 0; j < image.getPixels()[i].size(); j++) {

      if (image.getPixels()[i][j]) {
        total += log(table[i][j]);

      } else {
        total += log(1 - table[i][j]);
      }
    }
  }
  return total;
}

/**
 *
 * @param images_of_digit vector of images for the digit
 */
void Digit::prototype_images(std::vector<Image> images_of_digit) {

  double min_value = 1000;
  double max_value = -1000;
  int min_index = -1;
  int max_index = -1;

  for (int i = 0; i < images_of_digit.size(); i++) {
    double temp = 0;
    temp = classify(images_of_digit[i]);

    if (temp > max_value) {
      max_value = temp;
      max_index = i;
    }

    if (temp < min_value) {
      min_value = temp;
      min_index = i;
    }
  }

  cout << "Best Image Prototype of: " << label << endl;
  images_of_digit[max_index].print_image();

  cout << "Worst Image Prototype of: " << label << endl;
  images_of_digit[min_index].print_image();
}