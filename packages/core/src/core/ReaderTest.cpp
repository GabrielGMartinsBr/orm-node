#include "orm/Reader.h"
#include "base/Log.hpp"
// #include "base/Log.hpp"

#include <string>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "ruby.h"


typedef boost::filesystem::path FPath;
namespace bpt = boost::property_tree;

std::string convertToJSON()
{
  VALUE test;
  boost::property_tree::ptree entries;

  entries.put("name", "Gabriel");
  std::ostringstream oss;
  bpt::json_parser::write_json(oss, entries, false);
  return oss.str();
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

  std::string str =convertToJSON();

  std::string name = "zarina!";

  return str;
}
