# MinGW WinRT Component Demo

This is a demo of in-proc WinRT component on MinGW.

## Why

To stress test the new C++/WinRT MinGW support mostly, also it is fun.

## Build

To build this, you'll need the following:

- CMake
- C++/WinRT `cppwinrt` in `$PATH`
- [WinMIDL](https://github.com/microsoft/WinMIDL) `Midl.Cli` in `$PATH`
- A MinGW toolchain, LLVM/Clang 17 and GCC 13 from MSYS2 are tested.

The best way to get a working toolchain (except WinMIDL) is install the following in MSYS2:

```sh
# CLANG64 Subsystem, with LLVM/Clang
pacman -S mingw-w64-clang-x86_64-{toolchain,cppwinrt,cmake,ninja}

# UCRT64 Subsystem, with GCC
pacman -S mingw-w64-ucrt-x86_64-{toolchain,cppwinrt,cmake,ninja}
```

With these, just build using CMake:

```sh
cd component
mkdir build && cd build
cmake ..
cmake --build .
```

## Test

C++ and C# test programs are provided, and can be built and run normally.

## Notes about metadata

Since the official MIDL 3.0 compiler `midl.exe` is proprietary, [WinMIDL](https://github.com/microsoft/WinMIDL) is used as an alternative.

The two compiler is mostly compatible, but WinMIDL is still in its early stages so expect some issues.

Some other alternatives: 

- Wait for Wine's widl to [support winmd output](https://bugs.winehq.org/show_bug.cgi?id=53905)\
It is mostly there in Wine 11.x, but still cannot express interface/reference type in method parameters or return value. \
Also it expects the earlier MIDLRT syntax (as seen in Windows SDK), instead of the modern MIDL 3.0 syntax.
- [riddle](https://crates.io/crates/riddle) from windows-rs, which uses Rust-like rdl syntax
- [CsWinMD](https://github.com/microsoft/CsWinRT/tree/2.0.7.240207.1/src/Authoring/cswinmd) from C#/WinRT, which uses C# syntax. 
- Just use `midl.exe` if you are OK with this

