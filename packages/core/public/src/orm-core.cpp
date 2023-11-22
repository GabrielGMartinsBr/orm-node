#include "orm-core.h"

#include <string>

#include "Core.hpp"

std::string ORMC::RXD::getIndexesFrom(const char* filePath)
{
  return Core::getInstance().rxdReader.readIndexes(filePath);
}

std::string ORMC::RXD::getContent(
  const char* filePath, unsigned int uid
)
{
  return std::string("Content!");
}