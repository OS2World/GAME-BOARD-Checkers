# GAME-BOARD-Checkers

Version 1.1 — A 32-bit Presentation Manager checkers game for OS/2 and ArcaOS.

Originally written by Charles Petzold and published in
*Microsoft Systems Journal*, September 1990. This version is an
Open Watcom port with enhanced menus, keyboard shortcuts, 6-language
support, and settings persistence.

## Controls

| Input | Action |
|-------|--------|
| Ctrl+N | New Game |
| Ctrl+Q | Quit current game |
| Ctrl+X | Exit application |
| Ctrl+F | Frame Controls (borderless) toggle |

## Build Instructions

Requires Open Watcom C/C++ and the OS/2 Toolkit 4.5 headers.

```
compile-wat.cmd
```

Or directly:

```
wmake -f makefile.wat all
```

Output is placed in `bin\checkers.exe`.

## Project Layout

```
src/            Source files (.c, .h, .rc, .def, .ptr, .ico)
bin/            Build output (.exe, .obj, .res, .map)
doc/            Documentation (Readme.txt, Changelog.txt, LICENSE.txt)
legacy/         Original unmodified source kept for reference
makefile.wat    Open Watcom build file
compile-wat.cmd OS/2 CMD build script
```

## Changelog Summary

**1.1 (2026-09-10)** — Keyboard accelerators fixed (FCF_ACCELTABLE added);
Ctrl+F shown on menu; Frame Controls toggle rewritten after Asteroids pattern
(private object window, all four frame controls); dialog language support for
New Game dialog; window title set; Background Run removed; compiler warnings
cleared; application icon added (checkers.ico).

**1.0 (2026-09-10)** — Open Watcom port; Game/Options/Help menus;
Ctrl+N/Q/X/F shortcuts; 6-language support; 1024×768 default window;
settings persistence in OS2.INI; BLDLEVEL.

**0.40 (1990-09-01)** — Original release by Charles Petzold,
*Microsoft Systems Journal*, September 1990.

## License

GNU GPL V3 — see [doc/LICENSE.txt](doc/LICENSE.txt)

## Authors

- Charles Petzold (original author, 1990)
- Martin Iturbide (Open Watcom port, 2026)

## Links

- https://www.os2world.com/games
- https://github.com/OS2World/GAME-BOARD-Checkers
