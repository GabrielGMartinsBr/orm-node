#include "Reader.hpp"
#include "ruby.h"

int main()
{
  ruby_init();
  Reader::read();
  // Reader::testJson();
  ruby_finalize();
}