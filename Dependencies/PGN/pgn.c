#include "pgn.h"

#include "string.h"
#include "stdlib.h"
#include "stdio.h"


/** PGN_TAG */

pgn_tag* pgn_tag_init(const char* key, const char* value) {
    pgn_tag* tag = malloc(sizeof(pgn_tag));
    if (tag == NULL) exit(1); // TODO: HANDLE ERROR

    tag->key = _strdup(key);
    tag->value = _strdup(value);
    return tag;
}

/** PGN_MOVE */

pgn_move* pgn_move_init(const int moveNumber, const int evalutation, const char* move, const bool isVariant, const char* comment, const bool isWhite) {
    pgn_move* newMove = malloc(sizeof(pgn_move));
    if (newMove == NULL) exit(1); // TODO: HANDLE ERROR

    newMove->number = moveNumber;
    newMove->evaluation = evalutation;
    newMove->move = _strdup(move);
    newMove->isVariant = isVariant;
    newMove->comment = _strdup(comment);
    newMove->isWhite = isWhite;

    return newMove;
}

/** PGN_GAME */

void pgn_game_init(pgn_game* game) {
    game->tags = NULL;
    game->tagCount = 0;
    game->moves = NULL;
    game->moveCount = 0;
}

void pgn_game_add_tag(pgn_game* game, const pgn_tag tag) {
    pgn_tag* tmp = (pgn_tag*)realloc(game->tags, sizeof(pgn_tag) * (game->tagCount + 1));
    if (tmp == NULL) exit(1); // TODO: HANDLE ERROR
    
    game->tags = tmp;
    game->tags[game->tagCount] = tag;
    game->tagCount++;
}

void pgn_game_add_move(pgn_game* game, const pgn_move* move) {
    pgn_move* tmp = (pgn_move*)realloc(game->moves, sizeof(pgn_move) * (game->moveCount + 1));
    if (tmp == NULL) exit(1); // TODO: HANDLE ERROR

    game->moves = tmp;
    game->moves[game->moveCount] = *move;
    game->moveCount++;
}

void pgn_game_to_file(const pgn_game* game, FILE * output) {
    for (int i = 0; i < game->tagCount; i++) {
        fprintf(output, "[%s \"%s\"]\n", game->tags[i].key, game->tags[i].value);
    }
    fprintf(output, "\n");

    bool startedVariant = FALSE;
    bool lastMoveHadComment = FALSE;
    for (int i = 0; i < game->moveCount; i++) {
        pgn_move move = game->moves[i];

        if (move.isVariant && !startedVariant) {
            fprintf(output, " ( ");
            startedVariant = TRUE;
        }
        else if (!move.isVariant && startedVariant) {
            fprintf(output, " ) ");
            startedVariant = FALSE;
        }

        if (move.isWhite) {
            fprintf(output, " %d.", move.number);
        }
        else if (lastMoveHadComment) {
            fprintf(output, "%d...", move.number);
        }
        fprintf(output, " %s", move.move);

        if (move.evaluation > 0) {
            fprintf(output, " $%d", move.evaluation);
        }

        if (move.comment != NULL) {
            fprintf(output, " { %s } ", move.comment);
        }

        lastMoveHadComment = move.comment != NULL;
    }

    if (startedVariant) {
        fprintf(output, " ) ");
        startedVariant = FALSE;
    }

}


