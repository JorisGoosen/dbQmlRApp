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

                 },
				 horizontaalLabelPerTypeRespondent=
				 {
				 welkeKolommen <- 'ikMijn'

                 kolommen <- switch(welkeKolommen,
				                       klas        = c("klasJezelf", "klasSfeerGoed", "klasSchoolGemopper", "klasOpschietenMet", "klasGoedSamenWerken", "klasAfkomstKlit", "klasOnaardigGepraat", "klasVeelRuzie", "klasKunJeZeggenVervelend", "klasDurfUitDeKast", "klasKwetstMetMijnIdentiteit", "klasWeetHoeHetMetMijGaat", "klasVoeltOnveilig"),
									   studenten   = c("studentenBuitenGesloten", "studentenUitgescholden", "studentenExpresLesVerstoren", "studentenSpullenSlopenJatten", "studentenGepest", "studentenDigitaalGepest", "studentenGediscrimineerdDoorLeerlingen", "studentenGediscrimineerdDoorLeraren", "studentenBedreigdGeintimideerd", "studentenGeduwdGeschoptGeslagen", "studentenVechten", "studentenSeksueelGetinteOpmerkingenMaken", "studentenSeksueleAfbeeldingenVerspreiden", "studentenOnveiligVoelenInKlas"),
									   ikMijn      = c("ikBuitengesloten", "ikUitgescholden", "ikExpresGestoord", "ikGepest", "ikDigitaalGepest", "ikGediscrimineerdDoorLeerlingen", "ikGediscrimineerdDoorLeraren", "ikBedreigdGeintimideerd", "ikGeduwdGeschoptGeslagen", "ikUitgedaagdOmTeVechten", "ikAangesprokenMetSeksueelGetinteOpmerkingen", "ikAangesprokenOpVervelendGedrag", "mijnSpullenGeslooptGejat", "mijnPriveFotosVerspreid"),
									   school      = c("schoolVoeltOnveilig", "schoolJezelfZijn", "schoolSfeerIsGoed", "schoolRaadIkAan", "schoolStudentenGediscrimineerd", "schoolDiversVoeltThuis", "schoolGoedOpschietenElkaar", "schoolLiefstMetGelijkeAfkomstOm", "schoolAnderenVoorgetrokkenAfkomstCultuurGeloof", "schoolActueleGebeurtenissenMijAangaanBehandeldOpSchool", "schoolStudentenZittenOngewildAlleen"),
									   WerkSchool  = c("werkenSchoolDuidelijkeRegelsOmgang", "werkenSchoolRegelsIedereenGelijk", "werkenSchoolStudentenDieRegelsBrekenAangesproken", "werkenSchoolDocentenDieRegelsBrekenAangesproken", "werkenSchoolRegelsIedereDocentGelijk", "werkenSchoolOmbudBekend", "werkenSchoolMeningStudentenTelt", "werkenSchoolStudentenHebbenRespectVoorDocenten", "werkenSchoolDocentenHebbenRespectVoorStudenten", "werkenSchoolDocentenGevenGoedeVoorbeeld"),
									   vervelend   = c("vervelendDanGaIkHelpen", "vervelendDanKijkIkWeg", "vervelendDanLoopIkWeg", "vervelendDanDoeIkMee", "vervelendDanZegIkErWatVan", "vervelendDanWaarschuwIkSchoolMedewerker", "vervelendDanLaatIkMedelevenWeten", "vervelendDanZieIkDatAndereStudentIngrijpt", "vervelendDanZieIkDatDocentIngrijpt", "vervelendDanZieIkDatAfdelingsleiderIngrijpt","alsIkVervelendeSituatieZieDanVindIkDatIkWatMoetDoen", "alsIkVervelendeSituatieZieDanWeetIkWatIkKanDoen"),
									   buitensluit = c("alsEenStudentWordtBuitengeslotenDanIsDatEigenKeuze", "alsEenStudentWordtBuitengeslotenDanIsDatEigenSchuld", "voelMeVerantwoordelijkOmBuitensluitenTegenTeGaan", "voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGediscrimineerd", "voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGepest", "ikStuurWelEensPrivefotosAnderenDoor"),
									   mentor      = c("mentorIkHebGoedContact", "docentIkHebGoedContact", "docentenKunnenGoedOrdeHouden", "docentenGevenMijComplimenten", "docentenHebbenLageVerwachtingVanMij", "docentenLettenOpTaalgebruikStudenten", "docentenlettenOpEigenTaalgebruik", "docentenBelonenPositiefGedrag", "docentenGrijpenInWanneerDatNodigIs", "mentorenWetenWatErInDeKlasSpeelt", "mentorenBespreektWatErInDeKlasSpeelt", "actueleGebeurtenissenSamenlevingWordenInKlasBesproken"))

                 TITEL <- switch(welkeKolommen,
				                 klas.       = "In de klas...",
								 studenten   = "Bij mij in de klas/op school zie ik dat andere studenten...",
								 ikMijn      = "In de klas/op school word ik/worden mijn... ",
								 school.     = "Op school...",
								 vervelend   = "Als iemand vervelend doet tegen een klasgenoot dan...",
								 buitensluit = "Bij buitensluiting...",
								 mentor      = "Docenten & mentoren")

                 allesPerType <- SchoolScannerTextOnly[c("type", kolommen)]


                 renamer <- switch(welkeKolommen,
				                   klas        = c(`kun je jezelf zijn`='klasJezelf',  `is de sfeer goed`='klasSfeerGoed',  `wordt gemopperd over school`='klasSchoolGemopper',  `kan ik goed opschieten met klasgenoten`='klasOpschietenMet',  `kunnen we goed samenwerken`='klasGoedSamenWerken',  `ga ik het liefst om met degene met dezelfde afkomst`='klasAfkomstKlit',  `hoor ik onaardig gepraat over elkaar`='klasOnaardigGepraat',  `is veel ruzie`='klasVeelRuzie',  `kun je er wat van zeggen als iemand vervelend tegen je doet`='klasKunJeZeggenVervelend',  `zou ik uit de kast durven komen`='klasDurfUitDeKast',  `worden kwetsende opmerkingen gemaakt over mijn identiteit`='klasKwetstMetMijnIdentiteit',  `weet men hoe het met mij gaat`='klasWeetHoeHetMetMijGaat',  `voelt het onveilig`='klasVoeltOnveilig'),
								   studenten   = c(`worden buitengesloten`='studentenBuitenGesloten',  `worden uitgescholden`='studentenUitgescholden',  `met opzet de les verstoren`='studentenExpresLesVerstoren',  `spullen slopen of jatten`='studentenSpullenSlopenJatten',  `worden gepest`='studentenGepest',  `digitaal worden gepest`='studentenDigitaalGepest',  `worden gediscrimineerd door leerlingen`='studentenGediscrimineerdDoorLeerlingen',  `worden gediscrimineerd door leraren`='studentenGediscrimineerdDoorLeraren',  `worden bedreigd of geintimideerd`='studentenBedreigdGeintimideerd',  `worden geschopt of geslagen`='studentenGeduwdGeschoptGeslagen',  `vechten`='studentenVechten',  `seksueel getinte opmerkingen maken`='studentenSeksueelGetinteOpmerkingenMaken',  `seksuele afbeeldingen verspreiden`='studentenSeksueleAfbeeldingenVerspreiden',  `onveilig voelen in de klas`='studentenOnveiligVoelenInKlas'),
								   ikMijn      = c(`buitengesloten`='ikBuitengesloten',  `uitgescholden`='ikUitgescholden',  `met opzet gestoord`='ikExpresGestoord',  `gepest`='ikGepest',  `digitaal gepest`='ikDigitaalGepest',  `gediscrimineerd door leerlingen`='ikGediscrimineerdDoorLeerlingen',  `gediscrimineerd door leraren`='ikGediscrimineerdDoorLeraren',  `bedreigd of geintimideerd`='ikBedreigdGeintimideerd',  `geduwd, geschopt of geslagen`='ikGeduwdGeschoptGeslagen',  `uitgedaagd om te vechten`='ikUitgedaagdOmTeVechten',  `aangesproken met seksueel getinte opmerkingen`='ikAangesprokenMetSeksueelGetinteOpmerkingen',  `aangesproken op vervelend gedrag`='ikAangesprokenOpVervelendGedrag',  `spullen gesloopt of gejat`='mijnSpullenGeslooptGejat',  `prive fotos verspreid`='mijnPriveFotosVerspreid'),
								   school      = c(`voelt het onveilig`='schoolVoeltOnveilig',  `kun je jezelf zijn`='schoolJezelfZijn',  `is de sfeer goed`='schoolSfeerIsGoed',  `zou ik aanraden`='schoolRaadIkAan',  `leerlingen gediscrimineerd`='schoolStudentenGediscrimineerd',  `voelen mensen van verschillende afkomsten zich thuis`='schoolDiversVoeltThuis',  `kunnen leerlingen goed opschieten met elkaar`='schoolGoedOpschietenElkaar',  `gaan leerlingen het liefst om met anderen van dezelfde afkomst`='schoolLiefstMetGelijkeAfkomstOm',  `worden anderen voorgetrokken op basis afkomst, cultuur of geloof`='schoolAnderenVoorgetrokkenAfkomstCultuurGeloof',  `komen actuele gebeurtenissen die mij aangaan aan bod`='schoolActueleGebeurtenissenMijAangaanBehandeldOpSchool',  `zitten leerlingen ongewild alleen`='schoolStudentenZittenOngewildAlleen'),
								   vervelend   = c(`ga ik helpen`='vervelendDanGaIkHelpen',  `kijk ik weg`='vervelendDanKijkIkWeg',  `loop ik weg`='vervelendDanLoopIkWeg',  `doe ik mee`='vervelendDanDoeIkMee',  `zeg ik er wat van`='vervelendDanZegIkErWatVan',  `waarschuw ik een schoolmedewerker`='vervelendDanWaarschuwIkSchoolMedewerker',  `laat ik medeleven weten`='vervelendDanLaatIkMedelevenWeten',  `zie ik dat andere leerling ingrijpt`='vervelendDanZieIkDatAndereStudentIngrijpt',  `zie ik dat docent ingrijpt`='vervelendDanZieIkDatDocentIngrijpt',  `zie ik dat afdelingsleider ingrijpt`='vervelendDanZieIkDatAfdelingsleiderIngrijpt', `vind ik dat ik wat moet doen`='alsIkVervelendeSituatieZieDanVindIkDatIkWatMoetDoen',  `weet ik wat ik moet doen`='alsIkVervelendeSituatieZieDanWeetIkWatIkKanDoen'),
								   buitensluit = c(`is dat de eigen keuze`='alsEenStudentWordtBuitengeslotenDanIsDatEigenKeuze',  `is dat de eigen schuld`='alsEenStudentWordtBuitengeslotenDanIsDatEigenSchuld',  `voel ik me verantwoordelijk dat tegen te gaan`='voelMeVerantwoordelijkOmBuitensluitenTegenTeGaan',  `door discriminatie voel ik me verantwoordelijk om in te grijpen`='voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGediscrimineerd',  `door pesten voel ik me verantwoordelijk om in te grijpen`='voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGepest',  `.. stuur ik wel eens prive fotos van anderen door`='ikStuurWelEensPrivefotosAnderenDoor'),
								   mentor      = c(`Ik heb goed contact met mijn mentor`='mentorIkHebGoedContact',  `Ik heb goed contact met mijn docent`='docentIkHebGoedContact',  `Docenten kunnen goed orde houden`='docentenKunnenGoedOrdeHouden',  `Docenten geven mij complimenten`='docentenGevenMijComplimenten',  `Docenten hebben lage verwachting van mij`='docentenHebbenLageVerwachtingVanMij',  `Docenten letten op taalgebruik van de leerlingen`='docentenLettenOpTaalgebruikStudenten',  `Docenten letten op eigen taalgebruik`='docentenlettenOpEigenTaalgebruik',  `Docenten belonen positief gedrag`='docentenBelonenPositiefGedrag',  `Docenten grijpen in wanneer dat nodig is`='docentenGrijpenInWanneerDatNodigIs',  `Mentoren weten wat er in de klas speelt`='mentorenWetenWatErInDeKlasSpeelt',  `Mentoren bespreekt wat er in de klas speelt`='mentorenBespreektWatErInDeKlasSpeelt',  `Actuele gebeurtenissen samenleving worden in klas besproken`='actueleGebeurtenissenSamenlevingWordenInKlasBesproken')
				 )

                 tafelTotaal      <- table(allesPerType$type)

                 allesPerType <- allesPerType %>% mutate_at(kolommen, funs(sapply(., function(x) {switch(x, FALSE, Dagelijks=TRUE, Wekelijks=TRUE, Altijd=TRUE, Vaak=TRUE)})))

                 allesPerType <- rename(allesPerType, all_of(renamer))

                 allesPerType <- allesPerType %>% pivot_longer(!type)
				 allesPerType <- filter(allesPerType, value)


                 tafelPerType  <- table(allesPerType)

                 dfPer		    <- as.data.frame(tafelPerType)


                 #dfPer$onveiligHier <- factor(as.character(dfPer$onveiligHier), rev(c("Nooit", "Soms", "Vaak", "Altijd")))
				 dfPer           <- dfPer %>% rowwise() %>% select(type, name, Freq) %>%
				   mutate(Freq = Freq / tafelTotaal[[type]], type=type, totaalType = tafelTotaal[[type]])
				 dfPer <- filter(dfPer, type != "")



                # dfPer <- arrange(dfPer, desc(name))

                 ggplot(dfPer, aes(x=name, y=Freq, fill=type)) +
				   geom_bar(position=position_dodge2(reverse=TRUE),stat="identity", width=1) +

                   geom_text(size=3,aes(group=type, label = paste0(round(Freq * 100), "%")), hjust=-0.1, vjust=0.4, position = position_dodge2(reverse=TRUE, width=1)) +
				   geom_text(size=3,aes(group=type, label =
				                          ifelse(Freq > 0.01,
										         paste0("N: ", totaalType),
												 "")),
												hjust=-0.1, vjust=0.4, y=0.0, position = position_dodge2(reverse=TRUE, width=1)) +

                   coord_flip() +
				   scale_y_continuous(labels = scales::percent) + xlab("") + ylab("") + theme(aspect.ratio=2.0) +
				   scale_x_discrete(labels = function(x) str_wrap(x, width = 20)) +

                   scale_fill_manual("",
				                     values=c(
									   Leerlingen  = kleuren$rozig,
									   Docenten     = kleuren$lichtblauwig,
									   Studenten   = kleuren$lichtrozig))
}
)

plot <- plot +
  theme_classic() +
  theme(text=element_text(size=18,  family="karla")) +
  theme(axis.ticks.x=element_blank(), axis.ticks.y=element_blank(), axis.line=element_blank()) +
  ggtitle(TITEL)


writeImage(plot=plot, plotFolder=PLOTFOLDER,	plotFile=PLOTFILE,	width=WIDTH, height=HEIGHT, ppi=120)

#check deze: https://r-graph-gallery.com/48-grouped-barplot-with-ggplot2
