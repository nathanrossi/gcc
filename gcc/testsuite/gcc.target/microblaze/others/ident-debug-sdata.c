/* { dg-do assemble } */
/* { dg-options "-g -O2" } */

/*
 * This test is based on a failure case that exposes an issue with switching
 * the section for the #ident directive.
 *
 * The emitted assembly references a label that is expected to be in the same
 * section (.text) but it is not due to being defined after the ident content
 * in a .sdata2 section.
 */

#ident "$Id$"

#include <string.h>

const char *test (const char *str)
{
	char *cp = strrchr (str, '/');
	return (NULL != cp) ? cp + 1 : str;
}

