# schema
1. 1-1 -> embedded
2. 1-N -> embeded, using array
3. N-N -> reference, using

# tips
1. 缓存某些field 
   - 比如array的大小 "votes":[], "votes_helper":10
   - 缓存其他object的字段 "user_name":, "user_id": 
- 