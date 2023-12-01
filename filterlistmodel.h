#ifndef FILTERLISTMODEL_H
#define FILTERLISTMODEL_H

#include <QAbstractListModel>
#include <set>
#include "columndefinition.h"

class FilterListModel : public QAbstractListModel
{
	Q_OBJECT
	Q_PROPERTY(QString				title		READ title		WRITE setTitle		NOTIFY titleChanged)
	Q_PROPERTY(QString				colName		READ colName	WRITE setColName	NOTIFY colNameChanged)
	Q_PROPERTY(ColumnDefinition *	cd			READ cd			WRITE setCd			NOTIFY cdChanged)
	Q_PROPERTY(bool					hasFilter	READ hasFilter						NOTIFY filterChanged)
	Q_PROPERTY(bool allowClicks READ allowClicks WRITE setAllowClicks NOTIFY allowClicksChanged)

public:
	explicit FilterListModel(QString title, QString colName, QObject *parent = nullptr);


	int						rowCount(	const QModelIndex &parent = QModelIndex())									const	override;
	QVariant				data(		const QModelIndex &index, int role = Qt::DisplayRole)						const	override;
	bool					setData(	const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)			override;
	Qt::ItemFlags			flags(		const QModelIndex& index)													const	override;
	QHash<int, QByteArray>	roleNames()																				const	override;

	bool			allowedThroughFilter(const QString & label) { return !_selectedLabels.size() || _selectedLabels.count(label); }


	ColumnDefinition *	cd()			const;
	bool				hasFilter()		const { return _selectedLabels.size() > 0; }
	QString				title()			const;
	QString				colName()		const;
	QString				dbplyerFilter() const;

	void				setTitle(const QString & newTitle);
	void				setColName(const QString & newColName);
	void				setLabels(QStringList allLabels);
	void				setCd(ColumnDefinition * newCd);

	bool allowClicks() const;
	void setAllowClicks(bool newAllowClicks);

signals:
	void titleChanged();
	void filterChanged();
	void colNameChanged();
	void cdChanged();

	void allowClicksChanged();

private:
	QStringList					_orderedLabels;
	std::set<QString>			_selectedLabels;
	QString						_title,
								_colName;
	ColumnDefinition	*		_cd					= nullptr;
	bool						_allowClicks		= true;
};

typedef std::vector<FilterListModel*> FilterListModels;

#endif // FILTERLISTMODEL_H
