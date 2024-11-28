#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
typedef struct _player {
	int player_id;
	pile* hand_card;
	struct _player* next;
	struct _player* prev;
} player;

void fprint_player(player* p, FILE* f, bool if_demo);
player* player_init(int player_num, int card_num, pile** draw_pile, FILE* f, bool if_demo);
void free_player(player* p);
player* first_player(player* head, pile* draw_pile, pile* store_pile, FILE* F, bool if_figure);
void play_card(player* p, pile** store_pile,
               int pos);  // pos stands for the position of the card to be played
#endif
