#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include "database.h"
#include <QFontMetrics>
#include <QTextOption>


class TableModel : public QAbstractTableModel
{
	Q_OBJECT

	Q_PROPERTY(QFont	metricFont			READ metricFont			WRITE setMetricFont			NOTIFY metricFontChanged		)
	Q_PROPERTY(int		cellMargin			READ cellMargin			WRITE setCellMargin			NOTIFY cellMarginChanged		)


public:
  TableModel(Database * db, const QString & tableName, const ColumnDefinitions & columnDefinitions);

	int			rowCount(	const QModelIndex &	parent = QModelIndex()) const override;
	int			columnCount(const QModelIndex &	parent = QModelIndex()) const override;
	QVariant	data(		const QModelIndex & index,										int role = Qt::DisplayRole) const override;
	QVariant	headerData(	int					section,	Qt::Orientation orientation,	int role = Qt::DisplayRole) const override;
	void		appendRows(const std::vector<QVariantList> & values, const ColumnDefinitions * columnDefinitions = nullptr);

	const QString			&	tableName()			const { return _tableName; }
	const ColumnDefinitions	&	columnDefinitions()	const { return _columnDefinitions;}

	QString		dbplyrCode(bool doInit=true) const;

	Q_INVOKABLE int			columnWidthProvider(int col);
	Q_INVOKABLE int			rowHeightProvider(int row);

	QFont metricFont() const;
	void setMetricFont(const QFont & newMetricFont);

	int cellMargin() const;
	void setCellMargin(int newCellMargin);

signals:
	void	metricFontChanged();
	void	cellMarginChanged();

private:
	Database			*   _db;
	QString					_tableName;
	ColumnDefinitions		_columnDefinitions;

	QFont					_metricFont;
	QFontMetrics			_metrics;
	QRect					_maxBounds;
	QTextOption				_textOption;
	int						_maxWidthCol = 250,
							_cellMargin = 20;

};

#endif // TABLEMODEL_H
