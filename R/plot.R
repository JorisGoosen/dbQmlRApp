library(tidyr)
library(ggplot2)
library(stringr)

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

library(showtext)
font_add_google("Karla", "karla")

## Automatically use showtext to render text
showtext_auto()

plot <- switch(WELKPLOT,

               horizontaalPerLabel =
			     {
				   tafelPerGender  <- table(SchoolScannerTextOnly[c('graagNaarSchool', 'gender')])
				   dfPer		    <- as.data.frame(tafelPerGender)

                   hoeVaaks        <- levels(as.factor(SchoolScannerTextOnly$graagNaarSchool))
				   genders         <- levels(as.factor(SchoolScannerTextOnly$gender))
				   dfGender	    <- table(SchoolScannerTextOnly$gender)

                   dfPer$graagNaarSchool	<- factor(as.character(dfPer$graagNaarSchool), rev(c("Nooit", "Soms", "Vaak", "Altijd")))
				   dfPer					<- dfPer %>% rowwise() %>% select(gender, graagNaarSchool, Freq) %>%  mutate(`Hoe vaak` = Freq / dfGender[[gender]], Gender=gender, `Graag naar school`=graagNaarSchool)
				   dfPer					<- filter(dfPer, Gender != "")

                   dfPer <- arrange(dfPer, desc(graagNaarSchool))

                   ggplot(dfPer, aes(x=Gender, y=`Hoe vaak`, fill=`Graag naar school`)) + geom_bar(position=position_stack(reverse = TRUE), stat="identity") + coord_flip() +
				     scale_y_continuous(labels = scales::percent) + xlab("") + ylab("") + theme(aspect.ratio=0.3) +
					 scale_fill_manual("", values=c(Altijd=kleuren$rozig, Vaak=kleuren$lichtblauwig, Soms=kleuren$lichtrozig, Nooit=kleuren$blauwig))
					},
				horizontaalMeerdere=
			     {

                   dfGraag <- as.data.frame(table(SchoolScannerTextOnly$graagNaarSchool))
				   dfBang  <- as.data.frame(table(SchoolScannerTextOnly$bangOpSchool))

                   dfGraag$Kolom <- "Graag naar school"
				   dfBang$Kolom  <- "Bang op school"

                   df <- rbind(dfGraag, dfBang)

                   df <- df %>% rowwise() %>% select(Var1, Freq, Kolom) %>% mutate(`Procent`= Freq / length(SchoolScannerTextOnly$graagNaarSchool), `Hoe vaak`=Var1)

                   df <- filter(df, `Hoe vaak` != "")

                   df$`Hoe vaak` <- factor(as.character(df$`Hoe vaak`), rev(c("Nooit", "Soms", "Vaak", "Altijd")))

                   df <- arrange(df, desc(`Hoe vaak`))

                   ggplot(df, aes(x=Kolom, y=`Procent`, fill=`Hoe vaak`)) + theme(aspect.ratio=0.3) +
				     geom_bar( stat="identity", na.rm=TRUE, position = position_stack(reverse = TRUE)) +
					 coord_flip() + scale_y_continuous(labels = scales::percent) + xlab("") + ylab("") +
					 scale_fill_manual("", values=c(Altijd=kleuren$rozig, Vaak=kleuren$lichtblauwig, Soms=kleuren$lichtrozig, Nooit=kleuren$blauwig))


                 },
				horizontaalLabelsGroepen=
			     {

                   allesPerCulturen <- SchoolScannerTextOnly[c('onveiligHier', 'cultuur')]

                   allesPerCulturen <- allesPerCulturen %>% rowwise() %>% select(cultuur, onveiligHier) %>%
				     mutate(cultuur=
					          switch(tolower(cultuur),
							         'nederlands'                = 'Nederlands',
									 'marokkaans'                = 'Marrokaans',
									 'marokkaans, nederlands'    = 'Marrokaans',
									 'turks'                     = 'Turks',
									 'nederlands, turks'         = 'Turks',
									 'surinaams'                 = 'Surinaams',
									 'nederlands, surinaams'     = 'Surinaams',
									 'antilliaans'               = 'Antilliaans',
									 'antilliaans, nederlands'   = 'Antilliaans',
									 'Anders'))

                   tafelTotaal      <- table(allesPerCulturen$cultuur)
				   allesPerCultuur  <- allesPerCulturen %>% mutate(onveiligHier=strsplit(onveiligHier, ", ")) %>% unnest(onveiligHier)
				   tafelPerCultuur  <- table(allesPerCultuur)



                   dfPer		    <- as.data.frame(tafelPerCultuur)

                   hoeVaaks        <- levels(as.factor(SchoolScannerTextOnly$onveiligHier))
				   cultuurs         <- levels(as.factor(SchoolScannerTextOnly$cultuur))
				   dfcultuur	    <- table(SchoolScannerTextOnly$cultuur)

                   #dfPer$onveiligHier <- factor(as.character(dfPer$onveiligHier), rev(c("Nooit", "Soms", "Vaak", "Altijd")))
				   dfPer           <- dfPer %>% rowwise() %>% select(cultuur, onveiligHier, Freq) %>%
				     mutate(Freq = Freq / tafelTotaal[[cultuur]], cultuur=cultuur,
					        `Onveilig in`=onveiligHier, totaalCultuur = tafelTotaal[[cultuur]])
							dfPer <- filter(dfPer, cultuur != "")
				   dfPer <- filter(dfPer, onveiligHier != "" && str_count(onveiligHier, "nergens onveilig") == 0)


                   dfPer <- arrange(dfPer, desc(onveiligHier))

                   ggplot(dfPer, aes(x=`Onveilig in`, y=Freq, fill=cultuur)) +
				     geom_bar(position=position_dodge2(reverse=TRUE),stat="identity", width=1) +

                     geom_text(size=3,aes(group=cultuur, label = paste0(round(Freq * 100), "%")), hjust=-0.1, vjust=0.4, position = position_dodge2(reverse=TRUE, width=1)) +
					 geom_text(size=3,aes(group=cultuur, label =
					                        ifelse(Freq > 0.01,
											       paste0("N: ", totaalCultuur),
												   "")),
												hjust=-0.1, vjust=0.4, y=0.0, position = position_dodge2(reverse=TRUE, width=1)) +

                     coord_flip() +
					 scale_y_continuous(labels = scales::percent) + xlab("") + ylab("") + theme(aspect.ratio=2.0) +
					 scale_x_discrete(labels = function(x) str_wrap(x, width = 20)) +

                     scale_fill_manual("",
					                   values=c(
									     Anders      = kleuren$rozig,
										 Antilliaans = kleuren$lichtblauwig,
										 Marrokaans  = kleuren$lichtrozig,
										 Nederlands  = kleuren$blauwig,
										 Surinaams   = kleuren$lichtgeel,
										 Turks       = kleuren$donkergroen))

                 }
)

plot <- plot +
  theme_classic() +
  theme(text=element_text(size=18,  family="karla")) +
  theme(axis.ticks.x=element_blank(), axis.ticks.y=element_blank(), axis.line=element_blank()) +
  ggtitle(TITEL)


writeImage(plot=plot, plotFolder=PLOTFOLDER,	plotFile=PLOTFILE,	width=WIDTH, height=HEIGHT, ppi=120)

#check deze: https://r-graph-gallery.com/48-grouped-barplot-with-ggplot2
