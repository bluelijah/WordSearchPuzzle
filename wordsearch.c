#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr); // Declared a function for printing the puzzle
void searchPuzzle(char** arr, char* word); // Declared a function to search foe a word in the puzzle
int bSize; // Is a global variable that stores the size of the puzzle grid (number of rows and columns)
void toUpper(char* word);
int searchMatrix(char** arr, char*word, int i, int j, int index, int bSize, int** foundIndices);
int findFirstLetter(char** arr, char* word, int** foundIndices);

int matrix[100][100]; //search path matrix

void initializeMatrix() {
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            matrix[i][j] = 0;
        }
    }
}

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) { // We expect a command-line argument for the puzzle file name
    if (argc != 2) { // It checks the command line if there is 2 arguments
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]); 
        return 2; 
    }
    int i, j; 
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r"); // This opens a file in read mode where argv[1] is our file name
    if (fptr == NULL) { // If the file can't open print the file cant open
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize); // Reads the first integer from the text file
                                // Where the value is stored into bsize
    
    // Alloc space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    // The outer loop iters through the rows, allocating memory for each row
    // The inner loop reads characters from the puzzle file, one by one and stores them in the grid
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char)); // Allocs space for each row in the puzzle grid
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j); // Reads each character from the file and stores it in the corresponding postion in the grid
    }
    fclose(fptr); // File close

    printf("Enter the word to search: ");
    scanf("%s", word);
  
    //To test the toUpper word
    //toUpper(word);
    //printf("Converted word: %s\n", word);
  
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    return 0;
}

void toUpper(char* word){
    for (int i = 0; *(word+i)!='\0'; i++){ 
        if(*(word+i) >= 'a' && *(word+i) <= 'z'){
            *(word+i) = *(word+i) -32;
        }
    }
}

void printPuzzle(char** arr) {
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            printf("%c ", *(*(arr + i) + j)); // Print each character in the puzzle grid
        }
        printf("\n"); // Newline after each row
    }
    printf("\n"); // Extra newline for formatting
}


int searchMatrix(char** arr, char* word, int i, int j, int index, int bSize, int** foundIndices) { //searches the matrix recursivly every direction for the word
    // Take the word length to an int
    int wordLength = strlen(word);
    // If the index is equal to the word length, the word has been found
    if (index == wordLength) {
        return 1; // The word was found
    }
    // Check if the current positon (i , j) is out of bounds 
    if (i < 0 || j < 0 || i >= bSize || j >= bSize) {
        return 0; // Out of bounds in the matrix
    }
    // Check if the current grid character matches the current word character 
    if (*(*(arr + i) + j) == *(word + index)) {

        foundIndices[index][0] = i;
        foundIndices[index][1] = j;

        // Searching in all eight directions
        int result = searchMatrix(arr, word, i - 1, j, index + 1, bSize, foundIndices) ||  // Up
                     searchMatrix(arr, word, i + 1, j, index + 1, bSize, foundIndices) ||  // Down
                     searchMatrix(arr, word, i, j - 1, index + 1, bSize, foundIndices) ||  // Left
                     searchMatrix(arr, word, i, j + 1, index + 1, bSize, foundIndices) ||  // Right
                     searchMatrix(arr, word, i - 1, j - 1, index + 1, bSize, foundIndices) ||  // Up left diagonal
                     searchMatrix(arr, word, i - 1, j + 1, index + 1, bSize, foundIndices) ||  // Up right diagonal
                     searchMatrix(arr, word, i + 1, j - 1, index + 1, bSize, foundIndices) ||  // down left diagonal
                     searchMatrix(arr, word, i + 1, j + 1, index + 1, bSize, foundIndices);    // down right diagonal
        
        // Return 1 if the word is found, 0 otherwise after completing the recursive search
        return result;
    }

    return 0;
}



int findFirstLetter(char** arr, char* word, int** foundIndices) { // Find the first letter of the word in the grid then intiate search in all directions
    int wordLength = strlen(word); // Get the length of the word 

    if (wordLength > bSize) { // If the length is greater than the matrix return 0 because the word doesn't exist in the matrix
        return 0;
    }
    // Traverse the entire matrix to find the first char
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            if (*(*(arr + i)+ j) == *word) { // Dereferencing the *word gives us the first char of the word and compare that to the current pos of the matrix char
                if (searchMatrix(arr, word, i, j, 0, bSize, foundIndices)) { //Start the recursive search for the word at the current position of the char (i, j)
                    return 1; // If the word is found
                }
            }
        }
    }

    return 0; // word was not found
}


void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...


    //a for loop that iters through the whole matrix, and stores the locations of every letter that is equal to the first letter of the search word CHECKMARK
    //8 functions, one that goes in each direction CHECKMARK
    //if one of those functions finds the second letter of the search word CHECKMARK
    //we upd the search letter, (3rd letter) CHECKMARK
    //make an array [2][2] CHECKMARK
    //check equality of every letter within i-1, i+1, j-1, j+1, with the second letter of the word CHECKMARK
    // [2][2], [2][3], [3][4] CHECKMARK
  
    toUpper(word);
    int wordLength = strlen(word);
    initializeMatrix();

    int** foundIndices = (int**)malloc(wordLength * sizeof(int*));
    for (int i = 0; i < wordLength; i++) {
        foundIndices[i] = (int*)malloc(2 * sizeof(int)); // each entry stores (i, j)
    }

    if (findFirstLetter(arr, word, foundIndices)) {
        printf("Word found!\n");
        printf("Printing the search path:\n");

        for (int k = 0; k < wordLength; k++) {
            int row = foundIndices[k][0];
            int col = foundIndices[k][1];
            int* currentCell = *(matrix + row) + col; // Accessing matrix using pointer arithmetic

            if (*currentCell == 0) {
                *currentCell = k + 1;
            } else {
                *currentCell = *currentCell * 10;
                *currentCell = *currentCell + (k + 1);
            }
        }

        // Prints matrix
        for (int i = 0; i < bSize; i++) {
            for (int j = 0; j < bSize; j++) {
                if(j == 0){
                    printf("%d ", *(*(matrix + i) + j)); // Accessing matrix using pointer arithmetic
                } else {
                    printf("%5d ", *(*(matrix + i) + j));
                }
                
            }
            printf("\n");
        }
    } else {
        printf("Word not found!\n");
    }
}
