# Win-Rearrange-CXX
[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/TumbleOwlee/ws-dissector-lib/blob/master/LICENSE)
[![Unix](https://github.com/TumbleOwlee/win-rearrange-cxx/actions/workflows/unix.yml/badge.svg)](https://github.com/TumbleOwlee/win-rearrange-cxx/actions/workflows/unix.yml)
[![Windows](https://github.com/TumbleOwlee/win-rearrange-cxx/actions/workflows/windows.yml/badge.svg)](https://github.com/TumbleOwlee/win-rearrange-cxx/actions/workflows/windows.yml)

This tool allows to position, resize and raise/lower windows on the stack based on a given configuration. Normally you would trigger that based on some feedback. Currently it just applies the rules of the configuration in a set interval of 10 seconds.

I created this project because I had to fix issues in a code base at my workplace that provided the same functionality but was way more complex. I got the feeling its way too overengineered. Thus, I took the time to implement it as a quick side project to check whether the huge code base at work was really necessary.
The project uses two libraries, [Xlib](https://x.org/releases/current/doc/libX11/libX11/libX11.html) for window control and [cereal](https://uscilab.github.io/cereal/index.html) for XML parsing. As you can see, the code base of this project is small and quick to understand.
