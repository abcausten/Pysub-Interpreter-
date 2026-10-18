# PySub

PySub is a small interpreter for a subset of Python, written in C++. All of the functions were created from September 2023 - December 2023 with two small changes made in October 2026 to transfter it from Microsoft to Mac. It also runs as an interactive command prompt and can also load and execute `.py` files. It is made of three parts:

- a **lexical analyzer** that breaks each line into tokens and labels them,
- an **expression evaluator** that converts infix expressions to postfix and evaluates them,
- an **interface** that handles variables, `print`, `if` / `elif` / `else`, `while`, and the commands below.

## Requirements

- A C++17 compiler (`clang++` or `g++`)
- `make`
- macOS: install both with `xcode-select --install`

## Platform notes

The project was originally written in Visual Studio on Windows and ported to macOS. All
filenames are lowercase (except `Main.cpp`) and must match the `#include` lines exactly,
because GitHub and Linux are case-sensitive.

## Build

    make            # builds ./pysub
    make debug      # builds ./pysub_debug with AddressSanitizer and UBSan (slower, finds memory bugs)
    make clean      # removes the compiled programs

The whole program lives in headers, so only `src/Main.cpp` is compiled. To build without `make`:

    clang++ -std=c++17 -Wall -Wextra src/Main.cpp -o pysub

## Run

Run the program from inside the `examples/` folder so you can use bare filenames:

    cd examples
    ../pysub

You will see a welcome message and the `>>>` prompt. Type commands at that prompt, not in the
terminal. (Typing `read(...)` in the terminal makes zsh print an error such as
`zsh: unknown file attribute`.)

To quit, press **Ctrl+C**.

## Commands
Below is a list of commands that have been coded into the custom interface. 

| Command          | What it does                                                         |
|------------------|----------------------------------------------------------------------|
| `read(file.py)`  | Loads a program into memory. It prints nothing when it succeeds.     |
| `show`           | Lists the loaded lines with their line numbers.                      |
| `show(token)`    | Prints every token on every loaded line, with its category.          |
| `run`            | Executes the loaded program.                                         |
| `clear`          | Clears the loaded program.                                           |
| `help`           | Starts the help utility.                                             |

You can also type single lines directly at the prompt, for example an assignment such as
`y = 50`, a `print(...)` call, or an arithmetic or comparison expression.

## Example: `examples/testing.py`

`testing.py` is a short program to test the expression evaluator by assigning two variables and picks a branch with
`if` / `elif` / `else`:


### Running the code
This is a sample of how to run the code from the top.

    clang++ -std=c++17 -Wall -Wextra src/Main.cpp -o pysub
    --This runs the C++ code to create the pysub file to later run

    cd examples

    ../pysub

    --In the Interface now
    >>>read(testing.py)
    >>>show
    [0]x = 25
    [1]y = 30
    [2]
    [3]if x < y:
    [4]     print(x, "is less than",y)
    [5]elif (x > y):
    [6]     print(x, "is greater than", y)
    [7]else:
    [8]     print(x, "is equal to ", y)
    [9]

    >>>run
    varaible x is 25
    varaible y is 30
    25 is less than 30
    --Final output with run 

What happened:

- `read(testing.py)` loaded the ten lines (it printed nothing).
- `show` listed them with line numbers.
- `run` executed the program. The two `varaible ... is ...` lines are the interpreter's
  messages for the assignments `x = 25` and `y = 30` (the spelling "varaible" is how the
  program currently prints it). Because `x < y` is true, only the first branch ran, so the
  program printed `25 is less than 30`. The `elif` and `else` branches were skipped.

### See the tokens

`show(token)` runs the lexical analyzer over the loaded program and prints each line's tokens
with their category. Part of the output for `testing.py`:

    ***** TOKEN INFORMATION *****
    Line #0:
    Token[0]:    x  -  IDENTIFIER
    Token[1]:    =  -  ASSIGNMENT_OP
    Token[2]:    25  -  NUMERIC_LITERAL
    Line #1:
    Token[0]:    y  -  IDENTIFIER
    Token[1]:    =  -  ASSIGNMENT_OP
    Token[2]:    30  -  NUMERIC_LITERAL
    Line #2:
    Line #3:
    Token[0]:    if  -  KEYWORD
    Token[1]:    x  -  IDENTIFIER
    Token[2]:    <  -  RELATIONAL_OP
    Token[3]:    y  -  IDENTIFIER
    Token[4]:    :  -  COLON
    Line #4:
    Token[0]:    (indent)  -  INDENT
    Token[1]:    print  -  KEYWORD
    Token[2]:    (  -  LEFT_PAREN
    Token[3]:    x  -  IDENTIFIER
    Token[4]:    ,  -  COMMA
    Token[5]:    "is less than"  -  STRING_LITERAL
    Token[6]:    ,  -  COMMA
    Token[7]:    y  -  IDENTIFIER
    Token[8]:    )  -  RIGHT_PAREN

Blank lines (such as Line #2) have no tokens. The indent token is printed as a tab character
in the real output; it is written as `(indent)` here so it is visible.

### Other example file

`examples/text1.py` is not a real program. It is a set of odd lines (comments, strings,
stray operators) used to test the lexer. Load it with `read(text1.py)` and use `show(token)` to
see how each line is tokenized. Running it with `run` prints little, which is expected.

## Project layout

    src/Main.cpp          command loop; decides whether a line is a command, an expression, or code
    src/interface.h       interpreter: variables, print, if/elif/else, while, read/show/run/clear/help
    src/lexanalyzer.h     tokenizer
    src/expevaluator.h    infix-to-postfix conversion and postfix evaluation
    examples/             sample programs
    Makefile              build instructions

## Known issues

- **Paths containing `/` crash the program.** `Main.cpp` scans each line for operator characters
  before checking for commands, so `read(examples/testing.py)` is treated as division. Run from
  inside `examples/` and use `read(testing.py)`.
- **`show(token)` prints `syntax error, no = following <`** on lines containing `<`, even though
  the token list for the line is correct.
- **Ctrl+D (end of input) loops forever**, because the input loop never checks whether
  `getline` failed. Quit with Ctrl+C.
- **Windows line endings in input files** create an extra `UNKNOWN` token at the end of every
  line. The repo's `.gitattributes` keeps files in LF form; convert any outside `.py` files to LF.
- **Compiler warnings.** Building with `-Wall -Wextra` shows many harmless warnings (signed vs.
  unsigned comparisons, unused variables).
- Expressions using `or` were fixed in the source but have not been tested thoroughly.

