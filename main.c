#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

//is used for terminating program if the population stays stagnant for multiple generations
struct population_track {
    int previous_generation_population;
    int number_of_stagnant_generations;
};

//prints the board into console and saves it in the output file
void print_board(int n, int m, int board[n][m])
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    FILE *board_output_file;

    board_output_file = fopen("board_output.txt", "w");

    //checks for file
    if(board_output_file == NULL) {
      printf("Error!");
      exit(1);
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(board[i][j]) {
                //sets color to a different one, so it's easier to see alive cells
                SetConsoleTextAttribute(hConsole, 863);
            }

            printf("%d ", board[i][j]);

            //back to the default color option
            SetConsoleTextAttribute(hConsole, 15);
            //copy current board to the output file
            fprintf(board_output_file, "%d ", board[i][j]);
            //start printing from a new line if the number of characters per line
            //equals to number of columns in the board
            if(j == m-1) {
                printf("\n");
                fprintf(board_output_file, "\n");
            }
        }
    }
    printf("\nPopulation: %d", total_alive_cells(n, m, board));
    printf("\n\n\n\n\n\n\n");
}

//returns the number of alive neighbours around a specific cell
//takes the board parameters and the coordinates of the cell in the board as arguments
int number_of_alive_neighbours(int n, int m, int board[n][m], int i, int j)
{
    int alive_neighbours_cnt = 0;

    if(i - 1 >= 0) {
        if(j - 1 >= 0) {
            alive_neighbours_cnt += board[i-1][j-1];
            alive_neighbours_cnt += board[i][j-1];
        }
        alive_neighbours_cnt += board[i-1][j];
        if(j + 1 < m) {
            alive_neighbours_cnt += board[i-1][j+1];
            alive_neighbours_cnt += board[i][j+1];

        }
    }
        if(i + 1 < n) {
            if(j - 1 >= 0) {
                alive_neighbours_cnt += board[i+1][j-1];
            }
            alive_neighbours_cnt += board[i+1][j];
            if(j + 1 < m) {
                alive_neighbours_cnt += board[i+1][j+1];
            }
    }

    return alive_neighbours_cnt;
}

//returns the total number of alive cells on the board
int total_alive_cells(int n, int m, int board[n][m])
{
    int total_cnt = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            total_cnt += board[i][j];
        }
    }

    return total_cnt;
}

//runs a generation according to the rules of Conway's Game of Life
//if there are alive cells on the board the function will run
//the next generation too otherwise by recursively calling itself
//otherwise the function will terminate
void run_generation(int n, int m, int board[n][m], int is_automatic, struct population_track *p_track)
{
    int *next_generation_board = (int *)malloc(n*m*sizeof(int));

    print_board(n, m, board);

    //all the conditions are written in accordance with the rules of Conway's Game of life
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(board[i][j]) {
                if(number_of_alive_neighbours(n,m,board,i,j) == 2 || number_of_alive_neighbours(n,m,board,i,j) == 3)
                    *(next_generation_board + i*m + j) = 1;
                else *(next_generation_board + i*m + j) = 0;
            } else {
                if(number_of_alive_neighbours(n,m,board,i,j) == 3) *(next_generation_board + i*m + j) = 1;
                else *(next_generation_board + i*m + j) = 0;
            }

        }
    }

    print_board(n, m, next_generation_board);

    if(is_automatic) {
        usleep(250000);
    } else {
        char s[80];
        printf("Press Enter to continue");
        fgets(s, sizeof s, stdin);
    }

    //check for changes in population
    if(p_track -> previous_generation_population == total_alive_cells(n, m, next_generation_board)) {
        p_track -> number_of_stagnant_generations += 1;
    } else {
        p_track -> previous_generation_population = total_alive_cells(n, m, next_generation_board);
        p_track -> number_of_stagnant_generations = 0;
    }

    //run the next generation if there are alive cells and the population number is changing
    //otherwise terminate the program
    if(total_alive_cells(n, m, next_generation_board) && p_track -> number_of_stagnant_generations < 10) {
        run_generation(n, m, next_generation_board, is_automatic, p_track);
    }

    //free the boards from the memory if the program terminates
    free(board);
    free(next_generation_board);
    return;
}

//starts the game with an input from the input file by calling
//run_generation function for the first time after run_generation
//function terminates it notifies the user about the end of the program
void input_file_start(int is_automatic) {
    FILE *board_input_file;

    board_input_file = fopen("board_input.txt", "r");

    int n, m, cel;

    fscanf(board_input_file, "%d %d", &n, &m);
    int *board = (int *)malloc(n*m*sizeof(int));

    struct population_track p_track;
    p_track.number_of_stagnant_generations = 0;
    p_track.previous_generation_population = 0;

    //check for the input file
    if(board_input_file == NULL) {
        printf("An error while opening the input file occurred!");
        exit(1);
    }

    fscanf(board_input_file, "%*[^\n]"); //skip first row of the file

    //takes the board from the input file
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            fscanf(board_input_file, "%d ", &cel);
            *(board + i*m + j) = cel;
        }
    }

//    can loop through SetConsoleTextAttributes to see different color options
//    for(int k = 1; k < 999; k++)
//    {
//        HANDLE  hConsole;
//        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//        SetConsoleTextAttribute(hConsole, k);
//        printf("%3d  %s\n", k, "Conway's Game of Life");
//    }

    run_generation(n, m, board, is_automatic, &p_track);
    if(p_track.number_of_stagnant_generations == 10) {
        printf("The population remained stagnant for 10 generations, terminating the program...\n");
    } else {
        printf("There's no population left, terminating the program...\n");
    }
}

//starts the game with a randomly generated board by calling
//run_generation function for the first time after run_generation
//function terminates it notifies the user about the end of the program
void random_board_start(int is_automatic) {
    int n, m, cel;

    srand(time(0)); //initialize random seed for the rand function using current time
    printf("Enter the size of the board: \nEnter n and m:\n");

    scanf("%d %d", &n, &m);
    int *board = (int *)malloc(n*m*sizeof(int));

    struct population_track p_track;
    p_track.number_of_stagnant_generations = 0;
    p_track.previous_generation_population = 0;

    //the state of every cell is determined independently from other cells
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cel = rand() % 2;
            *(board + i*m + j) = cel;
        }
    }

    run_generation(n, m, board, is_automatic, &p_track);
    if(p_track.number_of_stagnant_generations == 10) {
        printf("The population remained stagnant for 10 generations, terminating the program...\n");
    } else {
        printf("There's no population left, terminating the program...\n");
    }
}

//main menu of the program, asks the user parameters of the game
//calls either input_file_start or random_board start depending on the
//chosen by the user option
int main ()
{
    int init_opt, is_automatic;

    //The program will either take the initial board state from the input
    //file that user can preset before running the game or by initializing
    //starting board randomly depending on this parameter
    printf("Should program scan the input file or create a random initial state?\nEnter 1 or 2:\n");
    scanf("%d", &init_opt);

    //The program will either ask user to press Enter to continue to the
    //next generation or run every new generation automatically depending
    //on this parameter
    printf("Should program run step by step or automatically?\nEnter 1 or 2:\n");
    scanf("%d", &is_automatic);

    if(init_opt == 1) {
        input_file_start(is_automatic-1);
    } else if(init_opt == 2) {
        random_board_start(is_automatic-1);
    }

    return 0;
}
