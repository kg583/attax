# attax

[Stax](https://staxlang.xyz/#) is a stack-oriented, hypercompressible golflang designed and maintained by Tom Theisen. [pysearch](https://github.com/lynn/pysearch) is a tool created by the code golf community for brute-forcing Python (or, generally, C-like) "magic formulas". This is our humble attempt to unite the two.

If you're not yet familiar with Stax, please play around with it in the online interpreter, and check out the docs and code.golf wiki for an introduction and tips.

## Building and Running

TODO: Explain further

Edit params.h and run with (on linux):

```bash
make run
```


## Search Procedure

We search over Stax snippets which send some input vector **u** of values to an output vector **v**, not caring for what the snippet does to values not in **u**; Stax has bigints, bigrats, and good ol' floats, but we restrict to the case of integer vectors for now.

### Expressions

Akin to pysearch, we generate all possible expressions of a given length, with result caching to prune formulas which are identical on the inputs, immediate failure on erroring or non-functional formulas, and some manual insight to prevent obvious redundancies. Since Stax uses postfix notation, expressions are simply sequences of stack operations (implemented as chains of node structs), which might push a value (`12`), operate on the top few values (`+`), or rearrange the stack (`a`). We also have two registers at our disposal, `X` & `Y`, and the input stack, which can act as a sort of register stack if the situation permits.

#### Int to Int Ops

| **Op** | **Code**         | **Status** |   | **Op** | **Code**                | **Status** |
|--------|------------------|------------|---|--------|-------------------------|------------|
| `1234` | `1234`           | Done       |   | `\|%`  | `a b -> a // b a % b`   | Done       |
| `A`    | `10`             | TODO       |   | `\|/`  | `a // b ** v_b(a)`      | Done       |
| `O`    | Tuck `1`         | Done       |   | `\|<`  | `a << b`                | Done       |
| `U`    | `-1`             | Done       |   | `\|>`  | `a >> b`                | Done       |
| `Z`    | Tuck `0`         | Done       |   | `\|1`  | `(-1) ** a`             | Done       |
|        |                  |            |   | `\|2`  | `2 ** a`                | Done       |
| `a`    | `a b c -> c a b` | Done       |   | `\|5`  | `a`th Fibonacci number  | TODO       |
| `b`    | `a b -> a b a b` | Done       |   | `\|6`  | `a`th prime             | TODO       |
| `c`    | `a b -> a a b`   | Done       |   | `\|a`  | `abs(a)`                | Done       |
| `d`    | `a b -> b`       | Done       |   | `\|C`  | `a nCr b`               | TODO       |
| `n`    | `a b -> b a b`   | Done       |   | `\|e`  | `(a + 1) % 2`           | Done       |
| `[`    | `a b -> a b b`   | Done       |   | `\|F`  | `a!`                    | TODO       |
| `s`    | `a b -> b a`     | Done       |   | `\|g`  | `gcd(a,b)`              | *...*      |
|        |                  |            |   | `\|l`  | `lcm(a,b)`              | *...*      |
| `+`    | `a + b`          | Done       |   | `\|N`  | `int(a ** (1/b))`       | TODO       |
| `-`    | `a - b`          | Done       |   | `\|p`  | Is `a` prime?           | TODO       |
| `*`    | `a * b`          | Done       |   | `\|q`  | `int(sqrt(a))`          | Done       |
| `/`    | `a // b`         | Done       |   | `:~`   | `a \| 2**bitlen(a) - 1` | Done       |
| `%`    | `a % b`          | Done       |   | `:!`   | Does `gcd(a,b) == 1`?   | Done       |
| `#`    | `a ** b`         | Done       |   | `:-`   | `abs(a - b)`            | Done       |
| `^`    | `a + 1`          | Done       |   | `:@`   | `(a >> b) & 1`          | Done       |
| `v`    | `a - 1`          | Done       |   | `:[`   | `a & ~(1 << b)`         | Done       |
| `h`    | `a // 2`         | Done       |   | `:]`   | `a \| (1 << b)`         | Done       |
| `H`    | `a * 2`          | Done       |   | `::`   | `a ^ (1 << b)`          | Done       |
| `I`    | `a & b`          | Done       |   | `:/`   | `v_b(a)`                | Done       |
| `M`    | `a \| b`         | Done       |   | `:+`   | `sign(a)`               | Done       |
| `S`    | `a ^ b`          | Done       |   | `:1`   | `bit_count(a)`          | TODO       |
| `J`    | `a ** 2`         | Done       |   | `:2`   | `int(log(a,2))`         | Done       |
| `N`    | `-a`             | Done       |   | `:A`   | `int(log(a,10))`        | Done       |
| `t`    | `min(a, b)`      | Done       |   | `:b`   | Is `b <= a < c`?        | Done       |
| `T`    | `max(a, b)`      | Done       |   | `:c`   | `min(max(a, b), c)`     | Done       |
|        |                  |            |   | `:C`   | `a`th Catalan number    | TODO       |
| `!`    | `!a`             | Done       |   | `:g`   | `a & -a`                | Done       |
| `<`    | `a < b`          | Done       |   | `:G`   | `2**int(log(a,2))`      | Done       |
| `>`    | `a > b`          | Done       |   | `:J`   | `a b -> a**2 b**2`      | Done       |
| `=`    | `a == b`         | Done       |   | `:m`   | `ceil(a / b) * b`       | Done       |
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

