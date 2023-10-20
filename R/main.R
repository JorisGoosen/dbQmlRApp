print("Running main.R!")

#list.of.packages <- c("Rcpp", "RInside", "RSQLite", "dbplyr", "showtext", "ggplot2", "stringr")
#new.packages <- list.of.packages[!(list.of.packages %in% installed.packages()[,"Package"])]

if(length(new.packages)) {
        install.packages(new.packages, type="binary", repos="https://cloud.r-project.org", dependencies=TRUE)
} else
{
        print("Alle pakketten zijn al geinstalleerd!")
}
