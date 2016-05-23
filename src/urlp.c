#include "urlp.h"

int urlp_get_pre_path(char *url, char *host)
{
  if (host == NULL) {
    fprintf(stderr, "host must be an zeroed buffer.\n");
    return 2;
  }
  int i = 0, j = 0, k = 0;
  if (url[0] == '/') {
    // no host
    return 1;
  }
  if (url[0] != 'h') {
    j = 1;
  } else {
    j = 3;
  }
  for (i=0; i<strlen(url); i++) {
    if (url[i] == '/') 
      k++;
    if (k == j) {
      break;
    }
    host[i] = url[i];
  }
  host[i] = '/';
  return 0;
}

int urlp_is_similar(char *url1, char *url2)
{
  int len;
  len = strlen(url1);
  if (strlen(url2) != len)
    return 0;
  if (memcmp(url1, url2, len) == 0) {
    return 1;
  }
  return 0;
}

static void scan(char *name,
                 struct struct_parts *parts)
{
  char *after_access;
  char *p;

  parts->access = NULL;
  parts->host = NULL;
  parts->absolute = NULL;
  parts->relative = NULL;
  parts->search = NULL;       /* normally not used - kw */
  parts->anchor = NULL;

  /*
   * Scan left-to-right for a scheme (access).
   */
  after_access = name;
  for (p = name; *p; p++) {
    if (*p == ':') {
      *p = '\0';
      parts->access = name;       /* Access name has been specified */
      after_access = (p + 1);
      break;
    }
    if (*p == '/' || *p == '#' || *p == ';' || *p == '?')
      break;
  }

  /*
   * Scan left-to-right for a fragment (anchor).
   */
  for (p = after_access; *p; p++) {
    if (*p == '#') {
      parts->anchor = (p + 1);
      *p = '\0';          /* terminate the rest */
      break;              /* leave things after first # alone - kw */
    }
  }
  /*
   * Scan left-to-right for a host or absolute path.
   */
  p = after_access;
  if (*p == '/') {
    if (p[1] == '/') {
      parts->host = (p + 2);      /* host has been specified    */
      *p = '\0';          /* Terminate access           */
      p = strchr(parts->host, '/');       /* look for end of host name if any */
      if (p != NULL) {
	*p = '\0';      /* Terminate host */
	parts->absolute = (p + 1);      /* Root has been found */
      } else {
	p = strchr(parts->host, '?');
	if (p != NULL) {
	  *p = '\0';  /* Terminate host */
	  parts->search = (p + 1);
	}
      }
    } else {
      parts->absolute = (p + 1);  /* Root found but no host */
    }
  } else {
    parts->relative = (*after_access) ?
      after_access : NULL;        /* NULL for "" */
  }

  /*
   * Check schemes that commonly have unescaped hashes.
   */
  if (parts->access && parts->anchor &&
      /* optimize */ strchr("lnsdLNSD", *parts->access) != NULL) {
    if ((!parts->host && strcasecmp(parts->access, "lynxcgi")) ||
	!strcasecmp(parts->access, "nntp") ||
	!strcasecmp(parts->access, "snews") ||
	!strcasecmp(parts->access, "news") ||
	!strcasecmp(parts->access, "data")) {
      /*
       * Access specified but no host and not a lynxcgi URL, so the
       * anchor may not really be one, e.g., news:j462#36487@foo.bar, or
       * it's an nntp or snews URL, or news URL with a host.  Restore the
       * '#' in the address.
       */
      /* but only if we have found a path component of which this will
       * become part. - kw  */
      if (parts->relative || parts->absolute) {
	*(parts->anchor - 1) = '#';
	parts->anchor = NULL;
      }
    }
  }
}

int urlp_parse(char *url, struct struct_parts *uobj)
{
  scan(url, uobj);
  return 0;
}

/*
 * @inout abs_url string. A url starts with httpx://...
 *                        Out with no dot in url.
 *
 */
int urlp_strip_dot(char *abs_url)
{
  char *pos, *prepos = NULL;
START:
  pos = abs_url;
  for (pos; *pos != '\0'; pos++) {
    if (*pos == '/' && *(pos + 1) == '/' && *(pos - 1) == ':') {
      break;
    }
  }
  pos+=2;
  for(; *pos != '\0'; pos++) {
    if (*pos == '/') {
      if (*(pos + 1) == '.') {
	switch(*(pos + 2)) {
	case '/':
	  while(*(pos+3) != '\0') {
	    *(pos + 1) == *(pos + 3);
	    pos++;
	  }
	  *(pos + 2) = *(pos + 3) = '\0';
	  goto START;
	case '.':
	  if (*(pos + 3) == '/') {
	    while(*(pos + 4) != '\0') {
	      *(pos + 1) = *(pos + 4);
	      pos++;
	    }
	    *(pos + 2) = *(pos + 3) = *(pos + 4) = '\0';
	  } else {
	    continue;
	  }
	  goto START;
	default:
	  continue;
	}
      }
    }
  }
  return 0;
}
