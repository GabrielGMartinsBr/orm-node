#include "orm/Reader.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "ruby.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "base/Log.hpp"
#include "ruby/internal/interpreter.h"

namespace bpt = boost::property_tree;
typedef boost::filesystem::path FPath;

std::string convertToJSON(const VALUE rbArr)
{
  bpt::ptree entries;

  unsigned int len = RARRAY_LEN(rbArr);
  for (int i = 0; i < len; i++) {
    VALUE rbEntry = rb_ary_entry(rbArr, i);
    VALUE rbId = rb_ary_entry(rbEntry, 0);
    VALUE rbName = rb_ary_entry(rbEntry, 1);
    VALUE rbCode = rb_ary_entry(rbEntry, 2);

    unsigned int id = FIX2INT(rbId);
    const char *name = StringValuePtr(rbName);
    // const char *code = StringValuePtr(rbCode);

    bpt::ptree item;
    item.put("id", id);
    item.put("name", name);
    // item.put("code", code);

    entries.push_back(
      bpt::ptree::value_type("", item)
    );
  }

  bpt::ptree full;
  full.put_child("scripts", entries);
  // bpt::write_json("out.json", full);

  std::ostringstream oss;
  bpt::json_parser::write_json(oss, full, false);
  return oss.str();
}

VALUE marshalLoad(const std::string &data)
{
  VALUE rbStr = rb_str_new(data.c_str(), data.size());
  if (NIL_P(rbStr)) {
    Log::err() << "Failed to create ruby string.";
  }

  VALUE rbArr = rb_marshal_load(rbStr);

  // VALUE errorMsg = rb_gv_get("$!");
  // if (errorMsg != Qnil) {
  //   rb_p(errorMsg);
  //   throw std::runtime_error("Marshal load failed.");
  // }

  return rbArr;
}

std::string resolvePath(const char *path)
{
  FPath relative(path);
  FPath absolutePath = boost::filesystem::canonical(relative);
  return absolutePath.string();
}

std::string readFile(const char *path)
{
  std::ifstream inputFile(resolvePath(path));
  if (!inputFile.is_open()) {
    throw std::runtime_error("Failed to read file.");
  }
  std::ostringstream oss;
  oss << inputFile.rdbuf();
  inputFile.close();
  return oss.str();
}

std::string ORM::Reader::readIndexes(const char *path)
{
  std::string absPath = resolvePath(path);
  std::string bin = readFile(path);
  Log::out() << "Size: " << bin.size();

  ruby_init();
  ruby_init_loadpath();
  rb_eval_string("puts RUBY_VERSION");

  VALUE arr = marshalLoad(bin);
  std::string json = convertToJSON(arr);

  ruby_finalize();
  return json;

  return absPath;
}