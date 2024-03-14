#include <cassert>

#include "set.hpp"

int main() {
  set s;
  assert(s.empty());

  s.insert(1);
  assert(!s.empty());

  s.remove(4);
  assert(!s.empty());

  s.insert(2);
  s.insert(3);
  assert(s.member(1));
  assert(s.member(2));
  assert(s.member(3));
  assert(!s.member(4));
  assert(s.size() == 3);

  s.remove(1);
  s.remove(2);
  s.remove(3);
  assert(s.empty());

  return 0;
}