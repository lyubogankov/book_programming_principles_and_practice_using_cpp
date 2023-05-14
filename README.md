## Slowly going through the book!

## Notes to self


#### Basic compilation
```
g++ -o [exe_name].exe [file].cpp   // if particular name is desired
g++ [file].cpp                     // default executable name 'a.out'
```

Can also specify multiple files if they're part of the same project!


#### Compilation using a specific C++ standard
```
g++ [file].cpp -std=c++11
```
Possible values: `c++11`, `c++14`, `c++17`, `c++20`.


#### Debugging

##### Compilation for debugging

```
g++ [file.cpp] [other flag(s)] -g
```

##### Running `gdb`

[Guide](https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_gdb.php)

Basic commands:
- `break {func name}` to set breakpoint
- `run` to start the program
- `continue` / `cont` to continue execution from current breakpoint
- `next` / `n` to run next line
- `print {variable}`


#### Textbook resources
- https://www.stroustrup.com/programming.html
- https://www.stroustrup.com/programming_support.html

#### I found other people that have gone on a similar journey -- can cross-check solutions with them!

- https://github.com/bewuethr/stroustrup-ppp
- https://github.com/Chrinkus/stroustrup-ppp

#### Using `g++` on WIndows

I found [MinGW-w64](https://www.mingw-w64.org/) and installed the [WinLibs standalone build](https://winlibs.com/).  I installed the "UCRT" version (between UCRT and MSVCRT) and permanently added the path to the `bin` folder to my `PATH` environment variable, and from there can use `g++` like on Linux!