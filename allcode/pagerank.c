#include "pagerank.h"

/*
 * Result print function
 * print the result into target files
 */
void print(){
    FILE *fp = fopen("./pagerankList.txt","w+");
    for(int i=0;i<FileCount;i++){
        FileNode t = FileList;
        while (t != NULL){
            if(t->rank == i)
                fprintf(fp, "%s, %d, %.7f\n",t->Filename,t->outdegree,t->PR);// print lines by lines accroring to requirement
            t = t->next;
        }
    }
    //putchar('\n');
    fclose(fp); // close fp
}

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

/*
 * Read Collection.txt
 * store the info into Filelist
 */
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
                FileList->rank = -1;
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
                LastNode->rank = -1;
                FileCount++;
            }
        }
        p++;
    }
}

/*
 * Draw a gragh with means of list
 */
void BuildConnect(char* filename, char* outname){
    FileNode tmp = FileList;
    while (tmp != NULL){
        if(strcmp(filename,tmp->Filename) == 0){
            tmp->outdegree++;
            if(tmp->out == NULL){
                tmp->out = (FileNode)malloc(sizeof(struct File));
                memset(tmp->out->Filename,0,FILENAMELENGTH * sizeof(char));
                strcpy(tmp->out->Filename,outname);
                tmp->out->next = NULL;
            }
            else{
                FileNode tout = tmp->out;
                while (tout->next != NULL){
                    tout = tout->next;
                }
                tout->next = (FileNode)malloc(sizeof(struct File));
                memset(tout->next->Filename,0,FILENAMELENGTH * sizeof(char));
                strcpy(tout->next->Filename,outname);
                tout->next->next = NULL;
            }
            break;
        }
        tmp = tmp->next;
    }
}

/*
 * split the content and get section-1
 */
void ReadOut(char *filepos, char* filename){
    char* Buffer = ReadTxt(filepos);
    char* p = Buffer;
    while (1){
        if(*p == '#' && *(p+1) == 'e' && *(p+2) == 'n' && *(p+3) == 'd'){
            break;
        }
        if(*p == 'u' && *(p+1) == 'r' && *(p+2) == 'l'){
            char name[30];
            memset(name,0,30*sizeof(char));
            int i=0;
            while(*p != '\n' && *p != '\t' && *p != ' '){
                name[i++] = *p;
                p++;
            }
            BuildConnect(filename,name);
        }
        p++;
    }
}

/*
 * try to build a pagerank list
 */
void BuildGraph(){
    FileNode t = FileList;
    while (t != NULL) {
        char filepos[100];
        memset(filepos,0,100 * sizeof(char));
        strcpy(filepos,RootDir);
        strcat(filepos,t->Filename);
        strcat(filepos,".txt");
        ReadOut(filepos,t->Filename);
        t = t->next;
    }
}

/*
 * input file name
 * return its PR
 */
double getPR(char* filename){
    FileNode t = FileList;
    while (t != NULL){
        if(strcmp(t->Filename,filename) == 0){
            return t->PR;
        }
        t = t->next;
    }
    printf("Fail to getPR\n");
    return 0;
}

/*
 * input filename
 * get outdegree of this file
 */
int getOutdegree(char* filename){
    FileNode t = FileList;
    while (t != NULL){
        if(strcmp(t->Filename,filename) == 0){
            return t->outdegree;
        }
        t = t->next;
    }
    return 0;
}

/*
 * compute the pagerank according to theory given in tutorial
 */
void PageRank(){
    FileNode tmp = FileList;
    while (tmp != NULL){
        tmp->PR = 1.0 / FileCount;
        tmp = tmp->next;
    }
    int iteration = 0;
    double diff = diffPR;


    while (iteration < maxIterations && diff >= diffPR) {
        iteration++;

        FileNode p1 = FileList;

        double sumPR;
        while (p1 != NULL){
            sumPR = 0;
            FileNode p2 = FileList;
            while (p2 != NULL){
                if(p1 == p2){
                    p2 = p2->next;
                    continue;
                }
                FileNode p3 = p2->out;
                while (p3 != NULL){
                    if(strcmp(p3->Filename, p1->Filename) == 0){
                        double nowPR = getPR(p2->Filename);
                        double nowout = getOutdegree(p2->Filename);
                        sumPR += nowPR/nowout;
                    }
                    p3 = p3->next;
                }
                p2 = p2->next;
            }
            p1->tmpPR = (1-d)/FileCount + d*sumPR; //  according to theory given in tutorial
            p1 = p1->next;
        }
        p1 = FileList;
        diff = 0;
        while (p1 != NULL){
            diff += fabs(p1->tmpPR - p1->PR);
            p1->PR = p1->tmpPR;
            p1 = p1->next;
        }
    }
}

/*
 * sort according to pagerank value
 */
void sortPR(){
    for(int i=0;i<FileCount;i++){
        double tmpPR = -1;
        FileNode t = FileList;
        FileNode Maxnode;
        while (t != NULL){
            if(t->rank < 0 && t->PR > tmpPR){
                tmpPR = t->PR;
                Maxnode = t;
            }
            t = t->next;
        }
        Maxnode->rank = i;
    }
//    FileNode t = FileList;
//    while (t){
//        printf("%s : %d\n",t->Filename,t->rank);
//        t = t->next;
//    }
}

int main(int argc, char *argv[]) {
    if(argc != 4){
        printf("Wrong argument! ./pagerank -d -diffPR -maxIterations\n");
        return 1;
    }
    else{
        d = atoi(argv[1]);
        diffPR = atoi(argv[2]);
        maxIterations = atoi(argv[3]);
    }
    ReadCollection();
    BuildGraph();
    PageRank();
    sortPR();
    print();
    printf("Done\n");
}