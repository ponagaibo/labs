# -*- coding: utf-8 -*-
import re

read = open("data.ged", "r", encoding="utf8")
write = open("new.txt", "w", encoding="utf8")
flag = 0
id_names = {}
id_sex = {}
child_and_parents = {}
id_search = 0
id_father = 0
id_mother = 0

for line in read:
    if(flag == 0):
        result = re.search(r'0 @I(\d+)@ INDI', line)
        if(result):
            flag = 1
            id_search = result.group(1)
        else:
            result = re.search(r'0 @F(\d+)@ FAM', line)
            if(result):
                flag = 4
    elif(flag == 1):
        result = re.search(r'1 NAME (\w+) /(\w*)/', line)
        if(result):
            if(not result.group(2)):
                flag = 2
                id_names[id_search] = result.group(1)
            else:
                flag = 3
                id_names[id_search] = result.group(1) + " " +  result.group(2)
    elif(flag == 2):
        result = re.search(r'2 _MARNM (\w+)', line)
        if(result):
            flag = 3
            id_names[id_search] = id_names[id_search] + " " + result.group(1)
    elif(flag == 3):
        result = re.search(r'1 SEX ([M|F])', line)
        if(result):
            flag = 0
            id_sex[id_search] = result.group(1).lower()
    elif(flag == 4):
        result = re.search(r'1 HUSB @I(\d+)@', line)
        if(result):
            flag = 5
            id_father = result.group(1)
    elif(flag == 5):
        result = re.search(r'1 WIFE @I(\d+)@', line)
        if(result):
            flag = 6
            id_mother = result.group(1)
    else:
        result = re.search(r'1 CHIL @I(\d+)@', line)
        if(result):
            child = id_names[result.group(1)]
            child_and_parents[child] = [id_names[id_father]]
            child_and_parents[child].append(id_names[id_mother])
        else:
            flag = 0
for key in child_and_parents:
    write.write('parents("' + key + '", "' + child_and_parents[key][0] + '", "' + child_and_parents[key][1] + '").\n')
for key in id_sex:
    write.write('sex("' + id_names[key] + '", ' + id_sex[key] + ').\n')
read.close()
write.close()