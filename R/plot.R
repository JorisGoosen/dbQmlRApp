#df		<- SchoolScannerTextOnly[c("graagNaarSchool", "bangOpSchool")]

dfGraag <- data.frame(table(SchoolScannerTextOnly$graagNaarSchool))
dfBang  <- data.frame(table(SchoolScannerTextOnly$bangOpSchool))

dfGraag$kolom <- "graagNaarSchool"
dfBang$kolom  <- "bangOpSchool"

df <- rbind(dfGraag, dfBang)
df$Freq <- df$Freq / length(SchoolScannerTextOnly$graagNaarSchool)

#levels moeten gesorteerd enzo
lelijkeBarChart <- ggplot(df, aes(x=kolom, y=Freq, fill=Var1)) + geom_bar(position="fill", stat="identity") + coord_flip()

writeImage(plot=lelijkeBarChart, plotFolder=PLOTFOLDER,	plotFile=PLOTFILE,	width=WIDTH, height=HEIGHT)

#check deze: https://r-graph-gallery.com/48-grouped-barplot-with-ggplot2
