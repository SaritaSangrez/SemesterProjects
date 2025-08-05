# Load the dataset into the R environment
# Set the file path
file_path <- "C:/Users/HP/Downloads/autompg.csv"

# Read the CSV file
data <- read.csv(file_path)

?data
data

library(corrplot)


# ==================================
# Task 3: Descriptive Statistics
# ==================================

library(psych)

#Shows Summary of all Data - detailed descriptive stats
describe(data)  

# Quick Summary descriptive stats
summary(data)


# descriptive stats for mpg
mean(data$ mpg.Y., na.rm = TRUE)
median(data$mpg.Y, na.rm = TRUE)
sd(data$mpg.Y, na.rm = TRUE)         # Standard deviation
var(data$mpg.Y, na.rm = TRUE)        # Variance
min(data$mpg.Y, na.rm = TRUE)
max(data$mpg.Y, na.rm = TRUE)
range(data$mpg.Y, na.rm = TRUE)
quantile(data$mpg.Y, na.rm = TRUE)

# descriptive stats for cylinders
mean(data$Cylinders, na.rm = TRUE)
median(data$Cylinders, na.rm = TRUE)
sd(data$Cylinders, na.rm = TRUE)
var(data$Cylinders, na.rm = TRUE)
min(data$Cylinders, na.rm = TRUE)
max(data$Cylinders, na.rm = TRUE)
range(data$Cylinders, na.rm = TRUE)
quantile(data$Cylinders, na.rm = TRUE)

# descriptive stats for displacement
mean(data$Displacement, na.rm = TRUE)
median(data$Displacement, na.rm = TRUE)
sd(data$Displacement, na.rm = TRUE)
var(data$Displacement, na.rm = TRUE)
min(data$Displacement, na.rm = TRUE)
max(data$Displacement, na.rm = TRUE)
range(data$Displacement, na.rm = TRUE)
quantile(data$Displacement, na.rm = TRUE)

# descriptive stats for horsepower
mean(data$HorsePower, na.rm = TRUE)
median(data$HorsePower, na.rm = TRUE)
sd(data$HorsePower, na.rm = TRUE)
var(data$HorsePower, na.rm = TRUE)
min(data$HorsePower, na.rm = TRUE)
max(data$HorsePower, na.rm = TRUE)
range(data$HorsePower, na.rm = TRUE)
quantile(data$HorsePower, na.rm = TRUE)

# descriptive stats for weight
mean(data$Weight, na.rm = TRUE)
median(data$Weight, na.rm = TRUE)
sd(data$Weight, na.rm = TRUE)
var(data$Weight, na.rm = TRUE)
min(data$Weight, na.rm = TRUE)
max(data$Weight, na.rm = TRUE)
range(data$Weight, na.rm = TRUE)
quantile(data$Weight, na.rm = TRUE)

# descriptive stats for acceleration
mean(data$acceleration, na.rm = TRUE)
median(data$acceleration, na.rm = TRUE)
sd(data$acceleration, na.rm = TRUE)
var(data$acceleration, na.rm = TRUE)
min(data$acceleration, na.rm = TRUE)
max(data$acceleration, na.rm = TRUE)
range(data$acceleration, na.rm = TRUE)
quantile(data$acceleration, na.rm = TRUE)

# descriptive stats for modelyear
mean(data$ModelYear, na.rm = TRUE)
median(data$ModelYear, na.rm = TRUE)
sd(data$ModelYear, na.rm = TRUE)
var(data$ModelYear, na.rm = TRUE)
min(data$ModelYear, na.rm = TRUE)
max(data$ModelYear, na.rm = TRUE)
range(data$ModelYear, na.rm = TRUE)
quantile(data$ModelYear, na.rm = TRUE)

# descriptive stats for origin
mean(data$origin, na.rm = TRUE)
median(data$origin, na.rm = TRUE)
sd(data$origin, na.rm = TRUE)
var(data$origin, na.rm = TRUE)
min(data$origin, na.rm = TRUE)
max(data$origin, na.rm = TRUE)
range(data$origin, na.rm = TRUE)
quantile(data$origin, na.rm = TRUE)


# Display the default number of rows(1st 6 rows) from the dataset
head(data)
# Display the first 3 rows of the dataset
head(data,3)

# Display the default number of rows(last 6 rows) from the dataset
tail(data)
# Display the first 4 rows of the dataset
tail(data,4)

