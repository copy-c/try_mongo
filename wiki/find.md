# 计算符
## 集合运算符 
in/ all / nin 一个或多个值的列表

1. $IN
   - find({'details.color': {$in: ['blue', 'green']}}) 
   - 查找所有的蓝色或绿色
2. all 
   - 所有的参数 

## 布尔运算符

ne/ not/ or/ and/ nor/ exists

1. $OR
    - check mulit fields
    - ```
      find({'or': [ {'details.color': 'blue'},  {'name': 'jeff'} ]})
    - check every index of fields
2. exists 
    - 包含特定的字段

# 匹配文档
1. 匹配单一文档
   - find({"details.id": 432})
2. 匹配整个项目 -> 逐字节匹配
   - find({"details": {"id":432, "name": "2"}})

# 数组
1. arrayFilter
2. size -> 查询特定长度
3. slice -> 返回子集

# 查询选择

limit  
skip 
sort 

