a=read.table("quickcomp2.csv")
b=read.table("mergecomp2.csv")

x=0
for(i in 1:1000){
	if(b[i,1]<a[i,1])
		x=x+1
}
print(x)
cat("\n")

a=read.table("quickcomp3.csv")
b=read.table("mergecomp3.csv")

x=0
for(i in 1:1000){
	if(b[i,1]<a[i,1])
		x=x+1
}
print(x)
cat("\n")

a=read.table("quickcomp4.csv")
b=read.table("mergecomp4.csv")

x=0
for(i in 1:1000){
	if(b[i,1]<a[i,1])
		x=x+1
}
print(x)
cat("\n")

a=read.table("quickcomp5.csv")
b=read.table("mergecomp5.csv")

x=0
for(i in 1:1000){
	if(b[i,1]<a[i,1])
		x=x+1
}
print(x)
cat("\n")

a=read.table("quickcomp6.csv")
b=read.table("mergecomp6.csv")

x=0
for(i in 1:1000){
	if(b[i,1]<a[i,1])
		x=x+1
}
print(x)
cat("\n")