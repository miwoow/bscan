cmake_minimum_required(VERSION 2.8)
#progect name
PROJECT(bscan)
#head file path
INCLUDE_DIRECTORIES(
  ./src/include/
  /usr/include/libxml2/
)

#source directory

AUX_SOURCE_DIRECTORY(src DIR_SRCS)
#set environment variable



ADD_EXECUTABLE(./bin/bscan ${DIR_SRCS})
TARGET_LINK_LIBRARIES(./bin/bscan curl pthread xml2)
