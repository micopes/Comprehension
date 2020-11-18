import graphviz as gv
import numpy as np


g1 = gv.Graph (format='PDF')
g1.attr(bgcolor='white', rankdir = 'LR')

station1_1 = ['Nopo', 'Beomeosa', 'Namsan', 'Dusil', 'Guseo', 'Jangjeon', 'Pusan National Univ', 'Oncheonjang', 'Myeongnyun',
              'Dongnae', 'Busan National Univ. Edu', 'Yeonsan', 'City Hall', 'Yangjeong','Bujeon', 'Seomyeon']

station1_2 = ['Beomnaegol', 'Beomil', 'Jwacheon', 'Busanjin', 'Choryang', 'Busan Station',
              'Jungang','Nampo', 'Jagalchi', 'Toseong', 'Dongdaesin', 'Seodaesin', 'Daeti', 'Goejeong', 'Saha',
              'Dangni', 'Hadan', 'Sinpyeong', 'Jangnim', 'sinjangnim', 'Natgae', 'Dadaepo Harbor', 'Dadaepo Beach']


num1_1station = len(station1_1)
station1_1.reverse()
num1_2station = len(station1_2)


for i in range(num1_1station) :
    g1.node(station1_1[i], shape = 'square', color = 'orange')

for i in range(num1_2station) :
    g1.node(station1_2[i], shape = 'square', color = 'orange')

for i in range(num1_1station-1) :
    g1.edge(station1_1[i], station1_1[i+1])

for i in range(num1_2station-1) :
    g1.edge(station1_2[i], station1_2[i+1])


g1.edge(station1_1[0], station1_2[0])

print((g1.source))
g1.view()