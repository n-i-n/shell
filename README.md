
# MyShell

A simple **Unix-like command-line shell** written in C++ supporting standard command execution, input/output redirection, pipes, and built-in commands.

---

## Features

- **Execute system commands** like `ls`, `cat`, `pwd`, etc.  
- **Built-in commands**:
  - `cd` – change directory  
  - `cwd` – print current working directory  
  - `oldcwd` – print previous working directory  
  - `help` – display shell help  
  - `exit` – exit the shell  
- **Command piping**: `ls | grep txt`  
- **Background execution** with `&`  
- **Input/output redirection**:  
  - `command < input.txt`  
  - `command > output.txt`  
- **Custom input prompt** using `readline` with history support.

---

## Requirements

- **C++ compiler** (g++ recommended)  
- **Linux / Unix system** (POSIX APIs used: `fork`, `execvp`, `dup2`, `pipe`, `wait`)  
- **GNU Readline library**  

Install Readline on Ubuntu/Debian:

```bash
sudo apt update
sudo apt install libreadline-dev
````

---

## Building

If you have a `Makefile`, simply run:

```bash
make
```

* This will compile all source files (`.cpp`) and link them with the Readline library.
* The output binary will be called `MyShell`.

To clean up compiled objects and the binary:

```bash
make clean
```

---

## Usage

Run the shell:

```bash
./MyShell
```

Examples:

```bash
> ls -l
> pwd
> cd /path/to/directory
> ls | grep cpp
> cat file.txt
> ls & echo "done"
```

* Background commands (`&`) execute without blocking the shell.
* Piped commands (`|`) connect multiple commands together.
* Redirection operators `<` and `>` read/write files.

---

## How it Works

* **`sh_loop()`** – main shell loop; reads input, parses commands, executes.
* **`sh_split_line()` / `parse_input()`** – tokenize input into commands and arguments.
* **`sh_execute()` / `sh_launch()`** – handle built-ins, forks, pipes, and redirections.
* **`sh_run()`** – forks a child process, sets up file descriptors, and executes commands.
* **Built-ins** – checked before `execvp`; executed in the shell process if matched.

---

## Notes

* Currently designed for **Unix-like systems**; Windows support requires POSIX compatibility (e.g., WSL).
* Properly frees allocated memory (`line`, `commands`) to avoid leaks.
* History is maintained using GNU Readline; previous inputs can be accessed with the **up/down arrows**.

---
