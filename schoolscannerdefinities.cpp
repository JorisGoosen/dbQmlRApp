#include "schoolscannerdefinities.h"

typedef ColumnDefinition	CD;

const QString SchoolScannerDefinities::_tableName = "SchoolScanner";

ColumnDefinitions * SchoolScannerDefinities::_columnDefsText = nullptr;

const ColumnDefinitions & SchoolScannerDefinities::columnDefsText()
{
	if(!_columnDefsText)
	{
		_columnDefsText = new ColumnDefinitions;

		for(CD * cd : _columnDefs)
			_columnDefsText->push_back(new ColumnDefinition(cd->friendlyName(), cd->dbName(), ColumnType::Text));
	}

	return *_columnDefsText;
}

const ColumnDefinitions SchoolScannerDefinities::_columnDefs =
{

	new CD("Tijdstempel",																														"timestamp",															ColumnType::DateTime	),
	new CD("Wat is de datum?",																													"datum",																ColumnType::Date		),
	new CD("Type respondent",																													"type",																	ColumnType::Label   	),
	new CD("Ben je een jongen of meisje?",																										"gender",																ColumnType::Label   	),
	new CD("Wat is jouw culturele achtergrond?",																								"cultuur",																ColumnType::Labels    	),
	new CD("Op welke school zit je?",																											"school",																ColumnType::Label   	),
	new CD("Schooltype",																														"schoolType",															ColumnType::Label   	),
	new CD("Op welke school/locatie heb je les?",																								"locatie",																ColumnType::Label   	),
	new CD("Welke opleiding volg je?",																											"opleiding",															ColumnType::Label    	),
	new CD("Onder welke sector valt jouw opleiding?",																							"sector",																ColumnType::Label    	),
	new CD("In welk jaar zit je?",																												"jaar",																	ColumnType::Label   	),
	new CD("In welke klas zit je?",																												"klas",																	ColumnType::Label    	),
	new CD("Welk opleidingstraject volg je?",																									"opleidingstraject",													ColumnType::Label    	),
	new CD("Welk niveau volg je?",																												"niveau",																ColumnType::Label   	),
	new CD("Ik voel me veilig  [Ik voel me veilig op school]",																					"veiligSchool",															ColumnType::NumInt  	),
	new CD("Ik voel me veilig  [Ik voel me veilig in de klas]",																					"veiligKlas",															ColumnType::NumInt     	),
	new CD("Ik voel me onveilig in/op/bij",																										"onveiligHier",															ColumnType::Labels    	),
	new CD(" [Ik ben wel eens bang op school]",																									"bangOpSchool",															ColumnType::Label		),
	new CD(" [Ik ga graag naar school]",																										"graagNaarSchool",														ColumnType::Label		),
	new CD("2. In de klas [In onze klas kun je jezelf zijn]",																					"klasJezelf",															ColumnType::Label		),
	new CD("2. In de klas [De sfeer in de klas is goed]",																						"klasSfeerGoed",														ColumnType::Label		),
	new CD("2. In de klas [Er wordt in mijn klas gemopperd over school]",																		"klasSchoolGemopper",													ColumnType::Label		),
	new CD("2. In de klas [Ik kan goed opschieten met mijn klasgenoten]",																		"klasOpschietenMet",													ColumnType::Label		),
	new CD("2. In de klas [In de klas kunnen we goed met elkaar samenwerken]",																	"klasGoedSamenWerken",													ColumnType::Label		),
	new CD("2. In de klas [In de klas ga ik het liefst om met studenten die dezelfde afkomst hebben als ik]",									"klasAfkomstKlit",														ColumnType::Label		),
	new CD("2. In de klas [In de klas hoor ik dat studenten onaardig over elkaar spreken]",														"klasOnaardigGepraat",													ColumnType::Label		),
	new CD("2. In de klas [In de klas wordt veel ruzie gemaakt]",																				"klasVeelRuzie",														ColumnType::Label		),
	new CD("2. In de klas [Als iemand vervelend tegen je doet, kun je er wat van zeggen]",														"klasKunJeZeggenVervelend",												ColumnType::Label		),
	new CD("2. In de klas [Als ik homo of lesbisch zou zijn, dan mogen klasgenoten dat weten]",													"klasDurfUitDeKast",													ColumnType::Label		),
	new CD("2. In de klas [In de klas worden kwetsende opmerkingen gemaakt over mijn identiteit]",												"klasKwetstMetMijnIdentiteit",											ColumnType::Label		),
	new CD("2. In de klas [Mijn klasgenoten weten hoe het met mij gaat]",																		"klasWeetHoeHetMetMijGaat",												ColumnType::Label		),
	new CD("Sommige studenten maken vervelende dingen mee in de klas. Hoe komt dit?",															"waaromVervelendeDingenInDeKlas",										ColumnType::Labels		),
	new CD("Bij mij in de klas/op school zie ik dat andere studenten... [...worden buitengesloten]",		                            		"studentenBuitenGesloten",												ColumnType::Label		),
	new CD("Bij mij in de klas/op school zie ik dat andere studenten... [...worden uitgescholden]",				                                "studentenUitgescholden",												ColumnType::Label		),
	new CD("Bij mij in de klas/op school zie ik dat andere studenten... [...met opzet de les verstoren]",			                        	"studentenExpresLesVerstoren",											ColumnType::Label		),
	new CD("Bij mij in de klas/op school zie ik dat andere studenten... [...met opzet spullen vernielen, verstoppen of kwijtmaken]",			"studentenSpullenSlopenJatten",											ColumnType::Label		),
	new CD("Bij mij in de klas/op school zie ik dat andere studenten... [...worden gepest]",				                                    "studentenGepest",														ColumnType::Label		),
	new CD("Bij mij in de klas/op school zie ik dat andere studenten... […worden gepest via internet, smartphone, social media]",				"studentenDigitaalGepest",												ColumnType::Label		),
	new CD("Bij mij in de klas/op school zie ik dat andere studenten... […worden gediscrimineerd (ongelijk behandeld) door medeleerlingen]",	"studentenGediscrimineerdDoorLeerlingen",								ColumnType::Label		),
	new CD("Bij mij in de klas/op school zie ik dat andere studenten... […worden gediscrimineerd (ongelijk behandeld) door docenten]",			"studentenGediscrimineerdDoorLeraren",									ColumnType::Label		),
	new CD("Bij mij in de klas/op school zie ik dat andere studenten... […worden bedreigd of geïntimideerd]",									"studentenBedreigdGeintimideerd",										ColumnType::Label		),
	new CD("Bij mij in de klas/op school zie ik dat andere studenten... […worden geduwd, geschopt of geslagen]",								"studentenGeduwdGeschoptGeslagen",										ColumnType::Label		),
	new CD("Bij mij in de klas/op school zie ik dat andere studenten... […met elkaar vechten]",												 	"studentenVechten",														ColumnType::Label		),
	new CD("Bij mij in de klas/op school zie ik dat andere studenten... […seksueel getinte opmerkingen maken]",								    "studentenSeksueelGetinteOpmerkingenMaken",								ColumnType::Label		),
	new CD("Bij mij in de klas/op school zie ik dat andere studenten... […seksuele afbeeldingen verspreiden]",									"studentenSeksueleAfbeeldingenVerspreiden",								ColumnType::Label		),
	new CD("Bij mij in de klas/op school zie ik dat andere studenten... [...zich niet veilig voelen in de klas]",								"studentenOnveiligVoelenInKlas",										ColumnType::Label		),
	new CD("In de klas/op school word ik...  [...buitengesloten]",																				"ikBuitengesloten",														ColumnType::Label		),
	new CD("In de klas/op school word ik...  [...uitgescholden]",																				"ikUitgescholden",														ColumnType::Label		),
	new CD("In de klas/op school word ik...  [...expres gestoord]",																				"ikExpresGestoord",														ColumnType::Label		),
	new CD("In de klas/op school word ik...  [...gepest]",																						"ikGepest",																ColumnType::Label		),
	new CD("In de klas/op school word ik...  [...gepest via internet, smartphone, social media]",												"ikDigitaalGepest",														ColumnType::Label		),
	new CD("In de klas/op school word ik...  [...gediscrimineerd (ongelijk behandeld) door medestudent]",										"ikGediscrimineerdDoorLeerlingen",										ColumnType::Label		),
	new CD("In de klas/op school word ik...  [...gediscrimineerd (ongelijk behandeld) door docenten]",											"ikGediscrimineerdDoorLeraren",											ColumnType::Label		),
	new CD("In de klas/op school word ik...  [...bedreigd of geïntimideerd]",																	"ikBedreigdGeintimideerd",												ColumnType::Label		),
	new CD("In de klas/op school word ik...  [...geduwd, geschopt of geslagen]",																"ikGeduwdGeschoptGeslagen",												ColumnType::Label		),
	new CD("In de klas/op school word ik...  [...uitgedaagd om te vechten]",																	"ikUitgedaagdOmTeVechten",												ColumnType::Label		),
	new CD("In de klas/op school word ik...  [...aangesproken met seksueel getinte opmerkingen]",												"ikAangesprokenMetSeksueelGetinteOpmerkingen",							ColumnType::Label		),
	new CD("In de klas/op school word ik...  [...aangesproken op vervelend gedrag]",															"ikAangesprokenOpVervelendGedrag",										ColumnType::Label		),
	new CD("In de klas/op school worden mijn...  [...spullen met opzet vernield, verstopt of kwijtgemaakt]",									"mijnSpullenGeslooptGejat",												ColumnType::Label		),
	new CD("In de klas/op school worden mijn...  [...privéfoto’s verspreid]",																	"mijnPriveFotosVerspreid",												ColumnType::Label		),
	new CD(" [In de klas voel ik me onveilig]",																									"klasVoeltOnveilig",													ColumnType::Label		),
	new CD(" [Op school voel ik me onveilig]",																									"schoolVoeltOnveilig",													ColumnType::Label		),
	new CD("4. Op school [Op onze school kun je jezelf zijn]",																					"schoolJezelfZijn",														ColumnType::Label		),
	new CD("4. Op school [De sfeer op school is goed]",																							"schoolSfeerIsGoed",													ColumnType::Label		),
	new CD("4. Op school [Ik raad mijn school aan anderen aan]",																				"schoolRaadIkAan",														ColumnType::Label		),
	new CD("4. Op school [Op school worden studenten gediscrimineerd (ongelijk behandeld)]",													"schoolStudentenGediscrimineerd",										ColumnType::Label		),
	new CD("4. Op school [Studenten van verschillende afkomsten voelen zich thuis bij ons op school]",											"schoolDiversVoeltThuis",												ColumnType::Label		),
	new CD("4. Op school [Studenten kunnen op school goed met elkaar opschieten]",																"schoolGoedOpschietenElkaar",											ColumnType::Label		),
	new CD("4. Op school [Op school ga ik het liefst om met studenten die dezelfde afkomst hebben als ik]",										"schoolLiefstMetGelijkeAfkomstOm",										ColumnType::Label		),
	new CD("4. Op school [Op school worden anderen voorgetrokken op basis van afkomst, cultuur of geloof]",										"schoolAnderenVoorgetrokkenAfkomstCultuurGeloof",						ColumnType::Label		),
	new CD("4. Op school [Actuele gebeurtenissen in de wereld die voor mij van belang zijn komen aan bod op school]",							"schoolActueleGebeurtenissenMijAangaanBehandeldOpSchool",				ColumnType::Label		),
	new CD("4. Op school [In de pauze zie ik vaak studenten ongewild alleen zitten]",															"schoolStudentenZittenOngewildAlleen",									ColumnType::Label		),
	new CD("5. Zo werken wij op school      [Op school zijn duidelijke regels/afspraken over hoe we met elkaar omgaan]",						"werkenSchoolDuidelijkeRegelsOmgang",									ColumnType::Label		),
	new CD("5. Zo werken wij op school      [De regels op school zijn voor iedereen gelijk]",													"werkenSchoolRegelsIedereenGelijk",										ColumnType::Label		),
	new CD("5. Zo werken wij op school      [Studenten die zich niet aan de regels houden, worden daarop aangesproken]",						"werkenSchoolStudentenDieRegelsBrekenAangesproken",						ColumnType::Label		),
	new CD("5. Zo werken wij op school      [Docenten die zich niet aan de regels houden, worden daarop aangesproken]",							"werkenSchoolDocentenDieRegelsBrekenAangesproken",						ColumnType::Label		),
	new CD("5. Zo werken wij op school      [De regels zijn bij elke docent hetzelfde]",														"werkenSchoolRegelsIedereDocentGelijk",									ColumnType::Label		),
	new CD("5. Zo werken wij op school      [Ik weet bij wie ik op school terecht kan met mijn problemen]",										"werkenSchoolOmbudBekend",												ColumnType::Label		),
	new CD("5. Zo werken wij op school      [De mening van studenten telt mee op onze school]",													"werkenSchoolMeningStudentenTelt",										ColumnType::Label		),
	new CD("5. Zo werken wij op school      [Studenten hebben respect voor docenten]",															"werkenSchoolStudentenHebbenRespectVoorDocenten",						ColumnType::Label		),
	new CD("5. Zo werken wij op school      [Docenten hebben respect voor studenten]",															"werkenSchoolDocentenHebbenRespectVoorStudenten",						ColumnType::Label		),
	new CD("5. Zo werken wij op school      [Docenten geven op school het goede voorbeeld]",													"werkenSchoolDocentenGevenGoedeVoorbeeld",								ColumnType::Label		),
	new CD("Als iemand vervelend doet tegen een klasgenoot dan .... [... ga ik helpen]",														"vervelendDanGaIkHelpen",												ColumnType::Label		),
	new CD("Als iemand vervelend doet tegen een klasgenoot dan .... [... kijk ik weg]",															"vervelendDanKijkIkWeg",												ColumnType::Label		),
	new CD("Als iemand vervelend doet tegen een klasgenoot dan .... [... loop ik weg]",															"vervelendDanLoopIkWeg",												ColumnType::Label		),
	new CD("Als iemand vervelend doet tegen een klasgenoot dan .... [... doe ik mee]",															"vervelendDanDoeIkMee",													ColumnType::Label		),
	new CD("Als iemand vervelend doet tegen een klasgenoot dan .... [... zeg ik er wat van]",													"vervelendDanZegIkErWatVan",											ColumnType::Label		),
	new CD("Als iemand vervelend doet tegen een klasgenoot dan .... [... waarschuw ik een docent, mentor of conciërge]",						"vervelendDanWaarschuwIkSchoolMedewerker",								ColumnType::Label		),
	new CD("Als iemand vervelend doet tegen een klasgenoot dan .... [... laat ik hem/haar weten dat ik meeleef]",								"vervelendDanLaatIkMedelevenWeten",										ColumnType::Label		),
	new CD("Als iemand vervelend doet tegen een klasgenoot dan .... [... zie ik dat een andere student ingrijpt]",								"vervelendDanZieIkDatAndereStudentIngrijpt",							ColumnType::Label		),
	new CD("Als iemand vervelend doet tegen een klasgenoot dan .... [... zie ik dat een docent ingrijpt]",										"vervelendDanZieIkDatDocentIngrijpt",									ColumnType::Label		),
	new CD("Als iemand vervelend doet tegen een klasgenoot dan .... [... zie ik dat de afdelingsleider ingrijpt]",								"vervelendDanZieIkDatAfdelingsleiderIngrijpt",							ColumnType::Label		),
	new CD("Heb je de afgelopen week vervelende situaties (als pesten, buitensluiten etc.) gezien?",											"afgelopenWeekVervelendeSituatiesGezien",								ColumnType::Label		),
	new CD(" [Als ik een vervelende situatie zie, dan vind ik dat ik iets moet doen]",															"alsIkVervelendeSituatieZieDanVindIkDatIkWatMoetDoen",					ColumnType::Label		),
	new CD(" [Als ik een vervelende situatie zie, dat weet ik wat ik kan doen]",																"alsIkVervelendeSituatieZieDanWeetIkWatIkKanDoen",						ColumnType::Label		),
	new CD(" [Als een student wordt buitengesloten, dan is dat zijn/haar eigen keuze]",															"alsEenStudentWordtBuitengeslotenDanIsDatEigenKeuze",					ColumnType::Label		),
	new CD(" [Als een student wordt buitengesloten, dan is dat zijn/haar eigen schuld]",														"alsEenStudentWordtBuitengeslotenDanIsDatEigenSchuld",					ColumnType::Label		),
	new CD(" [Ik voel me verantwoordelijk om buitensluiten tegen te gaan]",																		"voelMeVerantwoordelijkOmBuitensluitenTegenTeGaan",						ColumnType::Label		),
	new CD(" [Ik voel me verantwoordelijk om in te grijpen als iemand wordt gediscrimineerd]",													"voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGediscrimineerd",		ColumnType::Label		),
	new CD(" [Ik voel me verantwoordelijk om in te grijpen als iemand wordt gepest]",															"voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGepest",				ColumnType::Label		),
	new CD(" [Ik stuur (weleens) privéfoto’s van andere studenten door]",																		"ikStuurWelEensPrivefotosAnderenDoor",									ColumnType::Label		),
	new CD("7. Docenten & mentoren [Ik heb goed contact met mijn mentor]",																		"mentorIkHebGoedContact",												ColumnType::Label		),
	new CD("7. Docenten & mentoren [Ik heb goed contact met mijn docenten]",																	"docentIkHebGoedContact",												ColumnType::Label		),
	new CD("7. Docenten & mentoren [Docenten kunnen goed orde houden in de klas]",																"docentenKunnenGoedOrdeHouden",											ColumnType::Label		),
	new CD("7. Docenten & mentoren [Ik krijg complimenten van docenten]",																		"docentenGevenMijComplimenten",											ColumnType::Label		),
	new CD("7. Docenten & mentoren [Docenten hebben een lage verwachting van mij]",																"docentenHebbenLageVerwachtingVanMij",									ColumnType::Label		),
	new CD("7. Docenten & mentoren [Docenten letten op het taalgebruik van de leerlingen]",														"docentenLettenOpTaalgebruikStudenten",									ColumnType::Label		),
	new CD("7. Docenten & mentoren [Docenten letten op hun eigen taalgebruik]",																	"docentenlettenOpEigenTaalgebruik",										ColumnType::Label		),
	new CD("7. Docenten & mentoren [Positief gedrag van studenten wordt door docenten beloond]",												"docentenBelonenPositiefGedrag",										ColumnType::Label		),
	new CD("7. Docenten & mentoren [Docenten grijpen in wanneer dat nodig is]",																	"docentenGrijpenInWanneerDatNodigIs",									ColumnType::Label		),
	new CD("7. Docenten & mentoren [Onze mentor weet wat er speelt in de klas]",																"mentorenWetenWatErInDeKlasSpeelt",										ColumnType::Label		),
	new CD("7. Docenten & mentoren [Onze mentor bespreekt wat er speelt in de klas]",															"mentorenBespreektWatErInDeKlasSpeelt",									ColumnType::Label		),
	new CD("7. Docenten & mentoren [Actuele gebeurtenissen in de samenleving worden in de klas besproken]",										"actueleGebeurtenissenSamenlevingWordenInKlasBesproken",				ColumnType::Label		),
	new CD("8. Waaraan vind jij dat jouw school meer moet doen? (max 3 antwoorden mogelijk)",													"waarMoetSchoolMeerAanDoen",											ColumnType::Labels		)
};

