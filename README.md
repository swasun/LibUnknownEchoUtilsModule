A lightweight utility library for C99 with cross-plateform features.

# Features

* byte
  * byte stream
  * byte utility
  * byte writing
  * byte reading
  * hex utility

* console
  * console color
  * progress bar
  * password input

* containers
  * byte vector
  * queue
  * string vector

* file system
  * file manipulation
  * folder manipulation

* string
  * string builder
  * string split
  * string utility

* multithreading
  * thread
  * mutex
  * condition

* time
  * current time
  * processor timestamp
  * real current time
  * sleep
  * timer measure

* safe alloc

* types
  * bool
  * ssize_t

# Installation

Clone the repository:
```bash
git clone http://github.com/swasun/LibUnknownEchoUtilsModule
```

Build in release mode:
```bash
mkdir -p build/release
cmake -Bbuild/release -H. -DCMAKE_BUILD_TYPE=Release
cd build/release
make
```

Or build in debug mode:
```bash
mkdir -p build/debug
cmake -Bbuild/debug -H. -DCMAKE_BUILD_TYPE=Debug
cd build/debug
make
```

By default, dependencies are built and install in the `build` directoy.
To install in another place, add `-DLIBEI_INSTALL=/usr` flag in `cmake` command.

To build with LIBEI already installed in the system, add `-DLIBEI_SYSTEM=TRUE` flag in `cmake` command.

Finally, to install in the system:
```bash
cd build/release
sudo make install
```

# Example

Some examples are available in `examples` directory.

```bash
./bin/release/examples/progress_bar_example
```

# Cross-plateform

Successfully tested on the following OS (on both 32 and 64 bits):
* Ubuntu 14.04
* Ubuntu 16.04
* Windows 10