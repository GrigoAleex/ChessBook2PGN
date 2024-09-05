#pragma once

#include "bool.h"

#define MAX_OUTPUT 102400
#include <stdio.h>

typedef struct {
    char* key;
    char* value;
} pgn_tag;

typedef struct {
    int number;
    int evaluation;
    char* move;
    char* comment;
    bool isVariant;
    bool isWhite;
} pgn_move;

typedef struct {
    pgn_tag* tags;
    int tagCount;
    pgn_move* moves;
    int moveCount;
} pgn_game;

/** PGN_TAG */
pgn_tag* pgn_tag_init(const char* key, const char* value);

/** PGN_MOVE */
pgn_move* pgn_move_init(
    const int moveNumber, 
    const int evalutation, 
    const char* move, 
    const bool isVariant, 
    const char* comment,
    const bool isWhite
);

/** PGN_GAME */
void pgn_game_init(pgn_game* game);
void pgn_game_add_tag(pgn_game* game, const pgn_tag tag);
void pgn_game_add_move(pgn_game* game, const pgn_move* move);
void pgn_game_to_file(const pgn_game* game, FILE* output);
