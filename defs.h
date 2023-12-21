#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <limits.h>


#define DEBUG 0
#define DIR_NONE 0
#define MIN_PORT            60001
#define MAX_PORT            60010

#define MAX_ROW                15
#define MAX_COL                60
#define MAX_HEALTH             20
#define MAX_STR                32
#define MAX_ARR               128
#define MAX_BUFF             4096

#define C_TRUE                  1
#define C_FALSE                 0

#define BIRD_SPAWN_RATE        80
#define MONKEY_SPAWN_RATE      40
#define OUTPUT_INTERVAL    200000

#define DIR_LEFT               -1
#define DIR_SAME                0
#define DIR_RIGHT               1
#define MAX_DISTANCE 999999
#define MAX_DISTANCE_SQUARED 1.0e+74
#define HERO_ALIVE 1
#define HERO_DEAD 0
#define HERO_ESCAPED 2
#define CLEAR_SCREEN() printf("\033[2J")
#define BUFFER_SIZE 100

typedef struct {
  int  row;
  int  col;
} PositionType;

typedef struct {
  char         avatar;
  PositionType pos;
} ParticipantType;

typedef struct {
  ParticipantType partInfo;
  char name[MAX_STR];
  int  health;
  int  dead;
} HeroType;

typedef struct {
  ParticipantType partInfo;
  int strength;
} FlyerType;

typedef struct {
  HeroType **elements;
  int       size;
} HeroArrayType;

typedef struct {
  FlyerType *elements[MAX_ARR];
  int       size;
} FlyerArrayType;

typedef struct {
  HeroArrayType   heroes;
  FlyerArrayType  flyers;
  int             listenSocket;
  int             viewSocket;
} EscapeType;

#endif

