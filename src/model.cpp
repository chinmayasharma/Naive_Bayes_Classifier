#include "model.h"
#include "image.h"
#include "digit.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stoi;
using std::ifstream;
using std::getline;
using std::ofstream;
using std::istringstream;

std::vector<Digit> digits;
std::vector<Image> all_images;
std::vector<int> labels;
std::vector<std::vector<Image>> categorized_Images;

const int no_of_digits = 10;
static int line_number = 0;

Model::Model(string file_path, string label_path) {

  pixels.reserve(28);
  for (int row = 0; row < 28; row++) {
    std::vector<bool> pixel_row;
    pixel_row.reserve(28);

    for (int col = 0; col < 28; col++) {
      pixel_row.push_back(false);
    }
    pixels.push_back(pixel_row);
  }
  labels = read_label(label_path);
  all_images = read_file(file_path);
}

std::vector<int> Model::read_label(string label_path) {
  std::vector<int> local_labels;
  string digit_line;
  int digit;

  ifstream label_reader;
  label_reader.open(label_path);

  if (label_reader.is_open()) {

    while (getline(label_reader, digit_line)) {
      digit = stoi(digit_line);
      local_labels.push_back(digit);
    }
    label_reader.close();

  } else {
    cout << "Unable to open file";
  }
  return local_labels;
}

std::vector<Image> Model::read_file(string file_path) {

  std::vector<Image> local_images;

  string line;
  ifstream pixel_reader;
  pixel_reader.open(file_path);

  if (pixel_reader) {

    while (getline(pixel_reader, line)) {
      background_check(line, local_images);
      line_number++;
    }
    pixel_reader.close();

  } else {
    cout << "Unable to open file";
  }

  return local_images;
}

std::vector<std::vector<std::vector<double>>> Model::read_table(string table_path) {
  std::vector<string> string_table(28);
  std::vector<double> digit_table(28);
  std::vector<std::vector<double>> line_table;
  std::vector<std::vector<std::vector<double>>> complete_table;

  string table_line;
  ifstream table_reader;
  table_reader.open(table_path);

  if (table_reader.is_open()) {

    while (getline(table_reader, table_line)) {
      if (!table_line.empty()) {
        string_table = split(table_line, " ");

        for (const auto &i : string_table) {
          digit_table.push_back(stod(i));
        }
        line_table.push_back(digit_table);
      } else {
        complete_table.push_back(line_table);
      }
    }
    table_reader.close();

  } else {
    cout << "Unable to open file";
  }

  return complete_table;
}

void Model::background_check(string line, std::vector<Image> &images) {

  int element_count = 0;

  for (char c: line) {
    // checks if it's a background element
    {
      pixels[line_number][element_count] = (c != ' ');
      element_count++;
    }
  }

  if (line_number == 27) {
    Image image(pixels);
    images.push_back(image);
    line_number = -1;
  }
}

void Model::categorize_images() {

  categorized_Images.reserve(10);
  for (int i = 0; i < 10; i++) {
    std::vector<Image> image_vector;
    categorized_Images.push_back(image_vector);
  }
  for (int i = 0; i < labels.size(); i++) {
    categorized_Images[labels[i]].push_back(all_images[i]);
  }
}

void Model::initial_digits() {

  for (int i = 0; i < 10; i++) {
    Digit digit(i, categorized_Images[i]);
    digits.push_back(digit);
  }
}

int Model::classify(Image image) {
  double max = -1000;
  int index_of_max = 0;

  for (int i = 0; i < 10; i++) { ;

    if (digits[i].classify(image) > max) {
      max = digits[i].classify(image);
      index_of_max = i;
    }
  }
  return index_of_max;
}

void Model::save_table() {
  ofstream file_writer;
  file_writer.open("/Users/chinmaya/CLionProjects/naivebayes-chinmayasharma/data/data.txt");
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 28; j++) {
      for (int k = 0; k < 28; k++) {
        file_writer << digits[i].get_table()[j][k] << " ";
      }
      file_writer << endl;
    }
    file_writer << endl;
  }
  file_writer.close();
}

std::vector<Digit> Model::get_digits() {
  return digits;
}

std::vector<string> Model::split(string str, string sep) {
  char *cstr = const_cast<char *>(str.c_str());
  char *current;
  std::vector<std::string> arr;
  current = strtok(cstr, sep.c_str());

  while (current != NULL) {
    arr.push_back(current);
    current = strtok(NULL, sep.c_str());
  }
  return arr;
}

void Model::initialize_table(std::vector<std::vector<std::vector<double>>> probability_table) {
  for (int i = 0; i < no_of_digits; i++) {
    digits[i].set_table(probability_table[i]);
  }
}
