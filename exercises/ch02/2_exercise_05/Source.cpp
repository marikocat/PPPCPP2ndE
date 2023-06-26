/*
// - "double slash", anything written after the token // on a line is a comment.

<< - (1) iostream output operator. (2) integer left-shift operator.

C++ - a general-purpose programming language with a bias towards systems programming 
that supports procedural programming, data abstraction, object-oriented programming, and generic programming. 
C++ was designed and originally implemented by Bjarne Stroustrup. 
C++ is defined by ISO/IEC 14882 - Standard for the C++ Programming Language. 
TC++PL describes C++ and the fundamental techniques for its use.
A description of the design considerations for C++ can be found in D&E. 
Many commercial and free implementations exist. TC++PL 1.3, -5, 2.1, D&E 0.

comment - is ignored by the compiler and written for the benefit of programmers who read the code.
Comments are written to describe what the program is intented to do and 
in general to provide information useful for humans that can't be directly expressed in code.
block comment - comment started by / * and terminated by * /. TC++PL 6.4, D& E 3.11.1.
line comment -  comment started by // and terminated by end-of-line. TC++PL 6.4, D&E 3.11.1.

compiler - a program that does translation from the human-readable form to something a machine can "understand".
The compiler reads your source code and tries to make sense of what you wrote. It looks to see if your program is grammatically correct,
if every word has a defined meaning, and if there is anything obviously wrong that 
can be detected without trying to actually execute the program.
compiler - the part of a C++ implementation that produces object code from a translation unit. See also: front-end, back-end.
front-end - the parts of a compiler that perform lexical and syntax checking, type checking, 
and initial semantic checking of a translation unit. 
Typically all compiler error messages comes from the front-end.
back-end - the parts of a compiler that generates code given an internal representation of a correct program. 
This representation is produced by a compiler front-end.

compile-time error - errors found by the compiler.

cout - refers to a standard output stream - standard ostream. TC++PL 3.4, 21.2.1, D&E 8.3.1. 
The name cout is pronounced "see-out" and is an abreviation of "character output stream".

executable - a program ready to be run (executed) on a computer.
executable file - the result of linking the object files of a complete program.

function - is basically a named sequence of instructions for the computer to execute in the order in which they are written.
function - a named unit of code that can be invoked (called) from different parts of a program; a logical unit of computation.
function - a named sequence of statements that can be invoked/called given arguments and that might return a value. 
The type of the function includes the number and types of argument and the type of the value returned, if any. TC++PL 2.3, 7, D&E 2.6.

header - or a header file - a file included using #include usually has the suffix .h. 
A header contains definitions of terms, such as cout, that we use in our program.
header file - file holding declarations used in more than one translation unit. 
Thus, a header file acts as an interface between separately compiled parts of a program. 
A header file often contains inline function definitions, const definitions, enumerations, and template definitions, 
but it cannot be #included from for than one source file if 
it contain non-inline function definitions or variable definitions. TC++PL 2.4.1, 9.2.1. D&E 2.5, 11.3.3.

IDE - Integrated (or Interactive) Development Environment. 
A software development environment (SDE) emphasizing a GUI interface centered around a source code editor.
There are many IDEs for C++, but no standard SDE.
IDEs usually include an editor with helpful features like color coding to help distinguish between comments, keywords, and
other parts of your program source code, plus other facilities to help you debug your code, compile it, and run it.

#include - an directive, that instructs the computer to make available ("to include") facilities from a file.
#include - a mechanism for textual inclusion of one source file into another. 
Typically used to compose a translation unit out of a .c file and the header files it needs to define its view 
of the rest of the program. TC++PL 2.7, 13, D&E 18.1.

library - is simply some code - usually written by others - that we access using declarations found in an #included file.

linker - the part of a C++ implementation that merge the code generated from separately compiled translation units 
into a program or part of a program. TC++PL 9.1, D&E 4.5, 11.3. 
A program usually consists of several separate parts, often developed by different people. For example, the “Hello, World!”
program consists of the part we wrote plus parts of the C++ standard library. These separate parts (sometimes called
translation units) must be compiled and the resulting object code files must be linked together to form an executable program.
The program that links such parts together is (unsurprisingly) called a linker.

link-time error - errors found by the linker.

main() - the function called by the system to start a C++ program. TC++PL 3.2, 6.1.7, 9.4 .
Every C++ program must have a function called main to tell it where to start executing.

object code - is what the computer executes, also called executable or machine code.
Typically C++ object code files are given the suffix .obj (on Windows) or .o (Unix).
object file - the result of compiling a source file.

output - values produced by a computation (e.g., a function result or line of characters written on a screen).

program - code (possibly with associated data) that is sufficiently complete to be executed by a computer.
program - a set of translation units complete enough to be made executable by a linker. TC++PL 9.4.

run-time error - errors not found until the program is run.
Generally, compile-time errors are easier to understand and fix than link-time errors, 
and link-time errors are often easier to find and fix than run-time errors and logic errors.

source code - is what programmer reads and writes, also called program text.
Typically C++ source code files are given the suffix .cpp or .h.
source file - .c file or header.

statement - a part of C++ program that specifies an action and isn't an #include directive (or some other preprocessor directive).
statement - the basic unit controlling the execution flow in a function, 
such as if-statement, while-statement, do-statement, switch-statement, expression statement, and declaration. TC++PL 6.3.

translation unit - a part of a program that can be separately compiled. TC++PL 9.1.
A program usually consists of several separate parts, often developed by different people. For example, the “Hello, World!”
program consists of the part we wrote plus parts of the C++ standard library. These separate parts (sometimes called
translation units) must be compiled and the resulting object code files must be linked together to form an executable program.
*/