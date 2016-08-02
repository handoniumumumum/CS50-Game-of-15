/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

//

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void get0(int *a, int *b);
void randomizer(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }
    
    
    srand48((long int) time(NULL));

    // greet user with instructions
    greet();
    // initialize the board
    init();
    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(200000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    //fill the arrays
    int k = 1;
    for(int j = 0; j<d; j++)
    {

        for(int i=0; i<d; i++)
        {
            
            board[j][i] = k;
            k++;
        }
    }
    
    board[d-1][d-1] = 0;
    
    // Make 1500 random moves to randomize the board.
    for(int i=0;i<1500;i++)
    {
        randomizer();
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    printf("\n");
    for(int i = 0; i<d; i++)
    {
        for(int j=0; j<d; j++)
        {
            if(board[i][j] > 9)
                printf("%i   ", board[i][j]);
            else if (board[i][j] == 0)
                printf("_    ");
            else
                printf("%i    ", board[i][j]);
        }
    
        printf("\n");
    }
    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int a, b;
    get0(&a, &b);
    if(tile == board[a-1][b] || tile == board[a][b-1]
    || tile == board[a+1][b] || tile == board[a][b+1])
    {
        if(tile == board[a-1][b] )
            board[a-1][b] = 0;
        else if(tile == board[a][b-1])
            board[a][b-1] = 0;
        else if(tile == board[a+1][b])
            board[a+1][b] = 0;
        else if(tile == board[a][b+1])
            board[a][b+1] = 0;
        board[a][b] = tile;
        printf("%i", board[a][b]);
        return true;
    }
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int countup = 1;
    
    for(int i = 0; i<d; i++)
    {
        for(int j=0; j<d; j++)
        {
            if(board[i][j] == countup)
                countup++;
        }
    }
    if(countup == d*d)
        return true;
    else
        return false;
}
//Get the blank tile's position in a way that we can break out of the necessary double loop.
void get0 (int *a, int *b)
{
    for(int i = 0; i<d; i++)
    {
        for(int j=0; j<d; j++)
        {
           if(board[i][j] == 0)
           {
                *a=i;
                *b=j;
                return;
           }
        }
    }
}
// This tries a random move and calls itself again if it doesn't make one.
void randomizer(void)
{
    
    int a, b;
    long random;
    get0(&a,&b);
    random = mrand48();
    if(random < -1073741824)
    {
       if(a != 0 && move(board[a-1][b]))
       {
       draw();
            return;
       }
    }
    else if(random>-1073741824 && random <= 0)
    {
        if(b != 0 && move(board[a][b-1]))
        {
        draw();
            return;
        }
            
    }
    else if(random > 0 && random < 1073741824)
    {
        if(a != d && move(board[a+1][b]))
        {
        draw();
        return;
    
        }
    }   
    else if(random > 1073741824)
    {
        if(b != d && move(board[a][b+1]))
        {
            draw();
            return;
        }
    }
    randomizer();
}
/*void god(void)
{
    bool solved = false;
    int count = 1
    int a, b = 0;

    while(!solved)
    {
        for(int i = 0; i<d; i++)
        {
            for(int j=0; j<d; j++)
            {
                if(board[i][j]!=count)
                    {
                     moveFinder(&a, &b, i, j);
                        
                    }
                else
                    count++;
            }    
        }
    }
}

//void moveFinder(int *a, *b, i, j)
{
    int number = board[a][b];
    int open[][];
    int closed[];
    bool pathed;
    int ba, bb, counter;
    // find the position of our number on the board
        for(int k = 0; k<d; k++)
        {
            for(int l=0; l<d; l++)
            {
                if(board[k][l] == number)
                {
                    a=k;
                    b=l;
                }
            }
        }
    // use get0 to find our blank space.
    get0(ba,bb);
    while (!pathed)
    {
        for(int k; k )
        getG(i, j, )
        
    }
}
//int getG(int a, b, c, d)
{
    
}
//int getH(int a, b, c ,d)
{
    
}
*/
