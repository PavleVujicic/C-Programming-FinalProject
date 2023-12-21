#include "hero.h"
#include "utils.h"
#include "flyer.h"


/* 
 * Function: initHero
 * -------------------
 * Dynamically allocates and initializes one hero.
 *
 * hero:   Pointer to the HeroType pointer.
 * avatar: Avatar character for the hero.
 * health: Initial health value for the hero.
 * name:   Name of the hero.
 */
void initHero(HeroType **hero, char avatar, int row, char *name) {
    *hero = (HeroType *)malloc(sizeof(HeroType));

    if (*hero == NULL) {
        perror("Failed to allocate memory for hero");
        exit(EXIT_FAILURE);
    }

    (*hero)->partInfo.avatar = avatar;
    (*hero)->partInfo.pos.row = row;
    (*hero)->partInfo.pos.col = randomInt(4);  
    strncpy((*hero)->name, name, MAX_STR - 1);
    (*hero)->name[MAX_STR - 1] = '\0'; 

    (*hero)->health = MAX_HEALTH;
    (*hero)->dead = C_FALSE;
}


/* 
 * Function: heroIsSafe
 * ---------------------
 * Determines if a hero has successfully escaped the Hollow.
 *
 * hero: Pointer to the HeroType structure.
 * 
 * Returns: 1 if hero is safe, 0 otherwise.
 */
int heroIsSafe(HeroType *hero) {
    
    return (hero->partInfo.pos.col >= MAX_COL-1);
}


/* 
 * Function: incurDamage
 * ---------------------
 * Decreases hero's health by flyer's strength (if health gets negative, reset to 0).
 * If hero dies, its avatar is changed.
 *
 * hero:  Pointer to the HeroType structure.
 * flyer: Pointer to the FlyerType structure.
 */
void incurDamage(HeroType* hero, FlyerType* flyer) {
    
    hero->health -= flyer->strength;

    if (hero->health < 0) {
        hero->health = 0;
    }

    if (hero->health == 0) {
        
        hero->dead = C_TRUE;
        hero->partInfo.avatar = '+';
        //printf("%s has died!\n", hero->name);
    }
}


/* 
 * Function: addHero
 * ------------------
 * Adds hero to escape's hero collection.
 *
 * heroes: Pointer to the HeroArrayType structure.
 * hero:   Pointer to the HeroType structure.
 */
void addHero(HeroArrayType *heroes, HeroType *hero) {
    heroes->elements = (HeroType **)realloc(heroes->elements, (heroes->size + 1) * sizeof(HeroType *));

    if (heroes->elements == NULL) {
        perror("Failed to reallocate memory for heroes array");
        exit(EXIT_FAILURE);
    }

    heroes->elements[heroes->size++] = hero;
}


/* 
 * Function: moveHero
 * -------------------
 * Computes hero's next move in accordance with instruction 3.4 and updates the hero's position.
 *
 * hero:   Pointer to the HeroType structure.
 * escape: Pointer to the EscapeType structure.
 */

void moveHero(HeroType *hero, EscapeType *escape) {
    if (hero->dead || heroIsSafe(hero)) {
        return;  
    }

    int moveProbability = randomInt(100);
    int moveDirection;

    if (hero->partInfo.avatar == 'T') {
        
        if (moveProbability < 50) {
            
            moveDirection = DIR_RIGHT+1;
        } else if (moveProbability < 80) {
            
            moveDirection = DIR_LEFT;
        } else {
            
            moveDirection = DIR_RIGHT;
        }
    } else if (hero->partInfo.avatar== 'H') {
        
        if (moveProbability < 20) {
            
            moveDirection = DIR_NONE;
        } else if (moveProbability < 30) {
            
            moveDirection = DIR_RIGHT * 5;
        } else if (moveProbability < 40) {
            
            moveDirection = DIR_LEFT * 4;
        } else if (moveProbability < 80) {
            
            moveDirection = DIR_RIGHT * 3;
        } else {
            
            moveDirection = DIR_LEFT * 2;
        }
    } else {
        return;
        
    }

    int newCol = hero->partInfo.pos.col + moveDirection;

    if (newCol < 0) {
        newCol = 0;
    } else if (newCol >= MAX_COL) {
        newCol = MAX_COL - 1;
    }

    hero->partInfo.pos.col = newCol;
}

