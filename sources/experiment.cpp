// Copyright 2018 Your Name <your_email>

#include <experiment.hpp>
#include <iostream>



Experiment::Experiment(const std::vector<unsigned int> &l_sizes)
    :
      buff_sizes(0),
      buff(0)
{
  set_buff_sizes(l_sizes);
}

void Experiment::set_buff_sizes(const std::vector<unsigned int> &l_sizes)
{
  std::vector<unsigned> tmp;
  unsigned cur_number;
  if (!is_power_of_two(l_sizes.at(0)))
  {
    cur_number=2;
    while (cur_number<l_sizes.at(0)/2) {
      cur_number*=2;
    }
    tmp.push_back(l_sizes.at(0)/2);
  }
  else
  {
    cur_number=l_sizes.at(0)/2;
  }
  for (unsigned i=0; i<l_sizes.size(); i++)
  {
    while (cur_number<l_sizes.at(i))
    {
      tmp.push_back(cur_number);
      cur_number*=2;
    }
    if (cur_number!=l_sizes.at(i)) tmp.push_back(l_sizes.at(i));
  }
  tmp.push_back(l_sizes.at(2));
  tmp.push_back(l_sizes.at(2)*3/2);
  tmp.erase(tmp.begin());// #TODO fix!!!
  tmp.erase(tmp.begin());// #TODO fix!!!
  buff_sizes=tmp;
}

const std::vector<unsigned> &Experiment::get_buff_sizes() const {
  return buff_sizes;
}

void Experiment::run_experiment()
{
  for (unsigned i=0;i<buff_sizes.size();i++){
    run_direct(buff_sizes.at(i));
  }
  for (unsigned i=0;i<buff_sizes.size();i++){
    run_reverse(buff_sizes.at(i));
  }
  for (unsigned i=0;i<buff_sizes.size();i++){
    run_random(buff_sizes.at(i));
  }
}

void Experiment::run_direct(unsigned int size)
{
  generate_buff(size/ sizeof(int));
  warm_up();
  std::cout << "Direct run: " << size/1024 << " KB" << std::endl;
}

void Experiment::run_reverse(unsigned int size)
{
  std::cout << "Reverse run: " << size/1024 << " KB" << std::endl;
}

void Experiment::run_random(unsigned int size)
{
  std::cout << "Random run: " << size/1024 << " KB" << std::endl;
}

bool Experiment::is_power_of_two(unsigned int number) {
  if (((number & (number - 1)) == 0) && (number>1)) return true;
  else return false;
}

void Experiment::generate_buff(unsigned int size)
{
  //size/=sizeof(int);
  for (unsigned i=0; i<size;i++)
  {
    buff.push_back(i); //change to rand
  }
}

void Experiment::warm_up()
{
  std::cout << buff.size() << " is buff size; int size is " << sizeof(int) << std::endl;
  [[maybe_unused]] unsigned t=0;
  for (unsigned i=0; i<L1DSIZE/4; i+=16)
  {
    t=buff.at(i);
    std::cout << i << " ";
  }
}
