#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>

#define MAX_ARGS 200
#define ARG_AT 300
#define HISTORY_SIZE 100

char history[HISTORY_SIZE][100];
int history_count = 0;
int current_history_index = 0;

/**
 * This program implements a simple Unix-like shell with basic functionality such as executing commands,
 * handling input/output redirection, executing commands in the background, and executing piped commands.
 * The shell provides a user-friendly interface with a greeting message and ASCII art during startup.
 * It supports built-in commands like cd, exit, and help, along with other general commands available in
 * Unix shell environments. The shell also handles improper space handling and provides a help command
 * to display information about supported commands.
 *
 * Known bugs: up and down arrows give the output of:  "^[[A
 *   execvp: No such file or directory" (A for up, and B for down). It is recognizing the arrows but not the command.
 * Ctrl C just terminates, not finding the history like specified in the code.
 * Grep and cd ~ commands also do not work as they are supposed to. 
 * 
 *
 * @author Vanessa Brouse
 */

struct Cmd
{
    char args[MAX_ARGS][ARG_AT];
    char file_in[100];
    char file_out[100];
    int has_pipe;
    int num_args;
};

void printDir();

void execArgs(struct Cmd *, char **);

void tokenize(char *, struct Cmd *);

void print_ascii_art()
{
    printf("\n\n\n");
    printf("  V       V   AAAA     N     N  EEEEEEEE    SSSSSSS    SSSSSSS     AAAA\n");
    printf("   V     V   A    A    NN    N  E          S         S            A    A\n");
    printf("    V   V   AAAAAAAA   N N   N  EEEEEEEE    SSSSSSS   SSSSSSS    AAAAAAAA\n");
    printf("     V V   A        A  N  N  N  E                  S         S  A        A\n");
    printf("      V   A          A N   N N  EEEEEEEE   SSSSSSSS  SSSSSSSS  A          A\n");
    printf("\n\n");
    printf("  ***   ***\n");
    printf(" ***** *****\n");
    printf("**************\n");
    printf("*************\n");
    printf(" ***********\n");
    printf("  *********\n");
    printf("   *******\n");
    printf("    *****\n");
    printf("     ***\n");
    printf("      *\n");
    printf("\n\n");
}

void print_date_and_time()
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("  Current date and time: %s", asctime(tm));
}

// greeting of shell
void init_shell()
{
    printf("\n\n\n******************"
           "*****************************");
    printf("\n\n\n\t**** Welcome to Thee Shell ****");
    printf("\n\n\t  My creator is Vanessa Brouse");
    printf("\n\n\t    All hail Vanessa Brouse");
    printf("\n\n\n\n*******************"
           "****************************");
    print_ascii_art();
    print_date_and_time();
    char *username = getenv("USER");
    printf("\n\n\nUSER is: @%s", username);
    printf("\n");
    sleep(1);
}

// help command builtin
void openHelp()
{
    puts("\n***WELCOME TO THEE SHELL HELP***"
         "\nList of Commands supported:"
         "\n>cd"
         "\n>ls"
         "\n>exit"
         "\n>all other general commands available in UNIX shell"
         "\n>pipe handling"
         "\n>improper space handling");

    return;
}

void add_to_history(const char *cmd) {
    if (history_count < HISTORY_SIZE) {
        strcpy(history[history_count++], cmd);
    } else {
        // Shift history to make space for new command
        for (int i = 0; i < HISTORY_SIZE - 1; ++i) {
            strcpy(history[i], history[i + 1]);
        }
        strcpy(history[HISTORY_SIZE - 1], cmd);
    }
}

void navigate_history(int direction) {
    current_history_index += direction;
    if (current_history_index < 0) {
        current_history_index = 0;
    } else if (current_history_index >= history_count) {
        current_history_index = history_count - 1;
    }
    printf("\r> %s", history[current_history_index]);
    fflush(stdout);
}


