# uno++
Simple game inspired by Uno with extra tweaks.

Written using C programming language and uses around 230 kilobytes of RAM.

**The name UNO is a registered trademark of its respective owner. All rights to the name, logo, and related branding are fully reserved and protected under applicable trademark laws.**

[v1.0.0](https://github.com/Andrej123456789/uno/releases/tag/v1.0.0)

[v1.1.0](https://github.com/Andrej123456789/uno_pp/releases/tag/v1.1.0)

## Rules
[Uno rules](https://en.wikipedia.org/wiki/Uno_(card_game))

In short, this game uses official Uno rules with additional house rules.

Most notable differences are those that you don't have to say word `uno` when you have only one card left; and when +2 and +4 cards are played, next player is not skipped.

## Compile

### Installing dependencies

| Package: | Command:                                                                                                                                |
| -------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| git      | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install git`</td><td>`pacman -S git`</td></tr></table>                   |
| make     | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install make`</td><td>`pacman -S make`</td></tr></table>                 |
| gcc      | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install gcc`</td><td>`pacman -S gcc`</td></tr></table>                   |
| json-c   | <table><tr><th>Debian</th><th>Arch Linux</th></tr><td>`apt-get install libjson-c-dev`</td><td>`sudo pacman -S json-c`</td></tr></table> |

### Compiling & running

| Number: | Step:                     | Command:                                              |
| ------- | ------------------------- | ----------------------------------------------------- |
| 1       | Clone a repository        | `git clone https://github.com/Andrej123456789/uno_pp` |
| 2       | Enter the `src` directory | `cd uno_pp/src`                                       |
| 3       | Compile                   | `make`                                                |
| 4       | Run the program           | `make run`                                            |

## Default settings
default.json:
```json
{
	"match_points": 250, // number of points required to win a match
	"points_path": "settings/points.json", // path to the JSON file storing points
	"players": 2, // number of players in the game [2, INT32_MAX>
	"tweaks": [{
		"colors": true, // are colors enabled
		"stacking": true, // is stacking allowed
		"swap_card": true, // is swap card present
		"seven_o": false // is SevenO house rule enabled
	}]
}
```

points.json:
```json
// reset manually after finishing a match
// otherwise, don't change these values manually
{ "Player 0": 0, "Player 1": 0 }
```

## External dependencies
- [c-vector](https://github.com/eteran/c-vector)
