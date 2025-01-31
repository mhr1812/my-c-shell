#include "headers.h"
#include <time.h> 

int is_hidden(char *filename){
    if(filename[0] == '.') return 1;
    else return 0;
}

void long_info(char *directory, char *filename){
    char* filepath = (char*)malloc(sizeof(char)*(strlen(directory)+strlen(filename)));
    strcpy(filepath,directory);
    strcat(filepath,"/");
    strcat(filepath,filename);
    struct stat name;
    if(stat(filepath,&name)<0) perror("ERROR!");
    else{
        struct group *gr = getgrgid(name.st_gid);
        struct passwd *pw =  getpwuid(name.st_uid);
        mode_t p = name.st_mode;
        char *perms = malloc(sizeof(char)*10+1);
        perms[0] = (stat(filepath,&name)==0 && S_ISDIR(name.st_mode))?'d':'-';
        perms[1] = (p & S_IRUSR)?'r':'-';
        perms[2] = (p & S_IWUSR)?'w':'-';
        perms[3] = (p & S_IXUSR)?'x':'-';
        perms[4] = (p & S_IRGRP)?'r':'-';
        perms[5] = (p & S_IWGRP)?'w':'-';
        perms[6] = (p & S_IXGRP)?'x':'-';
        perms[7] = (p & S_IROTH)?'r':'-';
        perms[8] = (p & S_IWOTH)?'w':'-';
        perms[9] = (p & S_IXOTH)?'x':'-';
        perms[10] = '\0';
        char *time = (char *)malloc(sizeof(char) * 50); 
        strftime(time, 50, "%b  %d %H:%M", localtime( &name.st_mtime));
        //printf("%s",filename);
        printf("%s\t%ld\t%s\t%s\t%ld\t %s\t%s\n", perms, name.st_nlink, pw->pw_name,gr->gr_name, name.st_size, time, filename);
        free(perms);
    }
   
    free(filepath);
}

void ls_out(char *dir_name, int flag, int hidden){
    struct dirent **file;
    int n = scandir(dir_name, &file, NULL, alphasort);
    if(n < 0)
    {
        perror("ERROR!");
        return;
    }

    blkcnt_t total_blocks = 0;

    if (flag == 1) {
        for(int i = 0; i < n; i++) {
            if(hidden == 0 && is_hidden(file[i]->d_name))
                continue;

            char* filepath = (char*)malloc(sizeof(char)*(strlen(dir_name)+strlen(file[i]->d_name) + 2));
            strcpy(filepath, dir_name);
            strcat(filepath, "/");
            strcat(filepath, file[i]->d_name);

            struct stat name;
            if (stat(filepath, &name) == 0) {
                total_blocks += name.st_blocks;
            } else {
                perror("ERROR!");
            }
            free(filepath);
        }
        printf("Total blocks: %ld\n", total_blocks / 2); // st_blocks is in 512-byte units, typically divided by 2 to get 1KB blocks
    }

    switch(flag){
        case 0:
            for(int i = 0; i < n; i++){ 
                if(hidden == 0 && !is_hidden(file[i]->d_name) || hidden == 1)
                {
                    printf("%s\t",file[i]->d_name);  
                }
                free(file[i]);
            }

            printf("\n");
            free(file);
            break;
    
        case 1:
            printf("Long list of %s: \n",dir_name);
            for(int i = 0; i < n; i++)
            {
                if(hidden == 0 && !is_hidden(file[i]->d_name) || hidden == 1)
                    long_info(dir_name, file[i]->d_name);
                free(file[i]);
            }
            free(file);
            break;
    }
}



void ls(char *command){
    int f1 = 0, hidden =0, x = 0, y = 0;
    char *token = command;
    token = strtok(NULL, " \n\t\r");
    while (token != NULL){
        x = 1;
        if(!strcmp(token,"-l"))	f1 = 1;
    	else if(!strcmp(token,"-a")) hidden = 1;
	else if(!strcmp(token,"-al") || !strcmp(token,"-la")){   
            f1 = 1; 
            hidden = 1;
        }    
        else{
            y = 1;
            char *final_path;
            int n = strlen(token);
            char *temp = (char *)malloc(sizeof(char) *n +1);
            temp[n] ='\0';
            if(token[0] == '~'){
                if(n > 1){
                    for(int i=1; i < n; i++)
                        temp[i-1] = token[i];
                }
                final_path = (char *)malloc(sizeof(char) *(n + strlen(HOME) + 10));
                strcpy(final_path, HOME);
                strcat(final_path, temp);
                final_path[n + strlen(HOME)-1] = '\0';
                free(temp);
            }
            else{
                final_path = (char *)malloc(sizeof(char)*n + 100);
                strcpy(final_path, token);
            }
        
            ls_out(final_path, f1, hidden);
            free(final_path);
        }
        token = strtok(NULL, " \n\t\r");
    }

    if(x==0 || (x==1 && y == 0))
        ls_out(".", f1, hidden);
        
}
