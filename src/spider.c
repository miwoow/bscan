#include "spider.h"
#include "htmlp.h"
#include <curl/curl.h>
#include "urlp.h"

size_t resp_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
  FILE *fh = (FILE*)userdata;
  size_t num = 0;
  if (fh) {
    num = fwrite(ptr, size, nmemb, fh);
  }
  return num;
}

spider_t* spider_init(char *url)
{

  if (strlen(url) > MAX_URL_LEN) {
    return NULL;
  }
  spider_t *sp = (spider_t *)calloc(1, sizeof(spider_t));
  strncpy(sp->root_url, url, strlen(url));
  sp->root_url_buf = calloc(1, strlen(url) + 1);
  memcpy(sp->root_url_buf, url, strlen(url));
  urlp_parse(sp->root_url_buf, &(sp->root_url_obj));
  sp->urlq = url_queue_init();
  url_queue_add(sp->urlq, url);
  return sp;
}

void spider_start(spider_t *sp)
{
  CURL *eh;
  CURLcode res;
  FILE *fh;
  struct curl_slist *header_list = NULL;

  curl_global_init(CURL_GLOBAL_ALL);

  eh = curl_easy_init();
  if (eh) {
    curl_easy_setopt(eh, CURLOPT_WRITEFUNCTION, resp_write_callback);
    header_list = curl_slist_append(header_list, "User-Agent: Mozilla/5.0 (Linux; U;Android 2.3.5;zh-cn;P331Build/GRJ22) AppleWebKit/533.1 (KHTML, like Gecko) Version/4.0 Mobile Safari/533.1");
    curl_easy_setopt(eh, CURLOPT_HTTPHEADER, header_list);
    
    while(sp->urlq->spider_index < url_queue_elenum(sp->urlq) - 1) {
      curl_easy_setopt(eh, CURLOPT_URL, url_queue_get(sp->urlq, sp->urlq->spider_index));
      fh = fopen("/tmp/bscan.spider.page", "w+");
      curl_easy_setopt(eh, CURLOPT_WRITEDATA, fh);
      
      res = curl_easy_perform(eh);
      if (res != CURLE_OK) {
	fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));
      }
      fclose(fh);
      htmlp_get_link(sp, "/tmp/bscan.spider.page", "UTF-8");
      printf("queu num: %ld\n", url_queue_elenum(sp->urlq));
      sp->urlq->spider_index++;
    }

    curl_easy_cleanup(eh);
  }
  curl_global_cleanup();
}
