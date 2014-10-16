/* 
 * File:   Mob.h
 * Author: maxence
 *
 * Created on 16 octobre 2014, 17:56
 */

#ifndef MOB_H
#define	MOB_H

#include "character/NonPlayer.h"

class Mob : public NonPlayer {
public:
    Mob();
    Mob(const Mob& orig);
    virtual ~Mob();
private:

};

#endif	/* MOB_H */

