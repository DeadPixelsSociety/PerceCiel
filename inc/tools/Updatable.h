/* 
 * File:   Updatable.h
 * Author: maxence
 *
 * Created on 8 décembre 2014, 17:36
 */

#ifndef UPDATABLE_H
#define	UPDATABLE_H

class Updatable {
public:
//    virtual ~Updatable();
    virtual void update(float dt) = 0;
};

#endif	/* UPDATABLE_H */

