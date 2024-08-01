# calendar 

## pre 
1. global user table 
2. global account id table 

## index rule
1. 等值过滤排在多值过滤之前
2. 排序的在多值前
3. 多值过滤在最后

## calendar_list
1. calendar_list = ref_calendar_id

## calendar 
1. calendar = ref_acl_id -> create index for acl: calendar_id + scope.value
2. calendar_events = ref_event_id -> create index for events: 
   - index0: event_id
   - index1: i_cal_uid
   - index2: calendar_id(等值过滤) + event_type + ~~status +~~ start_ts(time_max) + end_ts(time_min) + updated (using attendees field(索引数组)?)
   - index3: ~~calendar_id + event_id~~ get then checking?

## acl 
1. account global -> domain 
2. user -> domain/ user/ group
eg: chao.zhao@zoom.us + 

## event
1. create event for attendees -> adding ref_event_id to calendar 
2. local change -> adding to attendees or local field (!!!how to create index, like local change start) 
3. delete -> tool to clean up status:cancelled

# scheduler 

## appointment

unique index: id  
index: slug  
Compound Index: attendees.id_start_ts + end_ts + status
