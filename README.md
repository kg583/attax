# attax

[Stax](https://staxlang.xyz/#) is a stack-oriented, hypercompressible golflang designed and maintained by Tom Theisen. [pysearch](https://github.com/lynn/pysearch) is a tool created by the code golf community for brute-forcing Python (or, generally, C-like) "magic formulas". This is our humble attempt to unite the two.

If you're not yet familiar with Stax, please play around with it in the online interpreter, and check out the docs and code.golf wiki for an introduction and tips.

## Building and Running

TODO


## Search Procedure

We search over Stax snippets which send some input vector **u** of values to an output vector **v**, not caring for what the snippet does to values not in **u**; Stax has bigints, bigrats, and good ol' floats, but we restrict to the case of integer vectors for now.

### Expressions

Akin to pysearch, we generate all possible expressions of a given length, with result caching to prune formulas which are identical on the inputs, immediate failure on erroring or non-functional formulas, and some manual insight to prevent obvious redundancies. Since Stax uses postfix notation, expressions are simply sequences of stack operations (implemented as chains of node structs), which might push a value (`12`), operate on the top few values (`+`), or rearrange the stack (`a`). We also have two registers at our disposal, `X` & `Y`, and the input stack, which can act as a sort of register stack if the situation permits.

#### Int to Int Ops

| **Op** | **Code**         | **Status** |   | **Op** | **Code**                | **Status** |
|--------|------------------|------------|---|--------|-------------------------|------------|
| `1234` | `1234`           | `int`      |   | `\|%`  | `a b -> a // b a % b`   | `int`      |
| `A`    | `10`             | TODO       |   | `\|/`  | `a // b ** v_b(a)`      | `int`      |
| `O`    | Tuck `1`         | TODO       |   | `\|<`  | `a << b`                | `int`      |
| `U`    | `-1`             | TODO       |   | `\|>`  | `a >> b`                | `int`      |
| `Z`    | Tuck `0`         | TODO       |   | `\|1`  | `(-1) ** a`             | `int`      |
|        |                  |            |   | `\|2`  | `2 ** a`                | `int`      |
| `a`    | `a b c -> c a b` | `int`      |   | `\|5`  | `a`th Fibonacci number  | TODO       |
| `b`    | `a b -> a b a b` | `int`      |   | `\|6`  | `a`th prime             | TODO       |
| `c`    | `a b -> a a b`   | `int`      |   | `\|a`  | `abs(a)`                | `int`      |
| `d`    | `a b -> b`       | `int`      |   | `\|C`  | `a nCr b`               | TODO       |
| `n`    | `a b -> b a b`   | `int`      |   | `\|e`  | `(a + 1) % 2`           | `int`      |
| `[`    | `a b -> a b b`   | `int`      |   | `\|F`  | `a!`                    | TODO       |
| `s`    | `a b -> b a`     | `int`      |   | `\|g`  | `gcd(a,b)`              | `int`      |
|        |                  |            |   | `\|l`  | `lcm(a,b)`              | `int`      |
| `+`    | `a + b`          | `int`      |   | `\|N`  | `int(a ** (1/b))`       | TODO       |
| `-`    | `a - b`          | `int`      |   | `\|p`  | Is `a` prime?           | TODO       |
| `*`    | `a * b`          | `int`      |   | `\|q`  | `int(sqrt(a))`          | `int`      |
| `/`    | `a // b`         | `int`      |   | `:~`   | `a \| 2**bitlen(a) - 1` | `int`      |
| `%`    | `a % b`          | `int`      |   | `:!`   | Does `gcd(a,b) == 1`?   | `int`      |
| `#`    | `a ** b`         | `int`      |   | `:-`   | `abs(a - b)`            | `int`      |
| `^`    | `a + 1`          | `int`      |   | `:@`   | `(a >> b) & 1`          | `int`      |
| `v`    | `a - 1`          | `int`      |   | `:[`   | `a & ~(1 << b)`         | `int`      |
| `h`    | `a // 2`         | `int`      |   | `:]`   | `a \| (1 << b)`         | `int`      |
| `H`    | `a * 2`          | `int`      |   | `::`   | `a ^ (1 << b)`          | `int`      |
| `I`    | `a & b`          | `int`      |   | `:/`   | `v_b(a)`                | `int`      |
| `M`    | `a \| b`         | `int`      |   | `:+`   | `sign(a)`               | `int`      |
| `S`    | `a ^ b`          | `int`      |   | `:1`   | `bit_count(a)`          | TODO       |
| `J`    | `a ** 2`         | `int`      |   | `:2`   | `int(log(a,2))`         | `int`      |
| `N`    | `-a`             | `int`      |   | `:A`   | `int(log(a,10))`        | `int`      |
| `t`    | `min(a, b)`      | `int`      |   | `:b`   | Is `b <= a < c`?        | `int`      |
| `T`    | `max(a, b)`      | `int`      |   | `:c`   | `min(max(a, b), c)`     | `int`      |
|        |                  |            |   | `:C`   | `a`th Catalan number    | TODO       |
| `!`    | `!a`             | `int`      |   | `:g`   | `a & -a`                | `int`      |
| `<`    | `a < b`          | `int`      |   | `:G`   | `2**int(log(a,2))`      | `int`      |
| `>`    | `a > b`          | `int`      |   | `:J`   | `a b -> a**2 b**2`      | `int`      |
| `=`    | `a == b`         | `int`      |   | `:m`   | `ceil(a / b) * b`       | `int`      |
|        |                  |            |   | `:N`   | Does `a == k ** b`?     | TODO       |
|        |                  |            |   | `:p`   | Largest prime `< a`     | TODO       |
|        |                  |            |   | `:P`   | Next prime `>= a`       | TODO       |
|        |                  |            |   | `:t`   | `totient(a)`            | TODO       |

#### Int to Float Ops

#### Float to Int Ops

#### Other Ops

TODO

### Cramming

In its quest for ultimate code shortness, Stax has [multiple forms of array compression](https://github.com/tomtheisen/stax/blob/master/docs/compressed.md) built in (which we'll call "cramming" from here on). Though they differ in their specific application, they all have the general form of converting the array into a compressed bit sequence, realizing this sequence as a number in base 92-94, then encoding the digits in printable ASCII.

The space of all possible crammed arrays is prohibitively large, so we cannot simply inject them into the expression-generating searcher. Instead, we note that crammed arrays are actually able to replace *any* magic formula: if `x` contains the cramming of **u** and `y` the cramming of **v**, then `xIy@` is a valid formula. Such a formula might be terribly long when applied to **u**, but the upshot is that we can perform this construction on the intermediate output of **u'** of *any* expression found by our normal search.

Thus, we consider possible "templates" which take an intermediate **u'** and attach some short final step involving a crammed array (perhaps with some restrictions on **u'**); these are guaranteed to yield a valid formula and just might be short too.

#### Templates

| **Template** | **Restriction(s)**                   | **Status** |
|--------------|--------------------------------------|------------|
| `xIy@`       | N/A                                  | TODO       |
| `x@`         | **u'** is distinct mod `x%`          | TODO       |
| `xIy+`       | **v** is (nearly) a contiguous range | TODO       |

### Other Considerations

Stax has a plethora of ad-hoc shortenings that we must manually add checks for (some of which are already done by tools in the online interpreter). To name just a few (none of which we have implemented yet):
- If **v** is periodic, array access with `@` can loop, or the period can be multiplied with `*`
- If **v** is a bit-array, it can be obtained via `:B`
- Some specific **v** (made of printable ASCII) are built-in constants
- Some useful ops require passing to arrays first (e.g. `E|+` for sum-of-digits) (regard these as "macro" ops?)

