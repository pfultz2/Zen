

// #include <cstdio>
#include <zlang.h>
#include <zen/function.h>

// #include <zen/function/is_callable.h>
// #include <zen/function/fix.h>
// #include <zen/function/pipable.h>
// #include <zen/function/static.h>
// #include <zen/function/defer.h>
// #include <zen/function/builder.h>

#include <zen/test.h>

// #include <zlang.h>

// $(function(sum)(x, y)(x + y));

ZEN_FUNCTION_OBJECT((sum)(x, y)(x + y));

int main()
{
    int i = sum(5, 3);
    zen::test::run();
    printf("Tests run\n");
}
