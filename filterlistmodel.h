#ifndef FILTERLISTMODEL_H
#define FILTERLISTMODEL_H

#include <QAbstractListModel>
#include <set>
#include "columndefinition.h"

class FilterListModel : public QAbstractListModel
{
	Q_OBJECT
	Q_PROPERTY(QString				title	READ title		WRITE setTitle		NOTIFY titleChanged)
	Q_PROPERTY(QString				colName	READ colName	WRITE setColName	NOTIFY colNameChanged)
	Q_PROPERTY(ColumnDefinition *	cd		READ cd			WRITE setCd			NOTIFY cdChanged)

public:
	explicit FilterListModel(QString title, QString colName, QObject *parent = nullptr);

	void	setLabels(QStringList allLabels);

	// Basic functionality:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	// Editable:
	bool setData(const QModelIndex &index, const QVariant &value,
				 int role = Qt::EditRole) override;

	Qt::ItemFlags flags(const QModelIndex& index) const override;

	QHash<int, QByteArray> roleNames() const override;

	QString title() const;
	void setTitle(const QString & newTitle);

	QString dbplyerFilter() const;

	QString colName() const;
	void setColName(const QString & newColName);

	bool allowedThroughFilter(const QString & label) { return !_selectedLabels.size() || _selectedLabels.count(label); }

	ColumnDefinition * cd() const;
	void setCd(ColumnDefinition * newCd);

signals:
	void titleChanged();
	void filterChanged();

	void colNameChanged();

	void cdChanged();

private:
	QStringList					_orderedLabels;
	std::set<QString>			_selectedLabels;
	QString						_title,
	_colName;
	ColumnDefinition * _cd = nullptr;
};

typedef std::vector<FilterListModel*> FilterListModels;

#endif // FILTERLISTMODEL_H
