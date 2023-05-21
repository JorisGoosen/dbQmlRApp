#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include "database.h"


class TableModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  TableModel(Database * db, const QString & tableName, const ColumnDefinitions & columnDefinitions);

	int			rowCount(	const QModelIndex &	parent = QModelIndex()) const override;
	int			columnCount(const QModelIndex &	parent = QModelIndex()) const override;
	QVariant	data(		const QModelIndex & index,										int role = Qt::DisplayRole) const override;
	QVariant	headerData(	int					section,	Qt::Orientation orientation,	int role = Qt::DisplayRole) const override;
	void		appendRows(const std::vector<QVariantList> & values, const ColumnDefinitions * columnDefinitions = nullptr);

	const QString			&	tableName()			const { return _tableName; }
	const ColumnDefinitions	&	columnDefinitions()	const { return _columnDefinitions;}

	QString		dbplyrCode() const;

private:
  Database			*   _db;
  QString				_tableName;
  ColumnDefinitions		_columnDefinitions;

};

#endif // TABLEMODEL_H
