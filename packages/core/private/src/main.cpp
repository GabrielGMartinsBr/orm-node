#include "Log.hpp"
#include "Reader.hpp"

int main()
{
  Log::out() << ORM_C::Reader::readIndexes("../../../data/Scripts.rxdata");
}