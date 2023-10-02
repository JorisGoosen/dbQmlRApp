#include "plotrenderers.h"
#include "plotrenderer.h"
#include <iostream>

#define GENEREERHET(SECTIE, PLOTTYPE, STU, KOLOM, TITEL, W, H)									\
	new PlotRenderer(this, SECTIE, PLOTTYPE,	PlotFilter::School,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, SECTIE, PLOTTYPE,	PlotFilter::Locatie,	STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, SECTIE, PLOTTYPE,	PlotFilter::Sector,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, SECTIE, PLOTTYPE,	PlotFilter::Niveau,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, SECTIE, PLOTTYPE,	PlotFilter::Jaar,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, SECTIE, PLOTTYPE,	PlotFilter::Klas,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, SECTIE, PLOTTYPE,	PlotFilter::Gender,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, SECTIE, PLOTTYPE,	PlotFilter::Cultuur,	STU, KOLOM, TITEL, W, H)

#define GENEREERHETDOC(SECTIE, PLOTTYPE, STU, KOLOM, TITEL, W, H)									\
	new PlotRenderer(this, SECTIE, PLOTTYPE,	PlotFilter::Gender,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, SECTIE, PLOTTYPE,	PlotFilter::Cultuur,	STU, KOLOM, TITEL, W, H)


#define GENEREERHETSL(SECTIE, PLOTTYPE, STU, KOLOM, TITEL, W, H)									\
	new PlotRenderer(this, SECTIE, PLOTTYPE,	PlotFilter::School,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, SECTIE, PLOTTYPE,	PlotFilter::Locatie,	STU, KOLOM, TITEL, W, H)


