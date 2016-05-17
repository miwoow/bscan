#include "htmlp.h"

static htmlDocPtr docp;

void htmlp_init_with_file(const char *fname, const char *encoding)
{

  xmlXPathContextPtr context;
  int i=0;
  xmlXPathObjectPtr result;
  xmlNodeSetPtr nodeset;
  struct _xmlAttr *attrs;

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
	  printf("%s\n", attrs->children->content);
	}
	attrs = attrs->next;
      }
      printf("\n");
    }
  }
  xmlXPathFreeObject (result);
  xmlCleanupParser();
}
