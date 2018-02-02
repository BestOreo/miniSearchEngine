//
// Created by 葛帅琦 on 2018/2/2.
//

#include "SearchEngine.h"

/*
 * insert keyword into keywordlist
 */
void InsertKeyWord(char * word){
    if(KeyWordList == NULL){ // if head node is null
        KeyWordList = (WordNode)malloc(sizeof(struct Word));
        KeyWordList->next = NULL;
        memset(KeyWordList->word,0,WORDLENGTH * sizeof(char));
        strcpy(KeyWordList->word, word);
    }
    else{
        WordNode t = KeyWordList;
        while (t->next != NULL){ // find the last node
            t = t->next;
        }
        t->next = (WordNode)malloc(sizeof(struct Word));
        t = t->next;
        t->next = NULL;
        memset(t->word,0,WORDLENGTH * sizeof(char));
        strcpy(t->word, word);
    }
}

/*
 * read the info from command line argument
 * store them into KeywordList
 */
void InputKeyWord(int argc, char* argv[]){

    for(int i=1;i<argc;i++){
        InsertKeyWord(argv[i]);
    }
}

/*
 * Function for reading txt
 * arg: positon
 * retrun string
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
 * insert url and pagerank into URLList
 */
void InsertURLList(char* name){
    if(URLList == NULL){ // if head is null
        URLList = (URLNode)malloc(sizeof(struct URL));
        memset(URLList->name,0,URLLENGTH* sizeof(char));
        strcpy(URLList->name,name);
        URLList->next = NULL;
    }
    else{
        URLNode tmp = URLList;
        while (tmp->next != NULL){  // find the last node
            tmp = tmp->next;
        }
        tmp->next = (URLNode)malloc(sizeof(struct URL));
        tmp = tmp->next;
        memset(tmp->name,0,URLLENGTH* sizeof(char));
        strcpy(tmp->name,name);
        tmp->next = NULL;
    }

}

/*
 * deal the data in pagerankList.txt
 * store the info in URLList
 * format: urlname, pagerank
 */
void Deal_prBuffer(char* Buffer){
    char *p = Buffer;
    while(*p != '\0'){
        if(*p == 'u'){
            char name[30];
            memset(name,0, sizeof(name));
            int i=0;
            while (*p != ','){
                name[i++] = *(p++);
            }
            InsertURLList(name);
        }
        p++;
    }
}

/*
 * insert a word with its url
 * all words are stored in a struct list
 */
void InsertWordList(char* word, WordNode urllist){
    WordListNode LastNode; // firstly find the last node of WordList
    if(WordList == NULL) {
        WordList = (WordListNode) malloc(sizeof(struct WNode)); // allocate memory to new node
        WordList->next = NULL;
        memset(WordList->word, 0, sizeof(char) * WORDLENGTH);
        strcpy(WordList->word,word);
        LastNode = WordList;
    }
    else {
        WordListNode t = WordList;
        while (t->next != NULL) {
            t = t->next;
        }
        t->next = (WordListNode) malloc(sizeof(struct WNode));  // allocate memory to new node
        t->next->next = NULL;
        memset(t->next->word, 0, sizeof(char) * WORDLENGTH);
        strcpy(t->next->word,word);
        LastNode = t->next;
    }
    //
    WordNode t = urllist;
    while (t!=NULL){
        if( LastNode->URLList == NULL){
            LastNode->URLList = (URLNode)malloc(sizeof(struct URL));
            LastNode->URLList->next = NULL;
            memset(LastNode->URLList->name,0,URLLENGTH* sizeof(char));
            strcpy(LastNode->URLList->name,t->word);
        }
        else{
            URLNode ut = LastNode->URLList;
            while (ut->next != NULL){
                ut = ut->next;
            }
            ut->next = (URLNode)malloc(sizeof(struct URL));
            ut = ut->next;
            ut->next = NULL;
            memset(ut->name,0,URLLENGTH* sizeof(char));
            strcpy(ut->name,t->word);
        }
        t =t->next;
    }
}

/*
 * Splilt a line, format: wordname url1, url2, url3
 * Store the infomation from invertedIndex.txt into WordList
 */
