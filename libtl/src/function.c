//
// libtl/src/function.c
//

#include <assert.h>
#include <tl/var.h>

tl_var_t * tl_call(tl_function_t * func, tl_var_t * args, tl_var_t * env)
{
	assert(!func->isuser);
	return func->u.builtin(args, env);
}
