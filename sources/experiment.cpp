// Copyright 2018 Your Name <your_email>

#include <experiment.hpp>
#include <iostream>
#include <chrono>
#include <random>

std::mt19937 engine;
std::random_device rd;

Experiment::Experiment(const std::vector<unsigned int> &l_sizes)
    :
      buff_byte_sizes(0),
      buff(0),
      report("eee.txt"),
      cur_experiment_number(0)
{
  engine.seed(static_cast<unsigned>(std::time(nullptr)));
  set_buff_sizes(l_sizes);
}

void Experiment::set_buff_sizes(const std::vector<unsigned int> &l_sizes)
{
  std::vector<unsigned> tmp;
  unsigned cur_number;
  if (!is_power_of_two(l_sizes.at(0)))
  {
    cur_number = 2;
    while (cur_number < l_sizes.at(0)/2) {
      cur_number*=2;
    }
    tmp.push_back(l_sizes.at(0)/2);
  }
  else
  {
    cur_number = l_sizes.at(0)/2;
  }
  for (unsigned i = 0; i < l_sizes.size(); i++)
  {
    while (cur_number < l_sizes.at(i))
    {
      tmp.push_back(cur_number);
      cur_number*=2;
    }
    if (cur_number != l_sizes.at(i)) tmp.push_back(l_sizes.at(i));
  }
  tmp.push_back(l_sizes.at(2));
  tmp.push_back(l_sizes.at(2)*3/2);
 // tmp.erase(tmp.begin());// #TODO fix!!!
 // tmp.erase(tmp.begin());// #TODO fix!!!
  buff_byte_sizes = tmp;
}

const std::vector<unsigned> &Experiment::get_buff_sizes() const {
  return buff_byte_sizes;
}

void Experiment::run_experiment()
{
  srand(static_cast<unsigned int>(time(0)));
  report << "investigation: " << "\n"
         << "  travel variant: \"random\"" << std::endl
         << "  experiments:" << std::endl;
  for (unsigned i=0; i<buff_byte_sizes.size(); i++){
    cur_experiment_number++;
    run_random(buff_byte_sizes.at(i));
  }
  std::cout << std::endl;
  report << "investigation: " << std::endl
         << "  travel variant: \"reverse\"" << std::endl;
  for (unsigned i=0; i<buff_byte_sizes.size(); i++){
    cur_experiment_number++;
    run_reverse(buff_byte_sizes.at(i));
  }
  std::cout << std::endl;
  report << "investigation: " << std::endl
         << "  travel variant: \"direct\"" << std::endl;
  for (unsigned i=0; i<buff_byte_sizes.size(); i++){
    cur_experiment_number++;
    run_direct(buff_byte_sizes.at(i));
  }
  std::cout << std::endl;
}

void Experiment::run_direct(unsigned int byte_size)
{
  unsigned int_size = byte_size/sizeof(int);
  [[maybe_unused]] unsigned t = 0;
  generate_buff(int_size);
  warm_up(byte_size);
  std::chrono::system_clock::time_point start =
      std::chrono::system_clock::now();
  //std::cout << std::endl << " int_size = " << int_size << std::endl;
  for (unsigned k = 0; k < 1000; k++){
    for (unsigned i = 0; i < int_size; i += 16)
    {
      t = buff.at(i);
    }
  }
  std::chrono::system_clock::time_point end =
      std::chrono::system_clock::now();
  std::chrono::duration<double> time = (end-start)/(1000*(int_size/16));
  print_to_report(byte_size, time.count());
}

void Experiment::run_reverse(unsigned int byte_size)
{
  unsigned int_size = byte_size/sizeof(int);
  [[maybe_unused]] unsigned t = 0;
  generate_buff(int_size);
  warm_up(byte_size);
  std::chrono::system_clock::time_point start =
      std::chrono::system_clock::now();
  //std::cout << std::endl << " int_size = " << int_size << std::endl;
  for (unsigned k=0; k<1000; k++){
    for (int i=static_cast<int>(int_size-1); i > 0; i -= 16)
    {
      t = buff.at(i);
    }
  }
  std::chrono::system_clock::time_point end =
      std::chrono::system_clock::now();
  std::chrono::duration<double> time = (end-start)/(1000*(int_size/16));
  //std::cout << "Reverse run: " << byte_size/1024 << " KB" << std::endl;
  print_to_report(byte_size, time.count());
}

void Experiment::run_random(unsigned int byte_size)
{
  unsigned int_size = byte_size/sizeof(int);
  [[maybe_unused]] unsigned t = 0;
  generate_buff(int_size);
  warm_up(byte_size);
  std::chrono::system_clock::time_point start =
      std::chrono::system_clock::now();
  //std::cout << std::endl << " int_size = " << int_size << std::endl;
  for (unsigned k = 0; k < 1000; k++){
    for (int i=static_cast<int>(int_size-1); i > 0; i-=16)
    {
      t = buff.at(engine()%(int_size));
    }
  }
  std::chrono::system_clock::time_point end =
      std::chrono::system_clock::now();
  std::chrono::duration<double> time = (end-start)/(1000*(int_size/16));
  //std::cout << "Random run: " << byte_size/1024 << " KB" << std::endl;
  print_to_report(byte_size, time.count());
}

bool Experiment::is_power_of_two(unsigned int number) {
  if (((number & (number - 1)) == 0) && (number > 1)) return true;
  else
    return false;
}

void Experiment::generate_buff(unsigned int int_size)
{
  buff.clear();
  for (unsigned i = 0; i < int_size; i++)
  {
    buff.push_back(engine()); //change to rand_r
  }
}

void Experiment::warm_up(unsigned byte_size)
{
  //std::cout << buff.size() << " is buff size; size of int is "
  //          << sizeof(int) << std::endl;
  //if (byte_size > L1DSIZE) byte_size = L1DSIZE;
  unsigned int_size = byte_size/4;
  [[maybe_unused]] unsigned t = 0;
  for (unsigned i = 0; i < int_size; i+=16)
  {
    t = buff.at(i);
    //std::cout << t << " ";
  }
}

void Experiment::print_to_report(unsigned byte_size, double time)
{
  std::string time_string = std::to_string(time*1000000000);
  do{
    time_string.pop_back();
  } while (time_string[time_string.size()-1] == '0');
  time_string.pop_back();
  time_string += " ns";
  report << "  - experiment" << std::endl
         << "    number: " << cur_experiment_number << std::endl
         << "    input data: " << std::endl
         << "      buffer_size: "
         << ((byte_size >= 1024*1024) ?
            (std::to_string(byte_size/(1024*1024)) + " MB") :
            (std::to_string(byte_size/1024) + " KB"))
         << std::endl << "    results: " << std::endl
         << "      duration: " << time_string << std::endl;
}

const std::ostringstream& Experiment::get_report() const { return report; }
