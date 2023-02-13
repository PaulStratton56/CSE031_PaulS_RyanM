#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
typedef struct point{
    int row;
    int col;
} point;
int bSize;
int length=0;//length of target word
point * surroundings; // shift for searching 8 points arround
int** output;
char* answer="Word not found!";
void printPuzzle(char** arr) {
    for(int i=0;i<bSize;i++){
        for(int j=0;j<bSize;j++){
            printf("%c ",*(*(arr+i)+j));
        }
        printf("\n");
    }
    printf("\n");
}
void printPaths(){
    for(int i=0;i<bSize;i++){
        for(int j=0;j<bSize;j++){
            printf("%d ",*(*(output+i)+j));
        }
        printf("\n");
    }
}
void printpoint(point p){
    printf("%d, %d",p.row,p.col);
}
point addPoints(point a, point b){
    return (point){a.row+b.row,a.col+b.col};
}
char checkPoint(char** arr, point p){
    return *(*(arr+p.row)+p.col);
}
void writetoOutput(point* path){
    for(int k=0;k<length;k++){//for every point in the path, write it in the output
        *(*(output+(path+k)->row)+(path+k)->col) = *(*(output+(path+k)->row)+(path+k)->col)*10+k+1;
    }
}
void fn(char** block, char* word, point* path, int index){
    for(int i=0;i<8;i++){//for every point surrounding 
        point p = addPoints(*(path+index-1),*(surroundings+i)); // current point to check
        if(p.row==-1 || p.col==-1 || p.row==bSize || p.col==bSize){ // if out of bounds then skip
            continue;
        }
        if(checkPoint(block,p)==*(word+index)){//if correct letter found
            *(path+index)=p;//add current point being checked to path found
            if(index!=length){
                fn(block,word,path,index+1);
            }
            else{
                writetoOutput(path);
                answer = "Word found!";
            }
        }
        *(path+index)=(point){-1,-1};//remove the most recently added point from path (backtracking)
    }
}
void searchPuzzle(char** block, char* word) {
    while(*(word+length)!='\0'){//calculate target word length
        length++;
    }
    output = malloc(bSize*sizeof(int*)); // define globabl array and intitialize everything to 0
    for(int i=0;i<bSize;i++){
        *(output+i)=malloc(bSize*sizeof(int));
        for(int j=0;j<bSize;j++){
            *(*(output+i)+j)=0;
        }
    }
    if(surroundings = malloc(8*sizeof(point)));{//if not void then define shift for 8 points surrounding
        *(surroundings) = (point){-1,-1};
        *(surroundings+1) = (point){-1,0};
        *(surroundings+2) = (point){-1,1};
        *(surroundings+3) = (point){0,-1};
        *(surroundings+4) = (point){0,1};
        *(surroundings+5) = (point){1,-1};
        *(surroundings+6) = (point){1,0};
        *(surroundings+7) = (point){1,1};
    }
    point* path = malloc(length*sizeof(point));//define path
    for(int i=0;i<bSize;i++){       //search every position for first letter
        for(int j=0;j<bSize;j++){
            if(*(*(block+i)+j)==*word){     //if first letter found, append current point i,j to path, and then depth first search from it
                *path = (point){i,j};
                fn(block, word, path,1);
            }
        }
    }

    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...
    
    printf("%s\n",answer);
    printPaths();
    
    
    //free memory
    free(word);
    for(int i=0;i<bSize;i++){
        free(*(block+i));
        free(*(output+i));
    }
    free(block);
    free(output);
    free(surroundings);
    free(path);

}

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);

    return 0;
}
