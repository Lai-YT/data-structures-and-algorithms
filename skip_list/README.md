# Skip List

Skip lists are data structures that use probabilistic balancing rather than strictly enforced balancing. \
As a result, the algorithms for insertion and deletion in skip lists are much simpler and significantly faster than equivalent algorithms for balanced trees.

## Complexity

|Operation       |Average    |Worst case    |
|----------------|-----------|--------------|
|Space           |O(*n*)     |O(*n\*lg(n)*) |
|Find            |O(*lg(n)*) |O(*n*)        |
|Insert (Update) |O(*lg(n)*) |O(*n*)        |
|Delete          |O(*lg(n)*) |O(*n*)        |

## Reference

- PUGH, William. Skip lists: a probabilistic alternative to balanced trees. Communications of the ACM, 1990, 33.6: 668-676.
