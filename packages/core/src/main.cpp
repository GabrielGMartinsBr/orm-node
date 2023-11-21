#include "Reader.hpp"
#include "ruby.h"

int main()
{
  ruby_init();
  Reader::testRead();
  // Reader::testJson();
  ruby_finalize();
}