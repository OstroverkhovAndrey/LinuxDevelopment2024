
#include <check.h>
#include "vector.h"

#suite initialization
#tcase initialization
#test initialization
    /* initialization, buf_free() */
    float *a = 0;
    ck_assert_int_eq(buf_capacity(a), 0);
    ck_assert_int_eq(buf_size(a), 0);
    buf_push(a, 1.3f);
    ck_assert_int_eq(buf_size(a), 1);
    ck_assert_float_eq(a[0], (float)1.3f);
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0);
    ck_assert_ptr_nonnull(a);
    buf_free(a);
    ck_assert_ptr_null(a);

    /* Clearing an NULL pointer is a no-op */
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0);
    ck_assert_ptr_null(a);


#suite buf_push
#tcase buf_push
#test buf_push
    /* buf_push(), [] operator */
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    ck_assert_int_eq(buf_size(ai), 10000);
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    ck_assert_int_eq(match, 10000);
    buf_free(ai);

#suite buf_grow
#tcase buf_grow
#test buf_grow
    /* buf_grow(), buf_trunc() */
    long *ai = 0;
    buf_grow(ai, 1000);
    ck_assert_int_eq(buf_capacity(ai), 1000);
    ck_assert_int_eq(buf_size(ai), 0);
    buf_trunc(ai, 100);
    ck_assert_int_eq(buf_capacity(ai), 100);
    buf_free(ai);

#suite buf_pop
#tcase buf_pop
#test buf_pop
    /* buf_pop() */
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    ck_assert_int_eq(buf_size(a), 4);
    ck_assert_float_eq(buf_pop(a), (float)1.4f);
    buf_trunc(a, 3);
    ck_assert_int_eq(buf_size(a), 3);
    ck_assert_float_eq(buf_pop(a), (float)1.3f);
    ck_assert_float_eq(buf_pop(a), (float)1.2f);
    ck_assert_float_eq(buf_pop(a), (float)1.1f);
    ck_assert_int_eq(buf_size(a), 0);
    buf_free(a);

