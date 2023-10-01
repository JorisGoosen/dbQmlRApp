#include "plotrenderers.h"
#include "plotrenderer.h"
#include <iostream>

#define GENEREERHET(PLOTTYPE, STU, KOLOM, TITEL, W, H)									\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::School,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Locatie,	STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Sector,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Niveau,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Jaar,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Klas,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Gender,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Cultuur,	STU, KOLOM, TITEL, W, H)

#define GENEREERHETDOC(PLOTTYPE, STU, KOLOM, TITEL, W, H)									\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Gender,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Cultuur,	STU, KOLOM, TITEL, W, H)



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
					schoolKolommen		= "schoolJezelfZijn,schoolSfeerIsGoed,schoolRaadIkAan,schoolStudentenGediscrimineerd,schoolDiversVoeltThuis,schoolGoedOpschietenElkaar,schoolLiefstMetGelijkeAfkomstOm,schoolAnderenVoorgetrokkenAfkomstCultuurGeloof,schoolActueleGebeurtenissenMijAangaanBehandeldOpSchool,schoolStudentenZittenOngewildAlleen";


	const int BB = 1280; //basisbreedte

	_plots =
	{

		//veiligheid leerlingen
		{ new PlotRenderer(this,	PlotType::Taart,								PlotFilter::Geen,	true,	"veiligSchool",						"Veilig op school",									BB,		BB			)},
		{ new PlotRenderer(this,	PlotType::Taart,								PlotFilter::Geen,	true,	"veiligKlas",						"Veilig in de klas",								BB,		BB			)},
		{ GENEREERHET(				PlotType::VerticaalStaaf,											true,	"veiligSchool",						"Veilig op school",									BB,		BB * 0.75	)},
		{ GENEREERHET(				PlotType::VerticaalStaaf,											true,	"veiligKlas",						"Veilig in de klas",								BB,		BB * 0.75	)},
		{ GENEREERHET(				PlotType::HoriStaafGroepPerFilter,									true,	"onveiligHier",						"Voel me onveilig in bij",							BB,		BB + BB		)},
		{ new PlotRenderer(this,	PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	"bangOpSchool,graagNaarSchool",		"Hoe graag naar school en hoe bang",				BB,		BB / 3		)},
		{ GENEREERHET(				PlotType::HoriStaafPerLabel,										true,	"bangOpSchool",						"Bang op school",									BB,		BB + BB		)},
		{ GENEREERHET(				PlotType::HoriStaafPerLabel,										true,	"graagNaarSchool",					"Graag naar school",								BB,		BB + BB		)},

		// 3 veiligheid docenten
		{ new PlotRenderer(this,	PlotType::Taart,								PlotFilter::Geen,	false,	"veiligSchool",						"Veilig op school",									BB,		BB			)},
		{ new PlotRenderer(this,	PlotType::Taart,								PlotFilter::Geen,	false,	"veiligKlas",						"Veilig in de klas",								BB,		BB			)},
		{ GENEREERHETDOC(			PlotType::VerticaalStaaf,											false,	"veiligSchool",						"Veilig op school",									BB,		BB * 0.75	)},
		{ GENEREERHETDOC(			PlotType::VerticaalStaaf,											false,	"veiligKlas",						"Veilig in de klas",								BB,		BB * 0.75	)},
		//{ GENEREERHETDOC(			PlotType::HoriStaafGroepPerFilter,									false,	"onveiligHier",						"Voel me (on?)veilig in bij",						BB,		BB + BB		)},
		{ new PlotRenderer(this,	PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	false,	"bangOpSchool,werkMetPlezier",		"Bang op school en werkplezier",					BB,		BB / 3		)},
		{ GENEREERHETDOC(			PlotType::HoriStaafPerLabel,										false,	"bangOpSchool",						"Bang op school",									BB,		BB + BB		)},
		{ GENEREERHETDOC(			PlotType::HoriStaafPerLabel,										false,	"werkMetPlezier",					"Werk met plezier",									BB,		BB + BB		)},

		// 4 veiligheid II/doc
		{ new PlotRenderer(this,	PlotType::HoriStaafPerTypeRespondent,			PlotFilter::Geen,	true,	"bangOpSchool",						"Bang op school",									BB,		BB			)},
		//{ new PlotRenderer(this,	PlotType::HoriStaafGroepPerFilter,				PlotFilter::Type,	false,	"bangOpSchool",						"Bang op school",									BB,		BB			)},


		//5.1 + 5.2 In de klas:
		{ new PlotRenderer(this,	PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	klasKolommen,						"In de klas...",									BB,		BB			)},
		{ GENEREERHET(				PlotType::HoriStaafGroepPerFilter,									true,	"waaromVervelendeDingenInDeKlas" ,	"Waarom vervelende dingen in de klas",				BB,		BB			)},
		{ GENEREERHET(				PlotType::HoriStaafPerLabel,										true,	klasKolommen,						"In de klas (Altijd + vaak)...",					BB,		BB			)},

		//6 In de klas - II/doc
		{ new PlotRenderer(this,	PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Type,	true,	klasKolommen,						"In de klas (Altijd + vaak)...",					BB,		BB			)},
		{ new PlotRenderer(this,	PlotType::HoriStaafGroepPerFilter,				PlotFilter::Type,	true,	"waaromVervelendeDingenInDeKlas",	"Waarom vervelende dingen in de klas",				BB,		BB			)},

		//7.1 + 7.2 + 7.3 In de klas op school
		{ new PlotRenderer(this,	PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	studentKolommen,					"In de klas/op school zie ik",						BB,		BB			)},
		{ new PlotRenderer(this,	PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	ikWordKolommen,						"In de klas/op school word ik",						BB,		BB			)},
		{ new PlotRenderer(this,	PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	mijnWordkolommen,					"In de klas/op school worden mijn",					BB,		BB			)},
		{ new PlotRenderer(this,	PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	"klasOnveilig,schoolOnveilig",		"Onveilig voelen",									BB,		BB			)},

		{ GENEREERHET(				PlotType::HoriStaafGroepPerFilter,									true,	studentKolommen,					"In de klas/op school zie ik",						BB,		BB			)},
		{ GENEREERHET(				PlotType::HoriStaafGroepPerFilter,									true,	ikWordKolommen,						"In de klas/op school word ik",						BB,		BB			)},
		{ new PlotRenderer(this,	PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	mijnWordkolommen,					"In de klas/op school worden mijn",					BB,		BB			)},
		{ new PlotRenderer(this,	PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	"klasOnveilig,schoolOnveilig",		"Onveilig voelen (altijd + vaak)",					BB,		BB			)},

		// 8 In de klas zie ik (dagelijks + wekelijks), leerlingen en docenten
		{ new PlotRenderer(this,	PlotType::HoriStaafGroepPerFilter,				PlotFilter::Type,	true,	studentKolommen,					"In de klas/op school zie ik (dagelijks + wekelijks)",	BB,		BB			)},

		// 10 Op school
		{ new PlotRenderer(this,	PlotType::HoriStaafMeerdereKolommen,			PlotFilter::Geen,	true,	schoolKolommen,						"Op school - ...",										BB,		BB			)},
		{ GENEREERHET(				PlotType::HoriStaafGroepPerFilter,									true,	schoolKolommen,						"Op school (altijd + vaak) - ...",						BB,		BB			)},

		// 11 Op school en werkwijze II/doc
		{ new PlotRenderer(this,	PlotType::HoriStaafGroepPerFilter,				PlotFilter::Geen,	false,	schoolKolommen,						"Op school (altijd + vaak) - ...",						BB,		BB			)},
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
