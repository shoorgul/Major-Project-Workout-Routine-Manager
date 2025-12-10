#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "workout_plan.h"
#include "workout_db.h"
#include "workout_io.h"

void cmd_add_routine(RoutineDB *db) {
    char name[128];
    read_line("Routine name:", name, sizeof(name));

    int mins = read_int("Target minutes:");
    if (mins <= 0) mins = 30;

    int id = add_routine(db, name, mins);
    printf("Added routine with ID %d.\n", id);

    printf("Enter exercises (blank name to finish):\n");

    while (1) {
        char ename[128];
        read_line("Exercise name:", ename, sizeof(ename));

        if (strlen(ename) == 0) break;

        int sets = read_int("Sets:");
        int reps = read_int("Reps:");
        double dur = read_double("Duration per set (minutes):");

        Routine *r = db_find_by_id(db, id);
        add_exercise(r, ename, sets, reps, dur);

        printf("Added exercise '%s'.\n", ename);
    }
}

void cmd_add_exercise(RoutineDB *db) {
    int id = read_int("Routine ID:");
    Routine *r = db_find_by_id(db, id);

    if (!r) {
        printf("Routine not found.\n");
        return;
    }

    char name[128];
    read_line("Exercise name:", name, sizeof(name));

    int sets = read_int("Sets:");
    int reps = read_int("Reps:");
    double dur = read_double("Duration per set:");

    add_exercise(r, name, sets, reps, dur);
    printf("Exercise added.\n");
}

void cmd_generate_weekly(RoutineDB *db) {
    int n = read_int("How many routines to include:");
    if (n <= 0) return;

    PlanChoice *arr = malloc(sizeof(PlanChoice) * n);

    for (int i = 0; i < n; i++) {
        arr[i].routine_id = read_int("Routine ID:");
        arr[i].requested_minutes = read_int("Minutes (0 = default):");
    }

    char fn[128] = "weekly_plan.txt";
    read_line("Output filename:", fn, sizeof(fn));
    if (strlen(fn) == 0) strcpy(fn, "weekly_plan.txt");

    FILE *f = fopen(fn, "w");

    double total = 0.0;

    printf("\n--- Weekly Plan ---\n");

    for (int i = 0; i < n; i++) {
        Routine *r = db_find_by_id(db, arr[i].routine_id);
        if (!r) continue;

        int m = arr[i].requested_minutes > 0 ?
                arr[i].requested_minutes : r->target_minutes;

        printf("%s : %d min\n", r->name, m);
        if (f) fprintf(f, "%s|%d\n", r->name, m);
        total += m;
    }

    printf("Total weekly time: %.2f minutes\n", total);
    if (f) {
        fprintf(f, "TOTAL|%.2f\n", total);
        fclose(f);
    }

    free(arr);
}
