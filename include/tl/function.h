//
// include/tl/function.h
//

#ifndef _TL_FUNCTION_H_
#define _TL_FUNCTION_H_

typedef struct tl_var tl_var_t;
typedef tl_var_t * (* tl_cfunction_t)(tl_var_t *, tl_var_t *);

typedef struct tl_function {
	int isuser;

	union {
		struct {
			tl_var_t * code;
			tl_var_t * argls;
			tl_var_t * env;
		} user;

		tl_cfunction_t builtin;
	} u;
} tl_function_t;

tl_var_t * tl_call(tl_function_t *, tl_var_t *, tl_var_t *);

#endif
