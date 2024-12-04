# AOS Assignment A2
## Roll No: 2024201007
## Name: Mihir Chowdhury

## Assumptions
1. Environment: The shell is intended to run on a Linux environment with standard C libraries and system calls.
2. File Structure: The codebase assumes specific file naming conventions as described in the folder contents.
3. Command Syntax: Commands should follow Unix shell conventions for foreground and background execution.
4. HOME directory is '~'. For my custom shell, it is the directory from which the file is run.

## Implementation

### Introduction
This assignment involves implementing a custom Linux shell using C. The shell supports both built-in commands and external system commands, handles foreground and background processes, and features advanced functionalities like job control, input/output redirection, and command history.

### Running the Shell
1. - Run `make` to build the shell executable.
   - Execute `./main` to start the shell and get a prompt of the form `username@system_name:path`.

2. Exiting the Shell:
   - To exit the shell, run the command **CTRL-D**.

### Commands
- **`pwd`**: Displays the current working directory. Implemented in `pwd.c`.
- **`ls [-l -a] [directory]`**: Lists files and directories. Supports multiple directories and highlights executable files in green and directories in blue. Implemented in `ls.c`.
- **`cd [directory]`**: Changes the current directory. Implemented in `cd.c`.
- **`echo [arguments]`**: Displays specified arguments, handling double quotes. Implemented in `echo.c`. 
- **`fg <jobNumber>`**: Brings a job to the foreground. Implemented in `fg.c`.
- **`bg <jobNumber>`**: Resumes a stopped job in the background. Implemented in `bg.c`.
- **`overkill`**: Kills all background processes. Implemented in `overkill.c`.
- **`search`**: Searches a file/directory.
- **`history [num]`**: Lists the last `num` commands from the command history. Defaults to the last 10 commands. Implemented in `history.c`.
- **`pinfo [PID]`**: Displays process details such as status, memory, and executable path. Implemented in `pinfo.c`.

### Foreground and Background Processes
- **Foreground Processes**: Commands executed without `&` are run in the foreground, where the shell waits for the process to complete.
- **Background Processes**: Commands followed by `&` are run in the background. The shell does not wait for these processes to finish and continues accepting new commands. The PID of background processes is displayed, and the shell handles multiple background processes.

### Additional Features
- **CTRL-Z**: Suspends the current foreground job and moves it to the background.
- **CTRL-C**: Sends a SIGINT signal to the current foreground job.
- **Command Recall**: Use the UP arrow key to recall and execute previous commands.
- **Input/Output Redirection & Piping**: Handles redirection (`<`, `>`, `>>`) and piping (`|`) as per Unix shell conventions.

### File Structure
- **`main.c`**: Contains the main function and shell initialization.
- **`cd.c`**: Implementation of `cd` command.
- **`echo.c`**: Implementation of `echo` command.
- **`execute_com.c`**: Handles command execution logic.
- **`headers.h`**: Header file with common definitions and function prototypes.
- **`history.c`**: Manages command history.
- **`ls.c`**: Implementation of `ls` command.
- **`makefile`**: Build instructions.
- **`overkill.c`**: Implementation of `overkill` command.
- **`pinfo.c`**: Implementation of `pinfo` command.
- **`pwd.c`**: Implementation of `pwd` command.
- **`bg.c`**: Implementation of `bg` command.
- **`fg.c`**: Implementation of `fg` command.
- **`redirection.c`**: Manages input/output redirection.
- **`run.c`**: Handles process execution and background job management.
- **`search.c`**: Search functionality for background jobs.


