// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "experiment.hpp"
#include <iostream>

const int L1d_size (98304);
const int L2_size (1048576);
const int L3_size (16777216);

TEST(Example, First_run)
{
  std::vector<unsigned> l_sizes;
  l_sizes.push_back(L1d_size);
  l_sizes.push_back(L2_size);
  l_sizes.push_back(L3_size);
  Experiment third(l_sizes);
  third.run_experiment();
  std::cout << std::endl << std::endl << std::endl << std::endl;
  std::cout << third.get_report().str();
  EXPECT_TRUE(true);
}
