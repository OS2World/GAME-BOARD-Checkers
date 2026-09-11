Checkers for OS/2 - Version 1.1
================================


OVERVIEW
--------
A 32-bit Presentation Manager checkers game for OS/2 and ArcaOS.
Originally written by Charles Petzold and published in Microsoft
Systems Journal, September 1990. This version is an Open Watcom port
with enhanced menu structure, keyboard shortcuts, multi-language
support, and settings persistence.


HOW TO PLAY
-----------
- Select Game > New Game (Ctrl+N) to choose your color and difficulty.
- Click on a piece to select it and drag or click a target square
  to move.
- The computer plays the opposite color.


DIFFICULTY LEVELS
-----------------
  Simple        Minimal look-ahead
  Beginner      Short look-ahead
  Intermediate  Medium look-ahead (default)
  Advanced      Deep look-ahead (may be slow or buggy)


CONTROLS
--------
  Ctrl+N        New Game
  Ctrl+Q        Quit current game
  Ctrl+X        Exit application
  Ctrl+F        Toggle Frame Controls (borderless mode)


MENUS
-----
  Game > New Game           Start a new game (Ctrl+N)
  Game > Quit Game          Abandon current game (Ctrl+Q)
  Game > Exit               Close the application (Ctrl+X)

  Options > Colors          Customize board and piece colors
  Options > Language        Switch display language
  Options > Save Settings on Exit
  Options > Frame Controls  Toggle title bar / menu bar (Ctrl+F)

  Help > About Checkers...  Version and author information


LANGUAGES
---------
  English, Espanol, Nederlands, Deutsch, Francais, Italiano


FILE LIST
---------
  bin\checkers.exe    The game executable
  doc\Readme.txt      This file
  doc\Changelog.txt   Change history
  doc\LICENSE.txt     BSD 3-Clause License
  src\                Source code


REQUIREMENTS
------------
  ArcaOS 5.x or OS/2 Warp 4


BUILD INSTRUCTIONS
------------------
  Requires Open Watcom C/C++ and the OS/2 Toolkit 4.5 headers.

    compile-wat.cmd

  Or directly:

    wmake -f makefile.wat all

  Output is placed in bin\checkers.exe.


DISCLAIMER
----------
This software is provided "as is" without warranty of any kind.
See doc\LICENSE.txt for the full license terms.


AUTHORS
-------
  Charles Petzold   (original author, 1990)
  Martin Iturbide   (Open Watcom port and enhancements, 2026)
