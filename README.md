# Minishell 🐚

A custom implementation of a Unix shell (bash replica) created as part of the 42 curriculum.

## Overview

Minishell is a simplified yet functional shell interpreter written in C. It replicates core bash functionality, including command execution, built-in commands, pipes, and I/O redirection operators.

## ✨ Features

- **Command Execution**: Execute external commands with argument parsing
- **Built-in Commands**: 
  - `echo` - Display text
  - `cd` - Change directory
  - `pwd` - Print working directory
  - `env` - Display environment variables
  - `export` - Set environment variables
  - `unset` - Unset environment variables
  - `exit` - Exit the shell

- **Operators & Redirections**:
  - `|` - Pipe: chain commands
  - `>` - Output redirection: write to file
  - `<` - Input redirection: read from file
  - `>>` - Append redirection: append to file
  - `<<` - Here-document: read from inline input

- **Variable Expansion**: `$VAR` expansion with special variables (`$?`, `$0`, etc.)
- **Quote Handling**: Single and double quote support
- **Signal Handling**: Interactive signal management (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)

## 🛠 Installation & Building

### Prerequisites
- GCC or Clang compiler
- Make
- Standard Unix development tools

### Build Instructions

```bash
make           # Compile the project
make clean     # Remove object files
make fclean    # Remove all generated files
make re        # Rebuild from scratch
```

## 🚀 Usage

Run the executable with no arguments:

```bash
./minishell
```

The shell will then accept commands interactively:

```bash
minishell> echo "Hello World"
Hello World
minishell> cd src
minishell> pwd
/path/to/minishell/src
minishell> exit
```

## 📁 Project Structure

- **`includes/`** - Header files
  - `minishell.h` - Main project header
  - `libft.h` - Custom library functions
  - `ft_printf.h` - Custom printf implementation
  - `get_next_line.h` - Line reading utility

- **`libft/`** - Custom C library with:
  - String manipulation functions
  - Memory management utilities
  - Linked list operations
  - Custom printf and get_next_line implementations

- **`src/`** - Main source code
  - Core shell logic and command execution
  - Parsing and tokenization
  - Built-in command implementations
  - I/O redirection and pipe handling
  - Variable expansion and quote processing

## 📋 Requirements

- Single process operations (except for pipes)
- Proper memory management (no leaks)
- Error handling for invalid commands
- Support for up to ~100 commands per line
- Heredoc support with variable expansion

## 🔍 Testing

A `valgrind` script is included for memory leak detection:

```bash
./valgrind              # Run with valgrind
```

## 📝 Notes

- This project strictly follows 42 School standards
- Norminette-compliant code formatting
- Manual implementation of core functions (no external libraries except libc)

## 🎓 Curriculum

This project is part of the 42 curriculum and demonstrates understanding of:
- Process management and system calls
- File I/O operations
- String parsing and tokenization
- Signal handling
- Environment variable management
