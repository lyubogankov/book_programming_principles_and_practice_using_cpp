## Notes

## Chapter Review Questions

1. *What do we mean by “Programming is understanding”?*

    In order to correctly implement some functionality within a program, the programmer must learn/know what success looks like so that they can verify their solution - in other words, they must understand!


2. *The chapter details the creation of a calculator program. Write a short analysis of what the calculator should be able to do.*

    Here is a short functional description for our calculator:
    ```
    --- Should be working                           input    expected-output
        --- two-number arithmetic
        . enter a single number and print           1;       =1
        . add two numbers and print                 1+1;     =2
        . subtract two numbers and print            1-1;     =0
        . multiply two numbers and print            2*2;     =4
        . divide two numbers (divisor non zero)     4/2;     =2
        . expression w/in parentheses               (1+1);   =2

        -- multi-number arithmetic
        . is Order of Operations followed?          2+2*3;   =8
        . are parentheses respected in OoO?         (2+2)*3; =12

        --- navigation
        . type 'q' to quit
        . multi-line expression (newlines between numbers/operators, then ';' on a separate line)

    --- Should raise error
    . enter non-operator, non-float char        m
    . divide two numbers (divisor = 0)          4/0;
    . no closing paren given                    (1+1;
    . ending on an operator                     1+;
    ```


3. *How do you break a problem up into smaller manageable parts?*

    - Identify elements that come up repeatedly (either operations, or types of information that appear together often).  These are good candidates for functions / classes.  These are used as higher-order building blocks (instead of just language primitives), and can be used as "pieces" of the software (akin to parts of a car).


4. *Why is creating a small, limited version of a program a good idea?*

    Get to working program faster - that way, can evaluate next steps based on working code instead of spending a lot of effort on a larger project that may not have the right features.


5. *Why is feature creep a bad idea?*

    According to the book, adding one extra feature opens the floodgates for more features to get added, bogging down the development process.  Better to implement one thing at a time.


6. *What are the three main phases of software development?*

    1. Analysis - develop requirements/specification
    2. Design - map specs onto high-level program structure, research libraries (if needed)
    3. Implementation

    This probably works well for smaller programs, but for larger ones it's probably an iterative process (with each slice consisting of these three phases).


7. *What is a “use case”?*

    An example of a program feature + how user is expected to interact with it.


8. *What is the purpose of testing?*

    To ensure that the program works as expected in all use cases and gracefully errors out outside of them.


9. *According to the outline in the chapter, describe the difference between a `Term`, an `Expression`, a `Number`, and a `Primary`.*

    **`Number`**: a decimal number stored, expressed in a format compatible with the C++ floating-point data type.  This isn't yet factored into the mathematical order of operations.

    **`Primary`**: the highest-priority operation within the mathematical order of operations (OoO) - it represents *parentheses* (either a single `Number`, or an `Expression` surrounded by parens, which evaluates to a single `Number`, aka a `double`).

    *If exponentiation were defined, it'd have a grammar element between `Term` and `Primary`.*

    **`Term`**: the second-highest priority within OoO.  For our calculator, that's division and multiplication of `Primaries`, the next-highest priority grammar element.

    **`Expression`**: the lowest priority within OoO.  For our calculator, that's addition and subtraction of `Terms`, the next-highest priority grammar element.


