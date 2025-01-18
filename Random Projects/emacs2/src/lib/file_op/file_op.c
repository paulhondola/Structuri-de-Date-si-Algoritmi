// Dependencies
#include "file_op.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>w

// adauga un fisier cu numele <filename> la finalul listei
int OPEN(list list, const char *filename){
    FILE *file = fopen(filename, "a");
    if (file == NULL){
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return 0;
    }

    if (add_node(list, filename) == 0){
        fprintf(stderr, "Error: Could not add file %s to list\n", filename);
        return 0;
    }

    return 1;
}

// scrie (insereaza) cuvantul <word> la indexul <index> in text. <word> nu contine spatii
void WRITE(const char *filename, int index, const char *word) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        fprintf(stderr, "Write Error: Could not open file %s\n", filename);
        return;
    }

    // Step 1: Read the entire content of the file into a buffer
    char buffer[MAX_FILE_CONTENT_SIZE] = {0};
    size_t length = fread(buffer, 1, MAX_FILE_CONTENT_SIZE - 1, file);
    buffer[length] = '\0';  // Ensure the buffer is null-terminated

    // Step 2: Handle the case where the index is larger than the file content
    if (index >= strlen(buffer)) {
        // Pad the buffer with spaces up to the index
        for (int i = strlen(buffer); i < index; i++) {
            buffer[i] = ' ';
        }
        buffer[index] = '\0';  // Null-terminate after padding

        // Append the word to the buffer
        strcat(buffer, word);

        // Write the modified content back to the file
        fseek(file, 0, SEEK_SET);
        fwrite(buffer, 1, strlen(buffer), file);
        fclose(file);
        return;
    }

    // Step 3: Shift the existing content to make room for the new word
    size_t word_len = strlen(word);
    size_t buffer_len = strlen(buffer);

    if (buffer_len + word_len >= MAX_FILE_CONTENT_SIZE) {
        fprintf(stderr, "Write Error: File content exceeds maximum allowed size\n");
        fclose(file);
        return;
    }

    // Shift content to the right to make space for the new word
    for (int i = buffer_len; i >= index; i--) {
        buffer[i + word_len] = buffer[i];
    }

    // Step 4: Insert the word at the specified index
    for (int i = 0; i < word_len; i++) {
        buffer[index + i] = word[i];
    }

    // Step 5: Write the modified buffer back to the file
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, strlen(buffer), file);

    fclose(file);
}

// sterge <count> caractere incepand de la <index>
void DELETE(const char *filename, int index, int count) {
    // Open file for reading and writing
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        fprintf(stderr, "Deletion Error: Could not open file %s\n", filename);
        return;
    }

    // Step 1: Read the entire file content into a buffer
    char buffer[MAX_FILE_CONTENT_SIZE];
    size_t length = fread(buffer, 1, MAX_FILE_CONTENT_SIZE - 1, file);
    if (ferror(file)) {
        fprintf(stderr, "Deletion Error: Failed to read the file\n");
        fclose(file);
        return;
    }

    buffer[length] = '\0'; // Null-terminate

    // Step 2: Validate index and count
    if (index < 0 || count < 0 || index >= length) {
        fprintf(stderr, "Deletion Error: Invalid index or count\n");
        fclose(file);
        return;
    }

    // Step 3: Check if the specified range exceeds the buffer length
    if (index + count > length) {
        count = length - index;
    }

    // Step 4: Shift content to remove the specified range
    for (int i = index; i <= length - count; i++) {
        buffer[i] = buffer[i + count];
    }

    for (int i = length - count; i < length; i++) {
        buffer[i] = ' ';
    }

    // Step 5: Write the modified content back to the file
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, length, file);

    fclose(file);
}

// copiaza continutul fisierului src in fisierul dst
int COPY(const char* source, const char* destination) {
    FILE *src_file = fopen(source, "rb");
    if (src_file == NULL) {
        fprintf(stderr, "Copy Error: Cannot open source file\n");
        return 0;
    }

    FILE *dst_file = fopen(destination, "wb");
    if (dst_file == NULL) {
        fprintf(stderr, "Copy Error: Cannot open destination file\n");
        fclose(src_file);
        return 0;
    }

    char buffer[MAX_FILE_CONTENT_SIZE];
    size_t bytes;

    // Read from source and write to destination
    while ((bytes = fread(buffer, 1, MAX_FILE_CONTENT_SIZE, src_file)) > 0) {
        if (fwrite(buffer, 1, bytes, dst_file) != bytes) {
            fprintf(stderr, "Copy Error: Cannot write to destination file\n");
            fclose(src_file);
            fclose(dst_file);
            return 0;
        }
    }

    if (ferror(src_file))
        fprintf(stderr, "Copy Error: Cannot read source file %s\n", source);

    fclose(src_file);
    fclose(dst_file);

    return 1;
}

// inchide(elimina din lista) si salveaza fisierul <filename> ca si alt fisier numit <newname>
int SAVEAS(list list, const char* src, const char* dst){
    if (list == NULL){
        fprintf(stderr, "Save Error: List is not initialized\n");
        return 0;
    }

    if (remove_node(list, src) == 0){
        fprintf(stderr, "Save Error: Could not remove file %s from list\n", src);
        return 0;
    }

    // Copy the contents of the source file
    if(COPY(src, dst) == 0){
        fprintf(stderr, "Save Error: Could not save file %s as %s\n", src, dst);
        return 0;
    }

    // Add the destination file to the end of the list
    if(OPEN(list, dst) == 0){
        fprintf(stderr, "Save Error: Could not open file %s\n", dst);
        return 0;
    }

    // Delete the source file
    if(remove(src) != 0){
        fprintf(stderr, "Save Error: Could not delete file %s\n", src);
        return 0;
    }

    return 1;
}

// printeaza numele fisierului si continutul fisierului
int PRINT(const char* filename, FILE *log){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        fprintf(stderr, "Print Error: Could not open file %s\n", filename);
        return 0;
    }

    fprintf(log, "\n------------------------\nFile: %s\n", filename);

    char buffer[MAX_FILE_CONTENT_SIZE];
    while(fgets(buffer, MAX_FILE_CONTENT_SIZE, file) != NULL)
        fprintf(log, "%s", buffer);

    fclose(file);
    fprintf(log, "\n------------------------\n");
    return 1;
}

// printeaza numele tuturor fisierelor din lista si continutul lor
void PRINT_ALL(list list, FILE *file){
    node iterator = get_head(list);
    while(iterator != NULL){
        PRINT(get_filename(iterator), file);
        iterator = get_next(iterator);
    }
}

// Deletes all files from the list
void REMOVE_ALL(list list){
    node iterator = get_head(list);
    while(iterator != NULL){
        remove(get_filename(iterator));
        iterator = get_next(iterator);
    }

    destroy_list(list);
}