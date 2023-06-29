#ifndef FILTERLISTMODEL_H
#define FILTERLISTMODEL_H

#include <QAbstractListModel>
#include <set>

class FilterListModel : public QAbstractListModel
{
	Q_OBJECT
	Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

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

signals:
	void titleChanged();

private:
	QStringList					_orderedLabels;
	std::set<QString>			_selectedLabels;
	QString						_title,
								_colName;
};

typedef std::vector<FilterListModel*> FilterListModels;

#endif // FILTERLISTMODEL_H
