Chakra REPL
===========

This is a really quickly put together REPL for Microsoft's Chakra JavaScript engine.

![REPL](https://raw.githubusercontent.com/DerFlatulator/ChakraREPL/master/chakra-repl.png)

To get this to run you will need to build ChakraCore (see [here](https://github.com/Microsoft/ChakraCore/wiki/Building-ChakraCore)), and link it to this project (`ChakraREPL.sln`) in Visual Studio. 

Build this project's `exe`, copy `ChakraCore.dll` file into `.\x64\Debug`, and run the `exe`.

[`ChakraREPL/ChakraREPL.cpp`](https://github.com/DerFlatulator/ChakraREPL/blob/master/ChakraREPL/ChakraREPL.cpp) is the entry point and main source file.

The reasons for this repo's existence are:
- I wanted to play around with Chakra.
- Hopefully someone finds this useful when getting started integrating ChakraCore into their software.


