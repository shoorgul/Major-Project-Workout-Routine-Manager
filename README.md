# Major-Project-Workout-Routine-Manager
A simple C-based Workout Routine Manager that lets you create routines, add exercises, save and load data, and generate a weekly workout plan. Built to practice dynamic memory, structs, and file handling while keeping the program useful, clean, and easy to expand
SHIKHARCHOUDHARY(590026369)
/* workout_manager.c
 *
 * A Workout Routine Manager 
 * - routines.txt stores: id|name|target_minutes
 * - exercises.txt stores: routine_id|name|sets|reps|duration_per_set_minutes
 *
 * Simple CLI:
 * 1) Add routine (and exercises immediately)
 * 2) Add exercise to existing routine
 * 3) List routines
 * 4) View routine details
 * 5) Remove routine
 * 6) Generate weekly plan (choose routines for days)
 * 7) Save data
 * 8) Load data
 * 0) Exit (saves automatically)
 */
