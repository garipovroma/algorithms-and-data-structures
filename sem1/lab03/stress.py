import random, os

def gen():
	n = random.randint(1, 500)
	a = []
	for i in range(n):
		a.append(random.randint(1, n))
	random.shuffle(a)
	s = str(n) + "\n"
	for i in a:
		s = s + str(i) + " "
	return s

for i in range(100000):
	f = open("input.txt", "w")
	test = gen()
	f.write(test)
	f.close()
	v1 = os.popen("./d < TEST.txt").read()
	v2 = os.popen("./main < TEST.txt").read()
	if (v1 != v2) :
		print("WA" + str(i + 1) + ", expected : |||" + str(v2) + "||| , but found : " + str(v1))
		print(test)
		break
	else:
		print(str(i) + " OK")