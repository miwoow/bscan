#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <curl/curl.h>
#include "htmlp.h"

size_t resp_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) 
{
  FILE *fh = (FILE*)userdata;
  size_t num = 0;
  if (fh) {
    num = fwrite(ptr, size, nmemb, fh);
  }
  return num;
}


int main(int argc, char *argv[]) 
{

  CURL *eh;
  CURLcode res;
  FILE *fh;
  struct curl_slist *header_list = NULL;

  curl_global_init(CURL_GLOBAL_ALL);
  
  eh = curl_easy_init();
  if (eh) {
    curl_easy_setopt(eh, CURLOPT_URL, "http://m.xxshipin.com/");
    fh = fopen("www.baidu.com", "w+");
    header_list = curl_slist_append(header_list, "User-Agent: Mozilla/5.0 (Linux; U;Android 2.3.5;zh-cn;P331Build/GRJ22) AppleWebKit/533.1 (KHTML, like Gecko) Version/4.0 Mobile Safari/533.1");
    curl_easy_setopt(eh, CURLOPT_WRITEFUNCTION, resp_write_callback);
    curl_easy_setopt(eh, CURLOPT_WRITEDATA, fh);
    curl_easy_setopt(eh, CURLOPT_HTTPHEADER, header_list);
    
    res = curl_easy_perform(eh);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
	      curl_easy_strerror(res));
    }
    fclose(fh);
    curl_easy_cleanup(eh);

    htmlp_init_with_file("www.baidu.com", "UTF-8");
  }
  curl_global_cleanup();
  printf("good\n");
  return 0;
}
