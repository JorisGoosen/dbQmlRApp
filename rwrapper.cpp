#include "rwrapper.h"

RWrapper::RWrapper(QObject *parent)
	: QObject{parent}, R(new RInside(0, nullptr, true, false, false))
{

}

QString RWrapper::runRCommand(QString command)
{
	std::cout << "Running R command:\n" << command.toStdString() << std::endl;

	RInside::Proxy res = R->parseEvalNT(command.toStdString());

	std::function<QString(SEXP sexp)> f;

	f = [&](SEXP res)
	{
		QStringList out;

		if(Rf_isString(res))
			for(Rcpp::String str : Rcpp::StringVector(res))
				out.append(QString::fromStdString(str));
		else if(Rf_isInteger(res))
			for(int r : Rcpp::IntegerVector(res))
				out.append(QString::number(r));
		else if(Rf_isReal(res))
			for(double r : Rcpp::DoubleVector(res))
				out.append(QString::number(r));
		else if(Rf_isNull(res))
			out.append("NULL");
		else if(Rf_isList(res))
			for(SEXP s : Rcpp::List(res))
				out.append(f(s));
		else
			out.append("???");


		return out.join("\n");
	};

	QString outQ = f(res);

	std::cout << ": " << outQ.toStdString() << std::endl;

	_prevOutput.append(outQ);
	emit prevOutputChanged();

	return outQ;
}

QStringList RWrapper::prevOutput() const
{
	return _prevOutput;
}

void RWrapper::setPrevOutput(const QStringList & newPrevOutput)
{
	if (_prevOutput == newPrevOutput)
		return;

	_prevOutput = newPrevOutput;
	emit prevOutputChanged();
}

int RWrapper::plotWidth() const
{
	return std::max(10, _plotWidth);
}

void RWrapper::setPlotWidth(int newPlotWidth)
{
	if (_plotWidth == newPlotWidth)
		return;

	_plotWidth = newPlotWidth;
	emit plotWidthChanged(_plotWidth);
}

int RWrapper::plotHeight() const
{
	return std::max(10, _plotHeight);
}

void RWrapper::setPlotHeight(int newPlotHeight)
{
	if (_plotHeight == newPlotHeight)
		return;

	_plotHeight = newPlotHeight;
	emit plotHeightChanged(_plotHeight);
}
