// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <cs50.h>
#include <ctype.h>

// declare number of words in dictionary as global variable
int num_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cur_node = root;

    for(int i = 0; word[i] != '\0'; i++)
    {
        // determine index
        int index = (isalpha(word[i])) ? (tolower(word[i]) - 'a') : 26;

        // if misspelled
        if (!cur_node->children[index])
        {
            return false;
        }

        cur_node = cur_node->children[index];
    }

    // check if end is actually a word
    if (cur_node->is_word == false)
    {
        return false;
    }

    return true;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open dictionary
    FILE *file = fopen(dictionary, "r");
    // check that file successfully loaded
    if (file == NULL)
    {
        printf("Could not open dictionary file.\n");
        return false;
    }

    // initializing node
    root = calloc(1,sizeof(node));
    node *cur_node = root;

    if (!root)
    {
        printf("Trie does not exist.\n");
        return false;
    }

    // iterating each character
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        // if not end of word
        if (c != '\n')
        {
            // set index depending on whether character is apostrophe or not
            int index = (isalpha(c)) ? (c - 'a') : 26;
            if(cur_node->children[index] == NULL)
            {
                // create new node and set to children[i]
                node *next = calloc(1,sizeof(node));
                cur_node->children[index] = next;
            }

            // iterate to next level
            cur_node = cur_node->children[index];
        }
        // set end of word flag to true
        else
        {
            cur_node->is_word = true;
            cur_node = root;
            num_words++;
        }
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return num_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // initialize node to root and call recursive frie function
    node *cursor = root;
    // check if not null
    if (cursor)
    {
        frie(cursor);
        return true;
    }
    else
    {
        return false;
    }
}

// Recursive function that frees the node if all children are null
void frie(node *cursor)
{
    for (int i = 0; i < 27; i++)
    {
        if (cursor->children[i] != NULL)
        {
            frie(cursor->children[i]);
        }
    }

    free(cursor);
}