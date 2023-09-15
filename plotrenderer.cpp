#define ENUM_DECLARATION_CPP
#include "plotrenderer.h"
#include <iostream>

PlotRenderer::PlotRenderer(QFile rFile, QString fileName, QDir outputFolder, QObject *parent)
	: QObject{parent}, _fileName(fileName), _plotFolder(outputFolder)
{
	rFile.open(			QIODeviceBase::ReadOnly);

	setRCode(rFile.readAll());
	rFile.close();

	init();
}

PlotRenderer::PlotRenderer(QString rCode, QString fileName, QDir outputFolder, QObject *parent)
	: QObject{parent}, _rCode(rCode), _fileName(fileName), _plotFolder(outputFolder)
{
	init();
}

QString PlotRenderer::plotUrl() const
{
	return	_plotFolder.absoluteFilePath(_fileName) + "?" + QString::number(revision());
}

void PlotRenderer::init()
{
	_timer.setInterval(50);
	_timer.setSingleShot(true);

	connect(&_timer, &QTimer::timeout, this, &PlotRenderer::runRCode);

	connect(this, &PlotRenderer::rCodeChanged,			this,	&PlotRenderer::runRCodeDelayed);
	connect(this, &PlotRenderer::widthChanged,			this,	&PlotRenderer::runRCodeDelayed);
	connect(this, &PlotRenderer::heightChanged,			this,	&PlotRenderer::runRCodeDelayed);
	connect(this, &PlotRenderer::plotFolderChanged,		this,	&PlotRenderer::runRCodeDelayed);
	connect(this, &PlotRenderer::revisionChanged,		this,	&PlotRenderer::plotUrlChanged);

	runRCode();
}

void PlotRenderer::runRCodeDelayed()
{
	emit plotUrlChanged();

	_timer.start();
}

void PlotRenderer::runRCode()
{
//	std::cout << "RUNNING RCODE!" << std::endl;
	emit runRCommand(	"WIDTH       <- "  + QString::number(width())		+  ";\n"
						"HEIGHT      <- "  + QString::number(height())		+  ";\n"
						"PLOTFILE    <- '" + _fileName						+ "';\n"
						"PLOTFOLDER  <- '" + _plotFolder.absolutePath()		+ "';\n" +
						"WELKPLOT    <- '" + PlotTypeToQString(_welkPlot)	+ "';\n" +
						"TITEL       <- '" + _title							+ "';\n" +
						 _rCode);

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
}

void PlotRenderer::setPlotFolder(const QDir & newPlotFolder)
{
	if (_plotFolder == newPlotFolder)
		return;

	_plotFolder = newPlotFolder;
	emit plotFolderChanged();
}

void PlotRenderer::setFileName(const QString & newFileName)
{
	if (_fileName == newFileName)
		return;
	_fileName = newFileName;
	emit fileNameChanged();
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
