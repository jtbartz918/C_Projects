#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

#define WIDTH 50
#define HEIGHT 20

typedef struct{
    int x;
    int y;
    bool equiped;
}Player;

typedef struct{
    int exit_x;
    int exit_y;
    char map[HEIGHT][WIDTH];
}Dungeon;


// Function to generate a random number between min and max
int random_number(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Function to initialize the dungeon
void init_dungeon(Dungeon* dungeon, Player player) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            dungeon->map[i][j] = '.'; // Empty space
        }
    }

    // Place player at a random position
    player.x = random_number(1, WIDTH - 2);
    player.y = random_number(1, HEIGHT - 2);
    dungeon->map[player.y][player.x] = 'P';

    // Place exit at a random position, different from player
    int exit_x, exit_y;

    exit_x = random_number(1, WIDTH - 2);
    exit_y = random_number(1, HEIGHT - 2);
    
    //Hard coded for now
    dungeon->map[exit_y][exit_x] = 'E';
    dungeon->exit_x=exit_x;
    dungeon->exit_y=exit_y;

    // Place some obstacles randomly
    int num_obstacles = random_number(5, 15);
    for (int i = 0; i < num_obstacles; i++) {
        int obstacle_x, obstacle_y;
        do {
            obstacle_x = random_number(1, WIDTH - 2);
            obstacle_y = random_number(1, HEIGHT - 2);
        } while ((dungeon->map[obstacle_y][obstacle_x] != '.'));
        dungeon->map[obstacle_y][obstacle_x] = '#'; // Obstacle
    }
}

// Function to print the dungeon
void print_dungeon(Dungeon* dungeon, Player player) {
    system("clear"); // Clears the terminal screen for Unix-based systems
    printf("Debug\n");
    printf("Player_y is %d\n", player.y);
    printf("Player_x is %d\n", player.x);
    printf("Player equiped is %d\n", player.equiped);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c ", dungeon->map[i][j]);
        }
        printf("\n");
    }
}

// Function to handle player movement
void move_player(Dungeon* dungeon, char move, Player player) {
    // Find the player's current position
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (dungeon->map[i][j] == 'P') {
                player.x = j;
                player.y = i;
                break;
            }
        }
    }
    
    int new_x = player.x;
    int new_y = player.y;

    // Update new position based on move
    switch (move) {
        case 'w': new_y--; break; // Up
        case 's': new_y++; break; // Down
        case 'a': new_x--; break; // Left
        case 'd': new_x++; break; // Right
    }

     // Check for boundaries and obstacles
    if (new_x >= 0 && new_x < WIDTH && new_y >= 0 && new_y < HEIGHT && dungeon->map[new_y][new_x] != '#') {
        // Update player position
        dungeon->map[player.y][player.x] = '.';
        dungeon->map[new_y][new_x] = 'P';
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
    Player player={};

    //char dungeon[HEIGHT][WIDTH];
    Dungeon dungeon={};
    init_dungeon(&dungeon, player);

    char move;
    while (1) {
        print_dungeon(&dungeon, player);  // Clear screen and print dungeon
        printf("Enter move (w/a/s/d or q to quit): ");
        move = get_input();  // Get the input without waiting for Enter

        if (move == 'q') {
            break;
        }

        move_player(&dungeon, move, player);

        // Check if player reached the exit
        
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (dungeon.map[i][j] == 'P') {
                    player.x = j;
                    player.y = i;
                    break;
                }
            }
        }
        
        if (player.y == dungeon.exit_y && player.x == dungeon.exit_x){
            printf("You equipted a helmet!\n");
            player.equiped = true;

            
        }
    }
    

    return 0;
}
