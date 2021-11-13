# Win-Rearrange-CXX
[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/TumbleOwlee/ws-dissector-lib/blob/master/LICENSE)
[![CMake](https://github.com/TumbleOwlee/win-rearrange-cxx/actions/workflows/cmake.yml/badge.svg)](https://github.com/TumbleOwlee/win-rearrange-cxx/actions/workflows/cmake.yml)

This tool allows to position, resize and raise/lower windows based on a given configuration. Normally this would apply on some kind of feedback. Currently it just applies the rules of the configuration in a set interval of 3 seconds. This project is only a personal test whether something like this can be done in under 1000 lines. It uses just two libraries, [Xlib](https://x.org/releases/current/doc/libX11/libX11/libX11.html) for window control and [cereal](https://uscilab.github.io/cereal/index.html) for XML parsing.
