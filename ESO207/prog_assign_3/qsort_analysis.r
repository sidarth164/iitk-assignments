a=read.table("quicktime6.csv")
mean= mean(a[,1]);

e= mean * 5 / 100;
count = 0
for(i in 1:1000){
	if(a[i,1]-mean > e)
		count = count +1
}

print(count)
cat("\n")

e= mean * 10 / 100;
count = 0
for(i in 1:1000){
	if(a[i,1]-mean > e)
		count = count +1
}

print(count)
cat("\n")

e= mean * 20 / 100;
count = 0
for(i in 1:1000){
	if(a[i,1]-mean > e)
		count = count +1
}

print(count)
cat("\n")

e= mean * 30 / 100;
count = 0
for(i in 1:1000){
	if(a[i,1]-mean > e)
		count = count +1
}

print(count)
cat("\n")

e= mean * 40 / 100;
count = 0
for(i in 1:1000){
	if(a[i,1]-mean > e)
		count = count +1
}

print(count)
cat("\n")

e= mean * 50 / 100;
count = 0
for(i in 1:1000){
	if(a[i,1]-mean > e)
		count = count +1
}

print(count)
cat("\n")

e= mean;
count = 0
for(i in 1:1000){
	if(a[i,1]-mean > e)
		count = count +1
}

print(count)
cat("\n")