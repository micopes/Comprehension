import graphviz as gv
import numpy as np


g1 = gv.Graph (format='PDF')
g1.attr(bgcolor='white', rankdir = 'LR')

station1_1 = ['Nopo', 'Beomeosa', 'Namsan', 'Dusil', 'Guseo', 'Jangjeon', 'Pusan National Univ', 'Oncheonjang', 'Myeongnyun',
              'Dongnae', 'Busan National Univ. Edu', 'Yeonsan', 'City Hall', 'Yangjeong','Bujeon', 'Seomyeon']

station1_2 = ['Beomnaegol', 'Beomil', 'Jwacheon', 'Busanjin', 'Choryang', 'Busan Station',
              'Jungang','Nampo', 'Jagalchi', 'Toseong', 'Dongdaesin', 'Seodaesin', 'Daeti', 'Goejeong', 'Saha',
              'Dangni', 'Hadan', 'Sinpyeong', 'Jangnim', 'sinjangnim', 'Natgae', 'Dadaepo Harbor', 'Dadaepo Beach']

station2_1 = ['Yangsan', 'Namyangsan', 'Pusan National Univ. Yangsan Campus', 'Jeungsan',
             'Hopo', 'Geumgok', 'Dongwon', 'Yulli', 'Hwamyeong', 'Sujeong', 'Deokcheon', 'Gumyeong', 'Genam', 'Mora',
             'Modeok', 'Deokpo','Sasang', 'Gamjeon', 'Jurye', 'Naengjeong', 'Gaegeum', 'Dongeui Univ.',
             'Gaya', 'Buam']

station2_2 = ['Jeonpo', 'Busan Int''l Finance Center Busan Bank', 'Munhyeon', 'Jigegol',
             'Motgol', 'Daeyeon', 'Kyungsung Univ. Pukyong Nat''l Univ.', 'Namcheon',
             'Geumnyeonsan', 'Gwangan', 'Suyeong']

station2_3 = ['Millak', 'Centum City', 'BEXCO']

station2_4 = ['Dongbaek', 'Haeundae', 'Jung-dong', 'Jangsan']


num1_1station = len(station1_1)
station1_1.reverse()
num1_2station = len(station1_2)

num2_1station = len(station2_1)
num2_2station = len(station2_2)
num2_3station = len(station2_3)
num2_4station = len(station2_4)


for i in range(num1_1station) :
    g1.node(station1_1[i], shape = 'square', color = 'orange')

for i in range(num1_2station) :
    g1.node(station1_2[i], shape = 'square', color = 'orange')

for i in range(num2_1station) :
    g1.node(station2_1[i], shape = 'square', color = 'green')

for i in range(num2_2station) :
    g1.node(station2_2[i], shape = 'square', color = 'green')

for i in range(num2_3station) :
    g1.node(station2_3[i], shape = 'square', color = 'green')

for i in range(num2_4station) :
    g1.node(station2_4[i], shape = 'square', color = 'green')

for i in range(num1_1station-1) :
    g1.edge(station1_1[i], station1_1[i+1])

for i in range(num1_2station-1) :
    g1.edge(station1_2[i], station1_2[i+1])

for i in range(num2_1station-1) :
    g1.edge(station2_1[i], station2_1[i+1])

for i in range(num2_2station-1) :
    g1.edge(station2_2[i], station2_2[i+1])

for i in range(num2_3station-1) :
    g1.edge(station2_3[i], station2_3[i+1])

for i in range(num2_4station-1) :
    g1.edge(station2_4[i], station2_4[i+1])

g1.node(station1_1[0], shape = 'square', color = 'red')

g1.edge(station1_1[0], station1_2[0])
g1.edge(station1_1[0], station2_1[num2_1station-1])

g1.edge(station1_1[0], station2_2[0])
g1.edge(station2_2[num2_2station-1], station2_3[0])
g1.edge(station2_3[num2_3station-1], station2_4[0])

print((g1.source))
g1.view()