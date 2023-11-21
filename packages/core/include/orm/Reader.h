#pragma once

#include <string>

namespace ORM {
struct Reader {
  static std::string readIndexes(const char *target);
};

} // namespace ORM
