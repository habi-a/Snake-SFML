# Snake-SFML
![Language (C++)](https://img.shields.io/badge/powered_by-C++-blue.svg?style=flat-square) [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0)

This is a very basic classic 2D snake game made with the SFML C++ game library.

## Requirements

#### Must Have (dependencies)
- SFML 2.4.1 or above - http://www.sfml-dev.org/
##### Linux
    
     sudo apt-get install libsfml-dev
    
##### Windows
- Vist www.sfml-dev.org and download the lastest version of the library.
- In project settings,
 1. Add the `</path/to/sfml/>/include` to your **c++ include path**.
 2. Then add `</path/to/sfml/>/lib` to the **linker extra library path**.
     
 #### MS Build
 * Visual Studio 15 or above
 * VC++ 15 or above

#### Linux
 * g++ 4.8 or above
 * GNU Make
  
## Building from source

### First Method (prefered and used) MS Build

  * Download the source code.
  * Import into Visual Studio
  * Build according to your need (x64 or x86 or whatever)
   
    ```
    Don't forget to link the sfml libraries - graphics, window and system.
    put the following files in linker input:
     sfml-system-d.lib, sfml-window-d.lib, sfml-graphics-d.lib and GameMenu.lib
    ```
  * Copy the sfml dlls (window, graphics and system) along with the executable
  * Then Run and enjoy
  
### Second Method Makefile
**BUILD DON'T WORK, SEE [ISSUE#1](https://github.com/habi-a/Snake-SFML/issues/1)**

 * Download source code
 * cd to directory
  ```
   $ cd sfml-snake
  ```
 * Run make
 
  ```
   $ make
  ```
 * The exectable `snake-sfml.out` should apear.
 * Run and enjoy


## Screenshots
![Title State](http://image.noelshack.com/fichiers/2018/40/6/1538848348-1.png)
![Menu State](http://image.noelshack.com/fichiers/2018/40/7/1538917455-2.png)
![Settings State](http://image.noelshack.com/fichiers/2018/40/6/1538848349-3.png)
![Begin Game State](http://image.noelshack.com/fichiers/2018/40/6/1538848344-4.png)
![Pause State](http://image.noelshack.com/fichiers/2018/40/6/1538848347-5.png)
![Gameplay Game State](http://image.noelshack.com/fichiers/2018/40/6/1538848345-6.png)
![Game Over State](http://image.noelshack.com/fichiers/2018/40/6/1538848786-7.png)
