// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "experiment.hpp"
#include <iostream>

TEST (Example, EmptyTest)
{
  std::vector<unsigned> l_sizes;
  l_sizes.push_back(L1DSIZE);
  l_sizes.push_back(L2SIZE);
  l_sizes.push_back(L3SIZE);
  Experiment first (l_sizes);
  auto& tmp = first.get_buff_sizes();
  for (unsigned i=0; i<tmp.size(); i++)
  {
    std::cout << tmp.at(i) << std::endl;
  }
  std::cout << "End of first test" << std::endl;
  EXPECT_TRUE(true);
}
/*
TEST (Example, power_of_two_test)
{
  std::vector<unsigned> l_sizes;
  l_sizes.push_back(96);
  l_sizes.push_back(1024);
  l_sizes.push_back(1024*16);
  Experiment second (l_sizes);
  auto& tmp = second.get_buff_sizes();
  for (unsigned i=0; i < tmp.size(); i++)
  {
    std::cout << tmp.at(i) << " is "
              << second.is_power_of_two(tmp.at(i)) << std::endl;
  }
  EXPECT_TRUE(true);
}*/

TEST (Example, First_run)
{
  std::vector<unsigned> l_sizes;
  l_sizes.push_back(L1DSIZE);
  l_sizes.push_back(L2SIZE);
  l_sizes.push_back(L3SIZE);
  Experiment third (l_sizes);
  third.run_experiment();
  std::cout << std::endl << std::endl << std::endl << std::endl;
  std::cout << third.get_report().str();
  EXPECT_TRUE(true);
}
