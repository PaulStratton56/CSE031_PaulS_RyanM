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
int length=0;
point * surroundings;
int** output;
void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...

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
void writetoGlobal(point* list){
    for(int k=0;k<length;k++){
        *(*(output+(list+k)->row)+(list+k)->col) = *(*(output+(list+k)->row)+(list+k)->col)*10+k+1;
    }
}
void fn(char** block, char* word, point* list, int index){
    for(int i=0;i<8;i++){
        point p = addPoints(*(list+index-1),*(surroundings+i));
        if(p.row==-1 || p.col==-1 || p.row==bSize || p.col==bSize){
            continue;
        }
        if(checkPoint(block,p)==*(word+index)){
            *(list+index)=p;
            if(index!=length){
                fn(block,word,list,index+1);
            }
            else{
                writetoGlobal(list);
            }
        }
    }
    *(list+index)=(point){-1,-1};
}
void searchPuzzle(char** block, char* word) {
    while(*(word+length)!='\0'){
        length++;
    }
    output = malloc(bSize*sizeof(int*));
    for(int i=0;i<bSize;i++){
        *(output+i)=malloc(bSize*sizeof(int));
        for(int j=0;j<bSize;j++){
            *(*(output+i)+j)=0;
        }
    }
    if(surroundings = malloc(8*sizeof(point)));{//if not void then define surrouding shift
        *(surroundings) = (point){-1,-1};
        *(surroundings+1) = (point){-1,0};
        *(surroundings+2) = (point){-1,1};
        *(surroundings+3) = (point){0,-1};
        *(surroundings+4) = (point){0,1};
        *(surroundings+5) = (point){1,-1};
        *(surroundings+6) = (point){1,0};
        *(surroundings+7) = (point){1,1};
    }
    point* path = malloc(length*sizeof(point));
    for(int i=0;i<bSize;i++){
        for(int j=0;j<bSize;j++){
            if(*(*(block+i)+j)==*word){
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
