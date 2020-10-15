```C
double *p;
double balance[10];
p = balance;
```
It is legal to use array names as constant pointers, and vice versa. Therefore, `*(balance + 4)` is a legitimate way of accessing the data at `balance[4]`.
Once you store the address of the first element in `p`, you can access the array elements using `*p`, `*(p+1)`, `*(p+2)` and so on.