/*
A Modular Cross-Platform Calculator
Copyright (C) 2025  Wdboyes13

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#ifdef _WIN32
  #include <windows.h>
  #define DLOPEN(path) LoadLibraryA(path)
  #define DLSYM(handle, sym) GetProcAddress(handle, sym)
  #define DLCLOSE(handle) FreeLibrary(handle)
  static char win_dlerror_buf[256];
    #define DLERROR() (FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, \
                                     NULL, GetLastError(), 0, win_dlerror_buf, sizeof(win_dlerror_buf), NULL), \
                      win_dlerror_buf)
#else
  #include <dlfcn.h>
  #define DLOPEN(path) dlopen(path, RTLD_NOW)
  #define DLSYM(handle, sym) dlsym(handle, sym)
  #define DLCLOSE(handle) dlclose(handle)
  #define DLERROR() dlerror()
#endif

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif