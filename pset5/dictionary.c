// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
#define HASH_MAX 32000

// Hash table
node *table[HASH_MAX];

int the_size_of_dictionary = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // printf("Word: %s\n", word);
    char *the_word = malloc(LENGTH + 1);

    strcpy(the_word, word);
    
    for (int i = 0; the_word[i] != '\0'; i++) {
        the_word[i] = tolower(the_word[i]);
    }
    
    unsigned int the_hash_code = hash(the_word);
    // printf("The hash code of %s: %d\n", the_word, the_hash_code);

    node *the_cursor = table[the_hash_code];

    while (true) {
        if (the_cursor == NULL) {
            free(the_word);
            return false;
        }
        if (!strcmp(the_cursor->word, the_word)) {
            free(the_word);
            return true;
        }
        the_cursor = the_cursor->next;
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long long the_hash = 5381;

    int the_check_length = strlen(word);

    for (int i = 0; i < the_check_length; i++) {
        the_hash = ((the_hash << 5) + the_hash) + word[i];
    }

    // printf("The Hash: %llu\n", the_hash);

    return (unsigned int)(the_hash % (unsigned long long)HASH_MAX);
} 

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // time_t start = time(NULL);

    // open dictionary
    FILE *the_dictionary = fopen(dictionary, "r");
    if (the_dictionary == NULL) {
        printf("Dict\n");
        return false;
    }

    char *the_current_word;
    unsigned int the_hash_code;

    for (int i = 0; i < HASH_MAX; i++) {
        table[i] = NULL;
    }

    int the_loop_count = 0;

    // unsigned int the_hashes_used[HASH_MAX];
    // for (int i = 0; i < HASH_MAX; i++) {
    //     the_hashes_used[i] = 0;
    // }

    // read dictionary file one line at a time
    while (!feof(the_dictionary)) {
        the_current_word = malloc(LENGTH + 1);
        if (the_current_word == NULL) {
            printf("Malloc Current Word\n");
            return false;
        }

        for (int j = 0, n = LENGTH + 1; j < n; j++) {
            the_current_word[j] = '\0';
        }
        
        // fgets(the_current_word, LENGTH + 1, the_dictionary);
        fscanf(the_dictionary, "%s", the_current_word);

        if (the_current_word != NULL && strcmp(the_current_word, "")) {
            the_loop_count++;

            the_hash_code = hash(the_current_word);
            
            // if (the_hash_code == 20777) {
            //     printf("The current word: %s\n", the_current_word);
            // }

            // printf("Hash code: %u\n", the_hash_code);
            // the_hashes_used[the_hash_code]++;

            node *n = malloc(sizeof(node));
            if (n == NULL) {
                printf("Malloc node\n");
                return false;
            }
            strcpy(n->word, the_current_word);
            n->next = table[the_hash_code];
            table[the_hash_code] = n;
        }
        
        free(the_current_word);
    }

    // printf("Loop Count: %d\n", the_loop_count);
    the_size_of_dictionary = the_loop_count;

    // for (int i = 0; i < HASH_MAX; i++) {
    //     if (the_hashes_used[i] > 12) {
    //         printf("Hash code %d was used %d times\n", i, the_hashes_used[i]);
    //     }
    // }

    // time_t end = time(NULL);
    // printf("The loading took: %ld seconds\n", end - start);

    // close dictionary
    fclose(the_dictionary);

    // should return true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return the_size_of_dictionary;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < HASH_MAX; i++) {
        node *the_current_cursor = table[i];
        node *the_next_cursor = table[i];
        while (the_next_cursor != NULL) {
            the_next_cursor = the_current_cursor->next;
            free(the_current_cursor);
            the_current_cursor = the_next_cursor;
        }
    }
    return true;
}
