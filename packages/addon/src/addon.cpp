#include "orm/Reader.h"

#include <node.h>

#include <string>
#include <vector>

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value> &args)
{
  std::string s = ORM::Reader::readIndexes("../../data/Scripts.rxdata");

  Isolate *isolate = args.GetIsolate();
  args.GetReturnValue().Set(
    String::NewFromUtf8(isolate, s.c_str()).ToLocalChecked()
  );
  // args.GetReturnValue().Set(
  //   String::NewFromUtf8(isolate, "hello").ToLocalChecked()
  // );
}

void Initialize(Local<Object> exports)
{
  NODE_SET_METHOD(exports, "hello", Method);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

} // namespace demo