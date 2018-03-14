#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/image.h"
#include "../src/model.h"

/**
 * **************************************************************************************************************
 * File Reading Tests
 * **************************************************************************************************************
 */
TEST_CASE("invalid_read_label_size_test") {
  Model model("../data/trainingimages", "../data/traininglabels");

  REQUIRE (5000 != model.read_label("../data/testlabels").size());
}

TEST_CASE("valid_read_label_size_test") {
  Model model("../data/trainingimages", "../data/traininglabels");

  REQUIRE (1000 == model.read_label("../data/testlabels").size());
}

TEST_CASE("invalid_read_label_first_content_test") {
  Model model("../data/trainingimages", "../data/testlabels");

  REQUIRE (5 != model.read_label("../data/testlabels")[0]);
}

TEST_CASE("valid_read_label_first_content_test") {
  Model model("../data/trainingimages", "../data/testlabels");

  REQUIRE (9 == model.read_label("../data/testlabels")[0]);
}

TEST_CASE("invalid_read_label_last_content_test") {
  Model model("../data/trainingimages", "../data/testlabels");

  REQUIRE (2 != model.read_label("../data/testlabels")[999]);
}

TEST_CASE("valid_read_label_last_content_test") {
  Model model("../data/trainingimages", "../data/testlabels");

  REQUIRE (5 == model.read_label("../data/testlabels")[999]);
}

TEST_CASE("invalid_name") {
  Model model("../data/trainingimages", "../data/testlabels");

  REQUIRE (5 == model.read_label("../data/testlabels")[999]);
}



/**
* **************************************************************************************************************
* Digit Tests
* **************************************************************************************************************
*/

TEST_CASE("invalid_label_test") {
  Model model("../data/trainingimages", "../data/traininglabels");
  model.categorize_images();
  model.initial_digits();

  REQUIRE (1 != model.get_digits()[0].get_label());
}

TEST_CASE("valid_label_test") {
  Model model("../data/trainingimages", "../data/traininglabels");
  model.categorize_images();
  model.initial_digits();

  REQUIRE (0 == model.get_digits()[0].get_label());
}


/**
* **************************************************************************************************************
* Probability Tests
* **************************************************************************************************************
*/

TEST_CASE("invalid_digit_probability_size_test") {
  Model model("../data/trainingimages", "../data/traininglabels");
  model.categorize_images();
  model.initial_digits();

  REQUIRE (10 != model.get_digits()[0].get_table().size());
}

TEST_CASE("valid_digit_probability_size_test") {
  Model model("../data/trainingimages", "../data/traininglabels");
  model.categorize_images();
  model.initial_digits();

  REQUIRE (28 == model.get_digits()[0].get_table().size());
}

TEST_CASE("invalid_digit_probability_zero_test") {
  Model model("../data/trainingimages", "../data/traininglabels");
  model.categorize_images();
  model.initial_digits();

  REQUIRE (0.000208681 - model.get_digits()[0].get_table()[0][0] != 0);
}

TEST_CASE("valid_digit_probability_zero_test") {
  Model model("../data/trainingimages", "../data/traininglabels");
  model.categorize_images();
  model.initial_digits();

  REQUIRE (0.0002087 - model.get_digits()[0].get_table()[0][0] < 0.00001);
}

TEST_CASE("invalid_digit_probability_nine_test") {
  Model model("../data/trainingimages", "../data/traininglabels");
  model.categorize_images();
  model.initial_digits();

  REQUIRE (0.000201939 - model.get_digits()[9].get_table()[27][27] != 0);
}

TEST_CASE("valid_digit_probability_nine_test") {
  Model model("../data/trainingimages", "../data/traininglabels");
  model.categorize_images();
  model.initial_digits();

  REQUIRE (0.000201939 - model.get_digits()[9].get_table()[27][27] < 0.00001);
}

/**
* **************************************************************************************************************
* Matches Tests
* **************************************************************************************************************
*/

TEST_CASE("invalid_matches") {
  Model model("../data/trainingimages", "../data/traininglabels");
  model.categorize_images();
  model.initial_digits();

  REQUIRE (0.000201939 - model.get_digits()[9].get_table()[27][27] < 0.00001);
}
