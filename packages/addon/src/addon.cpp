#include <napi.h>

#include <iostream>
#include <string>

#include "orm-core.h"

namespace rxd {

std::string getIndexes(const char* filePath)
{
  return ORMC::RXD::getIndexesFrom(filePath);
}

std::string getContent(const char* filePath, unsigned int scriptId)
{
  return ORMC::RXD::getContent(filePath, scriptId);
}

Napi::String getIndexesWrapped(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  if (info.Length() != 1 || !info[0].IsString()) {
    Napi::TypeError::New(env, "File path is expected.")
      .ThrowAsJavaScriptException();
  }

  Napi::String param = info[0].As<Napi::String>();
  std::string filePath = param.Utf8Value();
  std::string result = getIndexes(filePath.c_str());

  Napi::String returnValue = Napi::String::New(env, result);

  return returnValue;
}

Napi::String getContentWrapped(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  if (info.Length() != 2 || !info[0].IsString() || !info[1].IsNumber()) {
    Napi::TypeError::New(env, "File path and scriptId are expected.")
      .ThrowAsJavaScriptException();
  }

  Napi::String filePathRaw = info[0].As<Napi::String>();
  std::string filePath = filePathRaw.Utf8Value();

  unsigned int scriptId = info[1].As<Napi::Number>();

  std::string result = getContent(filePath.c_str(), scriptId);

  Napi::String returnValue = Napi::String::New(env, result);

  return returnValue;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(
    "getIndexes",
    Napi::Function::New(env, getIndexesWrapped)
  );

  exports.Set(
    "getContent",
    Napi::Function::New(env, getContentWrapped)
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
