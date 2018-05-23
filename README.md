zen.h
=====

C preprocessor utilities


Introduction
------------


**zen.h** is a collection of C preprocessor macros. Right now it offers only a small framework for managing a 32-bit counter purely via the C preprocessor, but it might expand in the future.

There are two main reasons for implementing a novel counter for the C preprocessor other than the built-in (and non-standard) `__COUNTER__`. The first reason is that `__COUNTER__` is not flexible: when two or more headers use it, the values that this yields are not predictable. The second and most important reason is that `__COUNTER__` is not reusable and gets increased every time it is invoked, making the storage of its yielded values within the preprocessor environment virtually impossible.

With these two reasons in mind, this framework has been designed to implement a counting macro that increments only when an incrementing function is explicitly called on it, but that keeps otherwise its current value; and that is able to deal with infinite identifiers, in order to avoid conflicts between different headers that might need to use a counter separately.

Unfortunately the C preprocessor is a tough beast, and the best way to implement such a counter and safely bind it to a 32-bit unsigned type is through fixed-length hexadecimal numbers. This does not produce any particular behavior when the values yielded by the counter are used as literal integers, but does produce a different result compared to the one produced by the built-in `__COUNTER__` when these values are used to create unique identifiers.

Within this implementation it is possible to set a counter to any 32-bit arbitrary value other than zero or a natural increment by providing its hexadecimal digits (see macro `ZEN_COUNTER_PARSE_HEX()`).


Sample usage
------------

```c
#include <stdio.h>
#include "zen.h"

int main() {

	#define FIRST_VALUE	ZEN_COUNTER_NEW()
	printf("%u\n", ZEN_COUNTER_AS_NUMBER(FIRST_VALUE));	// "0"

	#define SECOND_VALUE	ZEN_COUNTER_NEXT(FIRST_VALUE)
	printf("%u\n", ZEN_COUNTER_AS_NUMBER(SECOND_VALUE));	// "1"

	#define THIRD_VALUE	ZEN_COUNTER_NEXT(SECOND_VALUE)
	printf("%u\n", ZEN_COUNTER_AS_NUMBER(THIRD_VALUE));	// "2"

	#define OTHER_COUNTER	ZEN_COUNTER_PARSE_HEX(0, 0, 0, 4, F, 3, B, 6)
	printf("%u\n", ZEN_COUNTER_AS_NUMBER(OTHER_COUNTER));	// "324534"

	#define FIFTH_VALUE	ZEN_COUNTER_NEXT(OTHER_COUNTER)
	printf("%u\n", ZEN_COUNTER_AS_NUMBER(FIFTH_VALUE));	// "324535"

	#define SIXTH_VALUE	ZEN_COUNTER_NEXT(THIRD_VALUE)
	printf("%u\n", ZEN_COUNTER_AS_NUMBER(SIXTH_VALUE));	// "3"

	return 0;

}
```


Manual
------


### Creating a new counter set to `0`


##### Syntax

```c
ZEN_COUNTER_NEW()
```


##### Description

Returns a new _zen counter_ set to `0`.


### Creating a new counter set to a given value


##### Syntax

```c
ZEN_COUNTER_PARSE_HEX(HEX1, HEX2, HEX3, HEX4, HEX5, HEX6, HEX7, HEX8)
```


##### Description

Returns a new _zen counter_ set to a given value.


##### Parameters

<dl><dt>

`HEX1`, &hellip; `HEX8`

</dt><dd>

The eight hexadecimal digits needed to represent a 32-bit unsigned integer.

</dd></dl>


### Increasing a counter


##### Syntax

```c
ZEN_COUNTER_NEXT(COUNTER)
```


##### Description

Returns a new _zen counter_ that equals the _zen counter_ passed as argument plus one.


##### Parameters

<dl><dt>

`COUNTER`

</dt><dd>

The counter to use as base of increment.

</dd></dl>


### Converting a counter to a literal unsigned integer


##### Syntax

```c
ZEN_COUNTER_AS_NUMBER(COUNTER)
```


##### Description

Returns the literal numerical representation of the _zen counter_ passed as argument.


##### Parameters

<dl><dt>

`COUNTER`

</dt><dd>

The counter to convert to a literal unsigned integer.

</dd></dl>


### Converting a counter to a unique identifier


##### Syntax

```c
ZEN_COUNTER_AS_IDENTIFIER(COUNTER, PREFIX)
```


##### Description

Returns a new unique identifier based on the concatenation of the prefix and the _zen counter_ passed as arguments.


##### Parameters

<dl><dt>

`COUNTER`

</dt><dd>

The _zen counter_ to use as unique suffix.

</dd><dt>

`PREFIX`

</dt><dd>

The prefix to which the counter will be concatenated.

</dd></dl>


### Converting a counter to a hexadecimal string


##### Syntax

```c
ZEN_COUNTER_AS_HEX_STRING(COUNTER)
```


##### Description

Returns a new literal string containing the hexadecimal representation of `COUNTER` (without the `0x` prefix).


##### Parameters

<dl><dt>

`COUNTER`

</dt><dd>

The counter to stringify.

</dd></dl>

