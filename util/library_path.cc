#include "library_path.hh"
#include "config/config.h"

#include <filesystem>
#include <string>
#include <system_error>

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#include <vector>
#endif

static std::filesystem::path executable_path(void) {
  std::filesystem::path result;
#if defined(_WIN32)
  std::wstring buffer(32768, L'\0');
  DWORD length = GetModuleFileNameW(NULL, &buffer[0], (DWORD)buffer.size());
  if (length > 0 && length < buffer.size()) {
    buffer.resize(length);
    result = buffer;
  }
#elif defined(__APPLE__)
  uint32_t size = 0;
  _NSGetExecutablePath(NULL, &size);
  std::vector<char> buffer(size);
  if (_NSGetExecutablePath(buffer.data(), &size) == 0)
    result = buffer.data();
#elif defined(__linux__) || defined(__FreeBSD__)
  std::error_code error;
#if defined(__linux__)
  result = std::filesystem::read_symlink("/proc/self/exe", error);
#else
  result = std::filesystem::read_symlink("/proc/curproc/file", error);
#endif
#endif
  return result;
}

const char *matiec_default_library_directory(void) {
  static const std::string directory = []() {
    std::filesystem::path executable = executable_path();
    std::filesystem::path candidates[] = {
      executable.empty() ? std::filesystem::path() :
        executable.parent_path() / MATIEC_RELATIVE_LIBDIR,
      MATIEC_INSTALL_LIBDIR,
      MATIEC_SOURCE_LIBDIR
    };
    for (const std::filesystem::path &candidate : candidates) {
      std::error_code error;
      if (!candidate.empty() && std::filesystem::is_regular_file(candidate / "ieclib.txt", error))
        return candidate.lexically_normal().generic_string();
    }
    return std::string(MATIEC_INSTALL_LIBDIR);
  }();
  return directory.c_str();
}