# Use the 'dim()' function to obtain the dimensions of the dataset
# This returns a vector with the number of rows and columns in dataset
dim(data)

# Use the 'names()' function to get the names of the columns in the dataset
names(data)

# Check the structure of the particular dataset
str(data)



# ==================================
# Task 4: Data Pre-processing
# ==================================



# Missing Values in dataset
# Total number of missing values in  dataset
sum(is.na(data))  
# Missing values per column in  dataset
colSums(is.na(data))  

data_cleaned <- data

#handling missing values
# For mean imputation:
data_cleaned$HorsePower[is.na(data_cleaned$HorsePower)] <- mean(data_cleaned$HorsePower, na.rm = TRUE)
data_cleaned$acceleration[is.na(data_cleaned$acceleration)] <- mean(data_cleaned$acceleration, na.rm = TRUE)

#visualization after removal
hist(data_cleaned$HorsePower, main="HorsePower Distribution After Cleaning", xlab="HorsePower")
boxplot(data_cleaned$acceleration, main="Acceleration Boxplot After Cleaning")

# Duplicate rows in 
# Number of duplicate rows in  dataset
sum(duplicated(data))
# Shows duplicate rows in 
duplicated_data <- data[duplicated(data), ]  
duplicated_data
 
# Assuming your dataset is called data
data$CarName_numeric <- as.numeric(factor(data$CarName))


# Check how car names are mapped to numbers
levels(factor(data$CarName))

# View the result
print(data)

# Standardize all 4 numeric features 
data_scaled <- as.data.frame(scale(data[, 1:8]))
# View the result (standardized values for all 150 rows)
head(data_scaled, 406)  # View first 10 rows

# Standardize by column names
# Select only numeric continuous variables
num_cols <- c("mpg.Y.", "Displacement", "HorsePower", "Weight", "acceleration")

# Standardize them
data[num_cols] <- scale(data[num_cols])

# Check summary again
summary(data[num_cols])


# Function to detect outliers using IQR method
find_outliers <- function(data) {
  Q1 <- quantile(data, 0.25)
  Q3 <- quantile(data, 0.75)
  IQR <- Q3 - Q1
  lower_bound <- Q1 - 2.4 * IQR
  upper_bound <- Q3 + 2.4 * IQR
  return(data[data < lower_bound | data > upper_bound])
}

# Outliers in  dataset
outliers_data_mpg.Y. <- find_outliers(data$mpg.Y.)
outliers_data_Cylinders <- find_outliers(data$Cylinders)
outliers_data_Displacement <- find_outliers(data$Displacement)
outliers_data_HorsePower <- find_outliers(data$HorsePower)
outliers_data_Weight <- find_outliers(data$Weight)
outliers_data_acceleration <- find_outliers(data$acceleration)
outliers_data_ModelYear <- find_outliers(data$ModelYear)
outliers_data_origin <- find_outliers(data$origin)



length(outliers_data_mpg.Y.)
length(outliers_data_Cylinders)
length(outliers_data_Displacement)
length(outliers_data_HorsePower)
length(outliers_data_Weight)
length(outliers_data_acceleration)
length(outliers_data_ModelYear)
length(outliers_data_origin)


data[outliers_data_mpg.Y., "mpg.Y."]
data[outliers_data_Cylinders, "Cylinders"]
data[outliers_data_Displacement, "Displacement"]
data[outliers_data_HorsePower, "HorsePower"]
data[outliers_data_Weight, "Weight"]
data[outliers_data_acceleration, "acceleration"]
data[outliers_data_ModelYear, "ModelYear"]
data[outliers_data_origin, "origin"]





# ============================================
# Task 7: Statistical Modeling and Inference
# ============================================



# STEP 1: Correlation Analysis
# Correlation Coefficient (single pair)
# Calculate the Pearson correlation coefficient between mpg.Y. and Weight
correlation_coefficient <- cor(data$mpg.Y., data$Weight, method = "pearson")
print(correlation_coefficient)  # This now works

# Correlation Matrix (all relevant numeric columns)
correlation_data <- data[, c("mpg.Y.", 
                             "Cylinders", 
                             "Displacement", 
                             "HorsePower", 
                             "Weight", 
                             "acceleration", 
                             "ModelYear",
                             "origin")]

correlation_matrix <- cor(correlation_data)
print(correlation_matrix)

