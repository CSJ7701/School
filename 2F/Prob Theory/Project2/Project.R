set.seed(1234)
data=runif(300000,0,0)
dim(data)=c(10000,30)
meanofrow=apply(data,1,mean)
standmean=(meanofrow/(sd(data)/sqrt(n)) # See p234 in text. n is undefined.
vectorofbreaks=seq(from=-6,to=6,by=.25)
hist(standmean,breaks=vectorofbreaks)
meanofrow[0:5]
standmean[0:5]
