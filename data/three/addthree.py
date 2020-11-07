f = open('three.nt','w',encoding='utf-8')

for i in range(1,10001):
   f.write('<v'+str(i)+'>   <a>   <v>.\n')

for i in range(10001,20001):
   f.write('<v>   <a>   <v'+str(i)+'>.\n')

f.write('<v20000>   <a>   <v\'>.')

f.close()
