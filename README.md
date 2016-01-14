Chakra REPL
===========

This is a really quickly put together REPL for Microsoft's Chakra JavaScript engine.

To get this to run you will need to build ChakraCore (see [here](https://github.com/Microsoft/ChakraCore/wiki/Building-ChakraCore)), and link it to this project (`ChakraREPL.sln`) in Visual Studio. 

Copy the `ChakraCore.dll` file into `.\x64\Debug`, build the `exe`, and run it.

The reasons for this repo's existence are:
- I wanted to play around with Chakra
- Hopefully someone finds this usefull when getting started integrating ChakraCore into their software.

`ChakraREPL/ChakraREPL.cpp` is the entry point and main source file.
