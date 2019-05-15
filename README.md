# Embedding LUA into C/C++ program

Here is trivial example how to embedd LUA into your C/C++ program.

# Setup

Tested OS: `Debian9.9 (Stretch)/amd64`

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
TODO:
```

should produce output like:

```
TODO
```


To run example with `valgrind(1)` memory leak detector use:

```bash
make valgrind
```


# Resources

* [http://tylerneylon.com/a/learn-lua/](LUA crash course)
* [https://www.lua.org/pil/24.1.html](LUA C API - 1st example) - unfortunately
  a bit outdated...


