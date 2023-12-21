#include "escape.h"
#include "utils.h"
#include "flyer.h"
#include "hero.h"
#include "connect.h"


/* 
 * Function: runEscape
 * -------------------
 * Top-level function for the server process. Initializes the escape, contains the game loop, 
 * handles escape result, and performs cleanup.
 */
void runEscape() {
    EscapeType escape;
    initEscape(&escape);

    while (!escapeIsOver(&escape)) {
        
        CLEAR_SCREEN();
        srand(time(NULL));
        for (int i = 0; i < escape.flyers.size; ++i) {
            
            moveFlyer(escape.flyers.elements[i], &escape);
        }
        
        for (int i = 0; i < escape.heroes.size; ++i) {
            moveHero(escape.heroes.elements[i], &escape);
        }
        int rate = randomInt(100);
        
        if (rate < BIRD_SPAWN_RATE) {
            
            int birdRow = randomInt(5); 
            int birdCol = randomInt(MAX_COL-1);
            int birdStrength = randomInt(3) + 3; 

            spawnFlyer(&escape, 'v', birdStrength, birdRow, birdCol); 
           
        }
        
        if (rate < MONKEY_SPAWN_RATE) {
            int monkeyRow = randomInt(MAX_ROW);
            int monkeyCol = randomInt(MAX_COL);
            int monkeyStrength = randomInt(4) + 8; 

            spawnFlyer(&escape, '@', monkeyStrength, monkeyRow, monkeyCol);
        }
        outputHollow(&escape);
        
        usleep(OUTPUT_INTERVAL);
    }
    handleEscapeResult(&escape);
    cleanupEscape(&escape);
}


/* 
 * Function: escapeIsOver
 * -----------------------
 * Determines if both heroes are dead or have escaped.
 *
 * escape: Pointer to the EscapeType structure.
 * 
 * Returns: 1 if escape is over, 0 otherwise.
 */
int escapeIsOver(EscapeType* escape) {
    
    int hero1Status = checkHeroStatus(escape->heroes.elements[0]);
    int hero2Status = checkHeroStatus(escape->heroes.elements[1]);

    return (hero1Status != HERO_ALIVE && hero2Status != HERO_ALIVE);
}


/* 
 * Function: checkHeroStatus
 * -------------------------
 * Checks the status of a game hero based on its attributes. Returns an enumeration
 * value indicating whether the hero is alive, dead, or has escaped.
 *
 * hero: A pointer to the HeroType structure representing the game hero.
 *
 * Returns:
 *   - HERO_ALIVE: The hero is alive and has not escaped.
 *   - HERO_DEAD: The hero is dead.
 *   - HERO_ESCAPED: The hero has escaped.
 */
int checkHeroStatus(HeroType* hero) {
    //printf("HERO1 "+hero->partInfo.pos.col);
    if (hero->dead) {
        
        return HERO_DEAD;
    } else if (hero->partInfo.pos.col >= MAX_COL - 1) {
        
        return HERO_ESCAPED;
    } else {
        
        return HERO_ALIVE;
    }
}


/* 
 * Function: initEscape
 * ---------------------
 * Initializes escape, including seeding PRNG, initializing the hero and flyer arrays,
 * allocating and initializing both heroes, and adding them to the heroes array.
 * Also initializes sockets and blocks until a client connection request is received.
 *
 * escape: Pointer to the EscapeType structure.
 */
void initEscape(EscapeType* escape) {
    
    //printf("initescape");
    seedRandom();
    escape->heroes.elements = NULL;
    escape->heroes.size = 0;

    escape->flyers.size = 0;
    escape->listenSocket = -1;  
    escape->viewSocket = -1;    
    
    HeroType* timmy, *harold;
    initHero(&timmy, 'T', MAX_ROW-2, "Timmy");
    initHero(&harold, 'H', MAX_ROW-2, "Harold");
    
    addHero(&escape->heroes, timmy);
    addHero(&escape->heroes, harold);
    
    setupServerSocket(&escape->listenSocket);
    
    acceptConnection(escape->listenSocket, &escape->viewSocket);
    
    //printf("Escape initialized successfully.\n");
}


/* 
 * Function: handleEscapeResult
 * ----------------------------
 * Prints out and sends to the client the outcome of the escape.
 *
 * escape: Pointer to the EscapeType structure.
 */

void handleEscapeResult(EscapeType *escape) {
    
    int hero1_dead = (escape->heroes.size > 0) ? escape->heroes.elements[0]->dead : 1;
    int hero2_dead = (escape->heroes.size > 1) ? escape->heroes.elements[1]->dead : 1;

    
    if (!hero1_dead && !hero2_dead) {
        printf("Both heroes have escaped.\n");
        
        sendData(escape->viewSocket, "Both heroes have escaped.\n");
    }
    
    else if (hero1_dead && hero2_dead) {
        printf("Both heroes are dead.\n");
        
        sendData(escape->viewSocket, "Both heroes are dead.\n");
    }
    
    else {
        HeroType *escapedHero = (hero1_dead) ? escape->heroes.elements[1] : escape->heroes.elements[0];
        HeroType *deadHero = (hero1_dead) ? escape->heroes.elements[0] : escape->heroes.elements[1];

        printf("%s has escaped!\n", escapedHero->name);
        printf("%s has died.\n", deadHero->name);

        
        char quitMessage[100];
        snprintf(quitMessage, sizeof(quitMessage), "%s has escaped! %s has died.\n", escapedHero->name, deadHero->name);
        sendData(escape->viewSocket, quitMessage);

    }
}


/* 
 * Function: cleanupEscape
 * -----------------------
 * Cleans up escape, including deallocating required memory, sending termination
 * (quit) message to the client, and closing sockets.
 *
 * escape: Pointer to the EscapeType structure.
 */

void cleanupEscape(EscapeType* escape) {
    
    for (int i = 0; i < escape->heroes.size; ++i) {
        free(escape->heroes.elements[i]);
    }
    free(escape->heroes.elements);

    for (int i = 0; i < escape->flyers.size; ++i) {
        free(escape->flyers.elements[i]);
    }
    
    close(escape->listenSocket);
    close(escape->viewSocket);

    //printf("Cleanup completed.\n");
}


/* 
 * Function: outputHollow
 * -----------------------
 * Top-level function for serializing hollow, printing, and sending it to the client.
 *
 * escape: Pointer to the EscapeType structure.
 */
void outputHollow(EscapeType* escape) {
    
    char* serializedHollow[MAX_BUFF];
    serializeHollow(escape, &serializedHollow);
    printf("%s\n", serializedHollow);
    
    sendData(escape->viewSocket, serializedHollow);
}


/* 
 * Function: viewEscape
 * ---------------------
 * Top-level function for the client process, given a server IP address.
 * Sends a connection request to the server at the given IP address, loops and
 * waits for data that it prints out, until a quit message is received.
 *
 * serverIP: IP address of the server.
 */
void viewEscape(char* serverIP) {
    int clientSocket;
    char buffer[MAX_BUFF];

    setupClientSocket(&clientSocket, serverIP);

    while (1) {
        //CLEAR_SCREEN();
        int bytesReceived = rcvData(clientSocket, buffer);

        if (bytesReceived <= 0) {
            
            //printf("Connection closed by the server.\n");
            break;
        }

        printf("%s", buffer);

    }

    close(clientSocket);
}


