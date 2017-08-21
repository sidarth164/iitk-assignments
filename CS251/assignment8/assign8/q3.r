count_11=0
count_12=0
count_13=0

count_21=0
count_22=0
count_23=0

count_31=0
count_32=0
count_33=0

count_41=0
count_42=0
count_43=0

for(i in 1:10)
{
  v1 = paste("uniform",as.name(i),sep = "_")
  v2 = paste("normal",as.name(i),sep = "_")
  data_1 <- scan(v1)
  data_2 <- scan(v2)
  i1 = 1
  i2 = 1
  i3 = 1

  v11 = 0
  v12 = 0
  v13 = 0

  v21 = 0
  v22 = 0
  v23 = 0
  
  v31 = 0
  v32 = 0
  v33 = 0
  
  v41 = 0
  v42 = 0
  v43 = 0
  

  for(j in 1:50)
  {
    if (data_1[j]>=0 && data_1[j]<=0.34){
      v11[i1] <- data_1[j]
      i1 = i1 + 1
    }
    else if(data_1[j]<0.66){
      v12[i2] <- data_1[j]
      i2 = i2 + 1
    }
    else if(data_1[j]<=1){
      v13[i3] <- data_1[j]
      i3 = i3 + 1
    }
  }
  count_11[i] = length(v11)
  count_12[i] = length(v12) 
  count_13[i] = length(v13)

  i1 = 1
  i2 = 1
  i3 = 1

  for(j in 1:50)
  {
    if (data_2[j]>=0 && data_2[j]<=0.34){
      v21[i1] <- data_2[j]
      i1 = i1 + 1
    }
    else if(data_2[j]<0.66){
      v22[i2] <- data_2[j]
      i2 = i2 + 1
    }
    else if(data_2[j]<=1){
      v23[i3] <- data_2[j]
      i3 = i3 + 1
    }
  }
  count_21[i] = length(v21)
  count_22[i] = length(v22) 
  count_23[i] = length(v23)

  i1 = 1
  i2 = 1
  i3 = 1

  for(j in 51:100)
  {
    if (data_1[j]>=0 && data_1[j]<=0.34){
      v31[i1] <- data_1[j]
      i1 = i1 + 1
    }
    else if(data_1[j]<0.66){
      v32[i2] <- data_1[j]
      i2 = i2 + 1
    }
    else if(data_1[j]<=1){
      v33[i3] <- data_1[j]
      i3 = i3 + 1
    }
  }
  count_31[i] = length(v31)
  count_32[i] = length(v32) 
  count_33[i] = length(v33)

  i1 = 1
  i2 = 1
  i3 = 1

  for(j in 51:100)
  {
    if (data_2[j]>=0 && data_2[j]<=0.34){
      v41[i1] <- data_1[j]
      i1 = i1 + 1
    }
    else if(data_2[j]<0.66){
      v42[i2] <- data_2[j]
      i2 = i2 + 1
    }
    else if(data_2[j]<=1){
      v43[i3] <- data_2[j]
      i3 = i3 + 1
    }
  }
  count_41[i] = length(v41)
  count_42[i] = length(v42) 
  count_43[i] = length(v43)
}

min_1 = c(min(count_11),min(count_12),min(count_13));
max_1 = c(max(count_11),max(count_12),max(count_13));
mean_1 = c(mean(count_11),mean(count_12),mean(count_13));

min_2 = c(min(count_21),min(count_22),min(count_23));
max_2 = c(max(count_21),max(count_22),max(count_23));
mean_2 = c(mean(count_21),mean(count_22),mean(count_23));

min_3 = c(min(count_31),min(count_32),min(count_33));
max_3 = c(max(count_31),max(count_32),max(count_33));
mean_3 = c(mean(count_31),mean(count_32),mean(count_33));

min_4 = c(min(count_41),min(count_42),min(count_43));
max_4 = c(max(count_41),max(count_42),max(count_43));
mean_4 = c(mean(count_41),mean(count_42),mean(count_43));

df_1 = data.frame(min_1,max_1,mean_1);
df_2 = data.frame(min_2,max_2,mean_2);
df_3 = data.frame(min_3,max_3,mean_3);
df_4 = data.frame(min_4,max_4,mean_4);

row.names(df_1) <- c("A","B","C")
row.names(df_2) <- c("A","B","C")
row.names(df_3) <- c("A","B","C")
row.names(df_4) <- c("A","B","C")

write.table(df_1, file = "uniformq3_G1", col.names = FALSE)
write.table(df_2, file = "normalq3_G1", row.names = FALSE, col.names = FALSE)
write.table(df_3, file = "uniformq3_G2", col.names = FALSE)
write.table(df_4, file = "normalq3_G2",  row.names = FALSE, col.names = FALSE)
