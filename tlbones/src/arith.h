//
// tlbones/src/arith.h
//

#ifndef ARITH_H
#define ARITH_H

#include <tl/var.h>

tl_var_t * tlm_add(tl_var_t *, tl_var_t *);
tl_var_t * tlm_sub(tl_var_t *, tl_var_t *);
tl_var_t * tlm_mul(tl_var_t *, tl_var_t *);
tl_var_t * tlm_div(tl_var_t *, tl_var_t *);

#endif
