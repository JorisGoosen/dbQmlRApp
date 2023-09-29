#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "abstractsizeprovidertable.h"
#include <QObject>
#include "database.h"
#include "filterlistmodel.h"
Q_MOC_INCLUDE("tablemodelfiltered.h")

typedef std::map<QString, FilterListModel *> FilterListModelMap;

class TableModelFiltered;
class TableModel : public AbstractSizeProviderTable
{
  Q_OBJECT

	Q_PROPERTY(TableModelFiltered * filtered READ filtered NOTIFY filteredChanged)

	friend TableModelFiltered;

public:
								TableModel(Database * db, const QString & tableName, const ColumnDefinitions & columnDefinitions);

	int							rowCount(	const QModelIndex &	parent = QModelIndex()) const override;
	int							columnCount(const QModelIndex &	parent = QModelIndex()) const override;
	QVariant					data(		const QModelIndex & index,										int role = Qt::DisplayRole) const override;
	QVariant					headerData(	int					section,	Qt::Orientation orientation,	int role = Qt::DisplayRole) const override;
	void						appendRows(const std::vector<QVariantList> & values, const ColumnDefinitions * columnDefinitions = nullptr);
	void						clear();

	const QString			&	tableName()			const { return _tableName; }
	const ColumnDefinitions	&	columnDefinitions()	const { return _columnDefinitions;}

	QStringList					allUniqueLabels(const QString & colName, bool filter=true);
	QStringList					allLabels(		const QString & colName);

	QString						dbplyrCode(bool collect = true) const;
	bool						rowAccepted(int row) const;
	int							columnIndex(const QString & name) const;

	void						registerFilter(FilterListModel * lm);
	TableModelFiltered		*	filtered();

signals:
	void						filteredChanged();

protected:
	QString						tableValueVarToString(QVariant val, ColumnType type, bool addValue = false) const;

	QString						_tableName;
	ColumnDefinitions			_columnDefinitions;

private:
	Database				*   _db;
	TableModelFiltered		*	_filtered;
	int							_rowCount = -1;
	FilterListModelMap			_filters;
};

#endif // TABLEMODEL_H
