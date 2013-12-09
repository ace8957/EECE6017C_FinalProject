#include "game.h"
#include "globals.h"
#include "keyboard.h"
#include "ui.h"

extern volatile int player_number;
extern int player1[total_board_size];
extern int player2[total_board_size];

/**
 * @brief take_turn - the player inputs a spot, and depending on what it is they input again or the turn is complete
 */
void take_turn() {
    int valid = 0;
    int x=0, y=0;//x and y of target
    int v1 = 0, v2 = 0, value = 0;//v1 = x 0-9, v2 = y 0-9, value = x + (10*y)
    int previous;//the previous value if correct
    int *editBoard;
    while(!valid) {
        do{
            y = getKey();
            x = getKey();
        }while(x != ONE && x != TWO && x != THREE && x != FOUR && x != FIVE && x != SIX && x != SEVEN &&
                x != EIGHT && x != NINE && x!= ZERO && y != Akey && y != Bkey && y!= Ckey && y != Dkey && y!= Ekey
                && y != Fkey && y != Gkey && y != Hkey && y != Ikey && y != Jkey);
        switch(x) {
        case ONE:
            v1 = 1;
            break;
        case TWO:
            v1 = 2;
            break;
        case THREE:
            v1 = 3;
            break;
        case FOUR:
            v1 = 4;
            break;
        case FIVE:
            v1 = 5;
            break;
        case SIX:
            v1 = 6;
            break;
        case SEVEN:
            v1 = 7;
            break;
        case EIGHT:
            v1 = 8;
            break;
        case NINE:
            v1 = 9;
            break;
        case ZERO:
            v1 = 0;
            break;
        }
        switch(y) {
        case  Akey:
            v2 = 0;
            break;
        case Bkey:
            v2 = 1;
            break;
        case Ckey:
            v2 = 2;
            break;
        case Dkey:
            v2 = 3;
            break;
        case Ekey:
            v2 = 4;
            break;
        case Fkey:
            v2 = 5;
            break;
        case Gkey:
            v2 = 6;
            break;
        case Hkey:
            v2 = 7;
            break;
        case Ikey:
            v2 = 8;
            break;
        case Jkey:
            v2 = 9;
            break;
        }
        value = x + (10 * y);
        if(player_number == player_one) editBoard = player2;
        else    editBoard = player1;
        if(editBoard[value] != hit || editBoard[value] != miss){//if valid position not picked already
            valid = 1;
        }
        if(valid)
        {
            if(editBoard[value] == water) {
                editBoard[value] = miss;
                //display message for miss
            }
            else{
                previous = editBoard[value];
                editBoard[value] = hit;//if not water by the if's should be a ship
                check_status();
                switch(previous){
                case (carrier):
                    if(editBoard[100] & (1 << 0) == 1){
                        //display carrier sunk message
                        displayMenu("You sunk enemy carrier",0);
                    }
                    break;
                case (battleship):
                    if(editBoard[100] & (1 << 1) == 1){
                        //display battleship
                        displayMenu("You sunk enemy battleship",0);
                    }
                    break;
                case (submarine):
                    if(editBoard[100] & (1 << 2) == 1){
                        //display submarine sunk
                        displayMenu("You sunk enemy submarine",0);
                    }
                    break;
                case (cruiser):
                    if(editBoard[100] & (1 << 3) == 1){
                        //display cruiser sunk
                        displayMenu("You sunk enemy cruiser",0);
                    }
                    break;
                case (destroyer):
                    if(editBoard[100] & (1 << 4) == 1) {
                        //display sunk destroyer
                        displayMenu("You sunk enemy destroyer",0);
                    }
                    break;
                }
            }
        }
    }

}

/**
 * @brief check_status - changes the status bits for both arrays to say which ships have been sunk
 */
void check_status() {
/*
    element 100 bits:
    bit	value	meaning
    -----------------------------
    0:	1		carrier sunk
    1:	2		battleship sunk
    2:	4		submarine sunk
    3:	8		cruiser sunk
    4:	16		destroyer sunk
    -----------------------------
    5:	32		carrier placed
    6:	64		battleship placed
    7:	128		submarine placed
    8:	256		cruiser placed
    9:	512		destroyer placed
    -----------------------------
    10-31;	undefined

*/
    int carrier1=0, carrier2=0, battleship1=0, battleship2=0, submarine1=0, submarine2=0, cruiser1=0,
            cruiser2=0, destroyer1=0, destroyer2=0;
    int i;
    for(i=0;i<100;i++){
        if(player1[i] == carrier) carrier1++;
        if(player2[i] == carrier) carrier2++;
        if(player1[i] == battleship) battleship1++;
        if(player2[i] == battleship) battleship2++;
        if(player1[i] == submarine) submarine1++;
        if(player2[i] == submarine) submarine2++;
        if(player1[i] == cruiser) cruiser1++;
        if(player2[i] == cruiser) cruiser2++;
        if(player1[i] == destroyer) destroyer1++;
        if(player2[i] == destroyer) destroyer2++;
    }
    if(carrier1 == 0)       player1[100] |= 1;
    if(carrier2 == 0)       player2[100] |= 1;
    if(battleship1 == 0)    player1[100] |= 1 << 1;
    if(battleship2 == 0)    player2[100] |= 1 << 1;
    if(submarine1 == 0)     player1[100] |= 1 << 2;
    if(submarine2 == 0)     player2[100] |= 1 << 2;
    if(cruiser1 == 0)       player1[100] |= 1 << 3;
    if(cruiser2 == 0)       player2[100] |= 1 << 3;
    if(destroyer1 == 0)     player1[100] |= 1 << 4;
    if(destroyer2 == 0)     player2[100] |= 1 << 4;
}


