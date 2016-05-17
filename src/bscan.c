#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "spider.h"

int main(int argc, char *argv[]) 
{
  spider_t *sp = spider_init("http://m.xxshipin.com");
  spider_start(sp);
  printf("good\n");
  return 0;
}
