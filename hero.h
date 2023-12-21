#ifndef HERO_H
#define HERO_H

#include "defs.h"

void initHero(HeroType** hero, char avatar, int row, char* name);
void addHero(HeroArrayType* heroes, HeroType* hero);
void moveHero(HeroType* hero, EscapeType* escape);
int heroIsSafe(HeroType* hero);
void incurDamage(HeroType* hero, FlyerType* flyer);


#endif