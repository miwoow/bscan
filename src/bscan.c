#include <stdio.h>
#include <stdlib.h>
#include <curl/multi.h>


#define MAX 10

int main(int argc, char *argv[]) 
{
  CURLM *cm;

  curl_global_init(CURL_GLOBAL_ALL);
  cm = curl_multi_init();

  curl_multi_setopt(cm, CURLMOPT_MAXCONNECTS, (long)MAX);

  curl_multi_cleanup(cm);
  curl_global_cleanup();

  printf("good\n");
  return 0;
}
