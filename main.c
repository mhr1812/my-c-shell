#include "headers.h"
#include "execute.c"

void ctrl_d(){
    printf("\n");
    write_history();
    killall();
    exit(EXIT_SUCCESS);
}

char *get_input(){
    ssize_t input_size = 0;
    char *input_line = NULL;
    ssize_t x = getline(&input_line, &input_size, stdin);
    if(x==-1) ctrl_d();
    return input_line;
}

void prompt(){
    char *DIR;
    if (getcwd(CWD, sizeof(CWD)) == NULL){
       perror("getcwd() error");
       exit(EXIT_FAILURE);
    }

    else{
        char * p;
        p = strstr(CWD, HOME);
        //printf("%s %s \n", CWD, HOME);
        if(p){
            DIR = p + strlen(HOME);
            printf("%s@%s:~%s>", USER, HOST, DIR);
        }
        else{
            DIR = CWD;
            printf("%s@%s:%s>", USER, HOST, DIR);
        }

    }

    
}

char **tokenize(char *input){
    char *p = strtok (input, ";");
    char **array = malloc(256 * sizeof(char *));
    no = 0;
    while (p != NULL){
        array[no++] = p;
        p = strtok (NULL, ";");
    }
    return array;
}

void shell(){
    char *input;
    do{
        CHILD_ID = -1;
        prompt();
        input = get_input();
        char **commands;
        commands = tokenize(input);
        for(int i = 0; i < no; i++)
            execute(commands[i]);
            
    } while(1);
}

void ctrl_c(int signum){
    pid_t p = getpid();
    if(p < 0)
        perror("Error");
    
    else if (p != SHELL_ID)
        return;

    if (CHILD_ID != -1){
    	kill(CHILD_ID, SIGINT); 
    	CHILD_ID = -1;
    }
               
    
    signal(SIGINT, ctrl_c); 
} 

void ctrl_z(int signum){
    pid_t p = getpid();

    if (p < 0) {
        perror("Error getting PID");
    } 
    else if (p != SHELL_ID) {
        return;
    }

    if (CHILD_ID != -1){
        if (kill(CHILD_ID, SIGTSTP) == -1) {
            perror("Error sending SIGTSTP");
        } else {
            int status;
            waitpid(CHILD_ID, &status, WUNTRACED);

            if (WIFSTOPPED(status)) {
                printf("Process %d stopped and moved to background.\n", CHILD_ID);
            }

            CHILD_ID = -1;
        }
    }

    signal(SIGTSTP, ctrl_z);
}

int main(){
    gethostname(HOST, sizeof(HOST));
    getlogin_r(USER, sizeof(USER));
    char *DIR;
    
    pid_t p_id;
    p_id = getpid();
    SHELL_ID = p_id;
    char *exe = malloc(sizeof(char) *(40));
    sprintf(exe,"/proc/%d/exe", p_id);
    int ret = readlink(exe, HOME, 1000);
    HOME[ret] = '\0';

    for(int i = strlen(HOME)-1; i>=0; i--){
        if(HOME[i] == '/'){
            HOME[i] = '\0';
            break;
        }
    }

    load_history();
    
    if (signal(SIGTSTP, ctrl_z) == SIG_ERR) {
        perror("signal SIGTSTP");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGINT, ctrl_c) == SIG_ERR) {
        perror("signal SIGINT");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGCHLD, handler) == SIG_ERR) {
        perror("signal SIGCHLD");
        exit(EXIT_FAILURE);
    }
    
    shell();
    return 0;
}
