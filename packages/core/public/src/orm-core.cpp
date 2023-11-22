#include "orm-core.h"

#include <string>

#include "Reader.hpp"

std::string ORM_C::RXD::getIndexesFrom(const char* filePath)
{
  return Reader::readIndexes(filePath);
}

std::string ORM_C::RXD::getContent(
  const char* filePath, unsigned int uid
)
{
  return std::string("Content!");
}