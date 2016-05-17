#include "htmlp.h"

static htmlDocPtr docp;

void htmlp_init_with_file(const char *fname, const char *encoding)
{
  docp = htmlParseFile(fname, encoding);
  xmlXPathContextPtr context;
  int i=0;
  context = xmlXPathNewContext(docp);
  xmlXPathObjectPtr result;
  result = xmlXPathEvalExpression("//a", context);
  xmlXPathFreeContext(context);
  if(!xmlXPathNodeSetIsEmpty(result->nodesetval)) {
    xmlNodeSetPtr nodeset;
    struct _xmlAttr *attrs;
    nodeset = result->nodesetval;
    for(i=0; i < nodeset->nodeNr; i++) {
      //printf("%s, ", nodeset->nodeTab[i]->name);
      attrs = nodeset->nodeTab[i]->properties;
      while(attrs) {
	if (strncasecmp(attrs->name, "href", 4) == 0) {
	  printf("%s\n", attrs->children->content);
	}
	/*
	printf("%s=%s\t", attrs->name,
	       attrs->children->content);
	*/
	attrs = attrs->next;
      }
      printf("\n");
    }
  }
  xmlXPathFreeObject (result);
  xmlCleanupParser();
}
