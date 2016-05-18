#ifndef _HTML_P_H
#define _HTML_P_H

#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include "urlqueue.h"

void htmlp_get_link(url_queue_t *uqueue, const char *fname, const char *encoding);



#endif
