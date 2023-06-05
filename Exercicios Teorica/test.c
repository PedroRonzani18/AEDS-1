#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* file = fopen("inp.txt", "r"); // Open the file for reading
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    int num_lines;
    fscanf(file, "%d", &num_lines); // Read the number of lines from the file

    // Process each line
    for (int i = 0; i < num_lines; i++) {
        int* numbers = NULL;
        int num, count = 0;

        // Read numbers dynamically until a newline character is encountered
        while (fscanf(file, "%d", &num) == 1) {
            count++;
            numbers = (int*)realloc(numbers, count * sizeof(int));
            numbers[count - 1] = num;

            // Check for newline character
            if (getc(file) == '\n') {
                break;
            }
        }

        // Print the numbers for demonstration
        for (int j = 0; j < count; j++) {
            printf("%d ", numbers[j]);
        }
        printf("\n");

        free(numbers); // Free the dynamically allocated memory
    }

    fclose(file); // Close the file
    return 0;
}
