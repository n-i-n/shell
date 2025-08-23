# MyShell

MyShell is a simple Unix-like shell implemented in C. It supports command execution, pipelines, and basic shell features.

## Features
- Execute external commands (e.g., `ls`, `grep`, `cat`)
- Pipe chaining (e.g., `ls -l | grep txt | wc -l`)
- Custom command parsing
- (Optional) Built-in commands like `cd` (add as needed)

## Usage
1. Build the shell:
   ```sh
   make
   ```
2. Run the shell:
   ```sh
   ./MyShell
   ```
3. Enter commands as you would in a normal shell. Use pipes to chain commands.

## File Structure
- `src/main.c` - Main shell implementation
- `Makefile` - Build instructions

## Example
```
> ls -l | grep .c | wc -l
```

## Notes
- The shell does not support advanced features like job control or scripting.
- For line editing and history, consider integrating GNU Readline.

## License
This project is licensed under the GNU General Public License v3.0. See the LICENSE file for details.
