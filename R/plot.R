
#welkPlot <- "horizontaalPerLabel"
welkPlot <- "horizontaalMeerdere"

plot <- switch(welkPlot,

horizontaalPerLabel =
{
    tafelPerGender  <- table(SchoolScannerTextOnly[c('graagNaarSchool', 'gender')])
	dfPer		        <- as.data.frame(tafelPerGender)

    hoeVaaks        <- levels(as.factor(SchoolScannerTextOnly$graagNaarSchool))
	genders         <- levels(as.factor(SchoolScannerTextOnly$gender))
	dfGender	      <- table(SchoolScannerTextOnly$gender)

    dfPer           <- dfPer %>% rowwise() %>% select(gender, graagNaarSchool, Freq) %>%  mutate(`Hoe vaak` = 100.0 * Freq / dfGender[[gender]], Gender=gender, `Graag naar school`=graagNaarSchool)

    ggplot(dfPer, aes(x=Gender, y=`Hoe vaak`, fill=`Graag naar school`)) + geom_bar(position="fill", stat="identity") + coord_flip()
},
horizontaalMeerdere=
{

    dfGraag <- as.data.frame(table(SchoolScannerTextOnly$graagNaarSchool))
	dfBang  <- as.data.frame(table(SchoolScannerTextOnly$bangOpSchool))

    dfGraag$Kolom <- "Graag naar school"
	dfBang$Kolom  <- "Bang op school"

    df <- rbind(dfGraag, dfBang)

    df <- df %>% rowwise() %>% select(Var1, Freq, Kolom) %>% mutate(`Procent`=100.0 * Freq / length(SchoolScannerTextOnly$graagNaarSchool), `Hoe vaak`=Var1)


    #levels moeten gesorteerd enzo
	ggplot(df, aes(x=Kolom, y=`Procent`, fill=`Hoe vaak`)) + geom_bar(position="fill", stat="identity") + coord_flip()
}
)


writeImage(plot=plot, plotFolder=PLOTFOLDER,	plotFile=PLOTFILE,	width=WIDTH, height=HEIGHT)

#check deze: https://r-graph-gallery.com/48-grouped-barplot-with-ggplot2
