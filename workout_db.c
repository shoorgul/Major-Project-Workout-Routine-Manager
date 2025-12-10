#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "workout_db.h"
#include "workout_io.h"

#define INITIAL_CAP 8
static const char ROUTINES_FILE[] = "routines.txt";
static const char EXERCISES_FILE[] = "exercises.txt";


static void *xmalloc(size_t n) {
    void *p = malloc(n);
    if (!p) { fprintf(stderr, "Memory allocation failed\n"); exit(1); }
    return p;
}
static char *xstrdup(const char *s) {
    char *p = xmalloc(strlen(s) + 1);
    strcpy(p, s);
    return p;
}

void db_init(RoutineDB *db) {
    db->arr = NULL;
    db->size = 0;
    db->cap = 0;
}

void db_free(RoutineDB *db) {
    if (!db) return;

    for (size_t i = 0; i < db->size; i++) {
        Routine *r = &db->arr[i];
        free(r->name);
        for (size_t j = 0; j < r->ex_count; j++) {
            free(r->exercises[j].name);
        }
        free(r->exercises);
    }
    free(db->arr);
}

static void ensure_db_cap(RoutineDB *db) {
    if (db->size < db->cap) return;
    size_t newcap = db->cap == 0 ? INITIAL_CAP : db->cap * 2;
    db->arr = realloc(db->arr, newcap * sizeof(Routine));
    db->cap = newcap;
}

static void ensure_ex_cap(Routine *r) {
    if (r->ex_count < r->ex_cap) return;
    size_t newcap = r->ex_cap == 0 ? INITIAL_CAP : r->ex_cap * 2;
    r->exercises = realloc(r->exercises, newcap * sizeof(Exercise));
    r->ex_cap = newcap;
}

static int next_id(RoutineDB *db) {
    int max = 0;
    for (size_t i = 0; i < db->size; i++)
        if (db->arr[i].id > max) max = db->arr[i].id;
    return max + 1;
}

Routine *db_find_by_id(RoutineDB *db, int id) {
    for (size_t i = 0; i < db->size; i++)
        if (db->arr[i].id == id) return &db->arr[i];
    return NULL;
}

int add_routine(RoutineDB *db, const char *name, int target_minutes) {
    ensure_db_cap(db);

    Routine r;
    r.id = next_id(db);
    r.name = xstrdup(name);
    r.target_minutes = target_minutes;
    r.exercises = NULL;
    r.ex_count = 0;
    r.ex_cap = 0;

    db->arr[db->size++] = r;
    return r.id;
}

void add_exercise(Routine *r, const char *name, int sets, int reps, double duration) {
    ensure_ex_cap(r);

    Exercise e;
    e.name = xstrdup(name);
    e.sets = sets;
    e.reps = reps;
    e.duration = duration;

    r->exercises[r->ex_count++] = e;
}

int remove_routine(RoutineDB *db, int id) {
    size_t idx = (size_t)-1;

    for (size_t i = 0; i < db->size; i++) {
        if (db->arr[i].id == id) { idx = i; break; }
    }
    if (idx == (size_t)-1) return 0;

    Routine *r = &db->arr[idx];
    free(r->name);
    for (size_t j = 0; j < r->ex_count; j++) free(r->exercises[j].name);
    free(r->exercises);

    for (size_t i = idx; i + 1 < db->size; i++)
        db->arr[i] = db->arr[i + 1];

    db->size--;
    return 1;
}

int save_all(RoutineDB *db) {
    FILE *fr = fopen(ROUTINES_FILE, "w");
    if (!fr) return 0;

    FILE *fe = fopen(EXERCISES_FILE, "w");
    if (!fe) { fclose(fr); return 0; }

    for (size_t i = 0; i < db->size; i++) {
        Routine *r = &db->arr[i];
        fprintf(fr, "%d|%s|%d\n", r->id, r->name, r->target_minutes);

        for (size_t j = 0; j < r->ex_count; j++) {
            Exercise *e = &r->exercises[j];
            fprintf(fe, "%d|%s|%d|%d|%.3f\n",
                r->id, e->name, e->sets, e->reps, e->duration);
        }
    }

    fclose(fr);
    fclose(fe);
    return 1;
}

int load_all(RoutineDB *db) {
    db_free(db);
    db_init(db);

    FILE *fr = fopen(ROUTINES_FILE, "r");
    if (!fr) return 0;

    char line[256];

    while (fgets(line, sizeof(line), fr)) {
        trimnl(line);

        int id, mins;
        char name[NAME_LEN];

        if (sscanf(line, "%d|%127[^|]|%d", &id, name, &mins) == 3) {
            ensure_db_cap(db);
            Routine r;
            r.id = id;
            r.name = xstrdup(name);
            r.target_minutes = mins;
            r.exercises = NULL;
            r.ex_count = 0;
            r.ex_cap = 0;

            db->arr[db->size++] = r;
        }
    }
    fclose(fr);

    FILE *fe = fopen(EXERCISES_FILE, "r");
    if (!fe) return 1;

    while (fgets(line, sizeof(line), fe)) {
        trimnl(line);
        int rid, sets, reps;
        double duration;
        char ename[NAME_LEN];

        if (sscanf(line, "%d|%127[^|]|%d|%d|%lf", &rid, ename, &sets, &reps, &duration) == 5) {
            Routine *r = db_find_by_id(db, rid);
            if (r) add_exercise(r, ename, sets, reps, duration);
        }
    }
    fclose(fe);

    return 1;
}

void print_routine(Routine *r) {
    printf("Routine ID: %d\n", r->id);
    printf("Name      : %s\n", r->name);
    printf("Target min: %d\n", r->target_minutes);
    printf("Exercises:\n");

    for (size_t i = 0; i < r->ex_count; i++) {
        Exercise *e = &r->exercises[i];
        printf("  %2zu) %-20s | Sets:%2d | Reps:%2d | %.2f min/set\n",
               i + 1, e->name, e->sets, e->reps, e->duration);
    }
}

void cmd_list_routines(RoutineDB *db) {
    printf("\n--- Routines ---\n");
    if (db->size == 0) {
        printf("No routines found.\n");
        return;
    }
    for (size_t i = 0; i < db->size; i++) {
        Routine *r = &db->arr[i];
        printf("%d) %s (target %d min, %zu exercises)\n",
               r->id, r->name, r->target_minutes, r->ex_count);
    }
}

void cmd_view_routine(RoutineDB *db) {
    int id = read_int("Routine ID:");
    Routine *r = db_find_by_id(db, id);

    if (!r) {
        printf("Routine not found.\n");
        return;
    }

    print_routine(r);
}

void cmd_remove_routine(RoutineDB *db) {
    int id = read_int("Routine ID to remove:");
    if (remove_routine(db, id))
        printf("Routine removed.\n");
    else
        printf("Routine not found.\n");
}
