#include <iostream>
#include "group.hpp"
#include "volunteer.hpp"

void Group::AddVolunteer(const Volunteer& vol) { group_.push_back(vol); }
double Group::GetAvgBuildingExp() const{
  double sum = 0;

  for (const Volunteer &vol : group_) {
    sum += vol.GetBuildingExperience();
  }
  if (group_.empty()) {
    return 0;
  }
  auto size = double (group_.size());
  return sum / size;
}
double Group::GetAvgStamina() const {
  double sum = 0;

  for (const Volunteer &vol : group_) {
    sum += vol.GetPhysicalStamina();
  }
  if (group_.empty()) {
    return 0;
  }
  auto size = double(group_.size());
  return sum / size;
}
int Group::GetReturningMembers() const{
  int count = 0;
  for (const Volunteer &vol : group_) {
    if(vol.IsReturning()) {
      count++;
    }
  }
  if (group_.empty()) {
    return 0;
  }
  return count;
}
Volunteer& Group::GetRandomVolunteer() {
  size_t size = group_.size();
  
    size_t num = rand() % size;
    return group_.at(num);
  
}



std::ostream& operator<<(std::ostream& os, const Group& g_in) {
  double avgb = g_in.GetAvgBuildingExp();
  double avgs = g_in.GetAvgStamina();
  int ret = g_in.GetReturningMembers();
  os << "Group: " << "Average Exp: " << avgb << "Average Stamina: " << avgs << "Returning members: " << ret <<std::endl;
  for (const Volunteer &vol : g_in.group_) {
    os << vol.GetName() << std::endl;
  }
  return os;
}
