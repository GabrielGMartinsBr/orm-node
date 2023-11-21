#pragma once

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "ruby.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace ORM {
typedef boost::filesystem::path FPath;

struct Reader {
  static std::string readIndexes(const char *target);

private:
  static std::string resolvePath(const char *path);
  static std::string readFile(const char *path);
  static VALUE marshalLoad(const std::string &data);
  static std::string convertToJSON(const VALUE rbArr);
};

} // namespace ORM
