#include "flyer.h"
#include "escape.h"
#include "utils.h"


/* 
 * Function: checkForCollision
 * ---------------------------
 * Checks if a flyer with the given position has collided with a hero,
 * and returns that hero as the return value (NULL if no collision).
 *
 * pos:    Pointer to the PositionType structure.
 * escape: Pointer to the EscapeType structure.
 * 
 * Returns: Pointer to the collided hero, or NULL if no collision.
 */
HeroType* checkForCollision(PositionType* flyerPosition, EscapeType* escape) {
    
    for (int i = 0; i < escape->heroes.size; ++i) {
        HeroType* hero = escape->heroes.elements[i];
        
        if (!hero->dead) {
           
            if (hero->partInfo.pos.row == flyerPosition->row && hero->partInfo.pos.col == flyerPosition->col) {
                hero->partInfo.avatar = '+';
                return hero;
            }
        }
    }

    
    return NULL;
}


/* 
 * Function: flyerIsDone
 * ----------------------
 * Determines if a flyer has reached the ground.
 *
 * flyer: Pointer to the FlyerType structure.
 * 
 * Returns: 1 if flyer is done, 0 otherwise.
 */
int flyerIsDone(FlyerType* flyer) {
    if(flyer->partInfo.pos.row >= MAX_ROW - 1){
        return 1;
    }
    return 0;
    //return (flyer->partInfo.pos.row >= MAX_ROW - 1);
}


/* 
 * Function: computeHeroDir
 * ------------------------
 * Computes direction (-1 for left, +1 for right, 0 for same) of the closest hero
 * that is still alive and participating. Direction is returned using parameter dir.
 *
 * escape: Pointer to the EscapeType structure.
 * flyer:  Pointer to the FlyerType structure.
 * dir:    Pointer to the integer where the direction will be stored.
 */

void computeHeroDir(EscapeType* escape, FlyerType* flyer, int* direction) {
    
    *direction = 0;

    int closestDistance = INT_MAX;
    int flyerCol = flyer->partInfo.pos.col;

    for (int i = 0; i < escape->heroes.size; ++i) {
        HeroType* hero = escape->heroes.elements[i];

        if (!hero->dead) {
            
            int distance = hero->partInfo.pos.col - flyerCol;
            if (abs(distance) < closestDistance) {
                closestDistance = abs(distance);
                *direction = (distance > 0) ? 1 : ((distance < 0) ? -1 : 0);
            }
        }
    }
}


/* 
 * Function: spawnFlyer
 * ---------------------
 * Dynamically allocates and initializes one flyer and adds it to escape's flyer collection.
 *
 * escape: Pointer to the EscapeType structure.
 * avatar: Avatar character for the flyer.
 * row:    Initial row position for the flyer.
 * col:    Initial column position for the flyer.
 * strength: Strength value for the flyer.
 */
void spawnFlyer(EscapeType* escape, char avatar, int strength, int row, int col) {
    if(escape->flyers.size< MAX_ARR){

        FlyerType* newFlyer = (FlyerType*)malloc(sizeof(FlyerType));
        newFlyer->partInfo.avatar = avatar;
        setPos(&(newFlyer->partInfo.pos), row, col);
        //newFlyer->partInfo.pos.row = row;
        //newFlyer->partInfo.pos.col = col;
        newFlyer->strength = strength;
        addFlyer(&(escape->flyers), newFlyer);
    }
}


/* 
 * Function: addFlyer
 * -------------------
 * Adds flyer to escape's flyer collection.
 *
 * flyers: Pointer to the FlyerArrayType structure.
 * flyer:  Pointer to the FlyerType structure.
 */
void addFlyer(FlyerArrayType* flyerArray, FlyerType* flyer) {
    
    if (flyerArray->size < MAX_ARR) {
        
        flyerArray->elements[flyerArray->size++] = flyer;
    }
}


/* 
 * Function: moveFlyer
 * -------------------
 * Moves a flyer based on its current position and behavior, potentially colliding
 * with heroes and affecting their health.
 *
 * flyer: A pointer to the FlyerType structure representing the flyer to be moved.
 * escape: A pointer to the EscapeType structure representing the game environment.
 */

void moveFlyer(FlyerType* flyer, EscapeType* escape) {
    
    if (flyerIsDone(flyer)) {
        return; 
    }

    if (flyer->partInfo.avatar == 'v') {
        
        flyer->partInfo.pos.row += 1; 

        int moveDirection = rand() % 3 - 1;
        flyer->partInfo.pos.col += moveDirection;
        if(flyer->partInfo.pos.col> MAX_COL-1){
            flyer->partInfo.pos.col = MAX_COL-1;
        }
        if(flyer->partInfo.pos.col< 0){
            flyer->partInfo.pos.col = 1;
        }
    } else if (flyer->partInfo.avatar == '@') {
        
        int verticalMove = rand() % 7 - 3; 
        flyer->partInfo.pos.row += verticalMove;

        int direction;
        computeHeroDir(escape, flyer, &direction);

        int horizontalMove = rand() % 3 + 1;
        flyer->partInfo.pos.col += direction * horizontalMove;
        if(flyer->partInfo.pos.col> MAX_COL-1){
            flyer->partInfo.pos.col = MAX_COL-1;
        }
        if(flyer->partInfo.pos.col< 0){
            flyer->partInfo.pos.col = 1;
        }
    }else{
        return;
    }

    HeroType* collidedHero = checkForCollision(&(flyer->partInfo.pos), escape);
    if (collidedHero != NULL) {
        
        incurDamage(collidedHero, flyer);
    }

    if (flyerIsDone(flyer)) {
        
        flyer->partInfo.avatar = ' '; 
        flyer->partInfo.pos.row = 0; 
        flyer->partInfo.pos.col = 0;
        flyer->strength = 0; 
    }
}

