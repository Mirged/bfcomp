# Brainfuck Compiler

This is a Brainfuck compiler that converts Brainfuck code to C and compiles it. It allows you to write Brainfuck programs and execute them on your Linux system.

## How it works

The Brainfuck compiler takes Brainfuck source code as input and translates it into equivalent C code. The generated C code is then compiled using a C compiler to create an executable binary file.

## Prerequisites

To use this Brainfuck compiler, you need to have the following installed on your Linux system:

- A C compiler (e.g., GCC)
- Git (optional, if you want to clone the repository)

## Installation

1. Clone the repository (if you haven't already):

"""git clone https://github.com/mirged/bfcomp.git"""

2. Navigate to the project directory:

"""cd bfcomp"""

3. Compile the Brainfuck compiler:

"""gcc bfcomp.c -o bfcomp"""


## Usage

To use the Brainfuck compiler, follow these steps:

1. Create a Brainfuck source code file (e.g., `hello.bf`) or use an existing one.

2. Open a terminal and navigate to the project directory.

3. Execute the compiler with the following command:

"""./bfcomp <input file> <output file>"""
  
Replace `<input file>` with the path to your Brainfuck source code file and `<output file>` with the desired name for the compiled binary.

For example:

"""./bfcomp hello.bf hello"""

This command will compile `hello.bf` into a binary file named `hello`.

4. Run the compiled Brainfuck program:

"""./hello"""
  
The output of your Brainfuck program will be displayed in the terminal.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).


