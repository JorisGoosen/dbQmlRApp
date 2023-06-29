#ifndef FILTERLISTMODEL_H
#define FILTERLISTMODEL_H

#include <QAbstractListModel>
#include <set>

class FilterListModel : public QAbstractListModel
{
	Q_OBJECT

public:
	explicit FilterListModel(QObject *parent = nullptr);

	void	setLabels(QStringList allLabels);

	// Basic functionality:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	// Editable:
	bool setData(const QModelIndex &index, const QVariant &value,
				 int role = Qt::EditRole) override;

	Qt::ItemFlags flags(const QModelIndex& index) const override;

	QHash<int, QByteArray> roleNames() const override;

private:
	QStringList					_orderedLabels;
	std::set<QString>			_selectedLabels;

};

#endif // FILTERLISTMODEL_H
