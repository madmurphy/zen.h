#include <stdio.h>
#include "../zen.h"


#define FIRST_VALUE	ZEN_COUNTER_NEXT(ZEN_COUNTER_NEW())
int ZEN_COUNTER_AS_IDENTIFIER(FIRST_VALUE, my_function_) () {	// `my_function_00000001`

	return ZEN_COUNTER_AS_NUMBER(FIRST_VALUE);

}

#define SECOND_VALUE	ZEN_COUNTER_NEXT(FIRST_VALUE)
int ZEN_COUNTER_AS_IDENTIFIER(SECOND_VALUE, my_function_) () {	// `my_function_00000002`

	return ZEN_COUNTER_AS_NUMBER(SECOND_VALUE);

}

#define THIRD_VALUE	ZEN_COUNTER_NEXT(SECOND_VALUE)
int ZEN_COUNTER_AS_IDENTIFIER(THIRD_VALUE, my_function_) () {	// `my_function_00000003`

	return ZEN_COUNTER_AS_NUMBER(THIRD_VALUE);

}

int main() {

	printf("%d, %d, %d\n", my_function_00000001(), my_function_00000002(), my_function_00000003());

	return 0;

}
