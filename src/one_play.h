#ifndef ONE_PLAY_H
#define ONE_PLAY_H
#include "player.h"
typedef struct _round_paramenters {
	int attack;
	int direction;
	card* former_card;
	bool is_former_card_effect;
} r_params;
typedef struct _record {
	int player_id;
	int round_score;
	int total_score;
} record;
r_params* round_init(pile** draw_pile, pile** store_pile);
void free_r(r_params* r);
void if_exhausted(pile** draw_pile, pile** store_pile, int num, FILE* f, bool if_demo);
void draw_cards(r_params* r, player* current_player, pile* draw_pile, int num, FILE* f,
                bool if_figure, bool if_demo, pile** store_pile);
int valid_input(player* player1, card* former_card, r_params r, FILE* f,
                bool if_demo);  // return the valid index of the card
record* one_play(player* current_player, r_params* r, pile** draw_pile, pile** store_pile, FILE* f,
                 bool if_figure, bool if_demo, record* rec, int player_num);

record* rec_init(int player_num);

#endif
