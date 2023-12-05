#pragma once

#include <zlib.h>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <cstdio>
#include <stdexcept>
#include <string>

#include "Log.hpp"
#include "ruby.h"

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

  std::string readContent(const char *path, unsigned int scriptId)
  {
    std::string bin = readFile(path);
    VALUE rbArr = marshalLoad(bin);
    std::string compressedContent = getContent(rbArr, scriptId);
    std::string content = decompressContent(compressedContent);
    rb_gc();
    return content;
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

      unsigned int id = FIX2INT(rbId);
      const char *name = RSTRING_PTR(rbName);

      bpt::ptree item;
      item.put("id", id);
      item.put("name", name);

      entries.push_back(
        bpt::ptree::value_type("", item)
      );
    }

    bpt::ptree full;
    full.put_child("scripts", entries);

    std::ostringstream oss;
    bpt::json_parser::write_json(oss, full, false);
    return oss.str();
  }

  std::string getContent(const VALUE rbArr, unsigned int scriptId)
  {
    VALUE rbEntry, rbId, rbName;
    unsigned int len = rb_array_len(rbArr);

    for (int i = 0; i < len; i++) {
      rbEntry = rb_ary_entry(rbArr, i);

      rbId = rb_ary_entry(rbEntry, 0);
      Check_Type(rbId, RUBY_T_FIXNUM);

      unsigned int id = FIX2INT(rbId);

      if (id == scriptId) {
        VALUE rbCode = rb_ary_entry(rbEntry, 2);

        const long len = RSTRING_LEN(rbCode);
        const char *code = RSTRING_PTR(rbCode);

        return std::string(code, len);
      }
    }

    return nullptr;
  }

  std::string decompressContent(std::string &compressedContent)
  {
    z_stream zStream;
    zStream.zalloc = Z_NULL;
    zStream.zfree = Z_NULL;
    zStream.opaque = Z_NULL;
    zStream.avail_in = 0;
    zStream.next_in = Z_NULL;

    if (inflateInit(&zStream) != Z_OK) {
      throw std::runtime_error("Failed to initialize zlib inflate.");
    }

    zStream.avail_in = compressedContent.length();
    zStream.next_in = reinterpret_cast<Bytef *>(compressedContent.data());

    const int bufferSize = 1024;
    char buffer[bufferSize];

    std::string inflatedData;
    int status;
    do {
      zStream.avail_out = bufferSize;
      zStream.next_out = reinterpret_cast<Bytef *>(buffer);
      status = inflate(&zStream, Z_NO_FLUSH);

      if (status != Z_OK && status != Z_STREAM_END) {
        inflateEnd(&zStream);
        Log::err() << "Error while inflating data: " << status;
        throw std::runtime_error("Failed to decompress script content.");
      }

      inflatedData.append(buffer, bufferSize - zStream.avail_out);

    } while (zStream.avail_out == 0);

    inflateEnd(&zStream);
    return inflatedData;
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
