#ifndef NAIVEBAYES_PROBABILITES_H
#define NAIVEBAYES_PROBABILITES_H
#include "image.h"
class Digit {
 private:
  int label;
  std::vector<Image> images;
  std::vector<std::vector<double>> table;

 public:
  Digit(int digit_label, std::vector<Image> digit_images);
  void probability_count();
  void occurrence_count(Image image);
  int get_label();
  std::vector<std::vector<double>> get_table();
  void set_table(std::vector<std::vector<double >> set_table);
  double classify(Image image);
  void prototype_images(std::vector<Image> images_of_digit);
};
#endif //NAIVEBAYES_PROBABILITES_H
