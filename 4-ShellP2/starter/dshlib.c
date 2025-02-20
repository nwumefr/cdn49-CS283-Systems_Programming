#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "dshlib.h"
#include <errno.h>
// #include "dragon.c"

/*
 * Implement your exec_local_cmd_loop function by building a loop that prompts the 
 * user for input.  Use the SH_PROMPT constant from dshlib.h and then
 * use fgets to accept user input.
 * 
 *      while(1){
 *        printf("%s", SH_PROMPT);
 *        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
 *           printf("\n");
 *           break;
 *        }
 *        //remove the trailing \n from cmd_buff
 *        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
 * 
 *        //IMPLEMENT THE REST OF THE REQUIREMENTS
 *      }
 * 
 *   Also, use the constants in the dshlib.h in this code.  
 *      SH_CMD_MAX              maximum buffer size for user input
 *      EXIT_CMD                constant that terminates the dsh program
 *      SH_PROMPT               the shell prompt
 *      OK                      the command was parsed properly
 *      WARN_NO_CMDS            the user command was empty
 *      ERR_TOO_MANY_COMMANDS   too many pipes used
 *      ERR_MEMORY              dynamic memory management failure
 * 
 *   errors returned
 *      OK                     No error
 *      ERR_MEMORY             Dynamic memory management failure
 *      WARN_NO_CMDS           No commands parsed
 *      ERR_TOO_MANY_COMMANDS  too many pipes used
 *   
 *   console messages
 *      CMD_WARN_NO_CMD        print on WARN_NO_CMDS
 *      CMD_ERR_PIPE_LIMIT     print on ERR_TOO_MANY_COMMANDS
 *      CMD_ERR_EXECUTE        print on execution failure of external command
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 1+)
 *      malloc(), free(), strlen(), fgets(), strcspn(), printf()
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 2+)
 *      fork(), execvp(), exit(), chdir()
 */

int alloc_cmd_buff(cmd_buff_t *cmd_buff){
    cmd_buff->argc = 0;
    cmd_buff->_cmd_buffer = malloc(CMD_MAX);
    return 0;
}
int free_cmd_buff(cmd_buff_t *cmd_buff){
    //free the cmd char buffer
    free(cmd_buff->_cmd_buffer);
    //for each argument free it character buffer
    for(int i=0; i<cmd_buff->argc;i++){
        free(cmd_buff->argv[i]);
    }
    //then free the argv array
    free(cmd_buff->argv);
    free(cmd_buff);
    return 0;
}
int clear_cmd_buff(cmd_buff_t *cmd_buff);

int build_cmd_buff(char *cmd_line, cmd_buff_t *cmd_buff){
    cmd_buff->argc = 0; //initialize command count

    if (!cmd_line || strlen(cmd_line) == 0) {
        printf(CMD_WARN_NO_CMD);
        return WARN_NO_CMDS;
    }

    // char * tok;
    char delim = '\"';
    char * opt = NULL;
    char * ipt = NULL;
    // tok = strtok_r(cmd_line,&delim1,&opt);
    // char * quote_buffer;
    int len = 0;//int to keep track of length 
    char *a,*b;
    char ** preargs;
    preargs = malloc(sizeof(char*)*CMD_ARGV_MAX);
    for(a=strtok_r(cmd_line,&delim,&opt); a!=NULL; a=strtok_r(NULL,&delim,&opt)) {
        // printf("%s %d\n",a, len);
        int la = strlen(a);
        preargs[len]=malloc(la+1);
        strcpy(preargs[len],a); 
        // Trim leading and trailing spaces
        while (*a == SPACE_CHAR) {
            a++;
        } // Trim leading spaces
        while (la > 0 && a[la - 1] == SPACE_CHAR){
            a[--la] = '\0'; // Trim trailing spaces
        }
        // if(len%2==0){
        //     printf("lol\n");
        //     // for(b=strtok_r(a,&delim2,&ipt); b!=NULL ; b=strtok_r(NULL,&delim2,&ipt) )
        //     //         printf("%s\n",b);
        // }
        len++;
    }
   
    int k = 0;
    for(int i=0; i<len;i++){
        if(k<CMD_MAX){
            // printf("%s\n",preargs[i]);
            if(i%2==0){
                char delim2 = SPACE_CHAR;
                for(b=strtok_r(preargs[i],&delim2,&ipt); b!=NULL ; b=strtok_r(NULL,&delim2,&ipt) ){
                    // printf("%s\n",b);
                    cmd_buff->argv[cmd_buff->argc] = malloc(strlen(b)+1);
                    strcpy(cmd_buff->argv[cmd_buff->argc],b);
                    cmd_buff->argc++;
                    k++;
                }
                        
            }else{
                int L = strlen(preargs[i]);
                char * new_st = malloc(L+1);
                // new_st[0] = '\"';
                // for(int j = 1; j<L+1; j++){
                //     new_st[j] = preargs[i][j-1];
                // }
                strcpy(new_st,preargs[i]);
                // new_st[L+1]='\"';
                // new_st[L]='\0';
                // printf("%s\n",new_st);
                cmd_buff->argv[cmd_buff->argc] = malloc(L+1);
                strcpy(cmd_buff->argv[cmd_buff->argc],new_st);
                cmd_buff->argc++;
                k++;
            }

        }else{
            printf("Too many args\n");
            return ERR_CMD_OR_ARGS_TOO_BIG;
        }
    }
    cmd_buff->argv[cmd_buff->argc] = NULL;
    // for(int i=0; i<cmd_buff->argc; i++){
    //     printf("<%d> %s\n",i,cmd_buff->argv[i]);
    // }
    
    return OK;
}

