# PySub

A small interpreter for a subset of Python, written in C++. It includes a lexical analyzer
(tokenizer), an infix-to-postfix expression evaluator, and an interactive command prompt.

## Build

Requires a C++17 compiler (clang++ on macOS: `xcode-select --install`).

    make            # builds ./pysub
    make debug      # builds ./pysub_debug with AddressSanitizer/UBSan
    make clean

## Run

Run from inside `examples/` so you can use bare filenames:

    cd examples
    ../pysub

At the `>>>` prompt:

| Command         | What it does                                  |
|-----------------|-----------------------------------------------|
| `read(file.py)` | Load a program (no output on success)         |
| `show`          | List the loaded lines with line numbers       |
| `show(token)`   | Print every token and its category            |
| `run`           | Execute the loaded program                    |
| `clear`         | Clear the loaded program                      |
| `help`          | Help utility                                  |

Quit with Ctrl+C.

## Examples

- `examples/testing.py` - assignments plus `if`/`elif`/`else`; try `read(testing.py)`, `run`.
- `examples/text1.py` - scratch input for the tokenizer; try `show(token)`.

## Project layout

    src/Main.cpp          command loop
    src/interface.h       interpreter / command handling
    src/lexanalyzer.h     tokenizer
    src/expevaluator.h    expression evaluator

## Known issues

- Paths containing `/` (for example `read(examples/x.py)`) are mistaken for division;
  run from inside `examples/`.
- `x < y` in `show(token)` reports "no = following <".
- Quitting with Ctrl+D loops forever; use Ctrl+C.
