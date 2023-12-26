# TINY Language Compiler

<img src="https://github-production-user-asset-6210df.s3.amazonaws.com/25803558/292908393-8c43c9bb-9565-4a50-818d-5417127686a8.jpg?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAIWNJYAX4CSVEH53A%2F20231226%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20231226T184921Z&X-Amz-Expires=300&X-Amz-Signature=8aad4f3bae69be4b43583da3cf9cbcdac126bf04259da904e4948c0c46b21799&X-Amz-SignedHeaders=host&actor_id=25803558&key_id=0&repo_id=726574775" width="800" height="400">

## Brief

The TINY Language Compiler is a project that implements a custom compiler for the TINY programming language. It consists of three main phases: Scanner, Analyzer, and Code Generation. Each phase contributes to the compilation process, transforming TINY source code into executable instructions.

## [Scanner Phase](https://github.com/Michael-M-aher/Tiny-Language-Compiler/blob/main/scanner)

The Scanner phase is responsible for tokenizing the input TINY source code. It processes the source code and identifies the different tokens, such as keywords, identifiers, numbers, and operators. The output is a list of tokens with their corresponding types and positions in the source code.

## [Analyzer Phase](https://github.com/Michael-M-aher/Tiny-Language-Compiler/blob/main/analyzer)

The Analyzer phase builds on the output of the Scanner and constructs a parse tree based on the grammar rules of the TINY language. It verifies the syntactic correctness of the source code and outputs the parse tree. Additionally, it performs type checking and ensures that the source code adheres to the specified rules.

## [Code Generation Phase](https://github.com/Michael-M-aher/Tiny-Language-Compiler/blob/main/code-generation)

The Code Generation phase takes the parse tree generated by the Analyzer and produces executable code. It includes generating a symbol table, annotating the syntax tree with data types, and simulating the compilation process. The output includes a symbol table, a syntax tree with data types, and a simulation of the compiled code.


## Getting Started

To begin using the Tiny Language Compiler, follow these steps:

1. **Download Latest Release**
    - Visit the [Tiny Compiler](https://github.com/Michael-M-aher/Tiny-Language-Compiler/releases/tag/compiler) page.
    - Download the latest release of the Tiny Compiler for your operating system.

2. **Write Your Program**
    - Create a new text file and write your Tiny source code.
    - Save the file with a `.m` extension.

3. **Run the Compiler**
    - Open a terminal or command prompt.
    - Navigate to the directory where you downloaded the Tiny Compiler.
    - Run the compiler program, providing the path to your Tiny source code file as an argument. For example:
      ```bash
      tiny_compiler my_program.m
      ```
    - The compiler will process your source code, and you will see the output, including any errors or warnings.

Now you have successfully compiled your Tiny source code using the Tiny Language Compiler.

## Example Usage

Here's an example of using the TINY Language Compiler:

```bash
./tiny_compiler input.m
```

## Installation

To use the TINY Language Compiler, you just need to run compiler on your <input.m> file <br> but if you want to make changes to compiler make sure you have a C++ compiler installed on your system. If not, you can download one compatible with your operating system.

Once you have the necessary compiler, you can change and compile each phase to serve your needs.

## Contributing
Pull requests are welcome. For major changes, please open an [issue](https://github.com/Michael-M-aher/Tiny-Language-Compiler/issues) first to discuss what you would like to change.

Please make sure to update tests as appropriate.


## Author

👤 **Michael Maher**

- Twitter: [@Michael___Maher](https://twitter.com/Michael___Maher)
- Github: [@Michael-M-aher](https://github.com/Michael-M-aher)

## Show your support

Please ⭐️ this repository if this project helped you!

<a href="https://www.buymeacoffee.com/michael.maher" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" height="60px" width="200" ></a>

## 📝 License

Copyright © 2023 [Michael Maher](https://github.com/Michael-M-aher).<br />
This project is [MIT](https://github.com/Michael-M-aher/Tiny-Language-Compiler/blob/main/LICENSE) licensed.