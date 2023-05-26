## Tutorial
Keywords: `Rabin–Karp algorithm`, `Hashing`, `Binary Search Tree`, `Booth's Algorithm`, `Trie`

Calculate the $M$ hash values of each rotation of a string. Then, we need to hash the $M$ values again to represent the blueprint of a string. One possible hash functions is "minima of the $M$ values". We say two strings are rotationally identical if their blueprints are identical. 

For each insert / remove operation, we insert / remove a value, representing the blueprint, into a multiset. To calculate the number of pairs, we can simply count the identical numbers in the multiset. The multiset can be implemented via any BST. It does not have to be a balanced BST, since the input value (our hash value) can be generated randomly.

Time complexity: $O((N+Q)(M + \log (N+Q)))$

### Hash Functions
- Good Hashes
    - minima
    - maxima
    - rolling hash again with decent $P, Q$
- Bad Hashes
    - Sum (super bad)
    - Xor (also super bad)
    - Squared / Cubic sum
    - Reciprocal sum
    - Rolling hash with unfortunate $P, Q$

### Binary Search Tree
We do not have to use a balanced BST only if we can ensure the hashed value to be random. Consider the minima hash, one common mistake, which the problem setter had made, is calculating the rolling hash with $a = 1, b = 2, ...$. In such cases, the input below may generate a skew tree.
```
aaa
aab
aac
...
yyz
yzz
zzz
```
To counter such input, it is suggested that we map each character to a random value. Therefore the hashed value will be more independent to the input order. 

### Booth's Algorithm
Another approach is to find the [lexicographically minimal string rotation](https://en.wikipedia.org/wiki/Lexicographically_minimal_string_rotation), which can be done in $O(M)$ via KMP. After finding such string, we only have to count the number of identical strings in $S$, which can be easily done with a trie. 

- time complexity: $O((N+Q)M)$
