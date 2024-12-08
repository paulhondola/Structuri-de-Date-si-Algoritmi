#include "list.h"
#include <stdlib.h>
#include <string.h>

// structures
typedef struct NODE
{
  char filename[MAX_FILE_NAME_SIZE];
  struct NODE *next;
}*node;

struct LIST
{
  struct NODE *head;
  struct NODE *rear;
};

// Constructors
node INIT_NODE(const char *filename){
  // Create a file
  FILE *file = fopen(filename, "a");
  if(file == NULL)
    return NULL;

  fclose(file);

  node new_node = malloc(sizeof(struct NODE));
  strncpy(new_node->filename, filename, MAX_FILE_NAME_SIZE);
  new_node->next = nullptr;
  return new_node;
}

list INIT_LIST(void){
  list new_list = malloc(sizeof(struct LIST));
  new_list->head = nullptr;
  new_list->rear = nullptr;
  return new_list;
}

// Destructors - free memory
void DESTROY_NODE(node node){
  if(node == NULL){
    fprintf(stderr, "Error: Node is not initialized or already freed\n");
    return;
  }
  free(node);
}

void DESTROY_LIST(list list){
  if(list == NULL){
    fprintf(stderr, "Error: List is not initialized or already freed\n");
    return;
  }

  node current = list->head;
  while(current != NULL){
    node next = current->next;
    DESTROY_NODE(current);
    current = next;
  }
  free(list);
}

// Destructors - remove files and free memory
void REMOVE_NODE(node node){
  if (node == NULL){
    fprintf(stderr, "Removal Error: Node is not initialized or already freed\n");
    return;
  }

  if (remove(node->filename) != 0)
    fprintf(stderr, "Removal Error: Could not remove file %s\n", node->filename);

  free(node);
}

void REMOVE_ALL(list list){
  if (list == NULL){
    fprintf(stderr, "Removal Error: List is not initialized or already freed\n");
    return;
  }

  node current = list->head;
  while(current != NULL){
    node next = current->next;
    REMOVE_NODE(current);
    current = next;
  }
  free(list);
}

// deschide un fisier si il adauga la coada listei
int OPEN(list list, const char* filename){
  node new_node = INIT_NODE(filename);

  if(new_node == NULL){
    fprintf(stderr, "Opening Error: Could not open file %s\n", filename);
    return 0;
  }

  if(list->head == NULL){
    list->head = new_node;
    list->rear = new_node;
  } else{
    list->rear->next = new_node;
    list->rear = new_node;
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

// inchide(elimina din lista) si salveaza fisierul <filename> ca si alt fisier numit <newname>
int SAVEAS(list list, const char* src, const char* dst){
  node current = list->head;
  node previous = NULL;

  while (current != NULL && strcmp(current->filename, src) != 0)
  {
    previous = current;
    current = current->next;
  }

  if(current == NULL){
    fprintf(stderr, "Save Error: Could not find file %s\n", src);
    return 0;
  }

  // Remove the node from the list
  if(previous == NULL){
    list->head = current->next;
  } else{
    previous->next = current->next;
  }

  // Save the file
  if(COPY(src, dst) == 0){
    fprintf(stderr, "Save Error: Could not save file %s as %s\n", src, dst);
    return 0;
  }

  REMOVE_NODE(current);

  if(OPEN(list, dst) == 0){
    fprintf(stderr, "Save Error: Could not open file %s\n", dst);
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
  if (list == NULL){
    fprintf(stderr, "Print Error: List is not initialized");
    return;
  }

  if (list->head == NULL){
    fprintf(stderr, "Print Error: List is empty");
    return;
  }

  node current = list->head;
  while(current != NULL){
    PRINT(current->filename, file);
    current = current->next;
  }
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