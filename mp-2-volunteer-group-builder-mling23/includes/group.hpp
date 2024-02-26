#ifndef GROUP_HPP
#define GROUP_HPP

#include <ostream>
#include "volunteer.hpp"
#include <vector>

class Group {
public:
  void AddVolunteer(const Volunteer& vol);

  double GetAvgBuildingExp() const;

  int GetReturningMembers() const;

  double GetAvgStamina() const;

  friend std::ostream& operator<<(std::ostream& os, const Group& g_in);

  Volunteer& GetRandomVolunteer();

  

private:
  std::vector<Volunteer> group_;
  

  // TODO create private member variable(s)
};

std::ostream& operator<<(std::ostream& os, const Group& g_in);

#endif
