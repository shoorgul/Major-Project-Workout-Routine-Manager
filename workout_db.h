#ifndef WORKOUT_DB_H
#define WORKOUT_DB_H

#include <stddef.h>

#define NAME_LEN 128


typedef struct {
    char *name;
    int sets;
    int reps;
    double duration; 
} Exercise;


typedef struct {
    int id;
    char *name;
    int target_minutes;
    Exercise *exercises;
    size_t ex_count;
    size_t ex_cap;
} Routine;

typedef struct {
    Routine *arr;
    size_t size;
    size_t cap;
} RoutineDB;


void db_init(RoutineDB *db);
void db_free(RoutineDB *db);


int add_routine(RoutineDB *db, const char *name, int minutes);
void add_exercise(Routine *r, const char *name, int sets, int reps, double duration);
int remove_routine(RoutineDB *db, int id);

Routine *db_find_by_id(RoutineDB *db, int id);


int save_all(RoutineDB *db);
int load_all(RoutineDB *db);


void print_routine(Routine *r);


void cmd_list_routines(RoutineDB *db);
void cmd_view_routine(RoutineDB *db);
void cmd_remove_routine(RoutineDB *db);

#endif
