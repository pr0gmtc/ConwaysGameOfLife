# ConwaysGameOfLife
The program is a C console application that runs Conway's Game of Life, a cellular automaton
invented by the British mathematician John Horton Conway in 1970.
The game is a zero-player game which means that the program only needs an initial board input. Other interactions with a
user do not exist. During a run of the game a user can observe different patterns emerging and
changing during the evolution of the Game’s population.
More can be read about the Game of Life in this article: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

## Requirements
The program is a C console application, it should be run in the appropriate environment. A
computer needs a C compiler to build the program.


## Inputs
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

## Outputs
The program continuously outputs boards of generations of the game. The program terminates if
every cell on the board becomes dead or if the population did not change for the past 10
generations.

![Alt Text](https://media.giphy.com/media/YacMaaM6GULoEIbZAF/giphy.gif)
![Alt Text](https://media.giphy.com/media/k37XuDb20d0i7wzIh1/giphy.gif)

## Explanation
The program runs using a recursive function that calls itself providing a modified by the rules of
Conway’s Game of Life dynamic 2D array with each new generation, it allows the user to set the
initial parameters of the game and it automatically terminates in case of continuous stagnated
repeating populations or in case of the end of the whole population of cells.

## Data structures
The main data structure used in the program is a 2D dynamic array. It is used for storing the state
of the board and running the next generations based on the arrays of the previous ones. 2D
dynamic was chosen as the most appropriate data structure for this particular problem. It is also
convenient and straightforward to visualize the 2D array for showing the state of board.
Another data structure was declared for a more compact track of the board’s population -
population_track, it combines two integers: one for storing previous generations’ population and
the other one is for counting generations with repeating numbers of population.

## Functions
**print_board** - prints the board into the console and saves it in the output file. Input parameters:
number of rows and columns of the board as n, m integers, the board in the form of 2D dynamic
array.

**number_of_alive_neighbours** - returns the number of alive neighbours around a specific cell as
an integer.
Input parameters: number of rows and columns of the board as n, m integers, the board in the
form of 2D dynamic array, the coordinates of the cell in the board as i, j integers.

**total_alive_cells** - returns the total number of alive cells on the board as an integer.
Input parameters: number of rows and columns of the board as n, m integers, the board in the
form of 2D dynamic array.

**run_generation** - runs a generation according to the rules of Conway's Game of Life if there are
alive cells on the board the function will run the next generation too by recursively calling itself
or otherwise the function will terminate.
Input parameters: number of rows and columns of the board as n, m integers, the board in the
form of 2D dynamic array, is_automatic parameter as an integer, which equals to 0 or 1, that
determines if run_generation function will run the next generation automatically or only after the
press of the Enter key by the user.

**input_file_start** - starts the game with an input from the input file by calling run_generation
function for the first time after run_generation function terminates it notifies the user about the
end of the program by console print.
Input parameters: is_automatic parameter as an integer, which equals to 0 or 1, that determines if
run_generation function will run the next generation automatically or only after the press of the
Enter key by the user, the input_file_start passes this parameter to the run_generation function.

**random_board_start** - starts the game with a randomly generated board by calling
run_generation function for the first time after run_generation function terminates it notifies the
user about the end of the program by console print.
Input parameters: is_automatic parameter as an integer, which equals to 0 or 1, that determines if
run_generation function will run the next generation automatically or only after the press of the
Enter key by the user, the input_file_start passes this parameter to the run_generation function.

**main** - main menu of the program, asks the user parameters of the game, calls either
input_file_start or random_board start depending on the chosen by the user option.