PlotRenderers::PlotRenderers( QObject *parent)
	: QAbstractListModel{parent}
{
	_plotFolder = QDir::home();

	const QString naamMap = "SchoolScannerGrafieken";
	if(!_plotFolder.exists(naamMap))
		_plotFolder.mkdir(naamMap);

	_plotFolder = _plotFolder.absoluteFilePath(naamMap);

	const QString	klasKolommen		= "klasJezelf,klasSfeerGoed,klasSchoolGemopper,klasOpschietenMet,klasGoedSamenWerken,klasAfkomstKlit,klasOnaardigGepraat,klasVeelRuzie,klasKunJeZeggenVervelend,klasDurfUitDeKast,klasKwetstMetMijnIdentiteit,klasWeetHoeHetMetMijGaat,klasVoeltOnveilig",
					studentKolommen		= "studentenBuitenGesloten,studentenUitgescholden,studentenExpresLesVerstoren,studentenSpullenSlopenJatten,studentenGepest,studentenDigitaalGepest,studentenGediscrimineerdDoorLeerlingen,studentenGediscrimineerdDoorLeraren,studentenBedreigdGeintimideerd,studentenGeduwdGeschoptGeslagen,studentenVechten,studentenSeksueelGetinteOpmerkingenMaken,studentenSeksueleAfbeeldingenVerspreiden,studentenOnveiligVoelenInKlas",
					ikWordKolommen		= "ikBuitengesloten,ikUitgescholden,ikExpresGestoord,ikGepest,ikDigitaalGepest,ikGediscrimineerdDoorLeerlingen,ikGediscrimineerdDoorLeraren,ikBedreigdGeintimideerd,ikGeduwdGeschoptGeslagen,ikUitgedaagdOmTeVechten,ikAangesprokenMetSeksueelGetinteOpmerkingen,ikAangesprokenOpVervelendGedrag",
					mijnWordkolommen	= "mijnSpullenGeslooptGejat,mijnPriveFotosVerspreid",
					schoolKolommen		= "schoolJezelfZijn,schoolSfeerIsGoed,schoolRaadIkAan,schoolStudentenGediscrimineerd,schoolDiversVoeltThuis,schoolGoedOpschietenElkaar,schoolLiefstMetGelijkeAfkomstOm,schoolAnderenVoorgetrokkenAfkomstCultuurGeloof,schoolActueleGebeurtenissenMijAangaanBehandeldOpSchool,schoolStudentenZittenOngewildAlleen",
					afsprakenKolommen	= "werkenSchoolDuidelijkeRegelsOmgang,werkenSchoolRegelsIedereenGelijk,werkenSchoolStudentenDieRegelsBrekenAangesproken,werkenSchoolDocentenDieRegelsBrekenAangesproken,werkenSchoolRegelsIedereDocentGelijk,werkenSchoolOmbudBekend,werkenSchoolMeningStudentenTelt,werkenSchoolStudentenHebbenRespectVoorDocenten,werkenSchoolDocentenHebbenRespectVoorStudenten,werkenSchoolDocentenGevenGoedeVoorbeeld",
					//afsprakenKortKol	= "werkenSchoolDuidelijkeRegelsOmgang,werkenSchoolRegelsIedereenGelijk,werkenSchoolStudentenDieRegelsBrekenAangesproken,werkenSchoolDocentenDieRegelsBrekenAangesproken",
					ingrijpenVervelend  = "vervelendDanKijkIkWeg,vervelendDanLoopIkWeg,vervelendDanDoeIkMee,vervelendDanZegIkErWatVan,vervelendDanWaarschuwIkSchoolMedewerker,vervelendDanLaatIkMedelevenWeten,vervelendDanZieIkDatAndereStudentIngrijpt,vervelendDanZieIkDatDocentIngrijpt,vervelendDanZieIkDatAfdelingsleiderIngrijpt",	
					ingrijpenPesten		= "alsIkVervelendeSituatieZieDanVindIkDatIkWatMoetDoen,alsIkVervelendeSituatieZieDanWeetIkWatIkKanDoen,alsEenStudentWordtBuitengeslotenDanIsDatEigenKeuze,alsEenStudentWordtBuitengeslotenDanIsDatEigenSchuld,voelMeVerantwoordelijkOmBuitensluitenTegenTeGaan,voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGediscrimineerd,voelMeVerantwoordelijkOmInTeGrijpenAlsIemandWordtGepest,ikStuurWelEensPrivefotosAnderenDoorOfIkGrijpIn",					
					ingrijpenDivers		= "medewerkerTreedOpDiscriminatie,medewerkerAnderenTredenOpDiscriminatie,medewerkerSchoolActiefContactAndereCulturen,medewerkerBewustEigenCulturelePercepties,medewerkerKentDeThuisCultuurLeerlingen,medewerkerKanOmgaanCultureVerschillenLeerlingen",
					docentenMentoren	= "mentorIkHebGoedContact,docentIkHebGoedContact,docentenKunnenGoedOrdeHouden,docentenGevenMijComplimenten,docentenHebbenLageVerwachtingVanMij,docentenLettenOpTaalgebruikStudenten,docentenlettenOpEigenTaalgebruik,docentenBelonenPositiefGedrag,docentenGrijpenInWanneerDatNodigIs,mentorenWetenWatErInDeKlasSpeelt,mentorenBespreektWatErInDeKlasSpeelt,actueleGebeurtenissenSamenlevingWordenInKlasBesproken",
					beleidKolommen		= "werkenSchoolDuidelijkeRegelsOmgang,werkenSchoolRegelsIedereenGelijk,werkenSchoolStudentenDieRegelsBrekenAangesproken,werkenSchoolDocentenDieRegelsBrekenAangesproken,werkenSchoolRegelsIedereDocentGelijk,werkenSchoolOmbudBekend,werkenSchoolMeningStudentenTelt,werkenSchoolStudentenHebbenRespectVoorDocenten,werkenSchoolDocentenHebbenRespectVoorStudenten,werkenSchoolDocentenGevenGoedeVoorbeeld";



										


	const int BB = 1280; //basisbreedte

	_plots =
	{

		//veiligheid leerlingen
		{ new PlotRenderer(this,	"2 veiligheid leerlingen", 			PlotType::Taart,								PlotFilter::Geen,	true,	"veiligSchool",						"Veilig op school",									BB,		BB			)},
		{ new PlotRenderer(this,	"2 veiligheid leerlingen", 			PlotType::Taart,								PlotFilter::Geen,	true,	"veiligKlas",						"Veilig in de klas",								BB,		BB			)},
		{ GENEREERHET(				"2 veiligheid leerlingen", 			PlotType::VerticaalStaaf,											true,	"veiligSchool",						"Veilig op school",									BB,		BB * 0.75	)},
		{ GENEREERHET(				"2 veiligheid leerlingen", 			PlotType::VerticaalStaaf,											true,	"veiligKlas",						"Veilig in de klas",								BB,		BB * 0.75	)},
		{ GENEREERHET(				"2 veiligheid leerlingen", 			PlotType::HoriStaafGroepPerFilter,									true,	"onveiligHier",						"Voel me onveilig in bij",							BB,		BB + BB		)},
		{ new PlotRenderer(this,	"2 veiligheid leerlingen", 			PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	"bangOpSchool,graagNaarSchool",		"Hoe graag naar school en hoe bang",				BB,		BB / 3		)},
		{ GENEREERHET(				"2 veiligheid leerlingen", 			PlotType::HoriStaafPerLabel,										true,	"bangOpSchool",						"Bang op school",									BB,		BB + BB		)},
		{ GENEREERHET(				"2 veiligheid leerlingen", 			PlotType::HoriStaafPerLabel,										true,	"graagNaarSchool",					"Graag naar school",								BB,		BB + BB		)},

		// 3 veiligheid docenten
		{ new PlotRenderer(this,	"3 veiligheid docenten", 			PlotType::Taart,								PlotFilter::Geen,	false,	"veiligSchool",						"Veilig op school",									BB,		BB			)},
		{ new PlotRenderer(this,	"3 veiligheid docenten", 			PlotType::Taart,								PlotFilter::Geen,	false,	"veiligKlas",						"Veilig in de klas",								BB,		BB			)},
		{ GENEREERHETDOC(			"3 veiligheid docenten", 			PlotType::VerticaalStaaf,											false,	"veiligSchool",						"Veilig op school",									BB,		BB * 0.75	)},
		{ GENEREERHETDOC(			"3 veiligheid docenten", 			PlotType::VerticaalStaaf,											false,	"veiligKlas",						"Veilig in de klas",								BB,		BB * 0.75	)},
		//{ GENEREERHETDOC(			"3 veiligheid docenten", 			PlotType::HoriStaafGroepPerFilter,									false,	"onveiligHier",						"Voel me (on?)veilig in bij",						BB,		BB + BB		)},
		{ new PlotRenderer(this,	"3 veiligheid docenten", 			PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	false,	"bangOpSchool,werkMetPlezier",		"Bang op school en werkplezier",					BB,		BB / 3		)},
		{ GENEREERHETDOC(			"3 veiligheid docenten", 			PlotType::HoriStaafPerLabel,										false,	"bangOpSchool",						"Bang op school",									BB,		BB + BB		)},
		{ GENEREERHETDOC(			"3 veiligheid docenten", 			PlotType::HoriStaafPerLabel,										false,	"werkMetPlezier",					"Werk met plezier",									BB,		BB + BB		)},

		// 4 veiligheid II/doc
		{ new PlotRenderer(this,	"4 veiligheid II",					PlotType::HoriStaafPerTypeRespondent,			PlotFilter::Geen,	true,	"bangOpSchool",						"Bang op school",									BB,		BB			)},
		//{ new PlotRenderer(this,	PlotType::HoriStaafGroepPerFilter,				PlotFilter::Type,	false,	"bangOpSchool",						"Bang op school",									BB,		BB			)},


		//5.1 + 5.2 In de klas:
		{ new PlotRenderer(this,	"5.1,2 In de klas",					PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	klasKolommen,						"In de klas...",									BB,		BB			)},
		{ GENEREERHET(				"5.1,2 In de klas",					PlotType::HoriStaafGroepPerFilter,									true,	"waaromVervelendeDingenInDeKlas" ,	"Waarom vervelende dingen in de klas",				BB,		BB			)},
		{ GENEREERHET(				"5.1,2 In de klas",					PlotType::HoriStaafPerLabel,										true,	klasKolommen,						"In de klas (Altijd + vaak)...",					BB,		BB			)},

		//6 In de klas - II/doc
		{ new PlotRenderer(this,	"6 In de klas",						PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Type,	true,	klasKolommen,						"In de klas (Altijd + vaak)...",					BB,		BB			)},
		{ new PlotRenderer(this,	"6 In de klas",						PlotType::HoriStaafGroepPerFilter,				PlotFilter::Type,	true,	"waaromVervelendeDingenInDeKlas",	"Waarom vervelende dingen in de klas",				BB,		BB			)},

		//7.1 + 7.2 + 7.3 In de klas op school
		{ new PlotRenderer(this,	"7.1,2, In de klas/op school",		PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	studentKolommen,					"In de klas/op school zie ik",						BB,		BB			)},
		{ new PlotRenderer(this,	"7.1,2, In de klas/op school",		PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	ikWordKolommen,						"In de klas/op school word ik",						BB,		BB			)},
		{ new PlotRenderer(this,	"7.1,2, In de klas/op school",		PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	mijnWordkolommen,					"In de klas/op school worden mijn",					BB,		BB			)},
		{ new PlotRenderer(this,	"7.1,2, In de klas/op school",		PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	"klasOnveilig,schoolOnveilig",		"Onveilig voelen",									BB,		BB			)},

		{ GENEREERHET(				"7.1,2, In de klas/op school",		PlotType::HoriStaafGroepPerFilter,									true,	studentKolommen,					"In de klas/op school zie ik",						BB,		BB			)},
		{ GENEREERHET(				"7.1,2, In de klas/op school",		PlotType::HoriStaafGroepPerFilter,									true,	ikWordKolommen,						"In de klas/op school word ik",						BB,		BB			)},
		{ new PlotRenderer(this,	"7.1,2, In de klas/op school",		PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	mijnWordkolommen,					"In de klas/op school worden mijn",					BB,		BB			)},
		{ new PlotRenderer(this,	"7.1,2, In de klas/op school",		PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	"klasOnveilig,schoolOnveilig",		"Onveilig voelen (altijd + vaak)",					BB,		BB			)},

		// 8 In de klas zie ik (dagelijks + wekelijks), leerlingen en docenten
		{ new PlotRenderer(this,	"8 In de klas zie ik",				PlotType::HoriStaafGroepPerFilter,				PlotFilter::Type,	true,	studentKolommen,					"In de klas/op school zie ik (dagelijks + wekelijks)",	BB,		BB			)},

		// 10 Op school
		{ new PlotRenderer(this,	"10 Op school",						PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	schoolKolommen,						"Op school - ...",										BB,		BB			)},
		{ GENEREERHET(				"10 Op school",						PlotType::HoriStaafGroepPerFilter,									true,	schoolKolommen,						"Op school (altijd + vaak) - ...",						BB,		BB			)},

		// 11 Op school en werkwijze II/doc
		{ new PlotRenderer(this,	"11 Op school en werkwijze",		PlotType::HoriStaafGroepPerFilter,				PlotFilter::Geen,	false,	schoolKolommen,						"Op school (altijd + vaak) - ...",						BB,		BB			)},
		{ new PlotRenderer(this,	"11 Op school en werkwijze",		PlotType::HoriStaafGroepPerFilter,				PlotFilter::Geen,	false,	afsprakenKolommen,					"Afspraken en regels (ja)",						BB,		BB			)},

		//12
		{ new PlotRenderer(this,	"12 Werkwijze",						PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	false,	afsprakenKolommen,					"Afspraken en regels",							BB,		BB			)},
		{ GENEREERHET(				"12 Werkwijze",						PlotType::HoriStaafGroepPerFilter,									false,	afsprakenKolommen,					"Afspraken en regels (ja)",						BB,		BB			)},

		//13
		{ new PlotRenderer(this,	"13 Ingrijpen",						PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	ingrijpenVervelend,					"Ingrijpen vervelend gedrag",					BB,		BB			)},
		{ new PlotRenderer(this,	"13 Ingrijpen",						PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	"afgelopenWeekVervelendeSituatiesGezien",		"Afgelopen week iets vervelends gezien",					BB,		BB			)},
		{ new PlotRenderer(this,	"13 Ingrijpen",						PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	ingrijpenPesten,					"Ingrijpen pesten en buitensluiten",			BB,		BB			)},

		{ new PlotRenderer(this,	"13 Ingrijpen",						PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	false,	ingrijpenPesten,					"Ingrijpen pesten en buitensluiten",			BB,		BB			)},
		//{ new PlotRenderer(this,	"13 Ingrijpen",						PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	false,	ingrijpenPesten,					"Ingrijpen schelden?",			BB,		BB			)},
		{ new PlotRenderer(this,	"13 Ingrijpen",						PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	false,	ingrijpenDivers,					"Ingrijpen diversiteit",			BB,		BB			)},

		
		{ GENEREERHET(				"13 Ingrijpen",						PlotType::HoriStaafGroepPerFilter,									false,	ingrijpenVervelend,					"Ingrijpen vervelend gedrag (altijd + vaak)",			BB,		BB			)},
		{ GENEREERHET(				"13 Ingrijpen",						PlotType::HoriStaafGroepPerFilter,									false,	ingrijpenPesten,					"Ingrijpen pesten en buitensluiten (altijd + vaak)",			BB,		BB			)},

		// 14
		{ new PlotRenderer(this,	"14 Ingrijpen II - doc",			PlotType::HoriStaafPerTypeRespondent,			PlotFilter::Type,	false,	ingrijpenVervelend,					"Ingrijpen vervelend (altijd + vaak)",			BB,		BB			)},
		{ new PlotRenderer(this,	"14 Ingrijpen II - doc",			PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Type,	false,	"afgelopenWeekVervelendeSituatiesGezien",					"Afgelopen week iets vervelends gezien?",			BB,		BB			)},
		{ new PlotRenderer(this,	"14 Ingrijpen II - doc",			PlotType::HoriStaafPerTypeRespondent,			PlotFilter::Type,	false,	ingrijpenPesten,					"Ingrijpen pesten en buitensluiten (altijd + vaak)",			BB,		BB			)},

		//15
		{ new PlotRenderer(this,	"15 Docenten en Mentoren",			PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Type,	false,	docentenMentoren,					"Docenten en mentoren",			BB,		BB			)},
		{ GENEREERHET(				"15 Docenten en Mentoren",			PlotType::HoriStaafGroepPerFilter,									false,	docentenMentoren,					"Docenten en mentoren (altijd + vaak)",			BB,		BB			)},

		//16
		{ new PlotRenderer(this,	"16 Docenten/Mentoren meer doen II",			PlotType::HoriStaafPerTypeRespondent,			PlotFilter::Type,	false,	docentenMentoren,				"Docenten en mentoren (altijd + vaak)",			BB,		BB			)},
		{ new PlotRenderer(this,	"16 Docenten/Mentoren meer doen II",			PlotType::HoriStaafPerTypeRespondent,			PlotFilter::Type,	false,	"waarMoetSchoolMeerAanDoen",	"Waar moet school meer aan doen?",			BB,		BB			)},

		// 17
		{ GENEREERHET(				"17 Meer doen",			PlotType::HoriStaafGroepPerFilter,				false,	"waarMoetSchoolMeerAanDoen",	"Waar moet school meer aan doen?",			BB,		BB			)},

		// 18
		{ new PlotRenderer(this,	"18 Beleid",			PlotType::HoriStaafMeerdereKolommen,			false, beleidKolommen,	"Beleid",				BB,		BB			)},
		{ GENEREERHETSL(			"18 Beleid",			PlotType::HoriStaafGroepPerFilter,				false, beleidKolommen,	"Beleid (ja)",			BB,		BB			)},

	};


}

