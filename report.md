Qixiang (David) Zhang  
Nai-Jack Li

## CS-260P Project 1

##### Problem statement
Find K Largest elements in a size N unsorted array Best.  
>For example, for n=7 and k=3,   
if the private array (indexed from 1 to 7) contains the values: 3,5,4,7,2,6,1   
then the integer array Best[] (indexed from 0 to 2) should hold: 4,6,2  



##### Our result

In this project, we implement the `"doalg.c"` with the framework of insertion sort and combine with binary search algorithm. With parameters $n = 10000$, $k = 40$, and $iteration = 1000$, the maximum number of comparisons is `11558`, and the average number of comparisons is `11316.97`.



##### Our algorithm

 We initialize the $Best$ array with $k$ number of $-1$'s. Then we take one element from the unsorted size-$n$ array and compare with the last item of $Best$ array. If smaller, we eliminate this choice and move on to the next element. If larger, then we replace the last item of $Best$ array with this element. $Best$ array is maintained to stay in descending order. Using binary search, we find the exact location to put the element, and shift the rest of the items down. The process continues until all elements of the unsorted array have been selected or eliminated.
 `COMPARE.c` gets invoked every time when elements gets compared. We intend to find the algorithm that uses least number of comparisons.

 ```
 doalg(n, k, Best)
    Initialize array Best as size k of -1's
    loop i from 1 increment to n
        Compare i with the last item of array Best
        If Best[k-1] = -1 or COMPARE(Best[k-1], i) == 2 Then
            Best[k-1] = i
            Use binary search to find the location to insert i
    return 1
 ```



##### Analysis for Theoretical Worst Case

Theoretically, the worst case for the number of comparisons is when the input array to be in ascending sorted order. Every element in the input array has to be compared with the smallest item once inside the $Best$ array (size = 40) and then goes through the binary search process for a maximum of $ceil(log_2{40})=6$. Follow this logic, let $n$ be the size of the input array, the number of total comparisons would be:
$$
n[ceil(\log_2{k})+ 1]
$$
In this case ($n = 10000,\space k = 40$), the total number of comparisons is 70000.

The probability of the input array that is already sorted in ascending order is 1/(10000!) ≈ 0. 10000 factorial is 35,658 digits long. Therefore, even if the algorithm runs for 1000 times, the chance for the worst case to occur is still close to zero.

To verify our hypothesis, we manually input an array with size 10000 and in ascending order. The observed total number of comparisons for the worst case is 69919, which is 81 comparisons short of 70000. This minor inconsistency occurs most likely due to the edge cases during the initialization of the size $k$ array.



##### Analysis for Theoretical Expected Worst Case
The expected worst case is the maximum total number of comparisons we expect to get after run this algorithm on 1000 random input size-$n$ arrays. The expected worst case comparisons is the product of the probability of the worst case and the number of comparisons that worst case uses.

For the probability of the worst case, consider this, let $n$ be the total number of elements in the input array, and $n_i$ be the number of the subarray which contains 1st large to ith large elements and is already sorted in ascending order. The total permutation of array is $n!$, and the total permutation of the subarray and the rest of the ($n-n_i$) elements is $(n-n_i+1)!$. Thus, the probability $P_i$ for the number of the largest elements already sorted in ascending order in the input array is
$$
P_i = \frac{(n-n_i+1)!}{n!}
$$
For the number of comparisons $N_i$ that the worst case uses, we can use the logic from the section above with a little modification. The number of the comparisons for $n_i$ would be $n_i(ceil(\log_2{k})+ 1)$. The number for the rest of the elements ($n-n_i$) is 1 for each, so $(n-n_i)*1$. Therefore, the number of comparisons that the worst cases uses is
$$
N_i = n_i[ceil(\log_2{k})+ 1] + (n-n_i)
$$
The probability of the worst case does not occur in 1000 times is $(1-P_i)^{1000}$, and the probability for the worst case does occur at least once in 1000 times is $1-(1-P_i)^{1000}$. Therefore, the total expected worst case $E_{WC}$ is
$$
E_{WC} = \sum_{i = 1}^{n}N_i [1-(1-P_i)^{1000}]
$$

When $n=10000$ and $k=40$, the result is `10958.9`.

To verify our hypothesis, we ran the `MAIN.c` program and observed that the worst case is `11558`. The difference is $5.467\%$ which is negligible.



##### Analysis for Theoretical Average Case
The average number of comparisons is the sum of the products of the probability and number of comparisons for each possible case. We know the average number of comparisons for binary search is $ceil(log_{2}k)$. And for every element, we at least do one comparison for checking whether it needs to do binary search. Therefore, let $num$ be a number in the input array, if we can get the probability 
$$
P_{num} = P(\text{not applying binary search to } num \text{ in algorithm})
$$
then we can get the average total number of comparisons by
$$
\sum_{num=1}^{n}[ (ceil(log_{2}k)+1)(1-P_{num}) + P_{num} ]
$$
To derive $P_{num}$, we first consider $num$ is located at  $i$th position in the input array. Let $p_{num, i}$ be the probability for not applying binary search to $num$ in algorithm when $num$ is at $i$th position. We can observe that $p_{num, i}$ is equal to the probability for at least $k$ elements larger than $num$ being front of $i$th position. Consider there are $(n-num)$ out of $(n-1)$ numbers larger than $num$ and there are $(i-1)$ elements in front of $i$th position. We can deduct the average number of elements in front of $i$th position which are larger than $num$,
$$
front = \frac{n-num}{n-1}*(i-1)
$$
If $front$ is larger than $k$, it means there are average more than $k$ large elements in front of $i$th position, so $p_{num,i}$ will be very close to 1. On the other hand, if $front$ is smaller than $k$, it means there are average less than $k$ elements. We can foresee that  $p_{num,i}$ and $front$ are positive correlation. To simplify the analysis, we assume it is linear.  Therefore,
$$
p_{num,i} = \begin{cases}
    1       & \quad \text{if } front >= k\\
    front/k  & \quad \text{else } 
  \end{cases}
$$
Then we can get $P_{num}$ by summing up $p_{num,i}$ from 1st position to nth position with the normalize factor
$$
P_{num} = \sum_{i=1}^{n} (\frac{1}{n} p_{num, i})
$$
Finally, let $n$ = 10000 and $k​$ = 40, we get the the average total number of comparisons:  `10907`, which is close to observed average number: `10590.82`.



##### Analysis for Observed Worst Case and Average Case and Inconsistencies

We conducted a number of tests by experimenting different values of $n$ and $k$. Below is the table in summary:

| n     | k    | Observed WC | Expected WC | Observed AVG | Expected AVG |
| ----- | ---- | ----------- | ----------- | ------------ | ------------ |
| 100   | 10   | 231         | 222.87      | 190.51       | 188.31       |
| -     | 20   | 343         | 226.17      | 285.54       | 282.67       |
| -     | 40   | 512         | 229.46      | 424.42       | 451.56       |
| 1000  | 10   | 1247        | 1642.38     | 1167.93      | 1135.01      |
| -     | 20   | 1494        | 1644.64     | 1386.30      | 1299.10      |
| -     | 40   | 1991        | 1646.91     | 1823.90      | 1630.21      |
| 10000 | 10   | 10345       | 10956.50    | 10247.75     | 10181.20     |
| -     | 20   | 10732       | 10957.70    | 10590.82     | 10414.50     |
| -     | 40   | 11558       | 10958.90    | 11316.97     | 10907.00     |