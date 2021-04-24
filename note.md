# 演算法筆記

## Insertion sort

![pseudo-code of inserion sort](https://i.imgur.com/YbtApbT.png)

- How to analyze?
- best case: $O(n)$
- worst case: $O(n^2)$
- 特點:
  - 雖然是$n^2$，但常數$c$相較其他sorting演算法小很多，在小$n$ (~ 15)相當優秀，常被使用於混合排序中
  - **Adaptive**, 資料越接近排序好的狀態時間複雜度越低，已經排好時為*O($n$)*
  - **In-place**, 額外空間複雜度$O(1)$
  - **Stable**

---

## Design

- incremental
- recursive: divide and conquer
  - 三個部分:
    - Divide: 把問題分切成小塊，$n - 1$, $n / 2$ 等
    - Conquer: 遞迴各自解決
    - Combine: 把各自的結果組合起來就解決了最初的問題

---

## Merge sort

- Divide and Conquer
- 第一部分: merge (conquer)
![pseudo-code of merge ](https://i.imgur.com/f5KefmM.png)
- 第二部分: merge sort (divide)
![pseudo-code of merge sort](https://i.imgur.com/YG49ykK.png)
- best case: $O(n \lg n)$
- worst case: $O(n \lg n)$
- 樹狀圖中每一層的merge都需花費$O(n)$，而merge sort切半分割會有$\lg n$層，故總複雜度$O(n \lg n)$
- 特點:
  - not-in-place(即使結果直接覆蓋了原來的數列): \
  merge 每次會複製兩個子數列，所以使用額外$O(n)$的空間
  - merge無論資料是否接近排序好都花費$O(n)$
  - **Stable**

---

## Asymptotic notation

![asymptotic graph](https://i.imgur.com/XbUR9I2.png)

### $\Theta-notation$

![big theta definition](https://i.imgur.com/hMTgLB1.png)

- $g(n)$ is an **asymptotically tight bound** for $f(n)$
- 若演算法的best case和worst case時間複雜度一樣，使用$\Theta$即可表示整體複雜度。\
e.g., merge sort is an $\Theta(n \lg n)$ algorithm

### $O-notation$

![big oh definition](https://i.imgur.com/wEUagYH.png)

- **asymptotic upper bound**
- 可以拿來表示worst case

### $\Omega-notation$

![big omega definition](https://i.imgur.com/EomnSoC.png)

- **asymptotic lower bound**
- 可以拿來表示best case

### $o-notation$

- an **upper** bound that is not asymptotically tight
- $2n^2$ is $O(n^2)$ but not $o(n^2)$
- $2n^2$ is $O(n^3)$ and $o(n^3)$

### $\omega-notation$

- a **lower** bound that is not asymptotically tight
- $2n^2$ is $\Omega(n^2)$ but not $\omega(n^2)$
- $2n^2$ is $\Omega(n)$ and $\omega(n)$

---

## Common functions

### Logarithm

$$
a^{log_bc} = c^{log_ba}
$$

### Stirling’s approximation

$$
n! = \sqrt{2\pi n}(\frac{n}{e})^n(1+\Theta(\frac{1}{n}))
$$

also derive that:
$$\begin{align}
n! &= o(n^n), \\
n! &= \omega(2^n), \\
\lg(n!) &= \Theta(n\lg n)
\end{align}$$

### Special Factorials

$$\begin{align}
\lg(\lceil\lg n\rceil!) & = \Theta(\lceil\lg n\rceil\lg\lceil\lg n\rceil) \\
& = \Theta(\lg n\lg\lg n) \\
& = \omega(\lg n)
\end{align}$$

$\text{Therefore,} \lg(\lceil\lg n\rceil!) \neq O(\lg n), \text{and so} \lceil\lg n\rceil!\text{ is not polynomially bounded.}$ 


$$\begin{align}
\lg(\lceil\lg\lg n\rceil!) & = \Theta(\lceil\lg\lg n\rceil\lg\lceil\lg\lg n\rceil) \\
& = \Theta(\lg\lg n\lg\lg\lg n) \\
& = o(({\lg\lg n})^2) \\
& = o(\lg^2(\lg n)) \\
& = o(\lg n)
\end{align}$$

$\text{Therefore,} \lg(\lceil\lg\lg n\rceil!) = O(\lg n), \text{and so} \lceil\lg\lg n\rceil! \text{ is polynomially bounded.}$ 

---

## Find max sub-array

- What is the pseudo-code?
- How to analyze the overall time complexity $T(n)$?
![max sub-array recurrence](https://i.imgur.com/mq1puAo.png)
- $T(n) = \Theta(n\lg n)$

---

## Strassen’s algorithm

利用複雜的數學公式讓本來每次遞迴要做8次的矩陣乘法減為7次$8T(n/2) \to 7T(n/2)$
![Strassen’s recurrence](https://i.imgur.com/TmnBkxB.png)

- 整體複雜度從$n^{\lg8} = n^3$降為$n^{\lg7} \approx n^{2.81}$
- $\Theta(n^{2.81})$
- 目前最快的矩陣乘法運算是$O(n^{2.37})$

---

## Solving recurrences

### The substitution method

- 先猜結果，然後用**數學歸納法**證明，處理**帶有多項的子問題**
- Show that the solution to $T(n) = 2T(\lfloor n/2 \rfloor + 17) + n$ is $O(n \lg n)$

### The recursion-tree method

- 當問題由**多個子問題組成**時使用，畫出遞迴樹，然後用數學方式**加總**
- What is the $\Theta-notation$ of $T(n) = T(n/3) + T(2n/3) + n$? \
(用$O$和$\Omega$夾擠出$\Theta$)

### Master Method

- 當遞迴有$T(n) = aT(n/b) + f(n),\,where\,a \geq 1\,and\,b\gt 1$

![master method](https://i.imgur.com/nCMPK4P.png)

- $\epsilon$ 表示要是多項式等級的差，所以case 1, 2和case 2, 3間都存在gap
- $T(n) = 8T(n/2) + cn2$ is $\Theta(n^3)$
- $T(n) = T(n/2) + cn$ is $\Theta(n)$
- $T(n) = 8T(n/4) + cn3/2$ is $\Theta(n^{3/2}\lg n)$
- What if $T(n) = 3T(n/4) + n \lg n$?
- How to analyze $T(n) = 2T(n/2) + n/(\lg n)$?

---

## Sorting

![time complexity of sortings](https://i.imgur.com/01JhMLk.png)

## Reference

- Introduction to Algorithms, Third Edition. \
By Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein.
- [Using the substituion and master methods - cs.cornell.edu](https://www.cs.cornell.edu/courses/cs3110/2014sp/recitations/24/using-the-substitution-and-master-method.html)
