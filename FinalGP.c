//Matthew Jones and George Martinez
//Final Project
//05/07/24


#include <stdio.h>
#include <stdbool.h>


#define MAX_SIZE 100 


// Structure to store image data
typedef struct {
    int size;
    int pixels[MAX_SIZE][MAX_SIZE];
} Image;


// Function prototypes
bool load(Image *image);
void display(const Image *image);
bool edit(Image *image);
bool crop(Image *image);
bool dim(Image *image);
bool brighten(Image *image);
bool save(const Image *image);

//Main Menu Function
int main() {
    int choice;
    Image currentImage = {0}; // Initialize currentImage size to 0
    bool imageLoaded = false;


    do {
        printf("\nMenu:\n");
        printf("1. Load Image\n");
        printf("2. Display Image\n");
        printf("3. Edit Image\n");
        printf("0. Exit\n");
        printf("Choose from one of the options above: ");
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                if (load(&currentImage)) {
                    imageLoaded = true;
                    printf("Image loaded successfully!\n");
                } else {
                    printf("Could not find an image with that filename.\n");
                }
                break;
            case 2:
                if (imageLoaded) {
                    display(&currentImage);
                } else {
                    printf("Sorry, no image to display\n");
                }
                break;
            case 3:
                if (imageLoaded) {
                    if (edit(&currentImage)) {
                        display(&currentImage);
                        printf("Do you want to save the changes? (y,n): ");
                        int saveChoice;
                        scanf("%d", &saveChoice);
                        if (saveChoice == 'y') {
                            save(&currentImage);
                        }
                    }
                } else {
                    printf("No image loaded. Please load an image first.\n");
                }
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 4);


    return 0;
}


// Function to load a new image from a file
bool load(Image *image) {
    char filename[50];
    printf("What is the name of the image file?: ");
    scanf("%s", filename);


    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return false;
    }
  
    
}


// Function to display the current image
void display(const Image *image) {
    printf("Displaying current image:\n");
    for (int i = 0; i < image->size; i++) {
        for (int j = 0; j < image->size; j++) {
            printf("%c", image->pixels[i][j] >= 128 ? '#' : '.');
        }
        printf("\n");
    }
}


// Function to edit the current image
bool edit(Image *image) {
    int editChoice;
    do {
        printf("\nEdit Menu:\n");
        printf("1: Crop image\n");
        printf("2: Dim image\n");
        printf("3: Brighten image\n");
        printf("0: Back to Main Menu\n");
        printf("Choose from one of the options above: ");
        scanf("%d", &editChoice);


        switch (editChoice) {
            case 1:
                crop(image);
                break;
            case 2:
                dim(image);
                break;
            case 3:
                brighten(image);
                break;
            case 0:
                printf("Returning to main menu.\n");
                break;
            default:
printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (editChoice != 0);


    return true;
}


// Function to crop the current image
bool crop(Image *image) {
    int newSize;
    printf("The image you want to crop is %d x %d.\n", image->size, image->size);
    printf("The row and column values start in the left-hand corner.\n");
    printf("which column do you want to be the new left side?(0 to %d)", image->size - 1);
    scanf("%d", &newSize);
    if (newSize >= 0 && newSize < image->size) {
    	for (int i = 0; i < image->size; i++) {
    		for(int j = 0; j < newSize; j++) {
    			image->pixels[i][j] = image->pixels[i][j + newSize];
    			}
    			}
        image->size = newSize;
        return true;
    }
    return false;
}


// Function to dim the current image
bool dim(Image *image) {
    for (int i = 0; i < image->size; i++) {
        for (int j = 0; j < image->size; j++) {
            image->pixels[i][j] = image->pixels[i][j] > 0 ? image->pixels[i][j] - 1 : 0;
        }
    }
    return true;
}


// Function to brighten the current image
bool brighten(Image *image) {
    for (int i = 0; i < image->size; i++) {
        for (int j = 0; j < image->size; j++) {
            image->pixels[i][j] = image->pixels[i][j] < 255 ? image->pixels[i][j] + 1 : 255;
        }
    }
    return true;
}


// Function to save the current image to a file
bool save(const Image *image) {
    char filename[50];
    printf("what do you want to name the file? (include extension): ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return false;
    }
    fprintf(file, "%d\n", image->size);
    for (int i = 0; i < image->size; i++) {
        for (int j = 0; j < image->size; j++) {
            fprintf(file, "%d ", image->pixels[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return true;
}





