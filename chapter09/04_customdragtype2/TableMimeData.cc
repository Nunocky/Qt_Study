#include <QtGui>
#include <QtWidgets>

#include "TableMimeData.h"

TableMimeData::TableMimeData(const QTableWidget *tableWidget, 
                             const QTableWidgetSelectionRange &range)
{
  myTableWidget = tableWidget;
  myRange = range;
  myFormats << "text/csv" << "text/html" << "text/plain";
}

QStringList 
TableMimeData::formats() const
{
  return myFormats;
}

QVariant
TableMimeData::retrieveData(const QString &format, 
                            QVariant::Type preferredType) const
{
  if (format == "text/plain") {
    return rangeAsPlainText();
  }
  else if (format == "text/csv") {
    return TableMimeData::toCsv(rangeAsPlainText());
  }
  else if (format == "text/html") {
    return TableMimeData::toHtml(rangeAsPlainText());
  }

  return QMimeData::retrieveData(format, preferredType);
}

QString
TableMimeData::text(int row, int column) const
{
  // TODO : IMPLEMENT THIS
  return "";
}

QString
TableMimeData::rangeAsPlainText() const
{
  // TODO : IMPLEMENT THIS
  return "";
}


QString 
TableMimeData::toHtml(const QString &plainText)
{
  QString result = plainText.toHtmlEscaped();
  result.replace("\t","<td>");
  result.replace("\n","\n<tr><td>");
  result.prepend("<table>\n<tr><td>");
  result.append("\n</table>");

  return result;
}

QString 
TableMimeData::toCsv(const QString &plainText)
{
  QString result = plainText;

  result.replace("\\", "\\\\");
  result.replace("\"", "\\\"");
  result.replace("\t", "\", \"");
  result.replace("\n", "\"\n\"");
  result.prepend("\"");
  result.append("\"");
  return result;
}


