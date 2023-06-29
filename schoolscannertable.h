#ifndef SCHOOLSCANNERTABLE_H
#define SCHOOLSCANNERTABLE_H

#include "tablemodel.h"
#include "schoolscannerdefinities.h"
#include "filterlistmodel.h"
#include "plotrenderer.h"

class SchoolScannerTable : public TableModel
{
	Q_OBJECT
	Q_PROPERTY(FilterListModel * school		READ school		NOTIFY schoolChanged)
	Q_PROPERTY(FilterListModel * locatie	READ locatie	NOTIFY locatieChanged)
	Q_PROPERTY(FilterListModel * sector		READ sector		NOTIFY sectorChanged)
	Q_PROPERTY(FilterListModel * niveau		READ niveau		NOTIFY niveauChanged)
	Q_PROPERTY(FilterListModel * leerjaar	READ leerjaar	NOTIFY leerjaarChanged)
	Q_PROPERTY(FilterListModel * klas		READ klas		NOTIFY klasChanged)
	Q_PROPERTY(FilterListModel * gender		READ gender		NOTIFY genderChanged)
	Q_PROPERTY(FilterListModel * cultuur	READ cultuur	NOTIFY cultuurChanged)


public:
	SchoolScannerTable(Database * db);

	const ColumnDefinition * findDbColumn(const QString & csvName);

	FilterListModel * school()		{ return &_school;		}
	FilterListModel * locatie()		{ return &_locatie;		}
	FilterListModel * sector()		{ return &_sector;		}
	FilterListModel * niveau()		{ return &_niveau;		}
	FilterListModel * leerjaar()	{ return &_leerjaar;	}
	FilterListModel * klas()		{ return &_klas;		}
	FilterListModel * gender()		{ return &_gender;		}
	FilterListModel * cultuur()		{ return &_cultuur;		}

	QString dbplyerFilter() const;


public slots:
	void loadFilters();
	void initPlots();
	void initRStuff();

signals:
	void schoolChanged();
	void locatieChanged();
	void sectorChanged();
	void niveauChanged();
	void leerjaarChanged();
	void klasChanged();
	void genderChanged();
	void cultuurChanged();
	void runRCommand(const QString & command);
	void plotWidthChanged(int plotWidth);
	void plotHeightChanged(int plotHeight);
	void addContextProperty(const QString & name, QObject * object);

private:
	FilterListModel					_school		= FilterListModel("School",		"school"),
									_locatie	= FilterListModel("Locatie",	"locatie"),
									_sector		= FilterListModel("Sector",		"sector"),
									_niveau		= FilterListModel("Niveau",		"niveau"),
									_leerjaar	= FilterListModel("Leerjaar",	"jaar"),
									_klas		= FilterListModel("Klas",		"klas"),
									_gender		= FilterListModel("Gender",		"gender"),
									_cultuur	= FilterListModel("Cultuur",	"cultuur");
	FilterListModels				_filters;

	TableModel					*	_textOnly	= nullptr;

	PlotRenderer				*	_plotPie	= nullptr;

	std::vector<QStringList>		_columns;


};

#endif // SCHOOLSCANNERTABLE_H
