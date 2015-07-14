#include <mex.h>

#ifdef WIN32
#  include <windows.h>
#else
#  include <unistd.h>
#endif

/* Missing function on Windows (it is available on GNU/Linux).
 * Copy/paste of a simple implementation found on the web.
 */
#ifdef WIN32
char *
strndup (const char *s,
	 size_t n)
{
	size_t len = strnlen (s, n);
	char *new = malloc (len + 1);

	if (new == NULL)
	{
		return NULL;
	}

	new[len] = '\0';
	return memcpy (new, s, len);
}
#endif

void
utils_portable_sleep (int milliseconds)
{
#ifdef WIN32
	Sleep (milliseconds);
#else
	usleep (milliseconds * 1000);
#endif
}

int
utils_get_socket_id (const mxArray *arg)
{
	int *arg_data;

	if (mxGetClassID (arg) != mxINT32_CLASS)
	{
		mexErrMsgTxt ("zmq_subscriber error: the subscriber_id has an invalid type, it should be int32.");
	}

	arg_data = (int *) mxGetData (arg);
	return *arg_data;
}