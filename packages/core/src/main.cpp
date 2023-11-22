#include "Reader.hpp"
#include "ruby.h"

int main()
{
  ruby_init();
  ORM_APP::Reader::testRead();
  // Reader::testJson();
  ruby_finalize();
}