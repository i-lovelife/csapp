import random
with open('gen1.in', 'w') as fh1, open('gen2.in', 'w') as fh2:
    cas = 99
    fh1.write(str(cas)+'\n')
    fh2.write(str(cas)+'\n')
    for _ in range(cas):
        s1 = ''
        s2 = ''
        n = random.randint(1,10)
        for i in range(n):
            temp = random.randint(1, 4)
            if temp == 1:
                s1 += 'X'
                s2 += 'X'
            if temp == 2:
                s1 += 'O'
                s2 += 'O'
            if temp == 3:
                s1 += 'F'
                s2 += 'F'
            if temp == 4:
                s1 += '.'
                s2 += s2
        fh1.write(str(len(s1)) + '\n')
        fh1.write(s1 + '\n')
        fh2.write(str(len(s2)) + '\n')
        fh2.write(s2 + '\n')