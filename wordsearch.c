#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr); // Declared a function for printing the puzzle
void searchPuzzle(char** arr, char* word); // Declared a function to search foe a word in the puzzle
int bSize; // Is a global variable that stores the size of the puzzle grid (number of rows and columns)

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
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    // The outer loop iterates through the rows, allocating memory for each row
    // The inner loop reads characters from the puzzle file, one by one and stores them in the grid
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char)); // Allocates space for each row in the puzzle grid
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j); // Reads each character from the file and stores it in the corresponding postion in the grid
    }
    fclose(fptr); // File close

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            printf("%c ", *(*(arr + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...

}
