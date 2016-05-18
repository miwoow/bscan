#ifndef _B_LIST_H_
#define _B_LIST_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct _blist_node_s
{
  char *data;
  size_t len;
  struct _blist_node_t *next;
}blist_node_t;

typedef struct _blist_s
{
  size_t index; // 当前空闲节点位置
  size_t num; // 当前空间能够容纳的节点数。
  uint8_t step; // 每次列表节点不足时，一次增长的节点数。 1-254之间。
  blist_node_t *nodes; // 所以节点
}blist_t;

blist_t *blist_init(uint8_t step);
void blist_append_data(blist_t *l, size_t len, char *data);
void blist_clean(blist_t *l);
size_t blist_elenum(blist_t *l);
blist_node_t* blist_get(blist_t *l, size_t ind);

#endif
