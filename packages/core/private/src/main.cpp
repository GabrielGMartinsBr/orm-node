#include "Core.hpp"
#include "Log.hpp"

int main()
{
  ORMC::Core& core = ORMC::Core::getInstance();
  const char* fname = "../../../data/Scripts.rxdata";

  // Log::out() << "size: " << core.rxdReader.readIndexes(fname).size();
  // Log::out() << "size: " << core.rxdReader.readIndexes(fname).size();
  // Log::out() << "size: " << core.rxdReader.readIndexes(fname).size();

  // ORMC::Core::getInstance().rxdReader.readIndexes(fname);
  // core.rxdReader.readContent(fname, 75819864);
  Log::out() << core.rxdReader.readContent(fname, 34503174);
}