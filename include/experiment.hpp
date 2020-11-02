// Copyright 2020 NickBBn <nickgeo.winner@gmail.com>

#ifndef INCLUDE_EXPERIMENT_HPP_
#define INCLUDE_EXPERIMENT_HPP_
#include <vector>
#include <iostream>
#include <sstream>
#include <chrono>

#define L1DSIZE 98304
#define L2SIZE 1048576
#define L3SIZE 16777216

class Experiment
{
 public:
  explicit Experiment(const std::vector<unsigned> &sizes);
  void set_buff_sizes(const std::vector<unsigned> &l_sizes);
  void run_experiment();
  void run_direct(unsigned byte_size);
  void run_reverse(unsigned byte_size);
  void run_random(unsigned byte_size);
  void generate_buff(unsigned int_size);
  void warm_up(unsigned byte_size);
  const std::vector<unsigned>& get_buff_sizes() const;
  bool is_power_of_two(unsigned number);
  void print_to_report (unsigned byte_size, double time);
  const std::ostringstream& get_report() const;
 private:
  std::vector<unsigned> buff_byte_sizes;
  std::vector<int> buff;
  std::ostringstream report;
  unsigned cur_experiment_number;
};

#endif // INCLUDE_EXPERIMENT_HPP_
