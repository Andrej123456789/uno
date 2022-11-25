# uno++
Simple game inspired by Uno in terminal with some extra features and networking in mind

Written using C programming language mainly

Uses around 230 kilobytes of RAM (it depends how long you play)

*Repo is called `uno` because `++` couldn't fit in repo name*

[v1.0.0](https://github.com/Andrej123456789/uno/releases/tag/v1.0.0)

## Rules
[Credits](https://en.wikipedia.org/wiki/Uno_(card_game))

In short, this game mostly uses official Uno rules which you can find on link above with swap card and special mode from Crazy Games.

### Rules which are different from Uno
1. New deck will not be generated from played cards
2. If 0 is played and `Seven-O` rule is enabled, all players except player which receives other players' cards get one card because there is only one winner in the both round and match
3. There can be players how much the computer allows (segmentation fault is an issue mostly)
4. There is no `Jump-In` rule which you can find on some implementations

## TODO
- [x] Basic AI (TODO: get rid of cards guesses)
- [x] Colors
- [x] Gameplay (most of gameplay)
- [x] Networking (TODO: implement it fully)
- [ ] Nice graphics
- [x] Settings (in .json files)
- [ ] Windows port (Win32 API)

## How to compile/run?
1. Install `gcc` compiler, if you use Windows use `WSL`, `Cygwin` or `MinGW`.
2. Install `json-c` library
    - Debian based distos: `apt-get install libjson-c-dev`
    - Arch based distos: `pacman -S json-c`
    - Distors which use `yum` package manager: `yum install json-c-devel`
2. Go to `src` folder/directory and type in your terminal (emulator) `make` and then if you want run from `Makefile` (be aware that by default 
will load default config file) type in your terminal (emulator) `make run`.
3. To clean `*.o`, simply type in your terminal (emulator) `make clean`.
4. To clean everything (`*.o` files and `uno` executable) type in your terminal (emulator) `make full_clean`

## How to change settings?
- Follow next rules to see what each settings represents.
0. Points required for players to win match
1. Path of file where points will be stored
2. debug_mode [0 - disabled, 1 - enabled]
3. colors [0 - disabled, 1 - enabled]
4. number of players
5. `special`
```
[
    {
        "swap_card": [0 - disabled, 1 - enabled],
        "stacking": [0 - disabled, 1 - enabled],
        "seven_o": [0 - disabled, 1 - enabled]
    }
]
```
6. AI sequence {[0 - disabled, 1 - enabled] per player}
7. `network`
```
[
    {
        "network_sequence": {[0 - disabled, 1 - enabled] per player} // also see client.c on how to properly connect client to server,
        "ip": "127.0.0.1", // example
        "port": 5956 // example
    }
]
```

## Known issues
- `points.txt` deleted upon winning match, to fix this problem, restart program
- If you get weird letters before string, try to disable colors

If you find new issue or can't fix issues above, report issue on GitHub with needed informations.

## External dependencies/stuff
- [c-vector](https://github.com/eteran/c-vector)
- [Chatroom-in-C](https://github.com/nikhilroxtomar/Chatroom-in-C)

*One small part was made on my live stream, just search my name for YouTube channel*
