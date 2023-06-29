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

public slots:
	void loadFilters();
	void initPlots();

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
	FilterListModel		_school		= FilterListModel("School"),
						_locatie	= FilterListModel("Locatie"),
						_sector		= FilterListModel("Sector"),
						_niveau		= FilterListModel("Niveau"),
						_leerjaar	= FilterListModel("Leerjaar"),
						_klas		= FilterListModel("Klas"),
						_gender		= FilterListModel("Gender"),
						_cultuur	= FilterListModel("Cultuur");

	TableModel		*	_textOnly	= nullptr;

	PlotRenderer	*	_plotPie	= nullptr;


};

#endif // SCHOOLSCANNERTABLE_H
