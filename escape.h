#ifndef ESCAPE_H
#define ESCAPE_H

#include "defs.h"

void runEscape();
int escapeIsOver(EscapeType* escape);
void initEscape(EscapeType* escape);
void handleEscapeResult(EscapeType* escape);
void cleanupEscape(EscapeType* escape);
int checkHeroStatus(HeroType* hero);

void initHollow(EscapeType* escape, char hollow[MAX_ROW][MAX_COL]);
void serializeHollow(EscapeType* escape, char* serializedHollow);

void setPos(PositionType* position, int row, int col);

void viewEscape(char* serverIP);
void outputHollow(EscapeType* escape);

#endif