void PlotRenderers::init()
{
	beginResetModel();
	for(auto & plotL : _plots)
		for(PlotRenderer * plot : plotL)
			plot->init();
	endResetModel();
}


int PlotRenderers::rowCount(const QModelIndex &) const
{
	return _plots.size();
}

QHash<int, QByteArray> PlotRenderers::roleNames() const
{
	static QHash<int, QByteArray> rolNamen = [&](){
		auto namen = QAbstractListModel::roleNames();
		namen[Qt::UserRole+0] = "filters";
		namen[Qt::UserRole+1] = "aspectData";
		namen[Qt::UserRole+2] = "hoogteData";
		namen[Qt::UserRole+3] = "titelData";
		namen[Qt::UserRole+4] = "bestandData";
		namen[Qt::UserRole+5] = "bestandAbsData";
		return namen;
	}();

	return rolNamen;
}

QVariant PlotRenderers::data(const QModelIndex & index, int role) const
{
	if(index.row() < 0 || index.row() >= int(_plots.size()))
		return QVariant();


	QVariantList lijst;
	for(PlotRenderer * plot : _plots[index.row()])
		if(role < Qt::UserRole)
			lijst.append(plot->plotUrl());
		else if(role == Qt::UserRole + 5)
			lijst.append(plot->plotFolder().absoluteFilePath(plot->fileName()));
		else if(role == Qt::UserRole + 4)
			lijst.append(plot->fileName());
		else if(role == Qt::UserRole + 3)
			lijst.append((plot->welkFilter() == PlotFilter::Type ? "Iedereen - " : plot->studenten() ? "Student - " : "Docent - ") + plot->title());
		else if(role == Qt::UserRole + 2)
			lijst.append(plot->height());
		else if(role == Qt::UserRole + 1)
			lijst.append(plot->height() > 0 ? float(plot->height()) / float(plot->width()) : 0);
		else
			lijst.append(PlotFilterToQString(plot->welkFilter()));

	return lijst;
}

