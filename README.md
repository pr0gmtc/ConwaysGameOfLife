# ConwaysGameOfLife

Conway’s Game of Life
User’s Manual

Goal of the program

The program is a C console application that runs Conway's Game of Life, a cellular automaton
invented by the British mathematician John Horton Conway in 1970. The game is a zero-player
game which means that the program only needs an initial board input. Other interactions with a
user do not exist. During a run of the game a user can observe different patterns emerging and
changing during the evolution of the Game’s population.


Requirements

The program is a C console application, it should be run in the appropriate environment. A
computer needs a C compiler to build the program.


Inputs

The program allows the user to determine the initial state of the game by taking the input file that
they provide or by creating a random initial state of the game if the user chooses the latter option.
The user should decide between the two options by entering 1 or 2 accordingly.
The input file should be filled accordingly to the following input conventions: the first row of the
input file is the size of the board, numbers of rows and columns, two numbers separated by a
whitespace character. Then the board itself, it should be of the entered size and every cell of the
board should be specified by a 0 or 1. 0 means that the cell is empty or dead and 1 means that the
cell is alive.
Another parameter that the user gets to decide is how exactly the program runs the generations -
step by step, requiring press of the Enter key each time to go to the next generation, or
automatically, every certain time interval. The user should decide between the two options by
entering 1 or 2 accordingly.
The third parameter is the size of the board, the user is required to enter the number of rows and
columns of the board.


Outputs

The program continuously outputs boards of generations of the game. The program terminates if
every cell on the board becomes dead or if the population did not change for the past 10
generations.
