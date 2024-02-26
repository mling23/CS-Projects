#include <ctime>
#include <fstream>
#include <iostream>

#include "constants.hpp"
#include "group.hpp"

std::vector<Group> GroupForming(std::ifstream& ifs, int number) {
  std::vector<Group> groups;
  for (int i = 0; i < number; i += kSizeGroups) {
    Group group;
    std::string name;
    int exp = 0;
    int stam = 0;
    bool re = true;
    ifs >> name >> exp >> stam >> re;
    Volunteer vol = Volunteer(name, exp, stam, re);  // first volunteer
    group.AddVolunteer(vol);
    ifs >> name >> exp >> stam >> re;  // 2nd
    vol = Volunteer(name, exp, stam, re);
    group.AddVolunteer(vol);
    ifs >> name >> exp >> stam >> re;  // 3rd
    vol = Volunteer(name, exp, stam, re);
    group.AddVolunteer(vol);
    ifs >> name >> exp >> stam >> re;  // 4th
    vol = Volunteer(name, exp, stam, re);
    group.AddVolunteer(vol);
    ifs >> name >> exp >> stam >> re;  // 5th
    vol = Volunteer(name, exp, stam, re);
    group.AddVolunteer(vol);

    groups.push_back(group);
  }
  return groups;
}

/*Write your main driver in this file! Remember to seperate
out things into functions to help with readability and reusability.

See specifications for how to get started and
go to office hours if you need help!*/

//convert some of these things to functions then pass it. 

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "invalid";
  }
  // DO NOT EDIT THIS LINE or add another srand call.
  srand(time(nullptr));
  std::string file = argv[1];
  int number = std::stoi(argv[2]);
  std::string out = argv[3];
  std::vector<Group> groups(number / kSizeGroups);
  std::ifstream ifs{file};
  if (ifs.is_open()) {groups = GroupForming(ifs, number);}
  bool exceeded = false;
  bool condition = false;
  unsigned int k = 0;
  while (!condition) {
    condition = true;
    for (size_t i = 0; i < groups.size(); i++) {
      Group& group = groups.at(i);
      if (group.GetReturningMembers() < kMinReturning || group.GetAvgBuildingExp() < kMinAvgBuildingExp || group.GetAvgStamina() < kMinAvgStamina) {
        condition = false;
        size_t rand1 = rand() % groups.size();
        while (rand1 == i) {rand1 = rand() % groups.size();}
        Volunteer& a = group.GetRandomVolunteer();
        Volunteer& b = groups.at(rand1).GetRandomVolunteer();
        std::swap(a, b);
        k++;
        if (k == kMaxIterations) { condition = true; exceeded = true; std::cout << "No groups found"; break;
        }}}}
  if(!exceeded) {
    std::ofstream ofs{out};
    for (size_t i = 0; i < groups.size(); i++) {
      Group group = groups.at(i);
      ofs << group;
    }
  } 
  return 0;
}
