#ifndef COMMANDS_H
#define COMMANDS_H

extern char *pending_loadfunc_file;

void handle_command(const char *cmd);
void handle_command_with_arg(const char *cmd, const char *arg);

#endif