# Heatmap of the correlation matrix
corrplot(correlation_matrix, method = "color", type = "upper", tl.col = "black", tl.srt = 45, addCoef.col = "black")


# STEP 2: Simple Linear Regression (SLR)
# Simple Linear Regression: mpg.Y. vs HorsePower
SLM <- lm(mpg.Y. ~ Cylinders, data = data)
SLM
summary(SLM)   # Print the summary of the model to check 
               # coefficients and statistical significance
SLM <- lm(mpg.Y. ~ acceleration, data = data)
SLM
summary(SLM)
SLM <- lm(mpg.Y. ~ ModelYear, data = data)
SLM
summary(SLM)
SLM <- lm(mpg.Y. ~ Weight, data = data)
SLM
summary(SLM)
SLM <- lm(mpg.Y. ~ HorsePower, data = data)
SLM
summary(SLM)
SLM <- lm(mpg.Y. ~ Displacement, data = data)
SLM
summary(SLM)
SLM <- lm(mpg.Y. ~ origin, data = data)
SLM
# Print the summary of the model
summary(SLM)



# CAN BE MODIFIED FOR OTHER VARIABES
# Plot the regression line
plot(data$origin, data$mpg.Y., 
     main = "SLR: mpg.Y. vs origin", 
     xlab = "origin", 
     ylab = "mpg.Y.", 
     col = "black")
abline(model_slr, col = "maroon")



# STEP 3: Multiple Linear Regression (MLR)
# Multiple Linear Regression: mpg.Y. as a function of multiple variables
model_mlr <- lm(mpg.Y. ~ HorsePower + Weight + Displacement + Cylinders + acceleration, data = data)

# Print the summary of the model
summary(model_mlr)

# Fit a Multiple linear regression model with more variables
MLM <- lm(mpg.Y. ~ Cylinders + Displacement + HorsePower + Weight + acceleration + ModelYear + origin, data = data)

# Summary of the model to see coefficients and statistics
summary(MLM)




# ============================================
# Task 5: Exploratory Data Analysis (EDA)
# ============================================




# Load required library for some plots
library(ggplot2)
library(corrplot)
library(gridExtra)



# Reset previous graphic state
dev.off()


# 1. Bar Chart – Count of Cars by Origin
barplot(table(data$origin), 
        main = "Count of Cars by Origin", 
        col = "steelblue", 
        xlab = "Origin", 
        ylab = "Count")

# 2. Pie Chart – Distribution of Cylinders
cyl_count <- table(data$Cylinders)
pie(cyl_count, 
    labels = names(cyl_count), 
    main = "Distribution of Cylinders", 
    col = rainbow(length(cyl_count)))

# 3. Histogram – HorsePower
hist(data$HorsePower, 
     main = "Histogram of HorsePower", 
     col = "orange", 
     xlab = "HorsePower", 
     breaks = 15)

# 4. Scatter Plot – HorsePower vs mpg.Y.
plot(data$HorsePower, data$mpg.Y., 
     main = "HorsePower vs MPG", 
     xlab = "HorsePower", 
     ylab = "mpg.Y.", 
     col = "darkgreen", 
     pch = 19)

# 5. Distribution Plot – mpg.Y. (converted to base R density + hist)
hist(data$mpg.Y., 
     prob = TRUE,
     main = "Distribution of mpg.Y.",
     xlab = "mpg.Y.",
     col = "skyblue", 
     border = "white")
lines(density(data$mpg.Y., na.rm = TRUE), col = "blue", lwd = 2)

# 6. Density Plot – HorsePower
plot(density(data$HorsePower, na.rm = TRUE), 
     main = "Density Plot of HorsePower", 
     col = "red", 
     lwd = 2)
polygon(density(data$HorsePower, na.rm = TRUE), col = "red", border = "black")

# 7. Pair Plot – Selected Features
pairs(data[, c("mpg.Y.", "HorsePower", "Weight", "Displacement")], 
      main = "Pair Plot of Features", 
      pch = 19, col = "purple")

# 8. Heatmap – Correlation Matrix
cor_matrix <- cor(data[, c("mpg.Y.", "Cylinders", "Displacement", "HorsePower", "Weight", "acceleration", "ModelYear", "origin")])
heatmap(cor_matrix, 
        main = "Correlation Heatmap", 
        col = colorRampPalette(c("red", "white", "navyblue"))(50), 
        scale = "none")




