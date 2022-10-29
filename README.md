# uno++
Simple game inspired by Uno in terminal with some extra features and networking in mind

Written using C programming language mainly

*Repo is called `uno` because `++` couldn't fit in repo name*

## Rules
[Credits](https://en.wikipedia.org/wiki/Uno_(card_game))

In short, this game uses official uno rules which you can find on link above with swap card and special mode from Crazy Games.

## TODO
- [x] Basic AI (TODO: get rid of cards guesses)
- [x] Colors
- [x] Gameplay (most of gameplay)
- [ ] Networking
- [ ] Nice graphics
- [ ] Nice graphics (in .png, .jpg or .svg format)
- [x] Settings (both in .txt and .json files)

## How to compile/run?
1. Install `gcc` compiler, if you use Windows use `WSL`, `Cygwin` or `MinGW`.
2. Install `json-c` library
    - Debian based distos: `apt-get install libjson-c-dev`
    - Arch based distos: `pacman -S json-c`
2. Go to `src` folder/directory and type in your terminal (emulator) `make` and then if you want run from `Makefile` (be aware that by default 
will load default config file) type in your terminal (emulator) `make run`.
3. To clean `*.o`, simply type in your terminal (emulator) `make clean`.
4. To clean everything (`*.o` files and `uno` executable) type in your terminal (emulator) `make full_clean`

## How to change settings?
- Follow next rules to see what each settings represents.
0. Points required for players to win match
1. number of players
2. special_mode [0 - disabled, 1 - enabled]
3. debug_mode [0 - disabled, 1 - enabled]
4. swap_card [0 - disabled, 1 - enabled]
5. colors [0 - disabled, 1 - enabled]
6. AI sequence {[0 - disabled, 1 - enabled] per player}]
7. Network sequence, same as AI sequence

## Known issues
- `points.txt` deleted upon winning match, to fix this problem, restart program

*One small part was made on my live stream, just search my name for YouTube channel*
