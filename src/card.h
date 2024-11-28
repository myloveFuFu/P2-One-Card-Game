#ifndef CARD_H
#define CARD_H
#include "tool_box.h"

typedef struct _card {
	int suit;  // 0: Spade, 1: Heart, 2: Diamond, 3: Club
	int rank;  // 1:A, 2~10:2~10, 11:J, 12:Q, 13:K, the order:  2, 3, 4, 5, 6, 7,
	           // 8, 9, 10, J, Q, K,A
	int type;  // -1: no card normal 0 {A,4,5,6,8,9,10,K};  attack cards 1 {2:draw
	           // 2 cards,3:draw 3 cards}; defense cards 2 {7:cancel the attack};
	           // special 3 {12: Q  change direction, 11 : J skip the next player}
} card;

typedef struct _pile {
	card* cards;
	int num_of_cards;
} pile;

// below are the functions for printing cards
// normal print card
void prt_one_card(card c);  // default without \n
void prt_pile(pile* p);
// used in card figure mode
void print_rank(card c);
void print_suit1(card c);
void print_suit2(card c);
void print_one_card(card c);  // default with \n
void print_hand_card(card* hand, int num_of_cards, int card_disp_aline);
void print_one_pile(pile* p);
// use in file
void fprint_one_card(card c, FILE* f);
void fprint_pile(pile* p, FILE* f);
// use in terminal and file depend on the situation
void print_card(card c, FILE* f, bool if_figure, bool if_demo);
void print_pile(pile* p, FILE* f, bool if_figure, bool if_demo);

bool card_cmp(card former_card, card later_card);
bool basic_cmp(card former_card, card later_card);
int can_paly(card former_card, pile* p,
             bool if_formal_card_effect);  // can't play return -1, can play return index

pile* initialise_pile(int card_num);
void free_pile(pile* p);
pile* shuffle(pile* p);
pile** if_realloc(pile** p,
                  int num);  // num stands for the number of cards to be added or removed
                             // only realloc when the number of cards when the number of cards is
                             // beyond the multiple of 64
void move_card(pile** add_pile, pile** remove_pile, int num);
// move num cards from the head of remove_pile to the tail of add_pile, num must be positive

pile* initialise_deck(int num);
#endif
