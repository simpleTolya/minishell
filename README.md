# minishell

mini version of bash
Supported:
- pipes      (Example: echo hello | cat)
- redirects  (Example: cat < input > outfile)
- &&, ||     (Example: echo hello && dftndfgn || echo error)
- wildcard * (Example: echo * fil* f*l*e***)
- $?
- env variables
- builtin: exit, cd, env, echo, export, unset, pwd
- signals    (Example: CTRL + C)

## Technologies

1. C
2. Make

## Launch

1. Build a project using Makefile

   ```sh
   $ make
   ```

2. Run the program, like this:

   ```sh
   $ ./minishell
   ```


  <img src="./screen/minishell_video.gif" width="500" alt="game">
