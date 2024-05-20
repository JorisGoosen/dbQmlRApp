#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "abstractsizeprovidertable.h"
#include <QObject>
#include "database.h"


class TableModel : public AbstractSizeProviderTable
{
  Q_OBJECT

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

	QStringList					allUniqueLabels(const QString & colName);
	QStringList					allLabels(		const QString & colName);

	QString						dbplyrCode(bool collect = true) const;
	bool						rowAccepted(int row) const;
	int							columnIndex(const QString & name) const;

protected:
	QString						tableValueVarToString(QVariant val, ColumnType type, bool addValue = false) const;

	QString						_tableName;
	ColumnDefinitions			_columnDefinitions;

private:
	Database				*   _db;
	int							_rowCount = -1;
};

#endif // TABLEMODEL_H
