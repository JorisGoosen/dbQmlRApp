
basisGrootteText <- 5

#kolomnamen is een vector/lijst die genaamde elementen heeft, de namen zijn hoe de kolom moet heten in de output en de waardes is welke kolom uit de database gewenst is
laadKolommen <- function(kolomnamen, studenten)
{
  if(is.null(names(kolomnamen)))
    names(kolomnamen) <- kolomnamen
  
  # alle kolommen hier?
  if(length(intersect(kolomnamen, names(SchoolScannerTextOnlysql))) != length(kolomnamen))
    return(data.frame())
  
  kolommen <-
    if(is.null(studenten) | length(intersect(kolomnamen, 'type')) > 0)
      collect(SchoolScannerTextOnlysql %>%                                                select(all_of(kolomnamen)))
    else
      collect(SchoolScannerTextOnlysql %>% filter((type != "Docenten") == studenten)  %>% select(all_of(kolomnamen)))
  
  naamCultuur <- ""
  for(naam in names(kolomnamen))
  {
      if(kolomnamen[[naam]] == 'cultuur')
        naamCultuur <- naam
      
      if(sum(names(kolommen) == naam) == 0)
        kolommen[[naam]] <- rep('', nrow(kolommen))
  }
  
  if(naamCultuur != "" & nrow(kolommen) > 0)
  {
    kolommen[["TEMP"]] <- kolommen[[naamCultuur]]
    kolommen <- kolommen %>% rowwise() %>%
      mutate(TEMP=
        switch(tolower(TEMP),
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
    kolommen[[naamCultuur]] <- droplevels(factor(as.character(kolommen[["TEMP"]]), levels=c('Anders', 'Antilliaans', 'Marrokaans', 'Nederlands', 'Surinaams', 'Turks', '')))
    kolommen$TEMP <- NULL
  }
  
  
  #controleer of alle rijen iig iets van data hebben
  # als er ook maar 1 kolom leeg is gooien we de regel weg
  for(naam in names(kolomnamen))
  {
    uniek <- unique( kolommen[[naam]] )
    
    if(sum(uniek == "") == 1 & sum(uniek != "") == 0)
      return(kolommen %>% filter(FALSE))
    
    keepThese <- str_trim(kolommen[[naam]]) != ''
    kolommen <- kolommen[keepThese,]
  }
  
  return(kolommen)
}

herordenVaak <- function(kolom, heen=TRUE)
{
  vaak <- c( 'Altijd', 'Dagelijks', 'Wekelijks', 'Vaak', 'Maandelijks', 'Soms', 'Af & toe', 'Nooit', 'Nvt')
  
  if(heen)
    vaak <- rev(vaak)
  
  if(length(intersect(vaak, unique(kolom))) == 0)
    return(kolom)
  
  return(factor(as.character(kolom), levels=vaak))
}

isFilterSensible <- function(filter, studenten)
{
  if(filter == 'geen')
    return(TRUE)
  
  sum("" != laadKolommen(filter, studenten)[[filter]]) > 0
}

afronder <- function(plot, plotFolder, plotFile, width, height, titel, filter, bottomLegend=FALSE)
{
    plot <- plot +
  	  theme_classic() +
      theme(text=element_text(          size=18,  family="karla", color="black")) +
      theme(legend.text=element_text(   size=18,  family="karla", color="black")) +
      theme(text=element_text(          size=18,  family="karla", color="black")) +
      theme(axis.text.x = element_text( size=18,  family="karla", color="black", lineheight=.0)) +
      theme(axis.text.y = element_text( size=18,  family="karla", color="black", lineheight=.0)) +
  	  theme(axis.ticks.x=element_blank(), axis.ticks.y=element_blank(), axis.line=element_blank()) +

      theme(
        panel.background = element_rect(fill = "transparent",
                                        colour = NA_character_), # necessary to avoid drawing panel outline
        panel.grid.major = element_blank(), # get rid of major grid
        panel.grid.minor = element_blank(), # get rid of minor grid
        plot.background = element_rect(fill = "transparent",
                                       colour = NA_character_), # necessary to avoid drawing plot outline
       legend.background = element_rect(fill = "transparent")
        #legend.box.background = element_rect(fill = "transparent"),
       # legend.key = element_rect(fill = "transparent")
      )
    
    
    if(bottomLegend)
      plot <- plot + theme(legend.position="bottom") 
    
    if(titel != "")
      plot <- plot +  ggtitle(titel)

    writeImage(plot=plot, plotFolder=plotFolder,	plotFile=plotFile,	width=width, height=height)
    
    HEIGHT <<- height
    
    return(plot)
}

dummyPlot <- function(plotFolder, plotFile, width, height, filter, titel="Alle data is weggefilterd")
{

  afronder(plotFolder=plotFolder, plotFile=plotFile, width=width, height=200, filter=filter, titel="", 
           plot=ggplot() + 
             scale_y_continuous(breaks=NULL, labels=NULL) + scale_x_continuous(breaks=NULL, labels=NULL) + 
             xlab("") + ylab("") +
             theme(plot.title=element_text(hjust=0.5, vjust=0.5)) +
             ggtitle(paste(titel, plotFile))
          ) 
            
}

doeCMPalet <- function(hetPlot, aantalWaardes, tekst="")
{
  if(aantalWaardes < length(paletKleuren))
    return(hetPlot + scale_fill_manual(tekst, values=unname(paletKleuren)))
  
  return(hetPlot + scale_fill_manual(tekst, values=palet(aantalWaardes)))
}

procentAsY <- function()
{
  scale_y_continuous(labels = scales::percent, breaks=c(0, 0.25, 0.5, 0.75, 1), limits=c(0, 1)) 
}

HoriStaafPerLabelFunc <- function(plotFolder, plotFile, width, height, titel, kolom, filter, studenten, mbo=FALSE)
{
  if(!isFilterSensible(filter, studenten))
    return(dummyPlot(plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter))
  
  kolommen        <- laadKolommen(c(kolom, filter), studenten)
  
  if(nrow(kolommen) == 0)
    return(dummyPlot(plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter))
  
  tafelPerGender  <- table(kolommen)
  dfPer		        <- as.data.frame(tafelPerGender)

  hoeVaaks        <- levels(as.factor(kolommen[[kolom]]))
	genders         <- levels(as.factor(kolommen[[filter]]))
	dfGender	      <- table(kolommen[[filter]])

  dfPer[[kolom]]	<- factor(as.character(dfPer[[kolom]], rev(c("Nooit", "Soms", "Vaak", "Altijd"))))
	dfPer			      <- dfPer %>% rowwise() %>% select({{filter}}, {{kolom}}, Freq) %>%  mutate(`Hoe vaak` = Freq / dfGender[[filter]], Filter={{filter}}, kolom={{kolom}})
	dfPer			      <- dplyr::filter(dfPer, Filter != "")
  dfPer           <- arrange(dfPer, desc(kolom))

    afronder(
	    plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter, titel=titel,
		  plot=ggplot(dfPer, aes(x=Filter, y=`Hoe vaak`, fill=kolom)) + geom_bar(position=position_stack(reverse = TRUE), stat="identity") + coord_flip() +
		  procentAsY() + xlab("") + ylab("") + theme(aspect.ratio=0.3) +
		  scale_fill_manual(paste0("N: ", nrow(kolommen)), values=c(Altijd=kleuren$rozig, Vaak=kleuren$lichtblauwig, Soms=kleuren$lichtrozig, Nooit=kleuren$blauwig))
	)
}

HoriStaafMeerdereKolommenFunc <- function(plotFolder, plotFile, width, height, titel, kolom, filter, studenten, mbo=FALSE)
{
  if(!isFilterSensible(filter, studenten))
    return(dummyPlot(plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter))
  
  kolomnamen <- str_split_1(kolom, ',')
  kolommen   <- laadKolommen(kolomnamen, studenten)
  rijen      <- nrow(kolommen)
  
  if(nrow(kolommen) == 0)
    return(dummyPlot(plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter))
  
  mooieTitelAUB <- list(
    graagNaarSchool="Graag naar school",
    bangOpSchool="Bang op school",
    werkMetPlezier="Werk met plezier op school"
  )
  
  df <- NULL
  for(kolomnaam in kolomnamen)
  {
    dfHier <- as.data.frame(table(kolommen[[kolomnaam]]))
    dfHier$Kolom <- mooieTitelAUB[[kolomnaam]]
    
    if(is.null(df))
      df <- dfHier
    else
      df <- rbind(df, dfHier)
  }
  
  

  df <- df %>% rowwise() %>% select(Var1, Freq, Kolom) %>% mutate(`Procent`= Freq / rijen, `Hoe vaak`=Var1)
  
  #df <- dplyr::filter(df, `Hoe vaak` != "")
  
  df$`Hoe vaak` <- herordenVaak(df$`Hoe vaak`, FALSE)
  
  df <- arrange(df, desc(`Hoe vaak`))
  
  afronder(
    plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter, titel=titel,
    plot=ggplot(df, aes(x=Kolom, y=`Procent`, fill=`Hoe vaak`)) + theme(aspect.ratio=0.3) +
      geom_bar( stat="identity", na.rm=TRUE, position = position_stack(reverse = TRUE)) +
      coord_flip() +
      procentAsY() + xlab("") + ylab("") +
      scale_fill_manual(paste0("N: ", nrow(kolommen)), values=c(Altijd=kleuren$rozig, Vaak=kleuren$lichtblauwig, Soms=kleuren$lichtrozig, Nooit=kleuren$blauwig))
  )
}

HoriStaafGroepPerFilterFunc <- function(plotFolder, plotFile, width, height, titel, kolom, filter, studenten, mbo=FALSE)
{
  if(!isFilterSensible(filter, studenten))
    return(dummyPlot(plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter))
  
  allesPerCulturen <- laadKolommen(c(kolom=kolom, filter=filter), studenten)
  
  if(nrow(allesPerCulturen) == 0)
    return(dummyPlot(plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter))

  tafelTotaal       <- table(allesPerCulturen$filter)
	allesPerCultuur   <- allesPerCulturen %>% mutate(kolom=strsplit(kolom, ", ")) %>% unnest(kolom)
	tafelPerCultuur   <- table(allesPerCultuur)
	
  dfPer		          <- as.data.frame(tafelPerCultuur)

  hoeVaaks          <- levels(as.factor(allesPerCulturen$kolom))
	filters           <- levels(as.factor(allesPerCulturen$filter))
	dffilter	        <- table(allesPerCulturen$filter)
	
	dfPer <- dfPer %>% rowwise() %>% select(filter, kolom, Freq) %>% mutate(Procent = Freq / tafelTotaal[[filter]], totaalCultuur = tafelTotaal[[filter]])
	#dfPer <- dplyr::filter(dfPer, filter != "")
			 
	#if(kolom == 'onveiligHier' & length(hoeVaaks) > 1 ) #haal nergens onveilig weg want die verstoord alles alleen maar. Tenzij het de enige is...
	#  dfPer <- dplyr::filter(dfPer, kolom != "" & str_count(kolom, "nergens onveilig") == 0)
	dfPer$kolom <- herordenVaak(dfPer$kolom)

	
  dfPer <- arrange(dfPer, desc(kolom))
  
  hetPlot <- ggplot(dfPer, aes(x=kolom, y=Procent, fill=filter)) +
    geom_bar(position=position_dodge2(reverse=TRUE),stat="identity", width=1) +
    
    geom_text(size=basisGrootteText, aes(group=filter, label = ifelse(Freq > 0, paste0(round(Procent * 100, 1), "%"), ""), hjust=ifelse(Procent > 0.1, 1.1, -0.1)), vjust=0.4, position = position_dodge2(reverse=TRUE, width=1)) +
    geom_text(size=basisGrootteText-1,aes(group=filter, label = ifelse(Freq > 0, Freq, "")),
              hjust=1.1, vjust=0.4, y=0.0, position = position_dodge2(reverse=TRUE, width=1)) +
    
    coord_flip() +
    procentAsY() + xlab("") + ylab("") + theme(aspect.ratio=2.0) 
    #scale_x_discrete(labels = function(x) str_wrap(x, width = 20))
  
  hetPlot <- doeCMPalet(hetPlot, length(filters), paste0("N: ", nrow(allesPerCulturen)))
  
  bodemLegenda <- length(hoeVaaks) > 6
  
  height <- max(width / 4, 
                min(width * 4, 
                    floor(
                      (50) 
                      * length(unique(dfPer$kolom)) 
                      * length(unique(dfPer$filter))  
                      )
                    + ifelse(bodemLegenda, 150, 0)
                    + 150
               )
            )
  
  

  afronder(
    plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter, titel=titel, bottomLegend=bodemLegenda, plot=hetPlot
	)
}

HoriStaafPerTypeRespondentFunc <- function(plotFolder, plotFile, width, height, titel, kolom, filter, studenten, mbo=FALSE)
{
  studenten <- NULL
  
  if(!isFilterSensible(filter, studenten))
    return(dummyPlot(plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter))
  
    welkeKolommen <- 'ikMijn'

    kolommen <- switch(welkeKolommen,
	            klas        = c("klasJezelf", "klasSfeerGoed", "klasSchoolGemopper", "klasOpschietenMet", "klasGoedSamenWerken", "klasAfkomstKlit", "klasOnaardigGepraat", "klasVeelRuzie", "klasKunJeZeggenVervelend", "klasDurfUitDeKast", "klasKwetstMetMijnIdentiteit", "klasWeetHoeHetMetMijGaat", "klasVoeltOnveilig"),
						  studenten   = c("studentenBuitenGesloten", "studentenUitgescholden", "studentenExpresLesVerstoren", "studentenSpullenSlopenJatten", "studentenGepest", "studentenDigitaalGepest", "studentenGediscrimineerdDoorLeerlingen", "studentenGediscrimineerdDoorLeraren", "studentenBedreigdGeintimideerd", "studentenGeduwdGeschoptGeslagen", "studentenVechten", "studentenSeksueelGetinteOpmerkingenMaken", "studentenSeksueleAfbeeldingenVerspreiden", "studentenOnveiligVoelenInKlas"),
						  ikMijn      = c("ikBuitengesloten", "ikUitgescholden", "ikExpresGestoord", "ikGepest", "ikDigitaalGepest", "ikGediscrimineerdDoorLeerlingen", "ikGediscrimineerdDoorLeraren", "ikBedreigdGeintimideerd", "ikGeduwdGeschoptGeslagen", "ikUitgedaagdOmTeVechten", "ikAangesprokenMetSeksueelGetinteOpmerkingen", "ikAangesprokenOpVervelendGedrag", "mijnSpullenGeslooptGejat", "mijnPriveFotosVerspreid"),
						  school      = c("schoolVoeltOnveilig", "schoolJezelfZijn", "schoolSfeerIsGoed", "schoolRaadIkAan", "schoolStudentenGediscrimineerd", "schoolDiversVoeltThuis", "schoolGoedOpschietenElkaar", "schoolLiefstMetGelijkeAfkomstOm", "schoolAnderenVoorgetrokkenAfkomstCultuurGeloof", "schoolActueleGebeurtenissenMijAangaanBehandeldOpSchool", "schoolStudentenZittenOngewildAlleen"),
						  WerkSchool  = c("werkenSchoolDuidelijkeRegelsOmgang", "werkenSchoolRegelsIedereenGelijk", "werkenSchoolStudentenDieRegelsBrekenAangesproken", "werkenSchoolDocentenDieRegelsBrekenAangesproken", "werkenSchoolRegelsIedereDocentGelijk", "werkenSchoolOmbudBekend", "werkenSchoolMeningStudentenTelt", "werkenSchoolStudentenHebbenRespectVoorDocenten", "werkenSchoolDocentenHebbenRespectVoorStudenten", "werkenSchoolDocentenGevenGoedeVoorbeeld"),
						  vervelend   = c("vervelendDanGaIkHelpen", "vervelendDanKijkIkWeg", "vervelendDanLoopIkWeg", "vervelendDanDoeIkMee", "vervelendDanZegIkErWatVan", "vervelendDanWaarschuwIkSchoolMedewerker", "vervelendDanLaatIkMedelevenWeten", "vervelendDanZieIkDatAndereStudentIngrijpt", "vervelendDanZieIkDatDocentIngrijpt", "vervelendDanZieIkDatAfdelingsleiderIngrijpt","alsIkVervelendeSituatieZieDanVindIkDatIkWatMoetDoen", "alsIkVervelendeSituatieZieDanWeetIkWatIkKanDoen"),
						  buitensluit = c("alsEenStudentWordtBuitengeslotenDanIsDatEigenKeuze", "alsEenStudentWordtBuitengeslotenDanIsDatEigenSchuld", "voelMeVerantwoordelijkOmBuitensluitenTegenTeGaan", "voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGediscrimineerd", "voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGepest", "ikStuurWelEensPrivefotosAnderenDoorOfIkGrijpIn"),
						  mentor      = c("mentorIkHebGoedContact", "docentIkHebGoedContact", "docentenKunnenGoedOrdeHouden", "docentenGevenMijComplimenten", "docentenHebbenLageVerwachtingVanMij", "docentenLettenOpTaalgebruikStudenten", "docentenlettenOpEigenTaalgebruik", "docentenBelonenPositiefGedrag", "docentenGrijpenInWanneerDatNodigIs", "mentorenWetenWatErInDeKlasSpeelt", "mentorenBespreektWatErInDeKlasSpeelt", "actueleGebeurtenissenSamenlevingWordenInKlasBesproken"))

#    titel <- switch(welkeKolommen,
#	        klas        = "In de klas...",
#					studenten   = "Bij mij in de klas/op school zie ik dat andere studenten...",
#					ikMijn      = "In de klas/op school word ik/worden mijn... ",
#					school     = "Op school...",
#					vervelend   = "Als iemand vervelend doet tegen een klasgenoot dan...",
#					buitensluit = "Bij buitensluiting...",
#					mentor      = "Docenten & mentoren")
#
    allesPerType <- laadKolommen(c("type", kolommen), studenten=NULL)
    
    if(nrow(allesPerType) == 0)
      return(dummyPlot(plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter))


    renamer <- switch(welkeKolommen,
	          klas        = c(`kun je jezelf zijn`='klasJezelf',  `is de sfeer goed`='klasSfeerGoed',  `wordt gemopperd over school`='klasSchoolGemopper',  `kan ik goed opschieten met klasgenoten`='klasOpschietenMet',  `kunnen we goed samenwerken`='klasGoedSamenWerken',  `ga ik het liefst om met degene met dezelfde afkomst`='klasAfkomstKlit',  `hoor ik onaardig gepraat over elkaar`='klasOnaardigGepraat',  `is veel ruzie`='klasVeelRuzie',  `kun je er wat van zeggen als iemand vervelend tegen je doet`='klasKunJeZeggenVervelend',  `zou ik uit de kast durven komen`='klasDurfUitDeKast',  `worden kwetsende opmerkingen gemaakt over mijn identiteit`='klasKwetstMetMijnIdentiteit',  `weet men hoe het met mij gaat`='klasWeetHoeHetMetMijGaat',  `voelt het onveilig`='klasVoeltOnveilig'),
					  studenten   = c(`worden buitengesloten`='studentenBuitenGesloten',  `worden uitgescholden`='studentenUitgescholden',  `met opzet de les verstoren`='studentenExpresLesVerstoren',  `spullen slopen of jatten`='studentenSpullenSlopenJatten',  `worden gepest`='studentenGepest',  `digitaal worden gepest`='studentenDigitaalGepest',  `worden gediscrimineerd door leerlingen`='studentenGediscrimineerdDoorLeerlingen',  `worden gediscrimineerd door leraren`='studentenGediscrimineerdDoorLeraren',  `worden bedreigd of geintimideerd`='studentenBedreigdGeintimideerd',  `worden geschopt of geslagen`='studentenGeduwdGeschoptGeslagen',  `vechten`='studentenVechten',  `seksueel getinte opmerkingen maken`='studentenSeksueelGetinteOpmerkingenMaken',  `seksuele afbeeldingen verspreiden`='studentenSeksueleAfbeeldingenVerspreiden',  `onveilig voelen in de klas`='studentenOnveiligVoelenInKlas'),
					  ikMijn      = c(`buitengesloten`='ikBuitengesloten',  `uitgescholden`='ikUitgescholden',  `met opzet gestoord`='ikExpresGestoord',  `gepest`='ikGepest',  `digitaal gepest`='ikDigitaalGepest',  `gediscrimineerd door leerlingen`='ikGediscrimineerdDoorLeerlingen',  `gediscrimineerd door leraren`='ikGediscrimineerdDoorLeraren',  `bedreigd of geintimideerd`='ikBedreigdGeintimideerd',  `geduwd, geschopt of geslagen`='ikGeduwdGeschoptGeslagen',  `uitgedaagd om te vechten`='ikUitgedaagdOmTeVechten',  `aangesproken met seksueel getinte opmerkingen`='ikAangesprokenMetSeksueelGetinteOpmerkingen',  `aangesproken op vervelend gedrag`='ikAangesprokenOpVervelendGedrag',  `spullen gesloopt of gejat`='mijnSpullenGeslooptGejat',  `prive fotos verspreid`='mijnPriveFotosVerspreid'),
					  school      = c(`voelt het onveilig`='schoolVoeltOnveilig',  `kun je jezelf zijn`='schoolJezelfZijn',  `is de sfeer goed`='schoolSfeerIsGoed',  `zou ik aanraden`='schoolRaadIkAan',  `leerlingen gediscrimineerd`='schoolStudentenGediscrimineerd',  `voelen mensen van verschillende afkomsten zich thuis`='schoolDiversVoeltThuis',  `kunnen leerlingen goed opschieten met elkaar`='schoolGoedOpschietenElkaar',  `gaan leerlingen het liefst om met anderen van dezelfde afkomst`='schoolLiefstMetGelijkeAfkomstOm',  `worden anderen voorgetrokken op basis afkomst, cultuur of geloof`='schoolAnderenVoorgetrokkenAfkomstCultuurGeloof',  `komen actuele gebeurtenissen die mij aangaan aan bod`='schoolActueleGebeurtenissenMijAangaanBehandeldOpSchool',  `zitten leerlingen ongewild alleen`='schoolStudentenZittenOngewildAlleen'),
					  vervelend   = c(`ga ik helpen`='vervelendDanGaIkHelpen',  `kijk ik weg`='vervelendDanKijkIkWeg',  `loop ik weg`='vervelendDanLoopIkWeg',  `doe ik mee`='vervelendDanDoeIkMee',  `zeg ik er wat van`='vervelendDanZegIkErWatVan',  `waarschuw ik een schoolmedewerker`='vervelendDanWaarschuwIkSchoolMedewerker',  `laat ik medeleven weten`='vervelendDanLaatIkMedelevenWeten',  `zie ik dat andere leerling ingrijpt`='vervelendDanZieIkDatAndereStudentIngrijpt',  `zie ik dat docent ingrijpt`='vervelendDanZieIkDatDocentIngrijpt',  `zie ik dat afdelingsleider ingrijpt`='vervelendDanZieIkDatAfdelingsleiderIngrijpt', `vind ik dat ik wat moet doen`='alsIkVervelendeSituatieZieDanVindIkDatIkWatMoetDoen',  `weet ik wat ik moet doen`='alsIkVervelendeSituatieZieDanWeetIkWatIkKanDoen'),
					  buitensluit = c(`is dat de eigen keuze`='alsEenStudentWordtBuitengeslotenDanIsDatEigenKeuze',  `is dat de eigen schuld`='alsEenStudentWordtBuitengeslotenDanIsDatEigenSchuld',  `voel ik me verantwoordelijk dat tegen te gaan`='voelMeVerantwoordelijkOmBuitensluitenTegenTeGaan',  `door discriminatie voel ik me verantwoordelijk om in te grijpen`='voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGediscrimineerd',  `door pesten voel ik me verantwoordelijk om in te grijpen`='voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGepest',  `.. stuur ik wel eens prive fotos van anderen door`='ikStuurWelEensPrivefotosAnderenDoorOfIkGrijpIn'),
					  mentor      = c(`Ik heb goed contact met mijn mentor`='mentorIkHebGoedContact',  `Ik heb goed contact met mijn docent`='docentIkHebGoedContact',  `Docenten kunnen goed orde houden`='docentenKunnenGoedOrdeHouden',  `Docenten geven mij complimenten`='docentenGevenMijComplimenten',  `Docenten hebben lage verwachting van mij`='docentenHebbenLageVerwachtingVanMij',  `Docenten letten op taalgebruik van de leerlingen`='docentenLettenOpTaalgebruikStudenten',  `Docenten letten op eigen taalgebruik`='docentenlettenOpEigenTaalgebruik',  `Docenten belonen positief gedrag`='docentenBelonenPositiefGedrag',  `Docenten grijpen in wanneer dat nodig is`='docentenGrijpenInWanneerDatNodigIs',  `Mentoren weten wat er in de klas speelt`='mentorenWetenWatErInDeKlasSpeelt',  `Mentoren bespreekt wat er in de klas speelt`='mentorenBespreektWatErInDeKlasSpeelt',  `Actuele gebeurtenissen samenleving worden in klas besproken`='actueleGebeurtenissenSamenlevingWordenInKlasBesproken')
	)

  tafelTotaal      <- table(allesPerType$type)
  
  allesPerType <- allesPerType %>% mutate_at(kolommen, funs(sapply(., function(x) {switch(x, FALSE, Dagelijks=TRUE, Wekelijks=TRUE, Altijd=TRUE, Vaak=TRUE)})))
  
  allesPerType <- rename(allesPerType, all_of(renamer))
  
  allesPerType <- allesPerType %>% pivot_longer(!type)
  allesPerType <- dplyr::filter(allesPerType, value)


  tafelPerType  <- table(allesPerType)
  
  dfPer		    <- as.data.frame(tafelPerType)
  
  
  #dfPer$onveiligHier <- factor(as.character(dfPer$onveiligHier), rev(c("Nooit", "Soms", "Vaak", "Altijd")))
  dfPer           <- dfPer %>% rowwise() %>% select(type, name, Freq) %>%
  mutate(Freq = Freq / tafelTotaal[[type]], type=type, totaalType = tafelTotaal[[type]])
  dfPer <- dplyr::filter(dfPer, type != "")

  # dfPer <- arrange(dfPer, desc(name))

  afronder(
    plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter, titel=titel,
		plot=ggplot(dfPer, aes(x=name, y=Freq, fill=type)) +
		  geom_bar(position=position_dodge2(reverse=TRUE),stat="identity", width=1) +
      geom_text(size=basisGrootteText,aes(group=type, label = paste0(round(Freq * 100), "%")), hjust=ifelse(dfPer$Freq < 0.9, 1.1, -0.1), vjust=0.4, position = position_dodge2(reverse=TRUE, width=1)) +
		  geom_text(size=basisGrootteText,aes(group=type, label =
		                         ifelse(Freq > 0.01,
								        paste0("N: ", totaalType),
										"")),
									   hjust=-0.1, vjust=0.4, y=0.0, position = position_dodge2(reverse=TRUE, width=1)) +
      coord_flip() +
		  procentAsY() + xlab("") + ylab("") + theme(aspect.ratio=2.0) +
		  scale_x_discrete(labels = function(x) str_wrap(x, width = 30)) +
      scale_fill_manual(paste0("N: ", nrow(allesPerType)),
	             values=c(
							  Leerlingen  = kleuren$rozig,
							  Docenten     = kleuren$lichtblauwig,
							  Studenten   = kleuren$lichtrozig))
	)
}

VerticaalStaafFunc <- function(plotFolder, plotFile, width, height, titel, kolom, filter, studenten, mbo=FALSE)
{
  if(!isFilterSensible(filter, studenten))
    return(dummyPlot(plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter))

  if(filter == 'geen')
    return(dummyPlot(titel="Kan niet zonder filter", plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter))
  
  kolommen   <- laadKolommen(c(kolom, filter), studenten)
  deKolommen <- dplyr::filter(kolommen, .data[[filter]] != "" & .data[[kolom]] != "")
  
  if(nrow(deKolommen) == 0)
    return(dummyPlot(plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter))
  
  df              <- as.data.frame(table(deKolommen))
  tafelPerFilter  <- table(deKolommen[[filter]])
  perFilter       <- as.data.frame(tafelPerFilter)
  df$totaal       <- tafelPerFilter[df[[filter]]]
  df$`Procent`    <- df$Freq / df$totaal
  
  # df <- df %>% rowwise() %>% select({{kolom}}, Freq, {{filter}}) %>% mutate(`Procent`= Freq / tafelPerFilter[[filter]])

  df[[kolom]] <- factor(as.character(df[[kolom]]), (c('1', '2', '3', '4', '5', '6', '7', '8', '9', '10')))
  
  # df <- arrange(df, desc(filter))
  # print(deKolommen[[kolom]])

  hetPlot <-       ggplot(df, aes(x=.data[[kolom]], y=`Procent`, fill=.data[[filter]])) +
  	geom_bar( stat="identity", na.rm=TRUE, position = position_dodge2(reverse=FALSE, width=1)) +
  	# coord_flip() +
    procentAsY() + xlab(str_to_title(filter)) + #ylab("") +
  	geom_text(size=basisGrootteText, aes(y = `Procent`, label=ifelse(Freq>0, Freq, '')), vjust=-0.5, position=position_dodge2(reverse=FALSE, width=1))# +
    ##  geom_text(size=4, aes(y = 0, label={{kolom}}), vjust=-0.5,  position=position_dodge2(reverse=TRUE, width=1))
  
  hetPlot <- doeCMPalet(hetPlot, length(unique(df[[filter]])), paste0("N: ", length(deKolommen[[kolom]])))

  afronder(
    plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter, titel=titel,
	plot=hetPlot

  )
}

TaartFunc <- function(plotFolder, plotFile, width, height, titel, kolom, filter, studenten, mbo=FALSE)
{
  if(!isFilterSensible(filter, studenten))
    return(dummyPlot(plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter))
  
  deKolom             <- laadKolommen(c(kolom), studenten)
  deKolom[["kolom"]]  <- deKolom[[kolom]]
  deKolom[[kolom]]    <- NULL
  
  levelsHier <- c('1', '2', '3', '4', '5', '6', '7', '8', '9', '10')
  
  df       <- dplyr::filter(deKolom, kolom != "")
  totaal   <- length(df$kolom)
  df$kolom <- factor(as.character(df$kolom), levels=levelsHier)
  df       <- as.data.frame(table(df))
  
  if(nrow(df) == 0)
    return(dummyPlot(plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter))
  
  df <- df %>% rowwise() %>% select(kolom, Freq) %>% mutate(Procent= Freq / totaal)
  
  df <- arrange(df, kolom)
  
  df$cumProcent <- cumsum(df$Procent)
  
  df <- df %>% mutate(middlePoint=cumProcent - (Procent / 2)) %>% mutate(angleData=middlePoint * -360) %>% mutate(angleData=ifelse(angleData < -180, angleData - 90, angleData + 90))
  
  afronder(
    plotFolder=plotFolder, plotFile=plotFile, width=width, height=height, filter=filter, titel=titel,
    plot=ggplot(df, aes(x="", y=Freq, fill=kolom)) + 
      geom_bar( stat="identity", position = position_stack(reverse = TRUE)) +
      # coord_flip() +
      scale_y_continuous(breaks=NULL, labels=NULL) + 
      xlab("") + ylab("") +
      scale_fill_manual(paste0("N: ", totaal), values=
                          c(`1`=kleuren$zwartig, `2`=kleuren$lichtgeel, `3`=kleuren$blauwig, `4`=kleuren$lichtrozig, `5`=kleuren$donkergroen, 
                            `6`=kleuren$lichtgeel, `7`=kleuren$blauwig, `8`=kleuren$lichtrozig, `9`=kleuren$lichtgroen, `10`=kleuren$rozig )) +
      
      geom_text(size=basisGrootteText, aes(x=1.6, y = middlePoint * totaal, label=ifelse(Freq > 0, paste0(kolom, ": ", Freq), ""), angle=angleData)) +
      geom_text(size=basisGrootteText, aes(x=1.3, y = (middlePoint) * totaal, label=ifelse(Procent > 0.01, sprintf("%2.1f%%", Procent * 100.), ""), angle=angleData)) +
      coord_polar("y", start=0) 
  )
}