int cd_command(cmd_buff_t *cmd){
    if(cmd->argc==2){
        chdir(cmd->argv[1]);
    }  
    return 0;
}

int bi_rc(){
    printf("%d\n",WEXITSTATUS);
    return 0;
}

Built_In_Cmds match_command(const char * input){
    if (strcmp(input, "dragon") == 0) return BI_CMD_DRAGON;
    else if (strcmp(input, "cd") == 0) return BI_CMD_CD;
    else if (strcmp(input, EXIT_CMD) == 0) return BI_CMD_EXIT;
    else if (strcmp(input, "rc") == 0) return BI_RC;
    else return BI_NOT_BI;
}


Built_In_Cmds exec_built_in_cmd(cmd_buff_t *cmd){
    if (strcmp(cmd->argv[0], "dragon") == 0) print_dragon();
    else if (strcmp(cmd->argv[0], "cd") == 0) cd_command(cmd);
    else if (strcmp(cmd->argv[0], EXIT_CMD) == 0)exit(0);
    else if (strcmp(cmd->argv[0], "rc") == 0) bi_rc();
    else{
        printf("unknown command\n");
    }
    return BI_EXECUTED;
}

int exec_cmd_external(cmd_buff_t *cmd){
    // for(int i=0; i<cmd->argc; i++){
    //     printf("<%d> %s\n",i,cmd->argv[i]);
    // }
    pid_t pid;
    int status;
    
    pid = fork();
    int sk = 0;
    if (pid ==  0){
        sk = execvp(cmd->argv[0], cmd->argv); 
        if (sk == -1){
            printf("error in child process\n");
            // WEXITSTATUS = sk;
        }
        exit(errno);
    }else if (pid < 0){
      perror("error in forking\n");
    }else{
        //wait for child process to end
        waitpid(pid, &status, 0);    
    }
    return status;
}

int exec_cmd(cmd_buff_t *cmd){
    Built_In_Cmds is_builtin = match_command(cmd->argv[0]);
    if(is_builtin == BI_NOT_BI){
        return exec_cmd_external(cmd);
    }else{
        return exec_built_in_cmd(cmd);
    }
    
}
 

int exec_local_cmd_loop()
{
    char *cmd_buff;
    int rc = 0;
    cmd_buff_t cmd;
    alloc_cmd_buff(&cmd);
    cmd_buff = malloc(ARG_MAX);
    int status = 0;
    // TODO IMPLEMENT MAIN LOOP
    while(1){
        printf("%s", SH_PROMPT);
        fgets(cmd_buff, ARG_MAX, stdin);
        // printf("\n");
        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
        // printf("%s %s %d\n", cmd_buff,EXIT_CMD,strcmp(cmd_buff,EXIT_CMD));
        if (feof(stdin)){
            // printf("\n");
            printf("cmd loop returned %d\n",status);
            exit(0);
            
        }
        // if(strcmp(cmd_buff, "dragon")==0){
            
        //     printDragon("dragon.txt");
        // }
        // // //remove the trailing \n from cmd_buff
        

        build_cmd_buff(cmd_buff, &cmd);
        int status = exec_cmd(&cmd);
        WEXITSTATUS = status;

    }
    // TODO IMPLEMENT parsing input to cmd_buff_t *cmd_buff

    // TODO IMPLEMENT if built-in command, execute builtin logic for exit, cd (extra credit: dragon)
    // the cd command should chdir to the provided directory; if no directory is provided, do nothing

    // TODO IMPLEMENT if not built-in command, fork/exec as an external command
    // for example, if the user input is "ls -l", you would fork/exec the command "ls" with the arg "-l"
    
    
    // printf("%d\n",cmd.argc);
    
    

    return OK;
}

