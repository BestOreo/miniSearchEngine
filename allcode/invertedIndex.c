//
// Created by 葛帅琦 on 2018/2/2.
//

#include "invertedIndex.h"

/*
 * this function is to read all content of a file
 * argument: file postion
 * return: string of content in the file
 */
char* ReadTxt(char* root){
    FILE *fp=fopen(root,"r");
    char *Buffer = NULL;
    int ContentLength = 0;
    if(fp==NULL)
    {
        printf("Fail to openg txt");
        return NULL;
    }
    fseek(fp, 0, SEEK_END); //move pointer to tail
    ContentLength = ftell(fp);  //get the current position of the point and get the length of content
    rewind(fp);    //reset pointer to head

    // Apply memeory to store the string note the last character is '\0'
    Buffer = (char*) malloc(sizeof(char)*ContentLength+1);
    if(Buffer == NULL)
    {
        perror("内存不够!\n");
        exit(0);
    }
    //Read the file
    ContentLength = fread(Buffer, sizeof(char), ContentLength, fp);
    Buffer[ContentLength] = '\0'; //add the end character
    fclose(fp);  //  close fp
    return Buffer;
}

// Read info from the collection.txt
void ReadCollection(){
    char root[30];
    memset(root,0, 30*sizeof(char));
    strcat(root,RootDir);
    strcat(root,"collection.txt");
    char name[50];
    char *p = ReadTxt(root);
    while(*p != '\0'){
        if(*p == 'u'){
            memset(name,0,50* sizeof(char));
            int i = 0;
            while(1){
                if(*p == ' ' || *p == '\n' || *p == '\t'){
                    break;
                }
                name[i++] = *p;
                p++;
            }

            if(FileList == NULL){
                FileList = (FileNode)malloc(sizeof(struct File));
                memset(FileList->Filename,0,FILENAMELENGTH * sizeof(char));
                strcpy(FileList->Filename,name);
                FileList->next = NULL;
                FileList->out = NULL;
                FileList->outdegree = 0;
                FileCount++;
                LastNode = FileList;
            }
            else{
                LastNode->next = (FileNode)malloc(sizeof(struct File));
                LastNode = LastNode->next;
                memset(LastNode->Filename,0,FILENAMELENGTH * sizeof(char));
                strcpy(LastNode->Filename,name);
                LastNode->outdegree = 0;
                LastNode->next = NULL;
                LastNode->out = NULL;
                FileCount++;
            }
        }
        p++;
    }
}

/*
 * insert file name into null child
 */
WordNode InsetNULLChild(char* word, char* filename){
    WordNode p = (WordNode)malloc(sizeof(struct Word));
    p->urlList = (URLNode)malloc(sizeof(struct URL));
    memset(p->urlList->name,0,URLLENGTH* sizeof(char));
    strcpy(p->urlList->name, filename);
    memset(p->word,0,WORDLENGTH* sizeof(char));
    strcpy(p->word,word);
    p->urlList->Right = p->urlList->Left = NULL;
    p->Left = p->Right = NULL;
    return p;
}

/*
 * insert a word into null chile
 */
URLNode InsertURLNullNode(char* word){
    URLNode tmp = (URLNode)malloc(sizeof(struct URL));
    tmp->Right = tmp->Left = NULL;
    memset(tmp->name,0, URLLENGTH*sizeof(char));
    strcpy(tmp->name,word);
    return tmp;
}

/*
 * insert url info into url binary search tree
 */
void InsertURL(URLNode p, char* url){
    if(strcmp(url,p->name) < 0){
        if(p->Left == NULL){
            p->Left = InsertURLNullNode(url);
        }
        else{
            InsertURL(p->Left,url);
        }
    }
    if(strcmp(url,p->name) == 0){
        return;
    }
    if(strcmp(url,p->name) > 0){
        if(p->Right == NULL){
            p->Right = InsertURLNullNode(url);
        }
        else{
            InsertURL(p->Right,url);
        }
    }
}

/*
 * insert a word into binary search tree
 */
void InsertWord(WordNode WordPoint, char* word, char* filename){
    if(WordTree == NULL){
        WordTree = InsetNULLChild(word, filename);
    }
    else{
        WordNode p = WordPoint;
        if(strcmp(word,p->word)<0){
            if(p->Left != NULL)
                InsertWord(p->Left,word,filename);
            else
                p->Left = InsetNULLChild(word, filename);
        }
        else if(strcmp(word,p->word) > 0){
            if(p->Right != NULL)
                InsertWord(p->Right,word,filename);
            else
                p->Right = InsetNULLChild(word, filename);
        }
        else if(strcmp(word,p->word) == 0){
            URLNode t = p->urlList;
            InsertURL(t,filename);
        }
    }
}

/*
 * read data from section-2
 */
void ReadWord(char* start, char* end, char* filename){
    char word[40];
    memset(word,0,40* sizeof(char));
    int i=0;
    char* p = start;
    int flag = 0;
    while (p != end){
        while ( (*p >= 'a' && *p<='z') || (*p >= 'A' && *p <= 'Z')) {
            flag = 1;
            if(*p >= 'A' && *p <= 'Z'){ // lowercase: 'a' - 'A' = 32
                *p += 32;
            }
            word[i++] = *p;
            p++;
        }
        if(flag == 1){
            InsertWord(WordTree,word,filename);
            memset(word,0,40* sizeof(char));
            i=0;
            flag = 0;
        }
        p++;
    }
}

/*
 * read content of every file
 */
void ReadContent(){
    FileNode fp = FileList;
    while (fp != NULL){
        char name[50];
        memset(name,0,50* sizeof(char));
        strcpy(name,RootDir);
        strcat(name,fp->Filename);
        strcat(name,".txt");
        char* Buffer = ReadTxt(name);

        char* start = strstr(Buffer,"#start Section-2");
        char* end   = strstr(Buffer,"#end Section-2");
        while (start != end){
            if(*start == '2')
            {
                start++;
                break;
            }
            start++;
        }
        ReadWord(start,end,fp->Filename);
        fp = fp->next;
    }
}

/*
 * print url
 */
void printURLNode(URLNode p){
    if(p->Left != NULL){
        printURLNode(p->Left);
    }
    fprintf(fp,"%s ", p->name);
    if(p->Right != NULL){
        printURLNode(p->Right);
    }
}

/*
 * print binary search tree recursively
 */
void printTree(WordNode p){
    if(p == NULL)
        return;
    if(p->Left != NULL){
        printTree(p->Left);
    }
    fprintf(fp,"%s ",p->word);
    printURLNode(p->urlList);
    fprintf(fp,"\n");
    if(p->Right != NULL){
        printTree(p->Right);
    }
}

int main(int argc, char *argv[]) {
    ReadCollection();
    ReadContent();
    fp = fopen("./invertedIndex.txt","w+");
    printTree(WordTree);
    fclose(fp);
    printf("Done!\n");
}