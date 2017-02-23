# Console-fx
<big> Math I/O engine tailored for monochrome-screen devices. </big>

## General

### Description
Console-fx is a project aimed to make it possible to display mathematical formulas on monochrome screens beautifully. The
project is written in pure C++ without using any other non-standard libraries, and is designed to be built on multi-platforms.

### Usage
The engine is designed as a lib. You need to include it in you own programs, and note that you have to implement some
platform-specific functions like displaying the contents in the VRAM to screen and detecting a key event. An example
is provided in main.cpp, which uses GLFW for graphics and key processing, and integrates Eigenmath as it's calculation kernel.

More detailed, a program using the engine should be like this:
```
// File main.cpp placed in the same directory as the folder "Console".

// First you have to include standard library headers and the engine header. Generally only "console.h" is needed.
#include <iostream>
#include "Console/Headers/console.h"

// Main enterance for the program.
int main(int argc, char *argv[])
{
    // Emulated VRAM.
    unsigned char vram[VRAM_SIZE_BYTE];

    // New instance for class Console and a string as the input/output buffer.
    // Note that all classes, enums, etc., are under the namespace fx.
    fx::Console console(vram);
    fx::String buffer;
    
    // Function "ShouldExit()" need to be implemented by yourself.
    while (!ShouldExit())
    {
        console.input(buffer);                      // Get input, and store it in buffer.
        std::cout << buffer.c_str() << std::endl;   // Process the input. Here we just print it out.
        console.output(buffer);                     // Output the processed string.
    }
    
    return 0;
}

```

For even more information, the source code is always there. :-)

### Shots
There are some screen shots when I run it on my Mac.

Simple expressions go well.
![01](Shots/01.png)

... and also no problem with complex ones as follows.
![02](Shots/02.png)

## About

### License
The program is a free software. You can do anything to it with non-commercial purpose.

### Contact
Email: mango@live.cn

Feel free to ask me any questions or propose any suggestions.

