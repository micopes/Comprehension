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
             'Modeok', 'Deokpo', 'Sasang', 'Gamjeon', 'Jurye', 'Naengjeong', 'Gaegeum', 'Dongeui Univ.',
             'Gaya', 'Buam']

station2_2 = ['Jeonpo', 'Busan Int''l Finance Center Busan Bank', 'Munhyeon', 'Jigegol',
             'Motgol', 'Daeyeon', 'Kyungsung Univ. Pukyong Nat''l Univ.', 'Namcheon',
             'Geumnyeonsan', 'Gwangan', 'Suyeong']

station2_3 = ['Millak', 'Centum City', 'BEXCO']

station2_4 = ['Dongbaek', 'Haeundae', 'Jung-dong', 'Jangsan']

station3_1 = ['Daejeo', 'Gangseo-gu Ofc', 'Sports Park', 'Gupo', 'Deokcheon', 'Sukdeung'
             'Namsanjeong', 'Mandeok', 'Minam', 'Sajik', 'Sports Complex', 'Geoje', 'Yeonsan', 'Mulmangol',
              'Baesan', 'Mangmi', 'Suyeong']

station4_1 = ['Anpyeong', 'Gochon', 'Dong-Busan College', 'Yeongsan Univ', 'Seokdae',
             'Banyeo Agricultural Market', 'Geumsa', 'Seo-dong', 'Myeongjang', 'Chungnyeolsa',
             'Nangmin', 'Suan', 'Dongnae', 'Minam']

station5_1 = ['Gaya Univ.', 'Presbyterian Univ.', 'Yeonji Park', 'Gimhae National Museum',
             'Royal Tomb of King Suro', 'Bonghwang', 'Buwon', 'Gimhae CityHall', 'Inje Univ.'
             'Gimhae College', 'Jinae', 'Bulam', 'Daesa', 'Pyeonggang', 'Daejeo', 'Deokdu',
             'Gimhae Int''l Airport', 'Seobusan Yutongjigu', 'Goebeop Renecite', 'Sasang']



num1_1station = len(station1_1)
station1_1.reverse()
num1_2station = len(station1_2)

num2_1station = len(station2_1)
num2_2station = len(station2_2)
num2_3station = len(station2_3)
num2_4station = len(station2_4)

num3_1station = len(station3_1)

num4_1station = len(station4_1)

num5_1station = len(station5_1)

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

for i in range(num3_1station) :
    g1.node(station3_1[i], shape = 'square', color = 'brown')

for i in range(num4_1station) :
    g1.node(station4_1[i], shape = 'square', color = 'blue')

for i in range(num5_1station) :
    g1.node(station5_1[i], shape = 'square', color = 'purple')

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

for i in range(num3_1station-1) :
    g1.edge(station3_1[i], station3_1[i+1])

for i in range(num4_1station-1) :
    g1.edge(station4_1[i], station4_1[i+1])

for i in range(num5_1station-1) :
    g1.edge(station5_1[i], station5_1[i+1])

g1.node('Deokcheon', shape = 'square', color = 'red')
g1.node('Yeonsan', shape = 'square', color = 'red')
g1.node('Seomyeon', shape = 'square', color = 'red')
g1.node('Seomyeon', shape = 'square', color = 'red')
g1.node('Suyeong', shape = 'square', color = 'red')
g1.node('Minam', shape = 'square', color = 'red')
g1.node('Dongnae', shape = 'square', color = 'red')
g1.node('Daejeo', shape = 'square', color = 'red')
g1.node('Sasang', shape = 'square', color = 'red')

g1.edge(station1_1[0], station1_2[0])
g1.edge(station1_1[0], station2_1[num2_1station-1])

g1.edge(station1_1[0], station2_2[0])
g1.edge(station2_2[num2_2station-1], station2_3[0])
g1.edge(station2_3[num2_3station-1], station2_4[0])

print((g1.source))
g1.view()