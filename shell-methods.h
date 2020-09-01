void parse(char input_str[]);
void timeDate();
void changeDirectory(char ** token, int tokenSize);
void signal_handler(int signal);
void executeCommand(char ** token, int tokenSize);
void redirect(char * token, int tokenSize);