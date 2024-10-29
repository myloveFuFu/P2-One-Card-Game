#ifndef _CARDS_H
#define _CARDS_H
#include <stdio.h>
typedef struct _cards{
        unsigned int suit; // 0: Spade, 1: Heart, 2: Diamond, 3: Club
        unsigned int rank; // 1:A, 2~10:2~10, 11:J, 12:Q, 13:K, the order:  2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K,A
        unsigned int type;// {0: normal: A,4,5,6,8,9,10,K};  attack cards{2:draw 2 cards,3:draw 3 cards}; 
                          // defense cards{7:cancel the attack};  special{12: Q  change direction, 11 : J skip the next player}
        unsigned int place; // -1: discard pile, 0: draw pile, 1 : player1, 2: player2, 3: player3, 4: player4 ...
    } cards;
void init_cards();
void assign_cards(unsigned int num_players,unsigned int num_cards);
void print_cards(unsigned int players_rank);
void cards_cmp(cards fromer , cards latter);
#endif