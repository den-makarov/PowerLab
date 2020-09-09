#include "modelresultvalidator.h"
#include "modelresultmeta.h"
#include "logger.h"

ModelResultValidator::ModelResultValidator(const QString& filename, QObject *parent)
  : QObject(parent)
  , m_filename(filename)
{
  E_DEBUG(this) << "filename assigned" << filename;
  m_meta = new ModelResultMeta(this);
}

bool ModelResultValidator::validate() {
  if(m_filename.isEmpty()) {
    E_CRITICAL(this) << "empty filename";
    return false;
  }

  return true;
}
