#include "filterlistmodel.h"

FilterListModel::FilterListModel(QString title, QString colName, QObject *parent)
	: QAbstractListModel(parent), _title(title), _colName(colName)
{
}

void FilterListModel::setLabels(QStringList allLabels)
{
	beginResetModel();

	_orderedLabels = allLabels;

	std::sort(_orderedLabels.begin(), _orderedLabels.end());

	endResetModel();
}

int FilterListModel::rowCount(const QModelIndex &parent) const
{
	// For list models only the root node (an invalid parent) should return the list's size. For all
	// other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
	if (parent.isValid())
		return 0;

	return _orderedLabels.size();
}

QVariant FilterListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	return _orderedLabels.size() <= index.row()
			? QVariant()
			: (role == Qt::DisplayRole
			   ? _orderedLabels[index.row()]
			   : QVariant(bool(_selectedLabels.count(_orderedLabels[index.row()]))));
}

bool FilterListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if((role != Qt::EditRole && role != Qt::CheckStateRole) || value.typeId() != QMetaType::Bool || index.row() >= _orderedLabels.size())
		return false;

	bool setEnabled = value.toBool();
	QString label = data(index).toString();

	if (_selectedLabels.count(label) != setEnabled)
	{
		if(setEnabled)	_selectedLabels.insert(label);
		else			_selectedLabels.erase(label);

		emit dataChanged(index, index, {role, Qt::DisplayRole, Qt::CheckStateRole});
		emit filterChanged();
		return true;
	}
	return false;
}

Qt::ItemFlags FilterListModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsUserCheckable;
}

QHash<int, QByteArray> FilterListModel::roleNames() const
{
	static QHash<int, QByteArray> _roleNames;

	if(_roleNames.size() == 0)
	{
		_roleNames = QAbstractListModel::roleNames();
		_roleNames[Qt::CheckStateRole] = "checkState";
	}

	return _roleNames;
}

QString FilterListModel::title() const
{
	return _title;
}

void FilterListModel::setTitle(const QString & newTitle)
{
	if (_title == newTitle)
		return;
	_title = newTitle;
	emit titleChanged();
}

QString FilterListModel::dbplyerFilter() const
{
	if(_selectedLabels.size() == 0) //nothing select == all
		return "";

	QStringList l;

	for(const QString & label : _selectedLabels)
		l.push_back(_colName + "=='" + label + "'");

	return "(" + l.join("|") + ")";
}
