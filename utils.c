#include "escape.h"

/* 
 * Function: seedRandom
 * --------------------
 * Seeds the random number generator with the current time.
 * This function should be called before using any random number generation functions.
 */
void seedRandom() {
    srand(time(NULL));
}


/* 
 * Function: randomInt
 * --------------------
 * Generates a random integer.
 *
 * range: Range of possible random values.
 *
 * Returns: Random integer.
 */
int randomInt(int max)
{
  return(rand() % max);
}
