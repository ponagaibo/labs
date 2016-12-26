# -*- coding: utf-8 -*-
import re

read = open("tree.ged", "r", encoding="utf8")
write = open("whynot.txt", "w", encoding="utf8")
flag = False
id_names = {}
id_sex = {}

for line in read: 
    result = re.search(r'0 @I(\d+)@ INDI', line) # ищем ID человека
    if(result): # если нашли
        id_search = result.group(1) # записывем ИД как ключ
        continue
    result = re.search(r'1 NAME (\w+) /(\w*)/', line) # ищем его имя с девичьей фамилией
    if(result):
        if(not result.group(2)): # если нет девичьей
            id_names[id_search] = result.group(1) # сопоставляем ИД имя
            flag = True # нужно искать фамилию
        else:
            id_names[id_search] = result.group(1) + " " +  result.group(2) # иначе добавляем по ИД имя и фамилию
        continue
    if(flag): # если нужно искать фамилию
        result = re.search(r'2 _MARNM (\w+)', line) # ищем фамилию после замужества
        if(result): 
            flag = False # дальше искать не нужно
            id_names[id_search] = id_names[id_search] + " " + result.group(1) # добавляем к строке имени фамилию
    result = re.search(r'1 SEX ([M|F])', line) # ищем пол
    if(result):
        id_sex[id_search] = result.group(1).lower() # добавляем в словарь пола по ИД 
        continue
    result = re.search(r'1 HUSB @I(\d+)@', line)
    if(result):
        id_father = result.group(1) # находим ИД отца
        continue
    result = re.search(r'1 WIFE @I(\d+)@', line)
    if(result):
        id_mother = result.group(1) # находим ИД матери
        continue
    result = re.search(r'1 CHIL @I(\d+)@', line) 
    if(result):
        child = id_names[result.group(1)] # находим ИД ребенка
        write.write('parents("' + child + '", "' + id_names[id_father] + '", "' + id_names[id_mother] + '").\n')
for key in id_sex:
    write.write('sex("' + id_names[key] + '", ' + id_sex[key] + ').\n')
read.close()
write.close()