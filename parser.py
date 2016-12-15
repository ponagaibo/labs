# -*- coding: utf-8 -*-
import re

read = open("tree.ged", "r", encoding="utf8")
write = open("predicates3.txt", "w", encoding="utf8")
flag = False
id_names = {} #dictionary of names
id_sex = {} #dictionary of sex
id_search = 0
id_father = 0
id_mother = 0

for line in read:
    result = re.search(r'0 @I(\d+)@ INDI', line)
    if(result):
        id_search = result.group(1)
        continue
    result = re.search(r'1 NAME (\w+) /(\w*)/', line)
    if(result):
        if(not result.group(2)):
            id_names[id_search] = result.group(1)
            flag = True
        else:
            id_names[id_search] = result.group(1) + " " +  result.group(2)
        continue
    if(flag):
        result = re.search(r'2 _MARNM (\w+)', line)
        if(result):
            flag = False
            id_names[id_search] = id_names[id_search] + " " + result.group(1)
    result = re.search(r'1 SEX ([M|F])', line)
    if(result):
        id_sex[id_search] = result.group(1).lower()
        continue
    result = re.search(r'1 HUSB @I(\d+)@', line)
    if(result):
        id_father = result.group(1)
        continue
    result = re.search(r'1 WIFE @I(\d+)@', line)
    if(result):
        id_mother = result.group(1)
        continue
    result = re.search(r'1 CHIL @I(\d+)@', line)
    if(result):
        child = id_names[result.group(1)]
        write.write('parents("' + child + '", "' + id_names[id_father] + '", "' + id_names[id_mother] + '").\n')
for key in id_sex:
    write.write('sex("' + id_names[key] + '", ' + id_sex[key] + ').\n')
read.close()
write.close()