print("Running main.R!")
#options(warn=-1)


list.of.packages <- c("Rcpp", "RInside", "RSQLite", "dbplyr", "showtext", "ggplot2", "stringr", "devtools", "remotes")
new.packages <- list.of.packages[!(list.of.packages %in% installed.packages()[,"Package"])]

if(length(new.packages)) {
        install.packages(new.packages, type="binary", repos="https://cloud.r-project.org", dependencies=TRUE)
} else
{
        print("Alle pakketten zijn al geinstalleerd!")
}	


#setwd("../dbQmlRApp/predped")
library(predped)

png("envPlot.png",256,256)
setting <- background(shape = rectangle(center = c(4, 4), 
                                        size = c(8, 8)),
                      objects = list(circle(center = c(4, 4), 
                                            radius = 1,
                                            interactable = TRUE),
                                     rectangle(center = c(1.5, 4),
                                               size = c(1, 6),
                                               interactable = TRUE),
                                     polygon(points = rbind(c(3, 1),
                                                            c(3, 2),
                                                            c(6, 2),
                                                            c(6, 6), 
                                                            c(3, 6),
                                                            c(3, 7),
                                                            c(7, 7),
                                                            c(7, 1)),
                                             interactable = TRUE)),
                      entrance = coordinate(c(0, 4)),
                      exit = coordinate(c(8, 4)),
                      same_exit = FALSE)

# You can visualize this setting with the `plot` function. Additional to the 
# setting, you can provide this function with several other arguments that 
# influence how the plot looks like. These additional arguments are passed on to
# `ggplot` functions.
plot(setting, fill = "grey", color = "black", linewidth = 1.5)
dev.off()
