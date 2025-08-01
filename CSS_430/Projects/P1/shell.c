#include "shell.h"

// ============================================================================
// Execute a child process.  
// Returns -1
// on failure.  On success, does not return to caller.
// ============================================================================
int child(char **args)
{
  int i = 0;
  while (args[i] != NULL)
  {
    if (equal(args[i], ">"))
    {
      // open the corresponding file and use dup to direct stdout to file
      int file = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (file < 0) {
        perror("open failed");
        return -1;
      }
      dup2(file, WR); //redirect STDOUT to file

      args[i] = NULL; //set > to NULL
      break;
    }
    else if (equal(args[i], "<"))
    {
     // open the corresponding file and use dup to pull stdin from file
     int file = open(args[i + 1], O_RDONLY);
     if (file < 0) {
       perror("open failed");
       return -1;
     }
     dup2(file, RD); //redirect STDIN to file

     args[i] = NULL; //set > to NULL
     break;
    }
    else if (equal(args[i], "|"))
    { 
     // do pipe in a separate function
     doPipe(args, i);
     return 0;
    }
    else
    {
      ++i;
    }
  }

  // call execvp on prepared arguments after while loop ends. You can modify arguments as you loop over the arguments above.
  execvp(args[0], args);
  return -1;
}

// ============================================================================
// Execute the shell command that starts at args[start] and ends at args[end].
// For example, with
//   args = {"ls" "-l", ">", "junk", "&", "cat", "hello.c"}
// start = 5 and end = 6, we would perform the command "cat hello.c"
//
// Or, with args = {"ls", "|", "wc"} and start = 0 and end = 2, we would
// execute: ls | wc
// ============================================================================
void doCommand(char **args, int start, int end, bool waitfor)
{
// you will have your classic fork() like implementation here. 
// always execute your commands in child. so pass in arguments there 
// based on waitfor flag, in parent implement wait or not wait  based on & or ;  
  
  pid_t pid; //make fork
  pid = fork();
  if (pid < 0) { //fork error
    perror("Error during fork");
    exit(EXIT_FAILURE);
  }
  //successfully made fork

  if (pid == 0)
  {
    //child
    //make the sub args that starts at start and ends at end
    char **subArgs = malloc(MAXLINE * sizeof(char*));  // allocate memory for tokens
    if (subArgs == NULL) {
      perror("malloc failed");
      exit(1);
    }
    
    for (int i = 0; i <= end - start; i++){ //get the sub argument
      subArgs[i] = args[i + start];
    }
    subArgs[end - start + 1] = NULL;  // Null-terminate

    child(subArgs); // execute command.
    exit(EXIT_SUCCESS);
  } else {
    //parent
    if (waitfor) {
      int status;
      wait(&status);
    }
  }
}

