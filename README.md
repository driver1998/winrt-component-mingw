# MinGW WinRT Component Demo

This is a demo of in-proc WinRT component on MinGW.

# Why

To stress test the new C++/WinRT MinGW support mostly, also it is fun.

# Build

To build this, you'll need the following:

- CMake
- C++/WinRT `cppwinrt.exe` in `$PATH`
- A MinGW toolchain, LLVM/Clang 17 and GCC 13 from MSYS2 are tested.

The best way to get a working toolchain is install the following in MSYS2:

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

# Test

C++ and C# test programs are provided, and can be built and run normally.

# Note about metadata

Since the official MIDL 3.0 compiler `midl.exe` is proprietary, [CsWinMD](https://github.com/microsoft/CsWinRT/tree/2.0.7.240207.1/src/Authoring/cswinmd) from C#/WinRT is used as an alternative, which uses C# code to define components instead of IDL. 

You can take a look at [component.cs](component/component.cs) for an example.

Some other alternatives: 

- Wait for Wine's widl to [support winmd output](https://bugs.winehq.org/show_bug.cgi?id=53905)
- [riddle](https://crates.io/crates/riddle) from windows-rs, which uses Rust-like rdl syntax
- Just use `midl.exe` if you are OK with this

