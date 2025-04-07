#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

#define WIDTH 50
#define HEIGHT 20

// Function to generate a random number between min and max
int random_number(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Function to initialize the dungeon
void init_dungeon(char dungeon[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            dungeon[i][j] = '.'; // Empty space
        }
    }

    // Place player at a random position
    int player_x = random_number(1, WIDTH - 2);
    int player_y = random_number(1, HEIGHT - 2);
    dungeon[player_y][player_x] = 'P';

    // Place exit at a random position, different from player
    int exit_x, exit_y;

    exit_x = random_number(1, WIDTH - 2);
    exit_y = random_number(1, HEIGHT - 2);
    
    dungeon[7][26] = 'E';

    // Place some obstacles randomly
    int num_obstacles = random_number(5, 15);
    for (int i = 0; i < num_obstacles; i++) {
        int obstacle_x, obstacle_y;
        do {
            obstacle_x = random_number(1, WIDTH - 2);
            obstacle_y = random_number(1, HEIGHT - 2);
        } while ((dungeon[obstacle_y][obstacle_x] != '.'));
        dungeon[obstacle_y][obstacle_x] = '#'; // Obstacle
    }
}

// Function to print the dungeon
void print_dungeon(char dungeon[HEIGHT][WIDTH], int player_y, int player_x) {
    system("clear"); // Clears the terminal screen for Unix-based systems
    printf("Debug\n");
    printf("Player_y is %d\n", player_y);
    printf("Player_x is %d\n", player_x);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c ", dungeon[i][j]);
        }
        printf("\n");
    }
}

// Function to handle player movement
void move_player(char dungeon[HEIGHT][WIDTH], char move) {
    int player_x, player_y;
    // Find the player's current position
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (dungeon[i][j] == 'P') {
                player_x = j;
                player_y = i;
                break;
            }
        }
    }
    
    int new_x = player_x;
    int new_y = player_y;

    // Update new position based on move
    switch (move) {
        case 'w': new_y--; break; // Up
        case 's': new_y++; break; // Down
        case 'a': new_x--; break; // Left
        case 'd': new_x++; break; // Right
    }

     // Check for boundaries and obstacles
    if (new_x >= 0 && new_x < WIDTH && new_y >= 0 && new_y < HEIGHT && dungeon[new_y][new_x] != '#') {
        // Update player position
        dungeon[player_y][player_x] = '.';
        dungeon[new_y][new_x] = 'P';
    }
}

// Function to get a single character input without waiting for Enter key
char get_input() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable buffering and echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    char dungeon[HEIGHT][WIDTH];
    init_dungeon(dungeon);

    char move;
    while (1) {
        int player_x, player_y;
        print_dungeon(dungeon, player_x, player_y);  // Clear screen and print dungeon
        printf("Enter move (w/a/s/d or q to quit): ");
        move = get_input();  // Get the input without waiting for Enter

        if (move == 'q') {
            break;
        }

        move_player(dungeon, move);

        // Check if player reached the exit
        
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (dungeon[i][j] == 'P') {
                    player_x = j;
                    player_y = i;
                    break;
                }
            }
        }
        
        if (player_y == 7 && player_x == 26){
            printf("Congratulations! You reached the exit!\n");
            break;
        }
    }
    

    return 0;
}
