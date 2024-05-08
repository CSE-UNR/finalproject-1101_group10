//Mathew Jones and George Martinez
//CS135
//Final Project
//05/07/24



#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100


typedef struct {
    int size;
    int pixels[MAX_SIZE][MAX_SIZE];
} Image;

bool load(Image *image);
int display(const Image *image);
bool edit(Image *image);
bool crop(Image *image);
bool dim(Image *image);
bool brighten(Image *image);
bool save(const Image *image);

int main() {
    int choice;
    Image currentImage = {0}; 
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
                    }
                } else {
                    printf("No image loaded. Please load an image first.\n");
                }
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

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

int display(const Image *image) {
    printf("Displaying current image:\n");
    for (int i = 0; i < image->size; i++) {
        for (int j = 0; j < image->size; j++) {
            printf("%c", image->pixels[i][j] >= 128 ? '#' : '.');
        }
        printf("\n");
    }
}

bool edit(Image *image) {
    int editChoice;
    char saveChoice;
    
    do {
        printf("\nEdit Menu:\n");
        printf("1: Crop image\n");
        printf("2: Dim image\n");
        printf("3: Brighten image\n");
        printf("0: Exit\n");
        printf("Choose from one of the options above: ");
        scanf("%d", &editChoice);

        switch (editChoice) {
            case 1:
                if (crop(image)) {
                    display(image);
                    printf("Do you want to save the changes? (y/n): ");
                    scanf(" %c", &saveChoice);
                    if (saveChoice == 'y' || saveChoice == 'Y') {
                        save(image);
                    }
                }
                break;
            case 2:
                if (dim(image)) {
                    display(image);
                    printf("Do you want to save the changes? (y/n): ");
                    scanf(" %c", &saveChoice);
                    if (saveChoice == 'y' || saveChoice == 'Y') {
                        save(image);
                    }
                }
                break;
            case 3:
                if (brighten(image)) {
                    display(image);
                    printf("Do you want to save the changes? (y/n): ");
                    scanf(" %c", &saveChoice);
                    if (saveChoice == 'y' || saveChoice == 'Y') {
                        save(image);
                    }
                }
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (editChoice != 0);

    return true;
}

bool crop(Image *image) {
    int newSize;
    printf("The image you want to crop is %d x %d.\n", image->size, image->size);
    printf("The row and column values start from the upper lefthand corner.");
    printf("which column do you want to be the new left side? ");
    scanf("%d", &newSize);

    if (newSize >= 0 && newSize < image->size) {
        image->size = newSize;
        return true;
    } else {
        printf("Invalid size entered for cropping.\n");
        return false;
    }
}

bool dim(Image *image) {
    for (int i = 0; i < image->size; i++) {
        for (int j = 0; j < image->size; j++) {
            image->pixels[i][j] = image->pixels[i][j] > 0 ? image->pixels[i][j] - 1 : 0;
        }
    }
    return true;
}


bool brighten(Image *image) {
    for (int i = 0; i < image->size; i++) {
        for (int j = 0; j < image->size; j++) {
            image->pixels[i][j] = image->pixels[i][j] < 255 ? image->pixels[i][j] + 1 : 255;
        }
    }
    return true;
}


bool save(const Image *image) {
    char filename[50];
    printf("What do you want to name the file? (include extension): ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for saving.\n");
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
    printf("Image saved successfully.\n");
    return true;
    }
