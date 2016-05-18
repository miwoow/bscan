#include "htmlp.h"
#include "urlp.h"

void htmlp_get_link(url_queue_t *uqueue, const char *fname, const char *encoding)
{
  htmlDocPtr docp;
  xmlXPathContextPtr context;
  int i=0;
  xmlXPathObjectPtr result;
  xmlNodeSetPtr nodeset;
  struct _xmlAttr *attrs;
  char pre_host[256] = {0};
  char *url;
  char complete_url[1024] = {0};

  urlp_get_pre_path(url_queue_get(uqueue, 0), pre_host);

  docp = htmlParseFile(fname, encoding);
  context = xmlXPathNewContext(docp);
  result = xmlXPathEvalExpression("//a", context);
  xmlXPathFreeContext(context);
  if(!xmlXPathNodeSetIsEmpty(result->nodesetval)) {
    nodeset = result->nodesetval;
    for(i=0; i < nodeset->nodeNr; i++) {
      attrs = nodeset->nodeTab[i]->properties;
      while(attrs) {
	if (strncasecmp(attrs->name, "href", 4) == 0) {
	  url = attrs->children->content;
	  if (strstr(url, "http") != url) {
	    memset(complete_url, 0, 1024);
	    strncat(complete_url, pre_host, 1023);
	    strncat(complete_url, url, 1023);
	    if (strstr(complete_url, pre_host) == complete_url) {
	      url_queue_uniq_add(uqueue, complete_url);
	    }
	  } else {
	    if (strstr(complete_url, pre_host) == complete_url) {
	      url_queue_uniq_add(uqueue, url);
	    }
	  }
	  //printf("%s\n", attrs->children->content);
	}
	attrs = attrs->next;
      }
    }
  }
  xmlXPathFreeObject (result);
  xmlCleanupParser();
}
