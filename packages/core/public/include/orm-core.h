#pragma once

#include <string>

#define EXPORT __attribute__((__visibility__("default")))

namespace ORM_C {

struct EXPORT RXD {
  static std::string getIndexesFrom(const char* filePath);

  static std::string getContent(const char* filePath, unsigned int uid);
};

}  // namespace ORM