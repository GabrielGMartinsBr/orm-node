#include <napi.h>

#include <string>

#include "orm-core.h"

namespace rxd {

std::string getIndexes()
{
  return ORM_C::RXD::getIndexesFrom("../../data/Scripts.rxdata");
  return "{ \"msg\": \"Hey, hello!\" }";
}

Napi::String getIndexesWrapped(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  Napi::String returnValue = Napi::String::New(env, getIndexes());

  return returnValue;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(
    "getIndexes",
    Napi::Function::New(env, getIndexesWrapped)
  );

  return exports;
}

}  // namespace rxd

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
  rxd::Init(env, exports);
  return exports;
}

NODE_API_MODULE(addon, InitAll);
