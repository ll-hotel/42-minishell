# Minishell

*As beautiful as a shell*

Summary:
This project is about creating a simple shell.
Yes, your own little bash.
You will learn a lot about processes and file descriptors.

*Version: 7.1*

## Introduction

The existence of shells is linked to the very existence of IT.

At the time, all developers agreed that communicating with a computer using aligned
1/0 switches was seriously irritating.

It was only logical that they came up with the idea of creating a software to com-
municate with a computer using interactive lines of commands in a language somewhat
close to the human language.

Thanks to **Minishell**, you’ll be able to travel through time and come back to problems
people faced when *Windows* didn’t exist.

## Common Instructions

- Your project must be written in C.
- Your project must be written in accordance with the [Norm](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf). If you have bonus
files/functions, they are included in the norm check and you will receive a 0 if there
is a norm error inside.
- Your functions should not quit unexpectedly (segmentation fault, bus error, double
free, etc) apart from undefined behaviors.
- All heap allocated memory space must be properly freed when necessary. No leaks
will be tolerated.
- You must submit a Makefile which will compile your source files to the required output with the
flags `-Wall`, `-Wextra` and `-Werror`, use
`cc`, and your Makefile must not relink.
- Your Makefile must at least contain the rules `$(NAME)`, `all`, `clean`, `fclean` and `re`.

## Mandatory part

| Program name | minishell |
| :--- | :---: |
| Turn in files | Makefile, *.h, *.c |
| Makefile | NAME, all, clean, fclean, re
| Arguments | |
| External functs. | readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs |
| Libft authorized | Yes |
| Description | Write a shell |

### Your shell should

1. Display a prompt when waiting for a new command.
2. Have a working history.
3. Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
4. Avoid using more than one global variable to indicate a received signal. Consider the implications: this approach ensures that your signal handler will not access your main data structures
5. Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
6. Handle ’ (single quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence.
7. Handle " (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for $ (dollar sign).
8. Implement redirections:
 - `<` should redirect input.
 - `>` should redirect output.
 - `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
 - `>>` should redirect output in append mode.
9. Implement pipes (`|` character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
10. Handle environment variables (`$` followed by a sequence of characters) which should expand to their values.
11. Handle `$?` which should expand to the exit status of the most recently executed foreground pipeline.
12. Handle `ctrl-C`, `ctrl-D` and `ctrl-\` which should behave like in bash.
13. In interactive mode:
 - `ctrl-C` displays a new prompt on a new line.
 - `ctrl-D` exits the shell.
 - `ctrl-\` does nothing.
14. Your shell must implement the following builtins:
 - `echo` with option `-n`
 - `cd` with only a relative or absolute path
 - `pwd` with no options
 - `export` with no options
 - `unset` with no options
 - `env` with no options or arguments
 - `exit` with no options

The `readline()` function can cause memory leaks. You don’t have to fix them. But
that doesn’t mean your own code, yes the code you wrote, can have memory
leaks.