######### BAR GRAPH  ########## 

# Bar chart 1: Average MPG by Origin
p1 <- ggplot(data, aes(x = factor(origin), y = mpg.Y.)) +
  stat_summary(fun = mean, geom = "bar", fill = "steelblue") +
  labs(title = "Avg MPG by Origin", x = "Origin", y = "Average mpg.Y.")

# Bar chart 2: Average MPG by Cylinders
p2 <- ggplot(data, aes(x = factor(Cylinders), y = mpg.Y.)) +
  stat_summary(fun = mean, geom = "bar", fill = "tomato") +
  labs(title = "Avg MPG by Cylinders", x = "Cylinders", y = "Average mpg.Y.")

# Bar chart 3: Average MPG by Model Year
p3 <- ggplot(data, aes(x = factor(ModelYear), y = mpg.Y.)) +
  stat_summary(fun = mean, geom = "bar", fill = "forestgreen") +
  labs(title = "Avg MPG by Model Year", x = "ModelYear", y = "Average mpg.Y.")

# Bar chart 4: Average MPG by HorsePower Range
data$HP_Bin <- cut(data$HorsePower, breaks = c(0, 75, 100, 150, 200, Inf),
                   labels = c("0-75", "76-100", "101-150", "151-200", "200+"))
p4 <- ggplot(data, aes(x = HP_Bin, y = mpg.Y.)) +
  stat_summary(fun = mean, geom = "bar", fill = "orchid") +
  labs(title = "Avg MPG by HorsePower Range", x = "HP Range", y = "Average mpg.Y.")


grid.arrange(p1, p2, p3, p4, ncol = 2)



######### PIE CHART  ##########

 
# Create necessary bins first
data$HP_Bin <- cut(data$HorsePower, breaks = c(0, 75, 100, 150, 200, Inf),
                   labels = c("0-75", "76-100", "101-150", "151-200", "200+"))

data$Year_Bin <- cut(data$ModelYear, breaks = c(69, 72, 75, 78, 82), 
                     labels = c("70-72", "73-75", "76-78", "79-82"))

# Pie 1: Cylinders Distribution
cyl_count <- as.data.frame(table(data$Cylinders))
p1 <- ggplot(cyl_count, aes(x = "", y = Freq, fill = factor(Var1))) +
  geom_bar(stat = "identity", width = 1) +
  coord_polar("y") +
  labs(title = "Cylinders Distribution", fill = "Cylinders") +
  theme_void()

# Pie 2: Origin Distribution
origin_count <- as.data.frame(table(data$origin))
p2 <- ggplot(origin_count, aes(x = "", y = Freq, fill = factor(Var1))) +
  geom_bar(stat = "identity", width = 1) +
  coord_polar("y") +
  labs(title = "Origin Distribution", fill = "Origin") +
  theme_void()

# Pie 3: HorsePower Bins
hp_bin_count <- as.data.frame(table(data$HP_Bin))
p3 <- ggplot(hp_bin_count, aes(x = "", y = Freq, fill = factor(Var1))) +
  geom_bar(stat = "identity", width = 1) +
  coord_polar("y") +
  labs(title = "HorsePower Ranges", fill = "HP Range") +
  theme_void()

# Pie 4: Model Year Bins
year_bin_count <- as.data.frame(table(data$Year_Bin))
p4 <- ggplot(year_bin_count, aes(x = "", y = Freq, fill = factor(Var1))) +
  geom_bar(stat = "identity", width = 1) +
  coord_polar("y") +
  labs(title = "Model Year Bins", fill = "Years") +
  theme_void()

# Combine all pie charts in a 2x2 grid
grid.arrange(p1, p2, p3, p4, ncol = 2)


######### HISTOGRAM  ##########

# Histogram 1: mpg.Y.
p1 <- ggplot(data, aes(x = mpg.Y.)) +
  geom_histogram(binwidth = 2, fill = "skyblue", color = "black") +
  labs(title = "Distribution of mpg.Y.", x = "mpg.Y.", y = "Count")

# Histogram 2: HorsePower
p2 <- ggplot(data, aes(x = HorsePower)) +
  geom_histogram(binwidth = 10, fill = "orange", color = "black") +
  labs(title = "Distribution of HorsePower", x = "HorsePower", y = "Count")

