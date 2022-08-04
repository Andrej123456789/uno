# uno++
Simple game inspired by Uno in terminal with some extra features and networking in mind

Written using C programming language mainly

*Repo is called `uno` because `++` couldn't fit in repo name*

## TODO
- [ ] Networking
- [x] Gameplay (full gameplay)
- [x] Settings
- [x] Colors
- [x] Basic AI (TODO: get rid of cards guesses)

## How to compile/run?
1. Install `gcc` compiler, if you use Windows you can use Microsoft's C compiler but you have to add `#pragma warning(disable : 4996)` on the top of the file
and maybe something more but that you have to figure on your own, but if you don't want use Microsoft's C compiler, you can also use WSL and there install gcc.
2. Go to `src` folder/directory and type in your terminal (emulator) `make` and then if you want run from `Makefile` (be aware that by default 
will load default config file) type in your terminal (emulator) `make run`.
3. To clean `*.o`, simply type in your terminal (emulator) `make clean`.
4. To clean everything (`*.o` files and `uno` executable) type in your terminal (emulator) `make full_clean`
5. There is also a web version with some better graphics.
6. If you get segmentation faults or other runtime errors try running program again, this fixes issue when`.points.txt` is not created already and then report an issue on this GitHub repo.

## How to change settings?
- Follow next rules to see what each settings represents.
0. Points required for players to win match
1. number of players
2. special_mode [0 - disabled, 1 - enabled]
3. debug_mode [0 - disabled, 1 - enabled]
4. swap_card [0 - disabled, 1 - enabled]
5. colors [0 - disabled, 1 - enabled]
6. AI sequence {[0 - disabled, 1 - enabled] per player}, it represents if some player is AI, be aware you need to write it reversed. Example:
```txt
There are 4 players in game. Player 1 and Player 3 are AI.
Logic example:
`0101`
Reversed example (what program recognise):
`1010`
```
7. Network sequence, same as AI sequence

*One small part was made on my live stream, just search my name for YouTube channel*
