#include "orm-core.h"

#include <string>

#include "Reader.hpp"

std::string ORM::RXD::getIndexesFrom(const char* filePath)
{
  return Reader::readIndexes(filePath);
}

std::string ORM::RXD::getContent(
  const char* filePath, unsigned int uid
)
{
  return std::string("Content!");
}