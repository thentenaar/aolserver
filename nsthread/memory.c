/*
 * The contents of this file are subject to the AOLserver Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://aolserver.com/.
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is AOLserver Code and related documentation
 * distributed by AOL.
 * 
 * The Initial Developer of the Original Code is America Online,
 * Inc. Portions created by AOL are Copyright (C) 1999 America Online,
 * Inc. All Rights Reserved.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU General Public License (the "GPL"), in which case the
 * provisions of GPL are applicable instead of those above.  If you wish
 * to allow use of your version of this file only under the terms of the
 * GPL and not to allow others to use your version of this file under the
 * License, indicate your decision by deleting the provisions above and
 * replace them with the notice and other provisions required by the GPL.
 * If you do not delete the provisions above, a recipient may use your
 * version of this file under either the License or the GPL.
 */

/* 
 * memory.c --
 *
 *	Memory allocation routines.
 */


#include "thread.h"


/*
 *----------------------------------------------------------------------
 *
 * ns_realloc, ns_malloc, ns_calloc, ns_free, ns_strdup, ns_strcopy --
 *
 *	Memory allocation wrappers which either call the platform
 *	versions or the fast pool allocator for a per-thread pool.
 *
 * Results:
 *	As with system functions.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */

void *
ns_realloc(void *ptr, size_t size)
{
    return (ptr ? Tcl_Realloc(ptr, size) : Tcl_Alloc(size));
}

void *
ns_malloc(size_t size)
{
    return Tcl_Alloc(size);
}

void
ns_free(void *ptr)
{
    if (ptr != NULL) {
	Tcl_Free(ptr);
    }
}

void *
ns_calloc(size_t num, size_t esize)
{
    void *new;
    size_t size;

    size = num * esize;
    new = ns_malloc(size);
    memset(new, 0, size);

    return new;
}

char *
ns_strcopy(const char *old)
{
    return (old == NULL ? NULL : ns_strdup(old));
}

char *
ns_strdup(const char *old)
{
    char *new;

    new = ns_malloc(strlen(old) + 1);
    strcpy(new, old);

    return new;
}
