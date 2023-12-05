#pragma once

#include "Log.hpp"
#include "RxdReader.hpp"

namespace ORMC {

class Core {
 public:
  RxdReader rxdReader;

  static Core& getInstance()
  {
    static Core instance;
    return instance;
  }

 private:
  Core(const Core&);
  Core& operator=(const Core&);

  Core()
  {
    ruby_init();
    Log::out() << "Ruby was initialized.";
  }

  ~Core()
  {
    rb_gc();
    ruby_finalize();
    Log::out() << "Ruby was finalized.";
  }
};
}  // namespace ORMC