# One Card
## Brief Introduction
- "One Card" is a simple card game designed for multiple players, also known as Uno. 
- In this game, the number of cards each player has and their scores are calculated each round, with the player having the highest score declared the winner. 
- This project allows players to experience strategic gameplay, generates game logs, and supports a demo mode.
- The project allows the user to set the number of players, initial cards, number of decks, and rounds, and provides a demo mode for automatic play.
- The prject provides two different card mode. One in the normal mode, like `Spade Ace`, another will show the card figure, using ASCII characters and unicode characters. The normal mode will be used by default, and the figure mode can be enabled by adding the `-f` command-line parameter.

## Setup
- The project is written in C and requires a C compiler(like GCC) to compile and run.

## Game Rules
- Game Basics
    - The game consists of a predetermined number of players (n) and rounds (r). After each round, scores are tallied, and the highest score wins.
    - Each player is dealt an extra card at the start to determine the play order, which is then discarded.
    - Players take turns playing cards in a counter-clockwise direction, starting with the player holding the lowest-ranking card.
- Playing and Discarding Cards
    - At the start, the top card of the stock pile is revealed to establish the initial rank and suit.
    - Each player plays one card per turn, matching the rank or suit of the previous card.
    - If unable to play, a player must draw a card from the top of the stock pile. If the stock pile is empty, the discard pile is shuffled and used as the new stock pile.
- Winning and Scoring
    - The round ends when a player has no cards left, and the remaining players receive penalty points equal to the number of cards they hold.
    - The player who wins the round leads the next round, and the total penalty points are accumulated to determine the final winner.
- Special Card Effects
    - Attack Cards:
        - Rank 2: The next player draws two cards.
        - Rank 3: The next player draws three cards.
    - Defense Cards:
        - Rank 7: Cancels the effect of an attack (if a 2 or 3 was played before, the next player does not draw cards).
        - `note`: The defense card can only be played when attacked, and can't be treated as a regular card.
    - Action Cards:
        - Queens: Reverse the playing order.
        - Jacks: Skip the next player.
    - Regular Cards: Used only to match the rank or suit, with no special effects.
- Important Notes
    - The effects of attack cards are cumulative.
    - A Queen or Jack of the same suit as the previous card can redirect an attack to the previous player or skip the player after the next one, respectively.
    - When attacked, if a player does not play a special card (2, 3, 7, Q, J), they must draw cards before their turn ends.

### Operation Method
The project supports command-line parameters to set various game parameters and the demo mode, such as:
```
sh $ ./onecard -h
-h|--help             Print this help message
--log filename        Save logs to the specified file (default: onecard.log)
-n n|--player-number=n Set the number of players (minimum 2, default: 4)
-c c|--initial-cards=c Set initial cards per player (minimum 2, default: 5)
-d d|--decks=d       Use d decks of cards (minimum 2, default: 2)
-r r|--rounds=r      Play r rounds (minimum 1, default: 1)
-a|--auto            Run in demo mode
-f|--figure          Add a figure card mode
```
### Layer Progamming
- The project is organized in three layers.
- The first layer includes `card.h` and `init_game.h`.
  - `card.h` with its implementation file `card.c` ,`card_figure.c` and `print_card.c` defines the basic `card` and `pile` structure and the function to allow two ways to print the card.
  - `init_game.h` with its implementation file `init_game.c` defines the function to initialize the game and deal with command-line parameters.
- The second layer includes `player.h`.
  - `player.h` with its implementation file `player.c` defines the `player` structure base on `card` and `pile` structure and includes the function to allow the player to play the card and decide the first player.
- The third layer includes `one_play.h`.
  - `one_play.h` with its implementation file `one_play.c` and `one_round.c` defines the function to allow the game to play and decide the winner.
- the `tool_box.h` with its implementation file `tool_box.c` as an additional tool to help simplify the code.
