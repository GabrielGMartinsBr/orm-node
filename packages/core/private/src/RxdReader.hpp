#pragma once

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include "Log.hpp"
#include "ruby/internal/intern/gc.h"
#include "ruby/ruby.h"

namespace ORMC {

typedef boost::filesystem::path FPath;

namespace bpt = boost::property_tree;

struct RxdReader {
  std::string readIndexes(const char *path)
  {
    std::string bin = readFile(path);
    VALUE rbArr = marshalLoad(bin);
    std::string json = convertToJSON(rbArr);
    rb_gc();
    return json;
  }

 private:
  std::string convertToJSON(const VALUE rbArr)
  {
    bpt::ptree entries;
    VALUE rbEntry, rbId, rbName;
    unsigned int len = rb_array_len(rbArr);
    
    for (int i = 0; i < len; i++) {
      rbEntry = rb_ary_entry(rbArr, i);
      rbId = rb_ary_entry(rbEntry, 0);
      rbName = rb_ary_entry(rbEntry, 1);
      // VALUE rbCode = rb_ary_entry(rbEntry, 2);

      unsigned int id = FIX2INT(rbId);
      const char *name = RSTRING_PTR(rbName);
      // const char *code = RSTRING_PTR(rbCode);

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

    VALUE errorMsg = rb_gv_get("$!");
    if (errorMsg != Qnil) {
      rb_p(errorMsg);
      throw std::runtime_error("Marshal load failed.");
    }

    return rbArr;
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

  std::string resolvePath(const char *path)
  {
    FPath relative(path);
    FPath absolutePath = boost::filesystem::canonical(relative);
    return absolutePath.string();
  }
};

}  // namespace ORMC
