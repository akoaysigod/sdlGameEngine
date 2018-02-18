#pragma once

#include <iostream>
#include <string>

#ifdef WIN32
#include <Rpc.h>
#include <objbase.h>
#endif

#if __unix__
#include <uuid/uuid.h>
#endif

#if __APPLE__
#include <CoreFoundation/CFUUID.h>
#endif

namespace ge {
  class UUID {
  public:
    static std::string make() {
#ifdef WIN32
      GUID guid;
      CoCreateGuid(&guid);
      char guid_cstr[39];
      snprintf(guid_cstr, sizeof(guid_cstr),
        "{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
      std::string s(guid_cstr);
#endif

#if __unix__
      uuid_t uuid;
      uuid_generate_random(uuid);
      char s[37];
      uuid_unparse(uuid, s);
#endif

#if __APPLE__
      //https://developer.apple.com/documentation/corefoundation/1542133-cfstringgetcstringptr
      //this can apparently break for no reason between releases?
      auto uuid = CFUUIDCreate(nullptr);
      auto bytes = CFUUIDCreateString(nullptr, uuid);
      CFRelease(uuid);
      auto pathUTF8 = CFStringGetCStringPtr(bytes, kCFStringEncodingUTF8);
      std::string s(pathUTF8);
      CFRelease(bytes);
#endif

      return s;
    }
  };
}