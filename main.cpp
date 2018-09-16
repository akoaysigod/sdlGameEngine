#include <v8.h>
#include <libplatform/libplatform.h>
#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Requires an input js file.";
    return 0;
  }

  v8::V8::InitializeICUDefaultLocation(argv[0]);
  v8::V8::InitializeExternalStartupData(argv[0]);
  std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
  v8::V8::InitializePlatform(platform.get());
  v8::V8::Initialize();


  return 0;
}
