//
// Created by 葛帅琦 on 2018/2/2.
//

#ifndef SEARCHENGINE_SEARCHENGINE_H
#define SEARCHENGINE_SEARCHENGINE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WORDLENGTH 50
#define URLLENGTH 30


// struct to store url info
typedef struct URL* URLNode;
struct URL{
    char name[URLLENGTH];
    URLNode next;
};
URLNode URLList = NULL;

// all words are stored in list, every listnode has a list stored with url concerning about this word
typedef struct WNode* WordListNode;
struct WNode{
    char word[WORDLENGTH];
    URLNode URLList;
    WordListNode next;
};
WordListNode WordList;

// struct for keyword(input)
typedef struct Word* WordNode;
struct Word{
    char word[WORDLENGTH];
    WordNode next;
    WordListNode target;
};
WordNode KeyWordList = NULL;


#endif //SEARCHENGINE_SEARCHENGINE_H
