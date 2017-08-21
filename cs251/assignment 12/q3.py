vowels="aeiouAEIOU"

a = raw_input("Number of times consonant is repeated : ");

if a.isdigit()==False:
	print "Please enter a valid number"
	exit()
else: a=int(a)

b = raw_input("Number of times vowel is repeated : ");

if b.isdigit()==False:
	print "Please enter a valid number"
	exit()
else: b=int(b)

v = raw_input("Vowel to be inserted : ");

if v[0] not in vowels or len(v)!=1:
	print "Please enter only one vowel!!"
	exit()

st = raw_input("Enter your input : ");

i=0;
while i<len(st):
	ka=0
	kb=0
	if(st[i] not in vowels and st[i].isalpha()):
		temp = st[i+1:]
		temp2 = st[:i]
		pattern = st[i]
		while kb<b:
			pattern = pattern + v
			kb = kb + 1
		while ka<a-1:
			temp2 = temp2 + pattern
			ka = ka +1
		temp2 = temp2 + st[i]
		st = temp2 + temp
		i = i + a * b + a - b
		
	else: i=i+1

print st