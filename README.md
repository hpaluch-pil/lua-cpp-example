# Embedding LUA into C/C++ program

Here is trivial example how to embed LUA into your C/C++ program.

Thre are implemented 2 custom commands available from LUA:

1. Command `uname_machine()` that returns
   machine name from [uname(2)](https://manpages.debian.org/stretch/manpages-dev/uname.2.en.html) system call.

1. Command `uptime_seconds()` that returns
   number of seconds from system start (uptime) from
   [sysinfo(2)](https://manpages.debian.org/stretch/manpages-dev/sysinfo.2.en.html) system call.


> NOTE:
>
> There is also [TCL Version](https://github.com/hpaluch-pil/tcl-cpp-example)
> of this example for comparison.
> 

# Setup

Tested OS:
```bash
echo `lsb_release -sd` - `uname -m`
   Debian GNU/Linux 9.9 (stretch) - x86_64
```

Install following required packages:

```bash
sudo apt-get install build-essential git valgrind \
     liblua5.3-0 liblua5.3-dev liblua5.3-0-dbg
```

Optional: Install Eclipse with CDT (C/C++ development support):

```bash
sudo apt-get install eclipse-cdt
```

TODO: import to Eclipse

# Building example

Just invoke:

```bash
make
```

# Running example

To run example just invoke:

```bash
make run
```

Following examples are run:

```lua
print('Hello, world on ' .. uname_machine() .. '!')
print('System uptime is ', uptime_seconds() ,' seconds.')
```

should produce output like:

```
Hello, world on x86_64!
System uptime is        5257     seconds.
```

> NOTE: That LUA's `print` function uses Tab instead of space
> to format arguments. Please
> see discussion at https://stackoverflow.com/a/48645420

To run example with `valgrind(1)` memory leak detector use:

```bash
make valgrind
```

There should be no leaks reported.

# Resources

* [LUA crash course](http://tylerneylon.com/a/learn-lua/)
* [LUA C API - 1st example](https://www.lua.org/pil/24.1.html) - unfortunately
  a bit out-of-date...
* [Calling C function from LUA](https://www.lua.org/pil/26.1.html)  
* [Embedding Tcl into C/C++ program](https://github.com/hpaluch-pil/tcl-cpp-example)

