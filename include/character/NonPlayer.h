/* 
 * File:   NonPlayer.h
 * Author: maxence
 *
 * Created on 16 octobre 2014, 17:56
 */

#ifndef NONPLAYER_H
#define	NONPLAYER_H

#include "character/Character.h"

class NonPlayer : public Character {
public:
    NonPlayer();
    NonPlayer(const NonPlayer& orig);
    virtual ~NonPlayer();
private:

};

#endif	/* NONPLAYER_H */

