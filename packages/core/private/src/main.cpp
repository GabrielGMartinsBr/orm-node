#include "Reader.hpp"
#include "ruby.h"

int main()
{
  ruby_init();
  ORM::Reader::testRead();
  // Reader::testJson();
  ruby_finalize();
}