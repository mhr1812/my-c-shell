#include "headers.h"

void cd(char *input){
	char *token = input;
	token = strtok(NULL," \n\r\t");
	//printf("Token:%s",token);
	char *curr_dir = getcwd(NULL, 0); 
	if(token==NULL){
		if(chdir(HOME)==-1){
			perror("ERROR!");
			//printf("Line 11");
		}	 
	}
	else if (strcmp(token, "-")==0){
        	if(prev_dir != NULL){
            		if(chdir(prev_dir)!=0){
                		perror("ERROR!");
                		//printf("Line 18");
            	}
            	else{
                	printf("%s\n", prev_dir); // Print the previous directory
            	}
        	} 
        	else{
            		printf("ERROR! No previous directory.\n");
        	}
    	}
	else if(token[0]=='~'){
		int n = strlen(token);
		char* file = (char*) malloc(sizeof(char)*n);
		strcpy(file,"\0");
		if(n>1){
			int i;
			for(i=1;i<n;i++){
				file[i-1] = token[i];
			}
			file[i] = '\0';
		}
		char* path = (char*) malloc(sizeof(char)*(n+strlen(HOME)));
		strcpy(path,HOME);
		strcat(path,file);
		path[n +strlen(HOME)-1] ='\0';
		//printf("%s ",path);
		
        	if(chdir(path) != 0){
        		perror("ERROR!");
        		printf("%s",path);
        		//printf(" Line 33 ");
        	}
		free(file);
        	free(path);
	}
	
	else if(chdir(token) != 0){
		perror("ERROR!");
		//printf(" Line 41 ");
		printf("%s",token);
	}
	if(prev_dir){
        	free(prev_dir);
    	}
    	prev_dir = curr_dir; 
	if(strtok(NULL," \n\r\t")!=NULL){
		printf("ERROR! Invalid! Too many arguments.");
	}
	return;
	
}
