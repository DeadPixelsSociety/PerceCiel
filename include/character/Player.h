/* 
 * File:   Player.h
 * Author: maxence
 *
 * Created on 16 octobre 2014, 17:54
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "character/Character.h"

class Player : public Character {
public:
    Player();
    Player(const Player& orig);
    virtual ~Player();
private:

};

#endif	/* PLAYER_H */

