f = open('three.nt','w',encoding='utf-8')

for i in range(1,5001):
   f.write('<v'+str(i)+'>   <a>   <v>.\n')

for i in range(5001,10001):
   f.write('<v>   <a>   <v'+str(i)+'>.\n')

f.write('<v10000>   <a>   <v\'>.')

f.close()
