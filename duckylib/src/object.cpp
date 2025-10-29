#include "../include/object.hpp"

using namespace ducky;

Object::Object() {
  using namespace std::chrono;
  using picoseconds = std::chrono::duration<long long, std::pico>;
  uint64_t current_time =
      duration_cast<picoseconds>(system_clock::now().time_since_epoch())
          .count();
  std::srand(std::time(0));
  int rand = std::rand() % 100 + 1;
  this->id_ = abs((int)(sin(current_time) * 10000000)) + rand;
  current_time = 0;
}

void Object::destroy() {
  if (this->destroyed)
    return;

  this->destroyed = true;
}

int Object::get_id() { return this->id_; }
