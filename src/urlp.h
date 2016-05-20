#ifndef _URLP_H_
#define _URLP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "bscan.h"

int urlp_parse(char *url, struct struct_parts *uobj);
int urlp_get_pre_path(char *url, char *host);
int urlp_is_similar(char *url1, char *url2);

#endif
