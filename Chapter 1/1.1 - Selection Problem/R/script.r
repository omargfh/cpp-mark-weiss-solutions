setwd(dirname(rstudioapi::getActiveDocumentContext()$path))
data <- read.csv("data.csv")
plot(data$N, data$Time / (1000 * 1000), main="Input vs. Time", xlab="Input", ylab="Time", type="l")

data <- read.csv("classic-efficientsort.csv")
plot(data$N, data$Time / (1000 * 1000), main="Input vs. Time", xlab="Input", ylab="Time", type="l")

data <- read.csv("classic-bubblesort.csv")
plot(data$N, data$Time / (1000 * 1000), main="Input vs. Time", xlab="Input", ylab="Time", type="l")