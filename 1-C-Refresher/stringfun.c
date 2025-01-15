#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
void word_print(char*,int,int);
//add additional prototypes here
int length(char*);
void word_print(char*,int,int);
void search_replace(char*,int,int,char*,char*);
void reverse(char*,int,int);

int setup_buff(char *buff, char *user_str, int len){
    //TODO: #4:  Implement the setup buff as per the directions
    char* temp = user_str;
    int ret = 0;
    int ws = 1;
    for(int i = len; i>0; i--){
        if(*temp!='\0'){
            if(*temp != ' '){
                ws = 0;
                buff[ret] = *temp;
                ret++;
            }else{
                // printf("space at %d, %d\n", ret,ws);
                if(ws == 0){
                    ws = 1;
                    buff[ret] = ' ';
                    ret++;
                }
            }
            temp++;
        }else{
            break;
        }

        for(int i = ret; i < len; i++){
            buff[i] = '.';
        }
        
    }
    if(*temp!='\0'){
        return -1;
    }
    return ret;
    // return 0; //for now just so the code compiles. 
}

void print_buff(char *buff, int len){
    printf("Buffer:  ");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}

int count_words(char *buff, int len, int str_len){
    //YOU MUST IMPLEMENT
    char* temp = buff;
    int count = 0;
    int ws = 0;//var to reference end of word
    for(int i = 0; i<str_len+1; i++){
        if(buff[i]==' ' || buff[i]=='.'){
            if(ws == 1){
                count++;
                ws = 0;//reset word ending at a space
            }
        }else{
            ws = 1;
        }
    }
    return count;
}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

void word_print(char *buff,int len,int strlen){
    printf("Word Print\n----------\n");
    int count = 0;
    int wcount = 0;
    int ws = 0;//var to reference end of word
    for(int i = 0; i < strlen; i++){
        if(buff[i]!=' '){
            if(ws==0){
                wcount++;
                printf("%d. ",wcount);
            }
            count++;
            printf("%c",buff[i]);
            ws = 1;
        }else{
            if(ws == 1){
                printf(" (%d)\n",count);
                count = 0;
                ws = 0;//reset word ending at a space
            }
        }
    }
    if(ws==1){
        printf(" (%d)\n",count);
    }
}

void reverse(char* buff,int len,int strlen){
    printf("Reversed String: ");
    char* temp = buff;
    for(int i = strlen-1; i>-1; i--){
        printf("%c",buff[i]);
    }
    printf("\n");
}

//function to get length of string
int length(char* st){
    char* temp = st;
    int len = 0;
    while(*temp!='\0'){
        len++;
        temp++;
    }

    return len;
}

void search_replace(char* buff,int len,int strlen,char* search, char* repl){
    int ws = 0;//var to reference end of word
    int scount = 0;
    int findex = 0;
    int lindex = 0;
    int slen = length(search);
    int rlen = length(repl);
    int nbi = 0;//index for new buffer
    char* newbuff = malloc(len);//new buffer
    int breakF = 0; //check if we maxed out buffer and if we should break for loop;
    for(int i = 0; i<strlen+1; i++){  
        if(buff[i]==' ' || buff[i]=='.'){
            if(ws == 1){
                //now we check if the word is equal to the search term;
                int iseq = 1;
                // printf("%d %d\n",findex,lindex);
                for(int j = 0; j < slen; j++){
                    // printf("%c %c\n", buff[j+findex],search[j]);
                    //compare search term to word
                    if(buff[j+findex]==search[j]){
                        iseq*=1;
                    }else{
                        iseq*=0;
                    }
                }
                if(iseq==1){
                    //we found a search term 
                    //and now we need to replace it
                    //check if there is buffer space
                    if(nbi+rlen>len){
                        breakF = 1;
                    }else{
                        for(int k = 0; k < rlen; k++){
                            newbuff[k+nbi] = repl[k];
                        }
                        nbi += rlen;
                    }
                }else{
                    //not a new search tearm 
                    //so put into new buffer as is
                    if(nbi+(lindex-findex)>len){
                        breakF = 1;
                    }else{
                        for(int k = 0; k < lindex-findex; k++){
                            newbuff[k+nbi] = buff[k+findex];
                        }
                        nbi += lindex-findex;
                    }
                    
                }
                //check if we are dealing with the last word
                if(buff[i]!='.'){
                    newbuff[nbi] = ' ';
                    nbi++;
                }else{
                    newbuff[nbi] = '\0';
                }
                // printf("%d\n",scount);
                findex = lindex+1;//begining of the next word
                lindex = findex;//reset last index
                ws = 0;//reset word ending at a space
            }
            //now check if the new buffer has maxed out og buffer
            if(nbi>len-1){
                breakF = 1;
                
            }
        }else{
            lindex++;//not end of word so we increase last index
            ws = 1;
        }

        if(breakF == 1){
            break;
        }

    }
    if(breakF == 1){
        printf("Error: Modified string is larger than buffer\n");
    }else{
        printf("Modified String: %s\n", newbuff);
    }
    
}

int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    char* search;
    char* replace;

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
    //      Answer: This is save because this doesnt check for argv[1] unless there are at least 2 arguments
    //              and spaces do not count as arguments so there will always be an argv[1] if there are at least 2 arguments    
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
    //      This is to check for the number of arguments.
    //      if we have more than 3 arguments, the code should
    //      not run, however this is only if we dont do the
    //      search and replace function, which adds 2 extra
    //      arguments, so i will add that
    
    
    if(opt == 'x'){
        if (argc != 5){
            usage(argv[0]);
            exit(1);
        }
    }else{
        if (argc > 3){
            usage(argv[0]);
            exit(1);
        }
    }
    

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    // CODE GOES HERE FOR #3
    buff = malloc(BUFFER_SZ);
    if(buff==NULL){
        printf("Memory allocation for buffer failed\n");
        exit(99);
    }

    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    // printf("%d\n", user_str_len);
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options
        case 'r':
            reverse(buff, BUFFER_SZ, user_str_len);
            break;
        case 'w':
            word_print(buff, BUFFER_SZ, user_str_len);
            break;
        case 'x':
            search = argv[3];
            replace = argv[4];
            search_replace(buff, BUFFER_SZ, user_str_len, search, replace);
            break;
        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    // print_buff(buff,BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          Answer: This is so that if we try to change the buffer size
//                  in the whole program,