// ============================================================================
// Execute the two commands in 'args' connected by a pipe at args[pipei].
// For example, with
//   args = {"ls" "-a", "|", "wc""}
// and pipei = 2, we will perform the command "ls -a | wc", pipei is the index of the pipe, so you can split commands between parent and child.
//
// We split off the command for the parent from 'args' into 'parentArgs'.  In
// our example, parentArgs = {"ls", "-a"}
//
// The parent will write, via a pipe, to the child
// ============================================================================
int doPipe(char **args, int pipei)
{
  enum { READ, WRITE };
  pid_t pid;
  int pipeFD[2];

  if (pipe(pipeFD) < 0) { //make pipe
    perror("Error in creating pipe");
    exit(EXIT_FAILURE);
  }

  pid = fork(); //make fork
  if (pid < 0) { 
    perror("Error during fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0){
    //child process
    // set up read pipe
    close(pipeFD[WRITE]);
    dup2(pipeFD[READ], RD);

    // make child args
    char **childArgs = &args[pipei + 1];
    // execute the command then exit
    child(childArgs); //should finish here
    perror("execvp failed for child");
    exit(EXIT_FAILURE);
  } else {
    //parent process
    // set up write pipe
    close(pipeFD[READ]);
    dup2(pipeFD[WRITE], WR);

    // make parent args
    char **parentArgs = malloc((pipei + 1) * sizeof(char*));
    for (int i = 0; i < pipei; i++) {
      parentArgs[i] = args[i];
    }
    parentArgs[pipei] = NULL;
    // put the result in pipe
    execvp(parentArgs[0], parentArgs); //should finish here
    perror("execvp failed for parent");
    exit(EXIT_FAILURE);
  }
  return 0;
}



// ============================================================================
// Main loop for our Unix shell interpreter
// ============================================================================
int main()
{
  bool should_run = true;          // loop until false
  char *line = calloc(1, MAXLINE); // holds user input

  char *historyCmd = NULL;
  
  int start = 0; // index into args array
  while (should_run)
  {
    printf(PROMPT);   // osh>
    fflush(stdout);   // because no "\n"
    fetchline(&line); // fetch NUL-terminated line

    if (equal(line, ""))
      continue; // blank line

    if (equal(line, "exit"))
    { // cheerio
      should_run = false;
      continue;
    }

    if (equal(line, "!!"))
    {
      if (historyCmd) {
        printf("%s\n", historyCmd);
        free(line);  // Free the old input buffer
        line = strdup(historyCmd);  // Duplicate the history command
      } else {
        printf("ERROR: no command in history\n");
        continue;
      }
    }

    if (equal(line, "ascii"))
    {
      printf("  |\\_/|        ****************************    (\\_/) \n / @ @ \\       *  \"Purrrfectly pleasant\"  *   (='.'=)\n( > º < )      *       Poppy Prinz        *   (\")_(\")\n `>>x<<´       *   (pprinz@example.com)   *\n /  O  \\       ****************************\n");
    }

    if (historyCmd) {
      free(historyCmd);  // free old command
    }
    historyCmd = strdup(line);  // duplicate full string
  
    // process lines
    char **args = tokenize(line); // split string into tokens
    //add to history
    // loop over to find chunk of independent commands and execute
    while (args[start] != NULL)
    {
      int end;
      int* endptr = &end;
      bool waitfor = parse(args, start, endptr);// parse() checks if current command ends with ";" or "&"  or nothing. if it does not end with anything treat it as ; or blocking call. Parse updates "end" to the index of the last token before ; or & or simply nothing
      doCommand(args, start, end, waitfor);    // execute sub-command
      start = end + 2;                         // next command
    }
    start = 0;              // next line
    // remember current command into history
  }

  free(line);
  if (historyCmd){
    free(historyCmd);
  } 

  return 0;
}

// ============================================================================
// Parse the shell command, starting at args[start].  For example, if
// start = 0 and args holds:
//    {"ls", "-a", ">", "junk.txt", "&", "cat", "hello.c", ";"}
// then parse will find the "&" terminator at index 4, and set end to this
// value.  This tells the caller that the current command runs from index
// 'start' thru index 'end'.
//
// We return true if the command terminates with ";" or end-of-line.  We
// return false if the command terminates with "&"
// ============================================================================
bool parse(char **args, int start, int *end)
{
  int i = start;
  while (args[i])
  {
    // If the argument is a command separator
    if (equal(args[i],"&") || equal(args[i],";")) {
      *end = i - 1;
      return (equal(args[i],";")); // true if ";", false if "&"
    }
    i++;
}

// Reached end of array, no explicit terminator found
*end = i;
return true;
}

// ============================================================================
// Tokenize 'line'.  Recall that 'strtok' writes NULLs into its string
// argument to delimit the end of each sub-string.
// Eg: line = "ls -a --color" would produce tokens: "ls", "-a" and "--color"
// ============================================================================
char **tokenize(char *line)
{
  //clear memory of history
  // allocate memory for tokens
  char **ret = malloc(MAXLINE * sizeof(char*)); 
  if (ret == NULL) {
      perror("malloc failed");
      exit(1);
  }
  // add to the return and history
  char* token = strtok(line, " ");
  int i = 0;
  while (token) {
    //printf("token: %s\n", token);
    ret[i] = token;
    i++;
    token = strtok(NULL, " ");
  }
  return ret;
}

// interactive shell to process commands
int interactiveShell() {
  bool should_run = true;
  char *line = calloc(1, MAXLINE);
  while (should_run) {
    printf(PROMPT);
    fflush(stdout);
    int n = fetchline(&line);
    printf("read: %s (length = %d)\n", line, n);
    // ^D results in n == -1
    if (n == -1 || equal(line, "exit")) {
      should_run = false;
      continue;
    }
    if (equal(line, "")) {
      continue;
    }
    processLine(line);
  }
  free(line);
  return 0;
}

void processLine(char *line) { printf("processing line: %s\n", line); }

int runTests() {
  printf("*** Running basic tests ***\n");
  char lines[7][MAXLINE] = {
      "ls",      "ls -al", "ls & whoami ;", "ls > junk.txt", "cat < junk.txt",
      "ls | wc", "ascii"};
  for (int i = 0; i < 7; i++) {
    printf("* %d. Testing %s *\n", i + 1, lines[i]);
    processLine(lines[i]);
  }

  return 0;
}

// return true if C-strings are equal
bool equal(char *a, char *b) { return (strcmp(a, b) == 0); }

// read a line from console
// return length of line read or -1 if failed to read
// removes the \n on the line read
int fetchline(char **line) {
  size_t len = 0;
  size_t n = getline(line, &len, stdin);
  if (n > 0) {
    (*line)[n - 1] = '\0';
  }
  return n;
}