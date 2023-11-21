#include "orm/Reader.h"
#include "base/Log.hpp"
// #include "base/Log.hpp"

#include <string>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

typedef boost::filesystem::path FPath;
// namespace bpt = boost::property_tree;

void convertToJSON()
{
  boost::property_tree::ptree entries;
}

std::string resolvePath(const char *path)
{
  FPath relative(path);
  FPath absolutePath = boost::filesystem::canonical(relative);
  return absolutePath.string();
}

std::string ORM::Reader::readIndexes(const char *path)
{
  Log::out() << resolvePath("./");

  convertToJSON();

  std::string name = "zarina!";

  return name;
}
