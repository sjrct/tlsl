//
// libtl/src/require.c
//

#include <dlfcn.h>
#include <assert.h>
#include <tl/tl.h>

int tl_require(const char * fn, tl_var_t * env)
{
	void * hndl;
	void (* init_mod)(tl_var_t *);

	hndl = dlopen(fn, RTLD_LAZY);
	if (hndl == NULL) return 0;

	init_mod = dlsym(hndl, "tl_init_module");
	if (init_mod == NULL) return 0;

	init_mod(env);
	return 1;
}
