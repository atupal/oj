
from random import randint

WHO = ['A', 'B', 'C', 'D', 'E']
BE = ['divine', 'human', 'evil', 'lying']
W = ['A', 'B', 'C', 'D', 'E']
IS = ['is', 'is not']
D = ['day','night']

for _ in xrange(10):
    n = randint(1, 20)
    print n
    for i in xrange(n):
        who = randint(0, 4)
        print WHO[who] + ": " + W[randint(0, 4)] , IS[randint(0,1)], BE[randint(0, 3)]+"."
        #if randint(1,8) < 2:
            #print "It is", D[randint(0,1)]  + "."
print 0
