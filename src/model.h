#ifndef NAIVEBAYES_TRAINING_H
#define NAIVEBAYES_TRAINING_H
#include "image.h"
#include "digit.h"
#include <string>
#include <vector>

class Model {
 private:
  std::vector<std::vector<bool>> pixels;

 public:
  Model(string file_path, string label_path);
  std::vector<int> read_label(string label_path);
  std::vector<std::vector<std::vector<double>>> read_table(string table_path);
  std::vector<Image> read_file(std::string file_path);
  void background_check(string line, std::vector<Image> &images);
  void categorize_images();
  void initial_digits();
  int most_probable_image(Image image);
  void save_table();
  std::vector<Digit> get_digits();
  std::vector<string> split(string str);
  void initialize_table(std::vector<std::vector<std::vector<double>>> probability_table);
};

#endif //NAIVEBAYES_TRAINING_H
