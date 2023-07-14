//A classic example of a pattern that cannot be expressed as a regular expression is matching nested parentheses.
// Regular expressions are not powerful enough to handle patterns with arbitrary levels of nesting.
//
//For example, consider the pattern of matching a balanced sequence of openingand closing parentheses, such as "((()))".
// While regular expressions can handle simple cases of matching a fixed number of parentheses, 
// they cannot handle patterns where the number of openingand closing parentheses needs to match in a nested manner.
//
//Regular expressions work based on finite state machines, which have a limited memoryand cannot keep track of nested structures.
// However, nested parentheses require a more powerful mechanism, such as a stack or a context - free grammar, 
// to handle the arbitrary depth of nesting.
//
//The inability of regular expressions to handle nested structures is an example of a language that is not regular but context-free.
//Context-free languages require more expressive tools, like context-free grammars or pushdown automata, to representand match their patterns.