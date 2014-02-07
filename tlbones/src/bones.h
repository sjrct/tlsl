//
// tlbones/src/bones.h
//

#ifndef BONES_H
#define BONES_H

#include <tl/tl.h>

void tl_init_module(tl_var_t *);

tl_var_t * tlm_reqpath(tl_var_t *, tl_var_t *);
tl_var_t * tlm_require(tl_var_t *, tl_var_t *);
tl_var_t * tlm_typeof(tl_var_t *, tl_var_t *);
tl_var_t * tlm_exit(tl_var_t *, tl_var_t *);

#endif
