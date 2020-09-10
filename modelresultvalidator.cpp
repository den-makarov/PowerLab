#include <QFile>

#include "modelresultvalidator.h"
#include "modelresultmeta.h"
#include "logger.h"

ModelResultValidator::ModelResultValidator(const QString& filename, QObject *parent)
  : QObject(parent)
  , m_filename(filename)
  , m_meta(new ModelResultMeta(this))
{
  E_DEBUG(this) << "filename assigned" << filename;
}

const ModelResultMeta* ModelResultValidator::validate() {
  if(m_filename.isEmpty()) {
    E_CRITICAL(this) << "empty filename";
    return nullptr;
  }

  QFile file(m_filename);
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return nullptr;
  }

  while(!file.atEnd()) {
    QByteArray line = file.readLine();
    if(!m_meta->addToken(line)) {
      E_DEBUG(this) << "End of meta data";
      break;
    }
  }

  m_meta->parseData();
  E_DEBUG(this) << m_meta->getData();
  return m_meta;
}
