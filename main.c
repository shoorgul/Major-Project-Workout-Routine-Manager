#include <stdio.h>
#include "workout_db.h"
#include "workout_io.h"
#include "workout_plan.h"

static void print_menu(void) {
    printf("\n=== Workout Routine Manager ===\n");
    printf("1) Add routine (and exercises in one go)\n");
    printf("2) Add exercise to routine (single)\n");
    printf("3) List routines\n");
    printf("4) View routine details\n");
    printf("5) Remove routine\n");
    printf("6) Generate weekly plan\n");
    printf("7) Save data\n");
    printf("8) Load data\n");
    printf("0) Exit\n");
}

int main(void) {
    RoutineDB db;
    db_init(&db);
    load_all(&db);

    while (1) {
        print_menu();
        int ch = read_int("Choice:");

        if (ch == 1) cmd_add_routine(&db);
        else if (ch == 2) cmd_add_exercise(&db);
        else if (ch == 3) cmd_list_routines(&db);
        else if (ch == 4) cmd_view_routine(&db);
        else if (ch == 5) cmd_remove_routine(&db);
        else if (ch == 6) cmd_generate_weekly(&db);
        else if (ch == 7) {
            if (save_all(&db)) printf("Saved data.\n");
            else printf("Save failed.\n");
        }
        else if (ch == 8) {
            if (load_all(&db)) printf("Loaded data.\n");
            else printf("Load failed.\n");
        }
        else if (ch == 0) {
            save_all(&db);
            break;
        }
        else printf("Invalid choice.\n");
    }

    db_free(&db);
    return 0;
}
