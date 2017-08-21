for(i in 1:10)
{
  a1 = paste("uniform",as.name(i),sep = "_")
  a2 = paste("normal",as.name(i),sep = "_")
  write(rnorm(100,0.5,0.15), file = a2,
        ncolumns = 1,
        append = FALSE, sep = " ")
  write(runif(100,0.0,1.0), file = a1,
        ncolumns = 1,
        append = FALSE, sep = " ")
}