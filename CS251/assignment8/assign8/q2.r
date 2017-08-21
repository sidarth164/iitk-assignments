count_11=0
count_12=0
count_13=0
count_14=0

count_21=0
count_22=0
count_23=0
count_24=0

for(i in 1:10)
{
  v1 = paste("uniform",as.name(i),sep = "_")
  v2 = paste("normal",as.name(i),sep = "_")
  data_1 <- scan(v1)
  data_2 <- scan(v2)
  i1 = 1
  i2 = 1
  i3 = 1
  i4 = 1

  v11 = 0
  v12 = 0
  v13 = 0
  v14 = 0
  v21 = 0
  v22 = 0
  v23 = 0
  v24 = 0
  for(j in 1:100)
  {
    if (data_1[j]>=0 && data_1[j]<0.25){
      v11[i1] <- data_1[j]
      i1 = i1 + 1
    }
    else if(data_1[j]<0.5){
      v12[i2] <- data_1[j]
      i2 = i2 + 1
    }
    else if(data_1[j]<0.75){
      v13[i3] <- data_1[j]
      i3 = i3 + 1
    }
    else if(data_1[j]<=1.0){
      v14[i4] <- data_1[j]
      i4 = i4 + 1
    }
  }
  count_11[i] = length(v11)
  count_12[i] = length(v12) 
  count_13[i] = length(v13)
  count_14[i] = length(v14)

  i1 = 1
  i2 = 1
  i3 = 1
  i4 = 1

  for(j in 1:100)
  {
    if (data_2[j]>=0 && data_2[j]<0.25){
      v21[i1] <- data_2[j]
      i1 = i1 + 1
    }
    else if(data_2[j]<0.5){
      v22[i2] <- data_2[j]
      i2 = i2 + 1
    }
    else if(data_2[j]<0.75){
      v23[i3] <- data_2[j]
      i3 = i3 + 1
    }
    else if(data_2[j]<=1.0){
      v24[i4] <- data_2[j]
      i4 = i4 + 1
    }
  }
  count_21[i] = length(v21)
  count_22[i] = length(v22) 
  count_23[i] = length(v23)
  count_24[i] = length(v24)

}

min_1 = c(min(count_11),min(count_12),min(count_13),min(count_14));
max_1 = c(max(count_11),max(count_12),max(count_13),max(count_14));
mean_1 = c(mean(count_11),mean(count_12),mean(count_13),mean(count_14));

min_2 = c(min(count_21),min(count_22),min(count_23),min(count_24));
max_2 = c(max(count_21),max(count_22),max(count_23),max(count_24));
mean_2 = c(mean(count_21),mean(count_22),mean(count_23),mean(count_24));

df_1 = data.frame(min_1,max_1,mean_1);
df_2 = data.frame(min_2,max_2,mean_2);
row.names(df_1) <- c("0-0.25","0.25-.5","0.5-.75","0.75-1")
row.names(df_2) <- c("0-0.25","0.25-.5","0.5-.75","0.75-1")

write.table(df_1, file = "uniformq2", col.names = FALSE)
write.table(df_2, file = "normalq2", col.names = FALSE)