# Find Anagrams

To find anagrams, one may lexicographically sort the word and check the
equality, or count letters with dictionary. \
But in this implementation, another approach is used, which is efficient and elegant: ***prime factorization***.

"*Every integer either is a prime number itself or can be represented as the product of prime numbers and that, moreover, \
this representation is unique, the order of the factors.*"

Assign each letter in the alphabet to a prime number, and group all the prime factorization up as the key. \
Since prime factorization is unique, this is a good hash function. \
To prevent *overflow*, which happens when a word is long, modulo a large prime.

Reference:

- brandon, [An Algorithm for Finding Anagrams](https://hackernoon.com/an-algorithm-for-finding-anagrams-2fe7655de85b). HackerNoon, 12, 31, 2018.
- [Generate same unique hash code for all anagrams](https://stackoverflow.com/questions/18781106/generate-same-unique-hash-code-for-all-anagrams/18785523). Stack Overflow.
