//
// Created by 葛帅琦 on 2018/2/2.
//

#ifndef SEARCHENGINE_PAGERANK_H
#define SEARCHENGINE_PAGERANK_H

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define FILENAMELENGTH 50
#define MAXFILECOUNT 100

char* RootDir = "./";

// struct to store info of Filenode
typedef struct File* FileNode;
struct File{
    char Filename[FILENAMELENGTH];
    FileNode next;
    FileNode out;
    double PR;
    double tmpPR;
    int outdegree;
    int rank;
};

FileNode FileList = NULL;
FileNode LastNode = NULL;
int FileCount = 0; // the number of files

// default value
double d = 0.85;
double diffPR = 0.00001;
int maxIterations = 1000;


#endif //SEARCHENGINE_PAGERANK_H