void SplitLine(char* Buffer){
    char* p = Buffer;
    char word[30];
    WordNode wordurl = NULL; // a word has several urls, so use list to store info of url
    if(*p == ' ')
        return;
    while (*p != '\n' && *p != '\0'){
        memset(word,0, 30 * sizeof(char));
        int i = 0;
        while (*p != ' '){
            word[i++] = *(p++); // get word name from the string
        }
        while (*p != '\n' && *p != '\0'){
            if(*p == ' '){
                p++;
                continue;
            }
            char url[30];
            memset(url,0,30* sizeof(char));
            int i = 0;
            while (*p != ' ' && *p != '\n' && *p != '\0'){
                url[i++] = *(p++); // get url from the string
            }

            if(wordurl == NULL){ // if head is null
                wordurl = (WordNode)malloc(sizeof(struct Word));
                wordurl->next = NULL;
                memset(wordurl->word,0, WORDLENGTH* sizeof(char));
                strcpy(wordurl->word,url);
            }
            else{
                WordNode t= wordurl;
                while (t->next != NULL){    // find the last node
                    t = t->next;
                }
                t->next = (WordNode)malloc(sizeof(struct Word));
                t->next->next = NULL;
                memset(t->next->word,0, WORDLENGTH* sizeof(char));
                strcpy(t->next->word,url);
            }

            p++;
        }
        p++;
    }
    InsertWordList(word,wordurl); // insert a word with its url
}

/*
 * Deal the string in invertedindex.txt
 */
void Deal_indexBuffer(char * Buffer){
    char *p = Buffer;
    while (*p != '\0'){
        // Read a line
        char Line[100];
        memset(Line,0,100* sizeof(char));
        int i = 0;
        while (*p != '0' && *p != '\n'){
            Line[i++] = *(p++);
        }
        SplitLine(Line);
        p++;
    }
}

/*
 * for test
 */
void PrintWordList(){
    WordListNode t = WordList;
    while (t != NULL){
        printf("%s ",t->word);
        URLNode p = t->URLList;
        while (p!=NULL){
            printf("%s ",p->name);
            p = p->next;
        }
        putchar('\n');
        t = t->next;
    }
}

/*
 * for test
 */
void PrintURLList(){
    URLNode t = URLList;
    while (t != NULL){
        printf("%s\n",t->name);
        t =t->next;
    }
}

/*
 * for test
 */
void PrintKeyWordList(){
    WordNode t= KeyWordList;
    while (t){
        printf("%s\n",t->word);
        t = t->next;
    }
}

/*
 * Read data from 2 txt into 2 buffers
 * Then Deal with strings in 2 buffers
 */
void ReadData(){
    char * prBuffer = ReadTxt("./pagerankList.txt");
    char * indexBuffer = ReadTxt("./invertedIndex.txt");
    Deal_prBuffer(prBuffer);
    Deal_indexBuffer(indexBuffer);
}

WordListNode SearchFromList(char* word){
    WordListNode t = WordList;
    while (t){
        if(strcmp(t->word, word) == 0)
            return t;
        t =t->next;
    }
    return NULL;
}

/*
 * check whether nowurl(argment) is in another word(target)'s urllist
 */
int FindWord(char* nowurl, WordListNode target){
    URLNode s = target->URLList;
    while (s){
        if(strcmp(s->name,nowurl) == 0)
            return 1;
        s = s->next;
    }
    return 0;
}

/*
 * now we have got all words with their urls seperately,
 * but we only need to print common url
 * The idea is parse one urllist of the first word in Wordlist
 * and check whether every word also has the word
 */
void FindCommon(){
    if(KeyWordList == NULL)
        return;
    URLNode t = KeyWordList->target->URLList;
    while (t){
        char* nowurl = t->name;

        WordNode keyp = KeyWordList;
        int flag = 1;
        while (keyp){
            flag *= FindWord(nowurl,keyp->target);
            keyp = keyp->next;
        }
        if(flag == 1){
            printf("%s ",nowurl);
        }
        t = t->next;
    }
    putchar('\n');
}

/*
 * function to start searching words
 */
void SearchEngine(){
    WordNode t = KeyWordList;
    while (t != NULL){
        // some preparation in advance
        char* inputword = t->word;
        WordListNode target = SearchFromList(inputword); // check whether the input word in indexfile. if not return null. else return node address
        if(target == NULL)
            return;
        t->target = target;
        t = t->next;
    }
    FindCommon();
}

int main(int argc, char* argv[]){
    ReadData(); // read data from files
    InputKeyWord(argc,argv);    // read command line arguments
    SearchEngine(); // start search engine
//    PrintKeyWordList();
    // PrintURLList();
    // PrintWordList();

}