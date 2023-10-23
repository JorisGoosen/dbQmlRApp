#include "plotrenderers.h"
#include <QUrl>

#define ENUM_DECLARATION_CPP
#include "plotrenderer.h"
#include <iostream>

/*
PlotRenderer::PlotRenderer(QFile rFile, QString fileName, QDir outputFolder, QObject *parent)
	: QObject{parent}, _fileName(fileName)
{
	rFile.open(			QIODeviceBase::ReadOnly);

	setRCode(rFile.readAll()
#ifdef WIN32
						  .replace("\r", "")
#endif
);
	rFile.close();

	init();
}

PlotRenderer::PlotRenderer(QString rCode, QString fileName, QDir outputFolder, QObject *parent)
	: QObject{parent}, _rCode(rCode), _fileName(fileName)
{
	init();
}*/

PlotRenderer::PlotRenderer(PlotRenderers * renderers, QString sectie, PlotType plotType, PlotFilter filter, bool studenten, const QString & kolom, const QString & title, int width, int height)
: QObject{renderers}, _ouder(renderers), _title(title), _kolom(kolom), _sectie(sectie), _studenten(studenten), _width(width), _height(height), _welkPlot(plotType), _welkFilter(filter)
{
	const QString baseName =  (_welkFilter == PlotFilter::Type ? "Iedereen_" : (studenten ? "Studenten_" : "Docenten_")) + PlotTypeToQString(_welkPlot) +
							 "_" + PlotFilterToQString(_welkFilter) + "Filter_" + kolom.left(std::min(qsizetype(20), kolom.size())).replace(",", "_");

	if(_title == "")
		_title = baseName;

	_fileName =  baseName + ".png";
	_rCode = " dontShowPlot <- " + PlotTypeToQString(_welkPlot) + "Func(plotFolder=PLOTFOLDER, plotFile=PLOTFILE, width=WIDTH, height=HEIGHT, titel=TITEL, kolom=KOLOM, filter=FILTER, studenten=STUDENTEN);";
}

QDir PlotRenderer::plotFolder() const
{
	return _ouder->plotFolder();
}

QString PlotRenderer::plotUrl() const
{
	//if(_running)
	//	return "";
//#ifdef WIN32
//	QString out = plotFolder().absoluteFilePath(_fileName);
//#else
	QString folder=plotFolder().dirName();

	QString out = "file:///"+ QUrl(plotFolder().absoluteFilePath(_fileName)).toString().replace(":", "%3A") + "?" + QString::number(revision());
//#endif
	std::cerr << "PlotRenderer::plotUrl(): " << out.toStdString() << std::endl;

	return out;
}

void PlotRenderer::init()
{

	connect(&_timer, &QTimer::timeout, this, &PlotRenderer::runRCode);

	connect(this, &PlotRenderer::rCodeChanged,			this,	&PlotRenderer::runRCodeDelayed		);
	//connect(this, &PlotRenderer::widthChanged,			this,	&PlotRenderer::runRCodeDelayed		);
	//connect(this, &PlotRenderer::heightChanged,			this,	&PlotRenderer::runRCodeDelayed		);
	connect(this, &PlotRenderer::plotFolderChanged,		this,	&PlotRenderer::runRCodeDelayed		);
	connect(this, &PlotRenderer::revisionChanged,		this,	&PlotRenderer::plotUrlChanged		);
	connect(this, &PlotRenderer::iUpdated,				_ouder,	&PlotRenderers::plotRenderUpdated	);
	connect(this, &PlotRenderer::runRCommand,			_ouder,	&PlotRenderers::runRCommand			);
	connect(this, &PlotRenderer::runRCommands,			_ouder,	&PlotRenderers::runRCommands		);


	//runRCode();
}

void PlotRenderer::runRCodeDelayed()
{
	setRunning(true);

	_timer.setInterval(50);
	_timer.setSingleShot(true);
	_timer.start();
}


void PlotRenderer::runRCode()
{
	std::cout << "PlotRenderer::runRCode " << _rCodeCalled++ << "!" << std::endl;
	QString hoogte = emit runRCommand(
						"TITEL       <- '" + _title														+ "';\n"+
						"WIDTH       <- "  + QString::number(width())									+  ";\n"+
						"PLOTFILE    <- '" + _fileName													+ "';\n"+
						"PLOTFOLDER  <- '" +
							QDir::toNativeSeparators(plotFolder().absolutePath()).replace("\\", "\\\\")	+ "';\n"+
						"STUDENTEN   <- "  + QString(_studenten ? "TRUE" : "FALSE")						+ "; \n"+
						"WELKPLOT    <- '" + PlotTypeToQString(_welkPlot)								+ "';\n"+
						"HEIGHT      <- "  + QString::number(height())									+  ";\n"+
						"FILTER      <- '" + PlotFilterToQString(_welkFilter).toLower()					+ "';\n"+
						"KOLOM       <- '" + _kolom														+ "';\n"+
						"# " + QString::number(_rCodeCalled) + "\n" +
						 _rCode																			+ "\n" +
						//"warnings();\n"
						"HEIGHT\n");

	bool ok = false;
	int h = hoogte.toInt(&ok);
	if(ok)
		setHeight(h);

	setRunning(false);
	incRevision();
}

void PlotRenderer::setRCode(const QString & newRCode)
{
	if (_rCode == newRCode)
		return;

	_rCode = newRCode;
	emit rCodeChanged();
}


void PlotRenderer::setWidth(int newWidth)
{
	if (_width == newWidth)
		return;

	_width = newWidth;
	emit widthChanged();
}


void PlotRenderer::setHeight(int newHeight)
{
	if (_height == newHeight)
		return;

	_height = newHeight;
	emit heightChanged();
}

void PlotRenderer::incRevision()
{
	_revision++;

	emit revisionChanged();
	emit iUpdated(this);
}


PlotType PlotRenderer::welkPlot() const
{
	return _welkPlot;
}

void PlotRenderer::setWelkPlot(const PlotType & newWelkPlot)
{
	if (_welkPlot == newWelkPlot)
		return;
	_welkPlot = newWelkPlot;
	emit welkPlotChanged();
}

QString PlotRenderer::title() const
{
	return _title;
}

void PlotRenderer::setTitle(const QString & newTitle)
{
	if (_title == newTitle)
		return;
	_title = newTitle;
	emit titleChanged();
}

PlotFilter PlotRenderer::welkFilter() const
{
	return _welkFilter;
}

void PlotRenderer::setWelkFilter(const PlotFilter & newWelkFilter)
{
	if (_welkFilter == newWelkFilter)
		return;
	_welkFilter = newWelkFilter;
	emit welkFilterChanged();
}

QString PlotRenderer::kolom() const
{
	return _kolom;
}

void PlotRenderer::setKolom(const QString & newKolom)
{
	if (_kolom == newKolom)
		return;
	_kolom = newKolom;
	emit kolomChanged();
}

bool PlotRenderer::running() const
{
	return _running;
}

void PlotRenderer::setRunning(bool newRunning)
{
	if (_running == newRunning)
		return;
	_running = newRunning;

	std::cerr<< "Plot " << _fileName.toStdString() << " is now " << (newRunning ? "RUNNING": "NOT RUNNING") << std::endl;

	emit runningChanged();
	emit plotUrlChanged();
}
