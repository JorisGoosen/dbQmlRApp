#ifndef IMPORTER_H
#define IMPORTER_H

#include "abstractsizeprovidertable.h"
#include "columndefinition.h"

class SchoolScannerTable;
class Labels;

struct ImportColumn
{
	ImportColumn(const QString & nameCSV, const QString & nameDB = "")
		: nameCSV(nameCSV), nameDB(nameDB)
	{}

	ImportColumn(ColumnDefinition * cd, QStringList values)
		: importMe(cd), nameCSV(cd->friendlyName()), nameDB(cd->dbName()), values(values), cd(cd)
	{}

	void setCD(ColumnDefinition * cdNew)
	{
		cd			= cdNew;
		importMe	= cd;
		nameDB		= importMe ? cd->dbName() : "";
	}

	bool						importMe = false;
	QString						nameCSV,
								nameDB;
	QStringList					values;
	ColumnDefinition		*	cd = nullptr;
};

typedef std::vector<ImportColumn*> ImportColumns;

class Importer : public AbstractSizeProviderTable
{
	Q_OBJECT

	Q_PROPERTY(QString		schoolType			READ schoolType			WRITE setSchoolType			NOTIFY schoolTypeChanged		)
	Q_PROPERTY(QString		type				READ type				WRITE setType				NOTIFY typeChanged				)
	Q_PROPERTY(bool			canImport			READ canImport			WRITE setCanImport			NOTIFY canImportChanged			)
	Q_PROPERTY(QStringList	ignoredCols			READ ignoredCols		WRITE setIgnoredCols		NOTIFY ignoredColsChanged		)
	Q_PROPERTY(bool			needsReset			READ needsReset			WRITE setNeedsReset			NOTIFY needsResetChanged		)
	Q_PROPERTY(QStringList	columnTitles		READ columnTitles		CONSTANT		)

public:
	explicit Importer(SchoolScannerTable * table, Labels * labels);

	int			rowCount(	const QModelIndex &	parent = QModelIndex()) const override;
	int			columnCount(const QModelIndex &	parent = QModelIndex()) const override;
	QVariant	data(		const QModelIndex & index,										int role = Qt::DisplayRole) const override;
	QVariant	headerData(	int					section,	Qt::Orientation orientation,	int role = Qt::DisplayRole) const override;

	void		collectDbColumns();
	void		processValues();


	Q_INVOKABLE void		importCsv(const QString & csvFile);
	Q_INVOKABLE bool		importCsv(QTextStream & csvStream, QChar sepa = ';');
	Q_INVOKABLE void		clearColumns();

	QStringList columnTitles() const;


	QString schoolType()	const;
	QString type()			const;


	bool canImport() const;
	void setCanImport(bool newCanImport);

	QStringList ignoredCols() const;
	void setIgnoredCols(const QStringList &newIgnoredCols);

	bool needsReset() const;
	void setNeedsReset(bool newNeedsReset);

public slots:
	void actuallyImport();
	void setSchoolType(	const QString & newSchoolType);
	void setType(		const QString & newType);


signals:
	void	openingFileFailed(const QString & filename, const QString & error);
	void	schoolTypeChanged();
	void	typeChanged();
	void	canImportChanged();
	void	showData();

	void	ignoredColsChanged();

	void needsResetChanged();

private:
	ImportColumns			_columns;
	SchoolScannerTable	*	_table			= nullptr;
	Labels				*	_labels			= nullptr;

	QString					_schoolType		= "VO",
							_type			= "Leerlingen";
	QStringList				_ignoredCols;
	bool					_canImport		= false,
							_needsReset;
};

#endif // IMPORTER_H
