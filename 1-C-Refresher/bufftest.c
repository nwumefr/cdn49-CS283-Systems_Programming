#include <stdio.h>
#include <stdlib.h>

#define BUFS 50

int setup_buffer(char* buffer, char* string, int buffsize){
    char* temp = string;
    int ret = 0;
    int ws = 1;
    for(int i = buffsize; i>0; i--){
        if(*temp!='\0'){    
            if(*temp != ' '){
                ws = 0;
                buffer[ret] = *temp;
                ret++;
            }else{
                // printf("space at %d, %d\n", ret,ws);
                if(ws == 0){
                    ws = 1;
                    buffer[ret] = ' ';
                    ret++;
                }
                
            }
            
            temp++;
        }else{
            break;
        }

        for(int i = ret; i < buffsize; i++){
            buffer[i] = '.';
        }
        
    }
    if(*temp!='\0'){
        return -1;
    }
    return ret;
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

void word_print(char *buff,int len,int strlen){
    printf("Word Print\n----------\n");
    int count = 0;
    int wcount = 0;
    int ws = 0;//var to reference end of word
    for(int i = 0; i<strlen+1; i++){
        if(buff[i]==' ' || buff[i]=='.'){
            if(ws == 1){
                printf(" (%d)\n",count);
                count = 0;
                ws = 0;//reset word ending at a space
            }
        }else{
            if(ws==0){
                wcount++;
                printf("%d. ",wcount);
            }
            count++;
            printf("%c",buff[i]);
            ws = 1;
        }
    }
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

void reverse(char* buff,int len,int strlen){
    printf("Reversed String: ");
    char* temp = buff;
    for(int i = strlen-1; i>-1; i--){
        printf("%c",buff[i]);
    }
    printf("\n");
}

int main(){
    char* test_str = " Replacing words in strings is not fun!";
    // printf("%d\n", len(test_str));
    printf("\n");
    char* buffer = malloc(BUFS);
    int test = setup_buffer(buffer,test_str,BUFS);
    printf("%d\n",test);
    // for(int i = 0; i<BUFS;i++){
    //     printf("%d %c\n",i+1,buffer[i]);
    // }
    // printf("%s\n",buffer);
    printf("%d\n",count_words(buffer,BUFS,test));
    // printf("%d\n",);
    search_replace(buffer,BUFS,test,"not","very");
    word_print(buffer,BUFS,test);
    reverse(buffer,BUFS,test);
    return 0;
}