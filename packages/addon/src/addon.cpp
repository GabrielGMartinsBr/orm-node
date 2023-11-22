#include <napi.h>

#include <iostream>
#include <string>

#include "orm-core.h"

namespace rxd {

std::string getIndexes(const char* filePath)
{
  return ORMC::RXD::getIndexesFrom(filePath);
}

Napi::String getIndexesWrapped(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  if (info.Length() != 1 || !info[0].IsString()) {
    Napi::TypeError::New(env, "File path expected.")
      .ThrowAsJavaScriptException();
  }

  Napi::String param = info[0].As<Napi::String>();
  std::string filePath = param.Utf8Value();
  std::string result = getIndexes(filePath.c_str());

  Napi::String returnValue = Napi::String::New(env, result);

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
