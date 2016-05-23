#include "htmlp.h"
#include "urlp.h"

void htmlp_get_link(spider_t *sp, const char *fname, const char *encoding)
{
  htmlDocPtr docp;
  xmlXPathContextPtr context;
  int i=0, j=0;
  xmlXPathObjectPtr result;
  xmlNodeSetPtr nodeset;
  struct _xmlAttr *attrs;
  char *url;
  char complete_url[1024] = {0};
  url_queue_t *uqueue = sp->urlq;
  char *pos = NULL;
  char *cur_chr = NULL;

  char *url_tmp_buf = NULL;

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
	  url_tmp_buf = calloc(1, strlen(url) + 1);
	  struct struct_parts uobj;
	  memcpy(url_tmp_buf, url, strlen(url));
	  printf("===================\n");
	  printf("url:%s\n", url);
	  urlp_parse(url_tmp_buf, &uobj);
	  printf("access: %s\n", uobj.access);
	  printf("host:%s\n", uobj.host);
	  printf("absolute:%s\n", uobj.absolute);
	  printf("relative:%s\n", uobj.relative);
	  printf("search:%s\n", uobj.search);
	  printf("anchor:%s\n", uobj.anchor);
	  printf("===================\n");
	  if (uobj.access != NULL) {
	    if (strcasecmp(uobj.access, "javascript") != 0) {
	      if (uobj.host != NULL) {
		if (memcmp(uobj.host, (sp->root_url_obj).host, strlen(uobj.host)) == 0) {
		  url_queue_uniq_add(uqueue, url);
		}
	      } else {
		url_queue_uniq_add(uqueue, url);
	      }
	    }
	  } else {
	    if (uobj.access == NULL)
	      uobj.access = (sp->root_url_obj).access;
	    if (uobj.host == NULL)
	      uobj.host = (sp->root_url_obj).host;
	    if (uobj.relative || uobj.absolute) {
	      memset(complete_url, 0, 1024);
	      if (uobj.relative) {
		pos = strrchr(sp->cur_url, '/');
		if (*(pos-1) == '/' && *(pos-2) == ':') {
		  snprintf(complete_url, 1023, "%s://%s",
			   uobj.access,
			   uobj.host);
		  complete_url[strlen(complete_url)] = '/';
		  strncat(complete_url, uobj.relative, 1023);
		} else {
		  for (j=0, cur_chr = sp->cur_url; cur_chr < pos + 1; cur_chr++, j++) {
		    complete_url[j] = *cur_chr;
		  }
		  strncat(complete_url, uobj.relative, 1023);
		}
	      }
	      
	      if (uobj.absolute) {
		snprintf(complete_url, 1023, "%s://%s",
			 uobj.access,
			 uobj.host);
		complete_url[strlen(complete_url)] = '/';
		strncat(complete_url, uobj.absolute, 1023);
	      }
	    } else {
	      memset(complete_url, 0, 1024);
	      snprintf(complete_url, 1023, "%s://%s",
		       uobj.access,
		       uobj.host);
	      complete_url[strlen(complete_url)] = '/'; 
	    }
	    if (uobj.search) {
	      complete_url[strlen(complete_url)] = '?';
	      strncat(complete_url, uobj.search, 1023);
	    }
	    if (uobj.anchor) {
	      complete_url[strlen(complete_url)] = '#';
	      strncat(complete_url, uobj.anchor, 1023);
	    }
	    url_queue_uniq_add(uqueue, complete_url);
	  }
	  
	  free(url_tmp_buf);
	  break;
	}
	attrs = attrs->next;
      }
    }
  }
  xmlXPathFreeObject (result);
  xmlCleanupParser();
}
