/*
 This drill has two parts. The first exercises/builds your understanding of free-store-allocated arrays and contrasts arrays with vectors:

1. Allocate an array of ten ints on the free store using new.

2. Print the values of the ten ints to cout.

3. Deallocate the array (using delete[]).

4. Write a function print_array10(ostream& os, int* a) that prints out the values of a (assumed to have ten elements) to os.

5. Allocate an array of ten ints on the free store; initialize it with the values 100, 101, 102, etc.; and print out its values.

6. Allocate an array of 11 ints on the free store; initialize it with the values 100, 101, 102, etc.; and print out its values.

7. Write a function print_array(ostream& os, int* a, int n) that prints out the values of a (assumed to have n elements) to os.

8. Allocate an array of 20 ints on the free store; initialize it with the values 100, 101, 102, etc.; and print out its values.

9. Did you remember to delete the arrays? (If not, do it.)

10. Do 5, 6, and 8 using a vector instead of an array and a print_vector() instead of print_array().

The second part focuses on pointers and their relation to arrays. Using print_array() from the last drill:

1. Allocate an int, initialize it to 7, and assign its address to a variable p1.

2. Print out the value of p1 and of the int it points to.

3. Allocate an array of seven ints; initialize it to 1, 2, 4, 8, etc.; and assign its address to a variable p2.

4. Print out the value of p2 and of the array it points to.

5. Declare an int* called p3 and initialize it with p2.

6. Assign p1 to p2.

7. Assign p3 to p2.

8. Print out the values of p1 and p2 and of what they point to.

9. Deallocate all the memory you allocated from the free store.

10. Allocate an array of ten ints; initialize it to 1, 2, 4, 8, etc.; and assign its address to a variable p1.

11. Allocate an array of ten ints, and assign its address to a variable p2.

12. Copy the values from the array pointed to by p1 into the array pointed to by p2.

13. Repeat 10–12 using a vector rather than an array.
*/