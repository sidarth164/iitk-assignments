st = raw_input("Enter your input: ");
vowels="aeiouAEIOU"
i=0

while i<len(st):
    if(st[i] not in vowels and st[i].isalpha()):
        temp=st[i:]
        st=st[:i+1]+"o"
        st=st+temp
        i=i+3
    else: i=i+1

print st