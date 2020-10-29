// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <vector>
#include <iostream>

#define L1DSIZE 98304
#define L2SIZE 1048576
#define L3SIZE 16777216

class Experiment
{
 public:
  Experiment(const std::vector<unsigned> &sizes);
  void set_buff_sizes(const std::vector<unsigned> &l_sizes);
  void run_experiment();
  void run_direct(unsigned size);
  void run_reverse(unsigned size);
  void run_random(unsigned size);
  void generate_buff(unsigned size);
  void warm_up();
  const std::vector<unsigned>& get_buff_sizes() const;
  bool is_power_of_two(unsigned number);
 private:
  std::vector<unsigned> buff_sizes;
  std::vector<int> buff;
};

#endif // INCLUDE_HEADER_HPP_
