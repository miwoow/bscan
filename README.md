# bscan
纯粹个人使用的web扫描器

# 依赖
1. libcurl
1. libpthread
1. libxml2

# 爬虫数据流
1. 从唯一URL列表获取一个URL。
1. 获取页面中的URL。
1. URL去重过滤后加入到唯一URL列表中。
1. goto 1

# 检测数据流
1. 从唯一URL列表获取一个URL。
1. 安全检测。
1. goto 1
