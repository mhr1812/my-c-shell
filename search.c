#include "headers.h"

bool search_directory(const char *dir_name, const char *target) {
    struct dirent *entry;
    DIR *dp = opendir(dir_name);

    if (dp == NULL) {
        return false; 
    }

    while ((entry = readdir(dp)) != NULL){
    	if (strcmp(entry->d_name, target) == 0){
                closedir(dp);
                return true;
        }
        if (entry->d_type == DT_DIR){
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            char new_dir_path[1024];
            snprintf(new_dir_path, sizeof(new_dir_path), "%s/%s", dir_name, entry->d_name);
            
            if (search_directory(new_dir_path, target)){
                closedir(dp);
                return true;
            }
        } 
      
            
        
    }

    closedir(dp);
    return false;
}

void search(char *command) {
    char *token = strtok(NULL, " \n\t\r");
    if (token == NULL){
        printf("ERROR! Please provide the name of the file or folder to search.\n");
        return;
    }

    if (search_directory(".", token)){
        printf("True");
    } 
    else{
        printf("False");
    }
    printf("\n");
}