# Histogram 3: Weight
p3 <- ggplot(data, aes(x = Weight)) +
  geom_histogram(binwidth = 200, fill = "seagreen", color = "black") +
  labs(title = "Distribution of Weight", x = "Weight", y = "Count")

# Histogram 4: Acceleration
p4 <- ggplot(data, aes(x = acceleration)) +
  geom_histogram(binwidth = 1, fill = "orchid", color = "black") +
  labs(title = "Distribution of Acceleration", x = "Acceleration", y = "Count")

# Combine all histograms in one window
grid.arrange(p1, p2, p3, p4, ncol = 2)



######### SCATTER PLOT  ##########


# Scatter 1: MPG vs HorsePower
p1 <- ggplot(data, aes(x = HorsePower, y = mpg.Y.)) +
  geom_point(color = "darkred", alpha = 0.6) +
  labs(title = "MPG vs HorsePower", x = "HorsePower", y = "mpg.Y.")

# Scatter 2: MPG vs Weight
p2 <- ggplot(data, aes(x = Weight, y = mpg.Y.)) +
  geom_point(color = "navy", alpha = 0.6) +
  labs(title = "MPG vs Weight", x = "Weight", y = "mpg.Y.")

# Scatter 3: MPG vs Displacement
p3 <- ggplot(data, aes(x = Displacement, y = mpg.Y.)) +
  geom_point(color = "darkgreen", alpha = 0.6) +
  labs(title = "MPG vs Displacement", x = "Displacement", y = "mpg.Y.")

# Scatter 4: MPG vs Acceleration
p4 <- ggplot(data, aes(x = acceleration, y = mpg.Y.)) +
  geom_point(color = "purple", alpha = 0.6) +
  labs(title = "MPG vs Acceleration", x = "Acceleration", y = "mpg.Y.")

# Combine all scatter plots in one window
grid.arrange(p1, p2, p3, p4, ncol = 2)


######### DISTRIBUTION  ##########

# Histogram + Density: mpg.Y.
p1 <- ggplot(data, aes(x = mpg.Y.)) +
  geom_histogram(aes(y = ..density..), bins = 20, fill = "skyblue", color = "black") +
  geom_density(color = "blue", size = 1) +
  labs(title = "Distribution of mpg.Y.", x = "mpg.Y.", y = "Density")

# Histogram + Density: HorsePower
p2 <- ggplot(data, aes(x = HorsePower)) +
  geom_histogram(aes(y = ..density..), bins = 20, fill = "salmon", color = "black") +
  geom_density(color = "darkred", size = 1) +
  labs(title = "Distribution of HorsePower", x = "HorsePower", y = "Density")

# Histogram + Density: Weight
p3 <- ggplot(data, aes(x = Weight)) +
  geom_histogram(aes(y = ..density..), bins = 20, fill = "lightgreen", color = "black") +
  geom_density(color = "darkgreen", size = 1) +
  labs(title = "Distribution of Weight", x = "Weight", y = "Density")

# Histogram + Density: Acceleration
p4 <- ggplot(data, aes(x = acceleration)) +
  geom_histogram(aes(y = ..density..), bins = 20, fill = "plum", color = "black") +
  geom_density(color = "purple", size = 1) +
  labs(title = "Distribution of Acceleration", x = "Acceleration", y = "Density")

# Display all distribution plots in one window
grid.arrange(p1, p2, p3, p4, ncol = 2)


######### DENSITY PLOT   ##########

# Density Plot: mpg.Y.
d1 <- ggplot(data, aes(x = mpg.Y.)) +
  geom_density(fill = "skyblue", alpha = 0.6) +
  labs(title = "Density of mpg.Y.", x = "mpg.Y.", y = "Density")

# Density Plot: HorsePower
d2 <- ggplot(data, aes(x = HorsePower)) +
  geom_density(fill = "salmon", alpha = 0.6) +
  labs(title = "Density of HorsePower", x = "HorsePower", y = "Density")

# Density Plot: Weight
d3 <- ggplot(data, aes(x = Weight)) +
  geom_density(fill = "lightgreen", alpha = 0.6) +
  labs(title = "Density of Weight", x = "Weight", y = "Density")

# Density Plot: Acceleration
d4 <- ggplot(data, aes(x = acceleration)) +
  geom_density(fill = "plum", alpha = 0.6) +
  labs(title = "Density of Acceleration", x = "Acceleration", y = "Density")

# Display all density plots
grid.arrange(d1, d2, d3, d4, ncol = 2)






