#include <stdio.h>
#include <pgn.h>

int main () {
    pgn_game game;
    pgn_game_init(&game);

    pgn_game_add_tag(&game, *pgn_tag_init("Event", "Van dam v2"));

    FILE *output = fopen("game.pgn", "w+");
    pgn_game_to_file(&game, output);

	return 0; 
}