10. *In the chapter, an input was broken down into its component `Terms`, `Expressions`, `Primarys`, and `Numbers`. Do this for (17+4)/(5–1).*

    ```mermaid

    graph TD

        e0["Expression"]
        e1["Expression"]
        e2["Expression"]
        e3["Expression"]
        e4["Expression"]

        t0["Term"]
        t1["Term"]
        t2["Term"]
        t3["Term"]
        t4["Term"]

        p0["Primary"]
        p1["Primary"]
        p2["Primary"]
        p3["Primary"]
        p4["Primary"]
        p5["Primary"]

        n0["Number"]
        n1["Number"]
        n2["Number"]
        n3["Number"]
    
        tok0["("]
        tok1["17"]
        tok2["+"]
        tok3["4"]
        tok4[")"]
        tok5["/"]
        tok6["("]
        tok7["5"]
        tok8["-"]
        tok9["1"]
        tok10[")"]

        %% top level
        e4 --- t4

        %% second level
        t4 --- p2
        t4 --- tok5

        %% (5 - 1) -> primary
        subgraph gp2[" "]

            %% direction TB
            p5 --- tok6
            p5 --- e3

            %% 5 - 1 -> expression
            subgraph ge2[" "]
                %% 5 -> expression
                subgraph gt3_4[" "]
                    subgraph gt3_3[" "]
                        subgraph gt3_2[" "]
                            subgraph gt3_1[" "]
                                n2 --- tok7
                            end
                            p3 --- n2
                        end
                        t2 --- p3
                    end
                    e2 --- t2
                end
                e3 --- e2

                e3 --- tok8

                %% 1 -> term
                subgraph gt4_3[" "]
                    subgraph gt4_2[" "]
                        subgraph gt4_1[" "]
                            n3 --- tok9
                        end
                        p4 --- n3
                    end
                    t3 --- p4
                end
                e3 --- t3
            end

            p5 --- tok10
        end

        %% (17 + 4) -> primary
        subgraph gp1[" "]

            %% direction TB
            p2 --- tok0
            p2 --- e1

            %% 17 + 4 -> expression
            subgraph ge1[" "]
                %% 17 -> expression
                subgraph gt1_4[" "]
                    subgraph gt1_3[" "]
                        subgraph gt1_2[" "]
                            subgraph gt1_1[" "]
                                n0 --- tok1
                            end
                            p0 --- n0
                        end
                        t0 --- p0
                    end
                    e0 --- t0
                end
                e1 --- e0

                e1 --- tok2
                %% 4 -> term
                subgraph gt2_3[" "]
                    subgraph gt2_2[" "]
                        subgraph gt2_1[" "]
                            n1 --- tok3
                        end
                        p1 --- n1
                    end
                    t1 --- p1
                end
                e1 --- t1
            end

            p2 --- tok4
        end

        t4 --- p5

    ```
    *This diagram was actually quite tricky to generate.  I ended up using subgraphs to force element grouping per [this mermaid-js github issue comment](https://github.com/mermaid-js/mermaid/issues/815#issuecomment-652844554).*



11. *Why does the program not have a function called `number()`?*

    The program does not have a `number()` function because this is implemented within `Token_stream::get()` - when a numerical digit or `.` is detected in the incoming character stream, `iostream::cin` is used to parse the characters into a C++ `double` (in other words, a `Number`).


12. *What is a token?*

    A token is a kind, value pair representing a "unit" of something in our program.  In our calculator, tokens were a user-defined type (a class) - `Token`.  According to Wikipedia, this is a [*lexical token*](https://en.wikipedia.org/wiki/Lexical_analysis#Token).


13. *What is a grammar? A grammar rule?*

    A grammar is a set of rules that define how a sequence of characters breaks down into subsequences, eventually down to the token level.  In our case, we use it to implement an order of operations for the calculator.


14. *What is a class? What do we use classes for?*

    A class is a user-defined type (similar to C++ built-ins like `double`, `string`, etc).  It can have member variables and functions.  Classes are used to abstract concepts (should be used to make things simpler, not more complicated).


15. *How can we provide a default value for a member of a class?*

    Within its constructor!  A class can have multiple constructors, depending on how many/which member variables are exposed as arguments into the constructor (each must have a different signature).  Examples from drill:
    
    Initializing a `Token`: two options!
    ```C++
    Token(char ch)                  // just specifying via argument, value has default of 0
        :kind(ch), value(0) { }
    Token(char ch, double val)
        :kind(ch), value(val) { }   // specifying both kind/value via arg, no defaults
    ```

    Initializing a `Token_stream` (setting `full` to `false` as default)
    ```C++
    Token_stream::Token_stream()
        :full(false), buffer(0) { }
    ```


16. *In `expression()`, why is the default for the switch-statement to “put back” the token?*

    If the token obtained from the stream / user input is not a `+` or `-`, then it does not match the grammar rules defining an expression.  The token is put back into the front of the stream (into the buffer) so that another function can process it (either as valid input, if it meets another grammar rule, or as invalid input).  Finally `expression()` returns the left `Term`, which is itself a valid `Expression` per grammar rules.


17. *What is “look-ahead”?*

    We can't directly evaluate expressions as the user enters them, char-by-char, because that could violate order of operations.  Ex: 2+2*3.  Therefore, before evaluating 2+2, we first need to be able to "look ahead" (see past this portion) to ensure there isn't a higher-priority operator (like * over +).  If there is, do that first.


18. *What does `putback()` do and why is it useful?*

    It "prepends" tokens to the front of the input stream.  This is implemented using a buffer - for our calculator, the buffer only stores one element, but could be implemented using an array as well.

    It is useful because if a given function cannot process a token (doesn't match its grammar rules), it can delegate the processing to another function by putting the token back into the stream.  That other function can decide whether the token is valid or invalid based on its  rules.  I'd imagine this only works in a cohesive system of grammar rules.


19. *Why is the remainder (modulus) operation, %, difficult to implement in the term()?*

    The modulus operator is only defined for integers, but calculator is written for floating point numbers (superset of integers).  Could result in undefined behavior.


20. *What do we use the two data members of the `Token` class for?*

    - `kind` is used to signify what type of token we are processing.
        - `Numbers` are represented with `kind=8` (chosen arbitrarily).
        - All other symbols (mathematical operators, print character, exit character) are their own `kind`.
    - `value` differentiates `Tokens` of the same kind for each other - only relevant for `Numbers`.  The value is the `double` read from the user and used for calculations.


21. *Why do we (sometimes) split a class’s members into private and public members?*

    Private = user does not have access to variables/functions, so they cannot mess with internal state of class.

    Public = interface between user/class - ideally, as simple as possible to get full benefits of abstraction.


22. *What happens in the `Token_stream` class when there is a token in the buffer and the `get() function` is called?*

    We don't read input from the user - instead, we return the buffered `Token` and reset `ts.full` to `false`.


23. *Why were the `;` and `q` characters added to the switch-statement in the get() function of the Token_stream class?*

    `Token_stream::get()` processes all user input.  They were added so that the `main()` function could also access the stream and check for print/exit.  Since they are not part of the grammar, as long as they occur between valid expressions they'll be put into buffer until `main()`.


24. *When should we start testing our program?*

    Right away, ideally (that's the point of test-driven-development).  Individual blocks of functionality (aka functions) can be tested independently using unit tests.


25. *What is a “user-defined type”? Why would we want one?*

    A class -- see #14.


26. *What is the interface to a C++ “user-defined type”?*

    Its public member functions and variables.


27. *Why do we want to rely on libraries of code?*

    They have pre-built functionality, no need for us to re-invent wheel (unless as an academic/learning exercise).