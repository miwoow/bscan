#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <curl/curl.h>


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
  curl_global_init(CURL_GLOBAL_ALL);
  
  eh = curl_easy_init();
  if (eh) {
    curl_easy_setopt(eh, CURLOPT_URL, "http://www.baidu.com/");
    fh = fopen("www.baidu.com", "w+");
    curl_easy_setopt(eh, CURLOPT_WRITEFUNCTION, resp_write_callback);
    curl_easy_setopt(eh, CURLOPT_WRITEDATA, fh);
    res = curl_easy_perform(eh);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
	      curl_easy_strerror(res));
    }
    fclose(fh);
    curl_easy_cleanup(eh);
  }
  curl_global_cleanup();
  printf("good\n");
  return 0;
}
