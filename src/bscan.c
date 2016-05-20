#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "spider.h"
#include "bscan.h"

int main(int argc, char *argv[]) 
{
  spider_t *sp;
  if (argc < 2) {
    printf("[USAGE]: %s http://www.baidu.com/\n", argv[0]);
    return 1;
  }
  sp = spider_init(argv[1]);
  spider_start(sp);
  printf("good\n");
  return 0;
}
