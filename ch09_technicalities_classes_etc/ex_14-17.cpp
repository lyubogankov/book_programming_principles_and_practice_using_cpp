/*
14. Design and implement a Money class for calculations involving dollars and cents
    where arithmetic has to be accurate to the last cent using the 4/5 rounding rule
    (.5 of a cent rounds up; anything less than .5 rounds down).
    
    Represent a monetary amount as a number of cents in a long int, but input and output as dollars and cents, e.g., $123.45.
    Do not worry about amounts that don’t fit into a long int.

15. Refine the Money class by adding a currency (given as a constructor argument).
    Accept a floating-point initializer as long as it can be exactly represented as a long int.
    
    Don’t accept illegal operations. For example, Money*Money doesn’t make sense, and USD1.23+DKK5.00 makes sense only if
    you provide a conversion table defining the conversion factor between U.S. dollars (USD) and Danish kroner (DKK).

16. Define an input operator (>>) that reads monetary amounts with currency denominations, such as USD1.23 and DKK5.00, into a Money variable.
    Also define a corresponding output operator (>>).

17. Give an example of a calculation where a Rational gives a mathematically better result than Money.

18. Give an example of a calculation where a Rational gives a mathematically better result than double.
*/