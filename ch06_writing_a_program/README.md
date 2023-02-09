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

    uhh


4. *Why is creating a small, limited version of a program a good idea?*

    Get to working program faster - that way, can evaluate next steps based on working code instead of spending a lot of effort on a larger project that may not have the right features.


5. *Why is feature creep a bad idea?*

    According to the book, adding one extra feature opens the floodgates for more features to get added, bogging down the development process.  Better to implement one thing at a time.


6. *What are the three main phases of software development?*

    1. meme
    2. meme
    3. meme


7. *What is a “use case”?*


8. *What is the purpose of testing?*


9. *According to the outline in the chapter, describe the difference between a `Term`, an `Expression`, a `Number`, and a `Primary`.

    **`Number`**: a decimal number stored, expressed in a format compatible with the C++ floating-point data type.  This isn't yet factored into the mathematical order of operations.

    **`Primary`**: the highest-priority operation within the mathematical order of operations (OoO) - it represents *parentheses* (either a single `Number`, or an `Expression` surrounded by parens, which evaluates to a single `Number`, aka a `double`).

    *If exponentiation were defined, it'd have a grammar element between `Term` and `Primary`.*

    **`Term`**: the second-highest priority within OoO.  For our calculator, that's division and multiplication of `Primaries`, the next-highest priority grammar element.

    **`Expression`**: the lowest priority within OoO.  For our calculator, that's addition and subtraction of `Terms`, the next-highest priority grammar element.


10. *In the chapter, an input was broken down into its component `Terms`, `Expressions`, `Primarys`, and `Numbers`. Do this for (17+4)/(5–1).

    ```mermaid

    graph GrammarTree

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

    https://github.com/mermaid-js/mermaid/issues/815#issuecomment-652844554 < use this method

    Almost there, but the order of the big primary blocks is flipped


11. *Why does the program not have a function called `number()`?*


12. *What is a token?*


13. *What is a grammar? A grammar rule?*


14. *What is a class?* What do we use classes for?*


15. *How can we provide a default value for a member of a class?*


16. *In the expression function, why is the default for the switch-statement to “put back” the token?*


17. *What is “look-ahead”?*


18. *What does `putback()` do and why is it useful?*


19. *Why is the remainder (modulus) operation, %, difficult to implement in the term()?*


20. *What do we use the two data members of the `Token` class for?*


21. *Why do we (sometimes) split a class’s members into private and public members?*


22. *What happens in the `Token_stream` class when there is a token in the buffer and the `get() function` is called?*


23. *Why were the `;` and `q` characters added to the switch-statement in the get() function of the Token_stream class?*


24. *When should we start testing our program?*


25. *What is a “user-defined type”?* Why would we want one?*


26. *What is the interface to a C++ “user-defined type”?*


27. *Why do we want to rely on libraries of code?*