int main(int argc, char *argv[])
{
    init_shell();
    char input[100];  
    struct Cmd *newCmd; 
    char *cmd_argv[MAX_ARGS + 1];
    char *cmd_argv2[MAX_ARGS + 1];

    if (argc > 1) {
        // Batch mode: read commands from file
        FILE *batch_file = fopen(argv[1], "r");
        if (batch_file == NULL) {
            perror("Error opening batch file");
            return 1;
        }
        while (fgets(input, sizeof(input), batch_file)) {
            // Process each line from the batch file
            // Same processing logic as interactive mode
            input[strcspn(input, "\n")] = '\0'; // remove newline
            // ...
        }

        fclose(batch_file);
        return 0;
    }

    printDir();

    while (1)
    {
        // get input from user 
        printf("\n> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (input[0] != '\0') {
        add_to_history(input); // Add command to history
        }

        // Handle auto-completion
        if (input[0] == '\003') { // Ctrl+c
            int prefix_len = strlen(input) - 1; // Exclude Ctrl+c from prefix length
            int matched_command_index = -1;

            for (int i = 0; i < history_count; ++i) {
                if (strncmp(input + 1, history[i], prefix_len) == 0) {
                    if (matched_command_index != -1) {
                        // Multiple matches found, exit auto-completion
                        matched_command_index = -1;
                        break;
                    }
                    matched_command_index = i;
                }
            }
            if (matched_command_index != -1) {
                printf("\r> %s", history[matched_command_index]);
                fflush(stdout);
                // Wait for user to press Enter or Ctrl+c to exit auto-completion
                while (1) {
                    char c = getchar();
                    if (c == '\n') {
                        // Execute the matched command
                        strncpy(input, history[matched_command_index], sizeof(input));
                        input[strcspn(input, "\n")] = '\0';
                        break;
                    } else if (c == '\003') {
                        // Ctrl+c, exit auto-completion
                        break;
                    }
                }
            }
        }

        // Handle command history navigation
        if (input[0] == '\033') { // Escape sequence for arrow keys
            char escape_seq[3] = "\033";
            if (memcmp(input, escape_seq, 2) == 0) {
                // Handle arrow key press
                if (input[2] == 'A') { // Up arrow
                    navigate_history(-1); // Navigate upwards
                } else if (input[2] == 'B') { // Down arrow
                    navigate_history(1); // Navigate downwards
                }
            }
        }

        // if the input is 'exit', loop breaks
        if (strcmp(input, "exit") == 0)
        {
            printf("Goodbye.\n");
            return 0;
        }

        // allocate memory for newCmd stuct and call tokenize to initialize input
        newCmd = (struct Cmd *)malloc(sizeof(struct Cmd));
        tokenize(input, newCmd);

        // change directory built-in function
        if (strcmp(newCmd->args[0], "cd") == 0 && newCmd->args[1] != NULL)
        {
            chdir(newCmd->args[1]);
            printDir();
        }
        else
        {
            // fork process
            pid_t pid = fork();

            // if this is the child process,
            if (pid == 0)
            {
                // if there is a pipe, go here
                if (newCmd->has_pipe > 0)
                {
                    // gather commands from before the pipe
                    int i;
                    for (i = 0; i <= newCmd->has_pipe && newCmd->args[i][0] != '\0'; i++)
                        cmd_argv[i] = newCmd->args[i];
                    cmd_argv[i] = NULL;

                    // gather commands from after the pipe
                    for (i = 0; i < MAX_ARGS && newCmd->args[i + newCmd->has_pipe][0] != '\0'; i++)
                        cmd_argv2[i] = newCmd->args[i + newCmd->has_pipe];
                    cmd_argv2[i] = NULL;

                    // handle pipe
                    int pipefd[2];
                    if (pipe(pipefd) == -1)
                    {
                        // display error if pipe creation is unsuccessful
                        perror("pipe");
                        exit(EXIT_FAILURE);
                    }

                    // fork child process again
                    pid_t subpid = fork();

                    // if in the sub-child process
                    if (subpid == 0)
                    {
                        // close read end of pipe, redirect stdout to write, and close write end
                        close(pipefd[0]);
                        dup2(pipefd[1], STDOUT_FILENO);
                        close(pipefd[1]);

                        // execute the command before the pipe
                        execArgs(newCmd, cmd_argv);
                    }
                    else if (subpid > 0)
                    {
                        // close write end of pipe, redirect stdin to read end and close read end
                        close(pipefd[1]);
                        dup2(pipefd[0], STDIN_FILENO);
                        close(pipefd[0]);

                        // execute the command after the pipe
                        execArgs(newCmd, cmd_argv2);
                    }
                    else
                    {
                        perror("fork");
                        exit(EXIT_FAILURE);
                    }
                }
                else
                {
                    int i;
                    for (i = 0; i < newCmd->num_args && newCmd->args[i][0] != '\0'; i++)
                        cmd_argv[i] = newCmd->args[i];
                    cmd_argv[i] = NULL;

                    execArgs(newCmd, cmd_argv);
                }
            }
            else
            {
                wait(0);
            }
        }

        // free memory for newCmd struct
        free(newCmd);
    }
    return 0;
}


   

// prints Current Directory
void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\npwd: %s", cwd);
}

// system command is executed
void execArgs(struct Cmd *newCmd, char **argv)
{
    // handle file redirection for input
    if (newCmd->file_in[0] != '\0')
    {
        int fd_in = open(newCmd->file_in, O_RDONLY);
        if (fd_in < 0)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd_in, STDIN_FILENO);
        close(fd_in); // Close the file descriptor after duplication
    }

    // handle file redirection for output
    if (newCmd->file_out[0] != '\0')
    {
        int fd_out = open(newCmd->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out < 0)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out); // Close the file descriptor after duplication
    }

    // execute process
    if (execvp(argv[0], argv) < 0)
    {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}


// takes input and tokenizes it
void tokenize(char *input, struct Cmd *command)
{
    char *token = strtok(input, " ");
    int counter = 0;
    command->file_in[0] = '\0';
    command->file_out[0] = '\0';

    while (token != NULL)
    {
        if (strcmp(token, "<") == 0)
        {
            token = strtok(NULL, " ");
            strcpy(command->file_in, token);
        }
        else if (strcmp(token, ">") == 0)
        {
            token = strtok(NULL, " ");
            strcpy(command->file_out, token);
        }
        else if (strcmp(token, "|") == 0)
        {
            command->has_pipe = counter;
            token = strtok(NULL, " ");
        }
        else
        {
            strcpy(command->args[counter], token);
            token = strtok(NULL, " ");
        }

        counter++;

        if (token == NULL)
            break;
    }
    command->num_args = counter;
}
