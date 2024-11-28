# Changelog
## [3.2.1]- 2024-11-24
### Fixed
- Polish the code

## [3.2.0] - 2024-11-23
### Added
- Rewrite the code and add `-f` command line argument to allow a extra figure card mode.
- Add the log file to record the game result.

### Fixed
- Fixed the bug of memory and address

## [3.1.0] - 2024-11-21
### Fixed
- Fixed the bug that sending address of a local variable to the variable `temp` in `one_player` function.

## [3.0.0] - 2024-11-18
### Added
- Add the `auto` mode to run the game automatically.

### Fixed
- Fixed the bug that card with type 3 is taking effect several times.

# [2.3.0] - 2024-11-16
### Added
- Allow multiple rounds of the game.
- Add the `record` structure and to record the score of each player in each round.

## [2.2.0] - 2024-11-14
### Added
- Add the `pile` structure and some related functions.
- Add the double linked list structure to `player` to stimulate the circle behavior.
- Allow the dynamic allocation of the player hand cards.

### Fixed
- Fix the bug of failing to allocate memory for the player hand cards.


## [2.1.0] - 2024-11-12
### Added
- Allow the attack card and defense card to take effect.
- Allow to clean the screen before each round.
- Add `check_memory` function to check the memory allocation status.

### Bugs
- Didn't allocate memory for the player hand cards.It should be, more precisely, must be fixed later.

## [1.3.0] - 2024-11-9
### Added
- Add `one_round` function to simulate one round of the game.
- Allow card with type 3 to have a special effect.


## [1.2.0] - 2024-11-7
### Added
- Add a new command line argument to initialize the game with the number of players, cards, decks and rounds.
- Allow user to determine the name of log file.
- Allow to open the log file.
- open the log file in append mode.
  
### Fixed
- Fix the bug of failing to allocate memory for the log file name.

## [1.1.0] - 2024-11-5
### Added
- Add a new command line argument to initialize the game with the number of players, cards, decks and rounds.
- Allow user to determine the name of log file.
  
### Bugs
- Fail to allocate memory for the log file name.

## [1.0.0] - 2024-11-1
### Added
- Add the card struct and some related functions.
- Add the player struct and some related functions.
- Add the main function to initialize the game.