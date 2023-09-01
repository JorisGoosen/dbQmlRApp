kleuren <- list(
  lichtrozig=		"#f6b6cc"	,
  rozig=			"#EF2560"	,
  lichtblauwig=		"#9CCDD1"	,
  blauwig=			"#038794"	,
  zwartig=			"#1D1D1B"	,
  lichtgroen=		"#BCE2D7"	,
  donkergroen=		"#5FA48F"	,
  lichtgeel=		"#FFF798"
)
themaPalet <- c(kleuren$rozig, kleuren$lichtgroen, kleuren$lichtrozig, kleuren$donkergroen)

scale_fill_manual(values=themaPalet)
scale_colour_manual(values=themaPalet)


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

    df <- filter(df, `Hoe vaak` != "")

    df$`Hoe vaak` <- factor(as.character(df$`Hoe vaak`), rev(c("Nooit", "Soms", "Vaak", "Altijd")))

    df <- arrange(df, desc(`Hoe vaak`))

    ggplot(df, aes(x=Kolom, y=`Procent`, fill=`Hoe vaak`)) +
	  geom_bar( stat="identity", na.rm=TRUE, position = position_stack(reverse = TRUE)) +
	  coord_flip()
}
)

plot <- plot + scale_fill_manual("Legenda", values=c(Altijd=kleuren$rozig, Vaak=kleuren$lichtblauwig, Soms=kleuren$lichtrozig, Nooit=kleuren$blauwig)) + theme_classic()

writeImage(plot=plot, plotFolder=PLOTFOLDER,	plotFile=PLOTFILE,	width=WIDTH, height=HEIGHT)

#check deze: https://r-graph-gallery.com/48-grouped-barplot-with-ggplot2
