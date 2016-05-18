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

int urlp_parse(char *url, url_t *uobj)
{

}
