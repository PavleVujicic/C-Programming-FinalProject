#include "escape.h"
#include <stdarg.h>


/* 
 * Function: initHollow
 * ---------------------
 * Initializes 2D grid with participant avatars in current positions.
 *
 * escape: Pointer to the EscapeType structure.
 * hollow: 2D array representing the hollow grid.
 */
void initHollow(EscapeType* escape, char hollow[MAX_ROW][MAX_COL]) {
    for (int i = 0; i < MAX_ROW; ++i) {
        for (int j = 0; j < MAX_COL; ++j) {
            hollow[i][j] = ' ';  
        }
    }

    
    for (int i = 0; i < escape->heroes.size; ++i) {
        PositionType pos = escape->heroes.elements[i]->partInfo.pos;
        if (pos.row >= 0 && pos.row < MAX_ROW && pos.col >= 0 && pos.col < MAX_COL){
           hollow[pos.row][pos.col] = escape->heroes.elements[i]->partInfo.avatar; 
        }
        
    }

    
    for (int i = 0; i < escape->flyers.size; ++i) {
        PositionType pos = escape->flyers.elements[i]->partInfo.pos;
        if (pos.row >= 0 && pos.row < MAX_ROW && pos.col >= 0 && pos.col < MAX_COL) {
            hollow[pos.row][pos.col] = escape->flyers.elements[i]->partInfo.avatar;
        }
        
    }
    
    
    for (int i = 0; i < MAX_ROW; ++i) {
        hollow[i][0] = '|';          
        hollow[i][MAX_COL - 1] = '|'; 
    }

    for (int j = 0; j < MAX_COL; ++j) {
        hollow[0][j] = '-';          
        hollow[MAX_ROW - 1][j] = '-'; 
    }

    
    hollow[0][0] = '+';                        
    hollow[0][MAX_COL - 1] = '+';              
    hollow[MAX_ROW - 1][0] = '+';               
    hollow[MAX_ROW - 1][MAX_COL - 1] = '+';  


    hollow[MAX_ROW-2][0] = '=';
    hollow[MAX_ROW-2][MAX_COL-1] = '=';    
}


/* 
 * Function: serializeHollow
 * --------------------------
 * Constructs a 1D array with formatted Hollow output, containing all avatars
 * in their positions, with borders, spacing, and newlines.
 *
 * escape:          Pointer to the EscapeType structure.
 * serializedHollow: Pointer to the character array where serialized hollow will be stored.
 */

void serializeHollow(EscapeType* escape, char* serializedHollow) {
    char hollow[MAX_ROW][MAX_COL];
    initHollow(escape, hollow);

    
    int index = 0;
    for (int i = 0; i < MAX_ROW; ++i) {
        for (int j = 0; j < MAX_COL; ++j) {
            if (index < MAX_BUFF - 1) {  
                
                serializedHollow[index++] = hollow[i][j];
            } else {
                fprintf(stderr, "Error: Insufficient space in the buffer for serialization.\n");
                exit(EXIT_FAILURE);
            }
        }

        if (index < MAX_BUFF - 1) {  
            serializedHollow[index++] = '\n';
        } else {
            fprintf(stderr, "Error: Insufficient space in the buffer for serialization.\n");
            exit(EXIT_FAILURE);
        }
    }

    
    if (index < MAX_BUFF - 1) {  
        serializedHollow[index++] = '\n';
    } else {
        fprintf(stderr, "Error: Insufficient space in the buffer for serialization.\n");
        exit(EXIT_FAILURE);
    }

    
    if (escape->heroes.size > 0) {
        HeroType* firstHero = escape->heroes.elements[0];
        int requiredSize = snprintf(NULL, 0, "%s:%d", firstHero->name, firstHero->health) + 1;

        
        if (index + requiredSize < MAX_BUFF) {
            
            char* nameAndHealth = (char*)malloc(requiredSize);

            if (nameAndHealth == NULL) {
                fprintf(stderr, "Error: Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }

            
            snprintf(nameAndHealth, requiredSize, "%s:%d", firstHero->name, firstHero->health);

            for (int k = 0; k < requiredSize - 1; ++k) {
                if (index < MAX_BUFF - 1) {  
                    serializedHollow[index++] = nameAndHealth[k];
                } else {
                    fprintf(stderr, "Error: Insufficient space in the buffer for serialization.\n");
                    exit(EXIT_FAILURE);
                }
            }

            
            free(nameAndHealth);

            
            if (index < MAX_BUFF - 1) {  
                serializedHollow[index++] = '\n';
            } else {
                fprintf(stderr, "Error: Insufficient space in the buffer for serialization.\n");
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "Error: Insufficient space in the buffer for serialization.\n");
            exit(EXIT_FAILURE);
        }
    }

    
    if (escape->heroes.size > 1) {
        HeroType* secondHero = escape->heroes.elements[1];
        int requiredSize = snprintf(NULL, 0, "%s:%d", secondHero->name, secondHero->health) + 1;

        
        if (index + requiredSize < MAX_BUFF) {
            
            if (index < MAX_BUFF - 1) {  
                serializedHollow[index++] = ' ';
            } else {
                fprintf(stderr, "Error: Insufficient space in the buffer for serialization.\n");
                exit(EXIT_FAILURE);
            }

            
            char* nameAndHealth = (char*)malloc(requiredSize);

            if (nameAndHealth == NULL) {
                fprintf(stderr, "Error: Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }

            
            snprintf(nameAndHealth, requiredSize, "%s:%d", secondHero->name, secondHero->health);

            for (int k = 0; k < requiredSize - 1; ++k) {
                if (index < MAX_BUFF - 1) {  
                    serializedHollow[index++] = nameAndHealth[k];
                } else {
                    fprintf(stderr, "Error: Insufficient space in the buffer for serialization.\n");
                    exit(EXIT_FAILURE);
                }
            }

            
            free(nameAndHealth);

            
            if (index < MAX_BUFF - 1) {  
                serializedHollow[index++] = '\n';
            } else {
                fprintf(stderr, "Error: Insufficient space in the buffer for serialization.\n");
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "Error: Insufficient space in the buffer for serialization.\n");
            exit(EXIT_FAILURE);
        }
    }

    
    if (index < MAX_BUFF) {  
        serializedHollow[index] = '\0';
    } else {
        fprintf(stderr, "Error: Insufficient space in the buffer for null-termination.\n");
        exit(EXIT_FAILURE);
    }
}


/* 
 * Function: setPos
 * ----------------
 * Sets a participant's position to given row/col, with values reset
 * to the closest edge if outside of range.
 *
 * pos: Pointer to the PositionType structure.
 * row: New row position.
 * col: New column position.
 */
void setPos(PositionType* position, int row, int col) {
    position->row = (row < 0) ? 0 : (row >= MAX_ROW) ? MAX_ROW - 1 : row;
    position->col = (col < 0) ? 0 : (col >= MAX_COL) ? MAX_COL - 1 : col;
}