// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

// Any header files included below this line should have been created by you

#include "gamePlay.h"
#include "tiles.h"
#include "proj_utils.h"
#include "rtc.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

static int print_usage() {
  printf("<filepath - filepath of the top score file, should be the top_score.txt file in the directory with the .c files>");

  return 1;
}

int(proj_main_loop)(int argc, char *argv[]) {
    char filepath_str[256];

    if (argc != 1)
        return print_usage();

    if (sscanf(argv[0], "%s", filepath_str) != 1) {
        printf("%s: invalid string(%s)\n", __func__, argv[0]);

        return print_usage();
    }

    game_func(filepath_str);

    /*
    game* Game = create_game(filepath_str);
    ih(Game);
    destroy_game(Game);
    */
    return 0;
}
