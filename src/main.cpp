#include <iostream>
#include <iomanip>
#include "image.h"
#include "model.h"

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::left;

void default_implementation(Model current_model);
void evaluate(int matches);
void categorize_images(Model existing_model, std::vector<Image> file_images, std::vector<int> file_label);

const int no_of_digits = 10;

std::vector<Image> images;
std::vector<int> labels_from_file;
std::vector<std::vector<std::vector<double>>> file_table;
std::vector<std::vector<double>> confusion_matrix;
std::vector<int> label_count(no_of_digits);
std::vector<std::vector<Image>> classified;

long image_size = 0;

int main(int argc, char *argv[]) {
  string choice;

  Model model("../data/trainingimages", "../data/traininglabels");
  model.categorize_images();
  model.initial_digits();

  file_table.reserve(no_of_digits);
  for (int i = 0; i < no_of_digits; i++) {
    std::vector<std::vector<double>> double_vector(28);
    for (int j = 0; j < 28; j++) {
      std::vector<double> one_d(28);
      for (int k = 0; k < 28; k++) {
        one_d.push_back(0);
      }
      double_vector.push_back(one_d);
    }
    file_table.push_back(double_vector);
  }

  if (argc == 4) {

    images = model.read_file(argv[1]);
    labels_from_file = model.read_label(argv[2]);
    file_table = model.read_table(argv[3]);
    model.initialize_table(file_table);
    default_implementation(model);

  } else if (argc == 3) {
    images = model.read_file(argv[1]);
    labels_from_file = model.read_label(argv[2]);
    file_table = model.read_table("/Users/chinmaya/CLionProjects/naivebayes-chinmayasharma/data/data.txt");
    model.initialize_table(file_table);
    default_implementation(model);

  } else {

    do {
      cout << "Do you wish to run default? (yes/no)" << endl;
      cin >> choice;
    } while (choice != "yes" and choice != "no");

    if (choice == "yes") {
      default_implementation(model);

    } else {
      string file_path;
      cout << "Please enter file for images: ";
      cin >> file_path;
    }
    return 0;
  }
}

void evaluate(int matches) {
  double accuracy = (matches * 100) / image_size;
  std::cout << "\n\nAccuracy: " << accuracy << "%" << endl << "\n\n\t";

  for (int i = 0; i < no_of_digits; i++) {
    cout << setw(no_of_digits) << left << i;
  }
  cout << "\n\n";

  for (int i = 0; i < no_of_digits; i++) {
    cout << i << "\t";

    for (int j = 0; j < no_of_digits; j++) {
      cout << setw(no_of_digits) << left << (confusion_matrix[i][j] * 100) / label_count[i];
    }
    cout << endl;
  }
}

void default_implementation(Model current_model) {

  images = current_model.read_file("../data/testimages");
  labels_from_file = current_model.read_label("../data/testlabels");
  int matches = 0;
  image_size = images.size();
  confusion_matrix.reserve(no_of_digits);

  for (int row = 0; row < no_of_digits; row++) {
    std::vector<double> confusion_row;
    confusion_row.reserve(no_of_digits);

    for (int col = 0; col < no_of_digits; col++) {
      confusion_row.push_back(0);
    }
    confusion_matrix.push_back(confusion_row);
  }

  for (int i = 0; i < images.size(); i++) {
    int predicted = current_model.classify(images[i]);
    confusion_matrix[labels_from_file[i]][predicted]++;

    if (labels_from_file[i] == predicted) {
      matches++;
    }
    label_count[labels_from_file[i]]++;
  }
  categorize_images(current_model, images, labels_from_file);
  evaluate(matches);

  string choice;

  do {
    cout << "\n\nDo you wish to save model? (yes/no)" << endl;
    cin >> choice;
  } while (choice != "yes" and choice != "no");

  if (choice == "yes") {
    current_model.save_table();
  }
}

void categorize_images(Model existing_model, std::vector<Image> file_images, std::vector<int> file_label) {

  classified.reserve(no_of_digits);
  for (int i = 0; i < no_of_digits; i++) {
    std::vector<Image> image_vector;
    classified.push_back(image_vector);
  }
  for (int i = 0; i < file_label.size(); i++) {
    classified[file_label[i]].push_back(file_images[i]);
  }

  for (int i = 0; i < no_of_digits; i++) {
    existing_model.get_digits()[i].prototype_images(classified[i]);
  }
}