void PlotRenderers::renderPlots()
{
	if(!_renderMaar)
		return;

	for(auto & plotL : _plots)
		for(PlotRenderer * plot : plotL)
			plot->runRCodeDelayed();

	setShowMe(true);
}

void PlotRenderers::plotRenderUpdated(PlotRenderer * plot)
{
	for(size_t i=0; i<_plots.size(); i++)
		for(auto * pr : _plots[i])
		if(pr == plot)
		{
			emit dataChanged(index(i), index(i));
			return;
		}
}


void PlotRenderers::setPlotFolder(const QDir & newPlotFolder)
{
	if (_plotFolder == newPlotFolder)
		return;

	_plotFolder = newPlotFolder;
	emit plotFolderChanged();
}

bool PlotRenderers::showMe() const
{
	return _showMe;
}

void PlotRenderers::setShowMe(bool newShowMe)
{
	if (_showMe == newShowMe)
		return;
	_showMe = newShowMe;
	emit showMeChanged();
}

bool PlotRenderers::renderMaar() const
{
	return _renderMaar;
}

void PlotRenderers::setRenderMaar(bool newRenderMaar)
{
	if (_renderMaar == newRenderMaar)
		return;
	_renderMaar = newRenderMaar;
	emit renderMaarChanged();


	renderPlots();
}
