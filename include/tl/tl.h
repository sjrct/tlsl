//
// include/tl/tl.h
//

#ifndef _TL_TL_H_
#define _TL_TL_H_

#include <tl/var.h>

void tl_init(void);
tl_var_t * tl_parse(char *);
tl_var_t * tl_eval(tl_var_t *, tl_var_t *);
int tl_require(const char *, tl_var_t *);

#endif
