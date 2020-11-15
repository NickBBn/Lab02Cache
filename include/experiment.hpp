// Copyright 2020 NickBBn <nickgeo.winner@gmail.com>

#ifndef INCLUDE_EXPERIMENT_HPP_
#define INCLUDE_EXPERIMENT_HPP_
#include <vector>
#include <iostream>
#include <sstream>
#include <chrono>
#include <random>

//#define L1DSIZE 98304
//#define L2SIZE 1048576
//#define L3SIZE 16777216

class Experiment
{
 public:
  explicit Experiment(const std::vector<unsigned> &sizes);
  void run_experiment();
  const std::ostringstream& get_report() const;
 private:
  void set_buff_sizes(const std::vector<unsigned> &l_sizes);
  void run_direct(const unsigned& byte_size);
  void run_reverse(const unsigned& byte_size);
  void run_random(const unsigned& byte_size);
  void generate_buff(const unsigned& int_size);
  void warm_up(const unsigned& byte_size);
  const std::vector<unsigned>& get_buff_sizes() const;
  bool is_power_of_two(const unsigned& number);
  void print_to_report(const unsigned& byte_size, double time);
 private:
  std::vector<unsigned> buff_byte_sizes;
  std::vector<int> buff;
  std::ostringstream report;
  unsigned cur_experiment_number;
  std::mt19937 engine;
  std::random_device rd;
};

#endif // INCLUDE_EXPERIMENT_HPP_
