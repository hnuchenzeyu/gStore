f = open('three.nt','w',encoding='utf-8')

for i in range(1,1001):
   f.write('<v'+str(i)+'>   <a>   <v>.\n')

for i in range(1001,2001):
   f.write('<v>   <a>   <v'+str(i)+'>.\n')

f.write('<v2000>   <a>   <v\'>.')

f.close()
