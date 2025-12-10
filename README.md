This is a small C project I built to manage workout routines from the terminal.
You can add routines, attach exercises to them, view everything in a clean format,
save your data to files, and even generate a weekly workout plan based on the routines you pick.
The whole idea was to create something that feels practical while still showing core 
C concepts like dynamic memory, structs, file handling, parsing, and building a menu-driven interface. 
Instead of keeping everything in one file or using fixed-size arrays, the program grows automatically as you add more routines and exercises./* workout_manager.c
 *
 * A Workout Routine Manager (modeled after your recipe manager).
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
