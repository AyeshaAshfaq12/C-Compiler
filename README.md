# C++ Compiler Project

This project aims to develop a fully functional compiler for the C++ programming language. Designed with comprehensive compiler features, this compiler is a work in progress, with the parsing phase already completed and tested.

## Project Status

**Current Progress:** Parsing stage has been completed and tested.  
**Upcoming Development Stages:** Semantic analysis, code generation, and optimization phases.

---

## Features

The compiler is designed to support all essential features expected in a modern compiler, including:

1. **Lexical Analysis**  
   - Efficiently tokenizes input C++ code into meaningful lexemes.
2. **Parsing**  
   - Completed and fully functional, the parsing phase verifies syntax and builds an Abstract Syntax Tree (AST) for further processing.
3. **Semantic Analysis** *(Planned)*  
   - Will analyze code semantics to ensure type safety, correct variable use, and overall logical correctness.
4. **Intermediate Code Generation** *(Planned)*  
   - Will convert parsed and validated code into an intermediate representation.
5. **Optimization** *(Planned)*  
   - Aims to optimize intermediate code for better runtime efficiency.
6. **Code Generation** *(Planned)*  
   - Will translate intermediate representation into executable machine code.
7. **Error Handling** *(Planned)*  
   - Robust error handling throughout compilation stages to ensure useful feedback for debugging.

---

## Project Structure


```makefile
├── parser.cpp           # Parses code into AST (completed)
└── README.md            # Project documentation
```

## Installation

To set up and run the compiler locally, please follow these steps:

1. Clone the repository:
```bash
git clone https://github.com/AyeshaAshfaq12/C-Compiler.git
cd C-Compiler
```

2. Compile the project:
```bash
make
```

3. Run the executable on your code file:
```bash
./compiler your_code.cpp
```

## Usage

- The compiler currently supports the parsing of C++ code and provides output in the form of an Abstract Syntax Tree.
- As development progresses, additional functionalities like code generation and optimization will be integrated.

  
## Example
Include an example to demonstrate the compiler's current parsing capabilities.

#### Sample C++ Code Input:
```cpp
int main() {
    int a = 5;
    int b = 10;
    return a + b;
}
```

  
## License
This project is licensed under the MIT License.



