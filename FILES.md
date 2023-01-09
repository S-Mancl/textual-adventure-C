# Files in this repo
* ./
1. FILES.md: is the current file
2. README.md: a brief description of the project
3. Windows.bat: a bat file for compiling and execute (in debug mode) on Windows
4. makefile: does this really need description?
5. runDebug: a shellscript that runs make and then executes (in debug mode) the executable
6. txt.c: the C file containing main and almost nothing more
* ./src/headers/headers/\*.h are the headers needed for the program to work properly
1. interface.h contains the CLI prototypes
2. NewFunctions.h contains the basic textual adventure prototypes
3. NewInteractions.h contains the prototypes for interactions with other characters
4. data.h are constants
5. structures.h and characters.h contain the main structures used in the project
* ./src/headers/implementation/\*.c contains the implementations of the headers above
* ./src/txts/data contains the files with all the data needed to run the adventure
1. data.txt contains the settings, encounters, items and spells
2. questions.txt contains the questions (and the answers) that are asked in encounters
3. randenc.txt contains the description paragraphs for the random encounters
* ./src/txts/savefiles/\*.txt are savefiles from previous games
