#include "dieharder.h"
void _dieharder_call(int test_num, int gen_num,int ts,int ps ) {
    _dieharder(test_num,gen_num,ts,ps);
}
void destroy_die_teste(Dtest * dtst,Test ** tst){
    destroy_test(dtst,tst);
}