const std::map<QString, QString> SchoolScannerDefinities::_mapCsvToDb =
{
	//uit wide dataset:
	//???{	"",		"waarMoetSchoolMeerAanDoen"	},
	//?{	"Opleiding",									"opleiding"	},
	{	"Cultuur",											"cultuur"				},
	{	"Geslacht",											"gender"				},
	{	"Klas",												"klas"					},
	{	"Type",												"type"					},
	{	"tijdstempel",										"tijdstempel"			},
	{	"Schoolnaam",										"school"	},
	{	"Schooltype",										"schoolType"},
	{	"Locatienaam",										"locatie"	},
	{	"Opleidingssector",									"sector"	},
	{	"Leerjaar",											"jaar"	},
	{	"Opleidingstraject",								"opleidingstraject"	},
	{	"Niveau",											"niveau"	},
	{	"veiligheid_1a",									"veiligSchool"	},
	{	"veiligheid_1b",									"veiligKlas"	},
	{	"veiligheid_3",										"bangOpSchool"	},
	{	"veiligheid_4",										"graagNaarSchool"	}, //Deze komt dubbel voor in de wide dataset...
	{	"klas_1",											"klasJezelf"	},
	{	"klas_2",											"klasSfeerGoed"	},
	{	"klas_3",											"klasSchoolGemopper"	},
	{	"klas_4",											"klasOpschietenMet"	},
	{	"klas_5",											"klasGoedSamenWerken"	},
	{	"klas_6",											"klasAfkomstKlit"	},
	{	"klas_7",											"klasOnaardigGepraat"	},
	{	"klas_8",											"klasVeelRuzie"	},
	{	"klas_9",											"klasKunJeZeggenVervelend"	},
	{	"klas_10",											"klasDurfUitDeKast"	},
	{	"klas_11",											"klasKwetstMetMijnIdentiteit"	},
	{	"klas_12",											"klasWeetHoeHetMetMijGaat"	},
	{	"klasschool_A1",									"studentenBuitenGesloten"	},
	{	"klasschool_A2",									"studentenUitgescholden"	},
	{	"klasschool_A3",									"studentenExpresLesVerstoren"	},
	{	"klasschool_A4",									"studentenSpullenSlopenJatten"	},
	{	"klasschool_A5",									"studentenGepest"	},
	{	"klasschool_A6",									"studentenDigitaalGepest"	},
	{	"klasschool_A7",									"studentenGediscrimineerdDoorLeerlingen"	},
	{	"klasschool_A8",									"studentenGediscrimineerdDoorLeraren"	},
	{	"klasschool_A9",									"studentenBedreigdGeintimideerd"	},
	{	"klasschool_A10",									"studentenGeduwdGeschoptGeslagen"	},
	{	"klasschool_A11",									"studentenVechten"	},
	{	"klasschool_A12",									"studentenSeksueelGetinteOpmerkingenMaken"	},
	{	"klasschool_A13",									"studentenSeksueleAfbeeldingenVerspreiden"	},
	{	"klasschool_A14",									"studentenOnveiligVoelenInKlas"	},
	{	"klasschool_B1",									"ikBuitengesloten"	},
	{	"klasschool_B2",									"ikUitgescholden"	},
	{	"klasschool_B3",									"ikExpresGestoord"	},
	{	"klasschool_B4",									"ikGepest"	},
	{	"klasschool_B5",									"ikDigitaalGepest"	},
	{	"klasschool_B6",									"ikGediscrimineerdDoorLeerlingen"	},
	{	"klasschool_B7",									"ikGediscrimineerdDoorLeraren"	},
	{	"klasschool_B8",									"ikBedreigdGeintimideerd"	},
	{	"klasschool_B9",									"ikGeduwdGeschoptGeslagen"	},
	{	"klasschool_B10",									"ikUitgedaagdOmTeVechten"	},
	{	"klasschool_B11",									"ikAangesprokenMetSeksueelGetinteOpmerkingen"	},
	{	"klasschool_B12",									"ikAangesprokenOpVervelendGedrag"	},
	{	"klasschool_C1",									"mijnSpullenGeslooptGejat"	},
	{	"klasschool_C2",									"mijnPriveFotosVerspreid"	},
	{	"klasschool_D1",									"klasVoeltOnveilig"	},
	{	"klasschool_D2",									"schoolVoeltOnveilig"	},
	{	"school_1",											"schoolJezelfZijn"	},
	{	"school_2",											"schoolSfeerIsGoed"	},
	{	"school_3",											"schoolRaadIkAan"	},
	{	"school_4",											"schoolStudentenGediscrimineerd"	},
	{	"school_5",											"schoolDiversVoeltThuis"	},
	{	"school_6",											"schoolGoedOpschietenElkaar"	},
	{	"school_7",											"schoolLiefstMetGelijkeAfkomstOm"	},
	{	"school_8",											"schoolAnderenVoorgetrokkenAfkomstCultuurGeloof"	},
	{	"school_9",											"schoolActueleGebeurtenissenMijAangaanBehandeldOpSchool"	},
	{	"school_10",										"schoolStudentenZittenOngewildAlleen"	},
	{	"werkwijze_1",										"werkenSchoolDuidelijkeRegelsOmgang"	},
	{	"werkwijze_2",										"werkenSchoolRegelsIedereenGelijk"	},
	{	"werkwijze_3",										"werkenSchoolStudentenDieRegelsBrekenAangesproken"	},
	{	"werkwijze_4",										"werkenSchoolDocentenDieRegelsBrekenAangesproken"	},
	{	"werkwijze_5",										"werkenSchoolRegelsIedereDocentGelijk"	},
	{	"werkwijze_6",										"werkenSchoolOmbudBekend"	},
	{	"werkwijze_8",										"werkenSchoolMeningStudentenTelt"	},
	{	"werkwijze_9",										"werkenSchoolStudentenHebbenRespectVoorDocenten"	},
	{	"werkwijze_10",										"werkenSchoolDocentenHebbenRespectVoorStudenten"	},
	{	"werkwijze_11",										"werkenSchoolDocentenGevenGoedeVoorbeeld"	},
	{	"ingrijpen_A1",										"vervelendDanGaIkHelpen"	},
	{	"ingrijpen_A2",										"vervelendDanKijkIkWeg"	},
	{	"ingrijpen_A3",										"vervelendDanLoopIkWeg"	},
	{	"ingrijpen_A4",										"vervelendDanDoeIkMee"	},
	{	"ingrijpen_A5",										"vervelendDanZegIkErWatVan"	},
	{	"ingrijpen_A6",										"vervelendDanWaarschuwIkSchoolMedewerker"	},
	{	"ingrijpen_A7",										"vervelendDanLaatIkMedelevenWeten"	},
	{	"ingrijpen_A8",										"vervelendDanZieIkDatAndereStudentIngrijpt"	},
	{	"ingrijpen_A9",										"vervelendDanZieIkDatDocentIngrijpt"	},
	{	"ingrijpen_A10",									"vervelendDanZieIkDatAfdelingsleiderIngrijpt"	},
	{	"ingrijpen_B1",										"afgelopenWeekVervelendeSituatiesGezien"	},
	{	"ingrijpen_B2",										"alsIkVervelendeSituatieZieDanVindIkDatIkWatMoetDoen"	},
	{	"ingrijpen_B3",										"alsIkVervelendeSituatieZieDanWeetIkWatIkKanDoen"	},
	{	"ingrijpen_B4",										"alsEenStudentWordtBuitengeslotenDanIsDatEigenKeuze"	},
	{	"ingrijpen_B5",										"alsEenStudentWordtBuitengeslotenDanIsDatEigenSchuld"	},
	{	"ingrijpen_B6",										"voelMeVerantwoordelijkOmBuitensluitenTegenTeGaan"	},
	{	"ingrijpen_B7",										"voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGediscrimineerd"	},
	{	"ingrijpen_B8",										"voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGepest"	},
	{	"ingrijpen_B9",										"ikStuurWelEensPrivefotosAnderenDoor"	},
	{	"docenten_1",										"mentorIkHebGoedContact"	},
	{	"docenten_2",										"docentIkHebGoedContact"	},
	{	"docenten_3",										"docentenKunnenGoedOrdeHouden"	},
	{	"docenten_4",										"docentenGevenMijComplimenten"	},
	{	"docenten_5a",										"docentenHebbenLageVerwachtingVanMij"	},
	{	"docenten_6",										"docentenLettenOpTaalgebruikStudenten"	},
	{	"docenten_7",										"docentenlettenOpEigenTaalgebruik"	},
	{	"docenten_8",										"docentenBelonenPositiefGedrag"	},
	{	"docenten_9",										"docentenGrijpenInWanneerDatNodigIs"	},
	{	"docenten_10",										"mentorenWetenWatErInDeKlasSpeelt"	},
	{	"docenten_11",										"mentorenBespreektWatErInDeKlasSpeelt"	},
	{	"docenten_12",										"actueleGebeurtenissenSamenlevingWordenInKlasBesproken"	},
	{	"veiligheid_2a#veiligheid_2b#veiligheid_2c#veiligheid_2d#veiligheid_2e#veiligheid_2f#veiligheid_2g#veiligheid_2h#veiligheid_2i#veiligheid_2j",		"onveiligHier"	},
	{	"klas_14a#klas_14b#klas_14c#klas_14d#klas_14e#klas_14f#klas_14g",		"waaromVervelendeDingenInDeKlas"	},

	//Uit MBO vragenlijst:
	{ "Tijdstempel",																													   	"timestamp"	},
	{ "Wat is de datum?",																													"datum"	},
	{ "Ben je een jongen of meisje?",																										"gender"	},
	{ "Wat is jouw culturele achtergrond?",																								    "cultuur"	},
	{ "Op welke school zit je?",																											"school"	},
	{ "Op welke school/locatie heb je les?",																								"locatie"	},
	{ "Welke opleiding volg je?",																											"opleiding"	},
	{ "Onder welke sector valt jouw opleiding?",																							"sector"	},
	{ "In welk jaar zit je?",																												"jaar"	},
	{ "In welke klas zit je?",																												"klas"	},
	{ "Welk opleidingstraject volg je?",																									"opleidingstraject"	},
	{ "Welk niveau volg je?",																												"niveau"	},
	{ "Ik voel me veilig  [Ik voel me veilig op school]",																					"veiligSchool"	},
	{ "Ik voel me veilig  [Ik voel me veilig in de klas]",																					"veiligKlas"	},
	{ "Ik voel me onveilig in/op/bij",																										"onveiligHier"	},
	{ " [Ik ben wel eens bang op school]",																									"bangOpSchool"	},
	{ " [Ik ga graag naar school]",																									    	"graagNaarSchool"	},
	{ "2. In de klas [In onze klas kun je jezelf zijn]",																					"klasJezelf"	},
	{ "2. In de klas [De sfeer in de klas is goed]",																						"klasSfeerGoed"	},
	{ "2. In de klas [Er wordt in mijn klas gemopperd over school]",																		"klasSchoolGemopper"	},
	{ "2. In de klas [Ik kan goed opschieten met mijn klasgenoten]",																		"klasOpschietenMet"	},
	{ "2. In de klas [In de klas kunnen we goed met elkaar samenwerken]",																	"klasGoedSamenWerken"	},
	{ "2. In de klas [In de klas ga ik het liefst om met studenten die dezelfde afkomst hebben als ik]",									"klasAfkomstKlit"	},
	{ "2. In de klas [In de klas hoor ik dat studenten onaardig over elkaar spreken]",														"klasOnaardigGepraat"	},
	{ "2. In de klas [In de klas wordt veel ruzie gemaakt]",																				"klasVeelRuzie"	},
	{ "2. In de klas [Als iemand vervelend tegen je doet, kun je er wat van zeggen]",														"klasKunJeZeggenVervelend"	},
	{ "2. In de klas [Als ik homo of lesbisch zou zijn, dan mogen klasgenoten dat weten]",													"klasDurfUitDeKast"	},
	{ "2. In de klas [In de klas worden kwetsende opmerkingen gemaakt over mijn identiteit]",												"klasKwetstMetMijnIdentiteit"	},
	{ "2. In de klas [Mijn klasgenoten weten hoe het met mij gaat]",																		"klasWeetHoeHetMetMijGaat"	},
	{ "Sommige studenten maken vervelende dingen mee in de klas. Hoe komt dit?",															"waaromVervelendeDingenInDeKlas"	},
	{ "Bij mij in de klas/op school zie ik dat andere studenten... [...worden buitengesloten]",		                            		    "studentenBuitenGesloten"	},
	{ "Bij mij in de klas/op school zie ik dat andere studenten... [...worden uitgescholden]",				                                "studentenUitgescholden"	},
	{ "Bij mij in de klas/op school zie ik dat andere studenten... [...met opzet de les verstoren]",			                        	"studentenExpresLesVerstoren"	},
	{ "Bij mij in de klas/op school zie ik dat andere studenten... [...met opzet spullen vernielen, verstoppen of kwijtmaken]",			    "studentenSpullenSlopenJatten"	},
	{ "Bij mij in de klas/op school zie ik dat andere studenten... [...worden gepest]",				                                        "studentenGepest"	},
	{ "Bij mij in de klas/op school zie ik dat andere studenten... […worden gepest via internet, smartphone, social media]",				"studentenDigitaalGepest"	},
	{ "Bij mij in de klas/op school zie ik dat andere studenten... […worden gediscrimineerd (ongelijk behandeld) door medeleerlingen]", 	"studentenGediscrimineerdDoorLeerlingen"	},
	{ "Bij mij in de klas/op school zie ik dat andere studenten... […worden gediscrimineerd (ongelijk behandeld) door docenten]",			"studentenGediscrimineerdDoorLeraren"	},
	{ "Bij mij in de klas/op school zie ik dat andere studenten... […worden bedreigd of geïntimideerd]",									"studentenBedreigdGeintimideerd"	},
	{ "Bij mij in de klas/op school zie ik dat andere studenten... […worden geduwd, geschopt of geslagen]",							    	"studentenGeduwdGeschoptGeslagen"	},
	{ "Bij mij in de klas/op school zie ik dat andere studenten... […met elkaar vechten]",												 	"studentenVechten"	},
	{ "Bij mij in de klas/op school zie ik dat andere studenten... […seksueel getinte opmerkingen maken]",								    "studentenSeksueelGetinteOpmerkingenMaken"	},
	{ "Bij mij in de klas/op school zie ik dat andere studenten... […seksuele afbeeldingen verspreiden]",									"studentenSeksueleAfbeeldingenVerspreiden"	},
	{ "Bij mij in de klas/op school zie ik dat andere studenten... [...zich niet veilig voelen in de klas]",								"studentenOnveiligVoelenInKlas"	},
	{ "In de klas/op school word ik...  [...buitengesloten]",																				"ikBuitengesloten"	},
	{ "In de klas/op school word ik...  [...uitgescholden]",																				"ikUitgescholden"	},
	{ "In de klas/op school word ik...  [...expres gestoord]",																				"ikExpresGestoord"	},
	{ "In de klas/op school word ik...  [...gepest]",																						"ikGepest"	},
	{ "In de klas/op school word ik...  [...gepest via internet, smartphone, social media]",												"ikDigitaalGepest"	},
	{ "In de klas/op school word ik...  [...gediscrimineerd (ongelijk behandeld) door medestudent]",										"ikGediscrimineerdDoorLeerlingen"	},
	{ "In de klas/op school word ik...  [...gediscrimineerd (ongelijk behandeld) door docenten]",											"ikGediscrimineerdDoorLeraren"	},
	{ "In de klas/op school word ik...  [...bedreigd of geïntimideerd]",																	"ikBedreigdGeintimideerd"	},
	{ "In de klas/op school word ik...  [...geduwd, geschopt of geslagen]",															    	"ikGeduwdGeschoptGeslagen"	},
	{ "In de klas/op school word ik...  [...uitgedaagd om te vechten]",																    	"ikUitgedaagdOmTeVechten"	},
	{ "In de klas/op school word ik...  [...aangesproken met seksueel getinte opmerkingen]",												"ikAangesprokenMetSeksueelGetinteOpmerkingen"	},
	{ "In de klas/op school word ik...  [...aangesproken op vervelend gedrag]",													    		"ikAangesprokenOpVervelendGedrag"	},
	{ "In de klas/op school worden mijn...  [...spullen met opzet vernield, verstopt of kwijtgemaakt]",							    		"mijnSpullenGeslooptGejat"	},
	{ "In de klas/op school worden mijn...  [...privéfoto’s verspreid]",																	"mijnPriveFotosVerspreid"	},
	{ " [In de klas voel ik me onveilig]",																									"klasVoeltOnveilig"	},
	{ " [Op school voel ik me onveilig]",																									"schoolVoeltOnveilig"	},
	{ "4. Op school [Op onze school kun je jezelf zijn]",																					"schoolJezelfZijn"	},
	{ "4. Op school [De sfeer op school is goed]",																							"schoolSfeerIsGoed"	},
	{ "4. Op school [Ik raad mijn school aan anderen aan]",																			    	"schoolRaadIkAan"	},
	{ "4. Op school [Op school worden studenten gediscrimineerd (ongelijk behandeld)]",												    	"schoolStudentenGediscrimineerd"	},
	{ "4. Op school [Studenten van verschillende afkomsten voelen zich thuis bij ons op school]",											"schoolDiversVoeltThuis"	},
	{ "4. Op school [Studenten kunnen op school goed met elkaar opschieten]",																"schoolGoedOpschietenElkaar"	},
	{ "4. Op school [Op school ga ik het liefst om met studenten die dezelfde afkomst hebben als ik]",										"schoolLiefstMetGelijkeAfkomstOm"	},
	{ "4. Op school [Op school worden anderen voorgetrokken op basis van afkomst, cultuur of geloof]",										"schoolAnderenVoorgetrokkenAfkomstCultuurGeloof"	},
	{ "4. Op school [Actuele gebeurtenissen in de wereld die voor mij van belang zijn komen aan bod op school]",							"schoolActueleGebeurtenissenMijAangaanBehandeldOpSchool"	},
	{ "4. Op school [In de pauze zie ik vaak studenten ongewild alleen zitten]",															"schoolStudentenZittenOngewildAlleen"	},
	{ "5. Zo werken wij op school      [Op school zijn duidelijke regels/afspraken over hoe we met elkaar omgaan]",					    	"werkenSchoolDuidelijkeRegelsOmgang"	},
	{ "5. Zo werken wij op school      [De regels op school zijn voor iedereen gelijk]",													"werkenSchoolRegelsIedereenGelijk"	},
	{ "5. Zo werken wij op school      [Studenten die zich niet aan de regels houden, worden daarop aangesproken]",					    	"werkenSchoolStudentenDieRegelsBrekenAangesproken"	},
	{ "5. Zo werken wij op school      [Docenten die zich niet aan de regels houden, worden daarop aangesproken]",							"werkenSchoolDocentenDieRegelsBrekenAangesproken"	},
	{ "5. Zo werken wij op school      [De regels zijn bij elke docent hetzelfde]",												    		"werkenSchoolRegelsIedereDocentGelijk"	},
	{ "5. Zo werken wij op school      [Ik weet bij wie ik op school terecht kan met mijn problemen]",										"werkenSchoolOmbudBekend"	},
	{ "5. Zo werken wij op school      [De mening van studenten telt mee op onze school]",													"werkenSchoolMeningStudentenTelt"	},
	{ "5. Zo werken wij op school      [Studenten hebben respect voor docenten]",															"werkenSchoolStudentenHebbenRespectVoorDocenten"	},
	{ "5. Zo werken wij op school      [Docenten hebben respect voor studenten]",															"werkenSchoolDocentenHebbenRespectVoorStudenten"	},
	{ "5. Zo werken wij op school      [Docenten geven op school het goede voorbeeld]",												    	"werkenSchoolDocentenGevenGoedeVoorbeeld"	},
	{ "Als iemand vervelend doet tegen een klasgenoot dan .... [... ga ik helpen]",													    	"vervelendDanGaIkHelpen"	},
	{ "Als iemand vervelend doet tegen een klasgenoot dan .... [... kijk ik weg]",															"vervelendDanKijkIkWeg"	},
	{ "Als iemand vervelend doet tegen een klasgenoot dan .... [... loop ik weg]",															"vervelendDanLoopIkWeg"	},
	{ "Als iemand vervelend doet tegen een klasgenoot dan .... [... doe ik mee]",															"vervelendDanDoeIkMee"	},
	{ "Als iemand vervelend doet tegen een klasgenoot dan .... [... zeg ik er wat van]",													"vervelendDanZegIkErWatVan"	},
	{ "Als iemand vervelend doet tegen een klasgenoot dan .... [... waarschuw ik een docent, mentor of conciërge]",					    	"vervelendDanWaarschuwIkSchoolMedewerker"	},
	{ "Als iemand vervelend doet tegen een klasgenoot dan .... [... laat ik hem/haar weten dat ik meeleef]",								"vervelendDanLaatIkMedelevenWeten"	},
	{ "Als iemand vervelend doet tegen een klasgenoot dan .... [... zie ik dat een andere student ingrijpt]",								"vervelendDanZieIkDatAndereStudentIngrijpt"	},
	{ "Als iemand vervelend doet tegen een klasgenoot dan .... [... zie ik dat een docent ingrijpt]",										"vervelendDanZieIkDatDocentIngrijpt"	},
	{ "Als iemand vervelend doet tegen een klasgenoot dan .... [... zie ik dat de afdelingsleider ingrijpt]",								"vervelendDanZieIkDatAfdelingsleiderIngrijpt"	},
	{ "Heb je de afgelopen week vervelende situaties (als pesten, buitensluiten etc.) gezien?",										    	"afgelopenWeekVervelendeSituatiesGezien"	},
	{ " [Als ik een vervelende situatie zie, dan vind ik dat ik iets moet doen]",															"alsIkVervelendeSituatieZieDanVindIkDatIkWatMoetDoen"	},
	{ " [Als ik een vervelende situatie zie, dat weet ik wat ik kan doen]",															    	"alsIkVervelendeSituatieZieDanWeetIkWatIkKanDoen"	},
	{ " [Als een student wordt buitengesloten, dan is dat zijn/haar eigen keuze]",															"alsEenStudentWordtBuitengeslotenDanIsDatEigenKeuze"	},
	{ " [Als een student wordt buitengesloten, dan is dat zijn/haar eigen schuld]",													    	"alsEenStudentWordtBuitengeslotenDanIsDatEigenSchuld"	},
	{ " [Ik voel me verantwoordelijk om buitensluiten tegen te gaan]",																		"voelMeVerantwoordelijkOmBuitensluitenTegenTeGaan"	},
	{ " [Ik voel me verantwoordelijk om in te grijpen als iemand wordt gediscrimineerd]",													"voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGediscrimineerd"	},
	{ " [Ik voel me verantwoordelijk om in te grijpen als iemand wordt gepest]",															"voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGepest"	},
	{ " [Ik stuur (weleens) privéfoto’s van andere studenten door]",																		"ikStuurWelEensPrivefotosAnderenDoor"	},
	{ "7. Docenten & mentoren [Ik heb goed contact met mijn mentor]",																		"mentorIkHebGoedContact"	},
	{ "7. Docenten & mentoren [Ik heb goed contact met mijn docenten]",																    	"docentIkHebGoedContact"	},
	{ "7. Docenten & mentoren [Docenten kunnen goed orde houden in de klas]",																"docentenKunnenGoedOrdeHouden"	},
	{ "7. Docenten & mentoren [Ik krijg complimenten van docenten]",																		"docentenGevenMijComplimenten"	},
	{ "7. Docenten & mentoren [Docenten hebben een lage verwachting van mij]",																"docentenHebbenLageVerwachtingVanMij"	},
	{ "7. Docenten & mentoren [Docenten letten op het taalgebruik van de leerlingen]",														"docentenLettenOpTaalgebruikStudenten"	},
	{ "7. Docenten & mentoren [Docenten letten op hun eigen taalgebruik]",																	"docentenlettenOpEigenTaalgebruik"	},
	{ "7. Docenten & mentoren [Positief gedrag van studenten wordt door docenten beloond]",										    		"docentenBelonenPositiefGedrag"	},
	{ "7. Docenten & mentoren [Docenten grijpen in wanneer dat nodig is]",																	"docentenGrijpenInWanneerDatNodigIs"	},
	{ "7. Docenten & mentoren [Onze mentor weet wat er speelt in de klas]",													    			"mentorenWetenWatErInDeKlasSpeelt"	},
	{ "7. Docenten & mentoren [Onze mentor bespreekt wat er speelt in de klas]",															"mentorenBespreektWatErInDeKlasSpeelt"	},
	{ "7. Docenten & mentoren [Actuele gebeurtenissen in de samenleving worden in de klas besproken]",										"actueleGebeurtenissenSamenlevingWordenInKlasBesproken"	},
	{ "8. Waaraan vind jij dat jouw school meer moet doen? (max 3 antwoorden mogelijk)",													"waarMoetSchoolMeerAanDoen"	}
};
