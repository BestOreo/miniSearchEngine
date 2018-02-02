//
// Created by 葛帅琦 on 2018/2/2.
//

#ifndef SEARCHENGINE_INVERTEDINDEX_H
#define SEARCHENGINE_INVERTEDINDEX_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define FILENAMELENGTH 50
#define MAXFILECOUNT 100
#define WORDLENGTH 30
#define URLLENGTH 30

char* RootDir = "./";
FILE *fp;

/*
 * info of url
 */
typedef struct URL* URLNode;
struct URL{
    char name[URLLENGTH];
    URLNode Left;
    URLNode Right;
};

typedef struct File* FileNode;
struct File{
    char Filename[FILENAMELENGTH];
    FileNode next;
    FileNode out;
    double PR;
    double tmpPR;
    int outdegree;
};

FileNode FileList = NULL;
FileNode LastNode = NULL;
int FileCount = 0;

/*
 * info of file
 */
typedef struct Word* WordNode;
struct Word{
    char word[WORDLENGTH];
    URLNode urlList;
    WordNode Left;
    WordNode Right;
};
WordNode WordTree = NULL;



#endif //SEARCHENGINE_INVERTEDINDEX_H
