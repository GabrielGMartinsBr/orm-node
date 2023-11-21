#pragma once

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "base/Log.hpp"
#include "ruby.h"

typedef boost::filesystem::path FPath;

struct Reader {

  static void testJson()
  {
    boost::property_tree::ptree pt;

    // Add data to the property tree
    pt.put("name", "John Doe");
    pt.put("age", 30);
    pt.put("is_student", false);

    std::ostringstream oss;
    boost::property_tree::json_parser::write_json(oss, pt);
    Log::out() << oss.str();
  }

  static void read()
  {
    std::string bin = readFile();
    VALUE arr = marshalLoad(bin);
    std::string json = convertToJSON(arr);

    Log::out() << json;

    // std::ifstream inputFile(getPath());

    // if (inputFile.is_open()) {
    //   std::ostringstream oss;
    //   oss << inputFile.rdbuf();

    //   VALUE rbStr = rb_str_new(oss.str().c_str(), oss.str().size());
    //   if (NIL_P(rbStr)) {
    //     Log::err() << "failed to create string";
    //     return;
    //   }

    //   VALUE rbArr = rb_marshal_load(rbStr);
    //   // Log::out() << RARRAY_LEN(rbArr);
    //   VALUE entry = rb_ary_entry(rbArr, 1);

    //   rb_p(rb_ary_entry(entry, 2));

    //   // Log::out() << rb_ary_entry(entry, 1);

    //   VALUE errorMsg = rb_gv_get("$!");
    //   if (errorMsg != Qnil) {
    //     rb_p(errorMsg);
    //   }

    //   // std::string line;
    //   // std::getline(inputFile, line);
    //   // Log::out() << line;

    //   // while (std::getline(inputFile, line)) {
    //   //   Log::out() << "line";
    //   // }
    // } else {
    //   Log::err() << "unable to open file.";
    // }
  }

private:
  static std::string convertToJSON(const VALUE rbArr)
  {
    std::ostringstream oss;
    boost::property_tree::ptree entries;

    unsigned int len = RARRAY_LEN(rbArr);

    for (int i = 0; i < len; i++) {
      VALUE rbEntry = rb_ary_entry(rbArr, i);
      VALUE rbId = rb_ary_entry(rbEntry, 0);
      VALUE rbName = rb_ary_entry(rbEntry, 1);
      VALUE rbCode = rb_ary_entry(rbEntry, 2);

      unsigned int id = FIX2INT(rbId);
      const char *name = RSTRING_PTR(rbName);
      const char *code = RSTRING_PTR(rbCode);

      boost::property_tree::ptree item;
      item.put("id", id);
      item.put("name", name);
      item.put("code", code);

      entries.push_back(
        std::make_pair("", item)
      );
    }

    boost::property_tree::json_parser::write_json(oss, entries, false);
    return oss.str();
  }

  static VALUE marshalLoad(const std::string &data)
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

  static std::string readFile()
  {
    std::ifstream inputFile(getPath());
    if (!inputFile.is_open()) {
      throw std::runtime_error("Failed to read file.");
    }
    std::ostringstream oss;
    oss << inputFile.rdbuf();
    inputFile.close();
    return oss.str();
  }

  static std::string getPath()
  {
    FPath relative("../../../data/Scripts.rxdata");
    FPath absolutePath = boost::filesystem::canonical(relative);
    return absolutePath.string();
  }
};