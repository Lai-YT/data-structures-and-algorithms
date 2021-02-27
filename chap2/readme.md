# Exercises

## 2.1-3

Consider the searching problem: \
Input: A sequence of n numbers A = [a1, a2, ... , an] and a value v. \
Output: An index i such that v = A[i] or the special value NIL if does not
appear in A.

- Pseudocode:
```
linearSearch(A, v)
  for i = 1 to A.length
    if A[i] == v
      return i
  return NIL
  ```

- Prove:
Elements in subarray A[1..i-1] are always checked not equal to v. \
If find v, returns i which v = A[i]; When the loop terminates at i = A.length + 1, the entire array A[1..A.length] has no element v, so returns NIL.
