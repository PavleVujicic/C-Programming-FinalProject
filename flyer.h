#ifndef FLYER_H
#define FLYER_H

#include "defs.h"

void spawnFlyer(EscapeType* escape, char avatar, int strength, int row, int col);
void addFlyer(FlyerArrayType* flyerArray, FlyerType* flyer);
void moveFlyer(FlyerType* flyer, EscapeType* escape);
void computeHeroDir(EscapeType* escape, FlyerType* flyer, int* direction);
int flyerIsDone(FlyerType* flyer);
HeroType* checkForCollision(PositionType* position, EscapeType* escape);

#endif