# Exercises

## 2.1-3

Consider the searching problem: \
Input: A sequence of n numbers A = [a1, a2, ..., an] and a value v. \
Output: An index i such that v = A[i] or the special value NIL if does not
appear in A.

- Pseudocode:
```
LinearSearch(A, v)
  for i = 1 to A.length
    if A[i] == v
      return i
  return NIL
  ```

- Prove:
Elements in subarray A[1..i-1] are always checked not equal to v. \
If find v, returns i which v = A[i]; When the loop terminates at i = A.length + 1, \
the entire array A[1..A.length] has no element v, so returns NIL.


## 2.2-3

Consider sorting n numbers stored in array A by first finding the smallest element \
of A and exchanging it with the element in A[1]. Then find the second smallest
element of A, and exchange it with A[2]. \
Continue in this manner for the first n1
elements of A. \
Write pseudocode for this algorithm, which is known as selection
sort.

- Pseudocode:
```
SelectionSort(A)
  n = A.length
  for j = 1 to n - 1
    min = j
    for i = j + 1 to n
      if A[i] < A[min]
        min = i
    exchange A[j] with A[min]
```