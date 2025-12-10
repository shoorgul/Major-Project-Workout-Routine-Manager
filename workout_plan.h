#ifndef WORKOUT_PLAN_H
#define WORKOUT_PLAN_H

#include "workout_db.h"

typedef struct {
    int routine_id;
    int requested_minutes;
} PlanChoice;

void cmd_add_routine(RoutineDB *db);
void cmd_add_exercise(RoutineDB *db);
void cmd_generate_weekly(RoutineDB *db);

#endif
