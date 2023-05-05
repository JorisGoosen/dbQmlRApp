#include "rwrapper.h"

RWrapper::RWrapper(QObject *parent)
    : QObject{parent}
{

}

QString RWrapper::runRCommand(QString command)
{
  RInside::Proxy res = R.parseEvalNT("paste0(" + command.toStdString() + ")");

  std::string out;

  if(!Rf_isString(res))
    out = "???";
  else
    for(Rcpp::String str : Rcpp::StringVector(res))
      {
        out += str;
        out += "\n";
      }


  return QString::fromStdString(out);
}
