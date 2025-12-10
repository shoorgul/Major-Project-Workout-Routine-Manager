SAPID:590026369
# Major-Project-Workout-Routine-Manager
A simple C-based Workout Routine Manager that lets you create routines, add exercises, save and load data, and generate a weekly workout plan. Built to practice dynamic memory, structs, and file handling while keeping the program useful, clean, and easy to expand

# Project-Structure
/
|-- src/
|     |-- main.c
|     |-- workout_db.c
|     |-- workout_io.c
|     |-- workout_plan.c
|
|-- include/
|     |-- workout_db.h
|     |-- workout_io.h
|     |-- workout_plan.h
|
|-- docs/
|     |-- project_report.pdf        (your coursework report goes here)
|     |-- flowchart.png             (system workflow diagrams)
|
|-- assets/
|     |-- screenshots/              (optional images)
|
|-- README.md
|
|-- sample_input.txt                

# FEATURES
✔ Routine Management
Add new routines (name + target duration)
Add exercises (sets, reps, duration per set)
View all routines
View details of a specific routine
Remove routines safely

✔ Exercises
Attach multiple exercises to each routine
Store repetitions, sets, and duration
Data grows dynamically — no fixed limits

✔ File Persistence
Automatically saves to:
routines.txt
exercises.txt
Load your data anytime

✔ Weekly Workout Planner
Pick routines for the week
Customize durations
Get a final summary + total weekly workout time
Export plan to a text file
