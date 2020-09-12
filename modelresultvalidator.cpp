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
    auto token = m_meta->determineToken(line);

    if(token == ModelResultMeta::TokenType::SIGNALS) {
      m_meta->parseData();

      for(size_t i = 0; i < m_meta->getData().varCount; i++) {
        if(i >= MAX_COUNT_OF_SIGNALS) {
          E_WARNING(this) << "Limit of signals reached" << MAX_COUNT_OF_SIGNALS;
          break;
        }
        if(!file.atEnd()) {
          QByteArray signal = file.readLine();
          line.append(signal);
        } else {
          E_CRITICAL(this) << "Unexpected file end";
          break;
        }
      }

      m_meta->addToken(ModelResultMeta::TokenType::SIGNALS, line);
      break;
    } else if(token == ModelResultMeta::TokenType::UNKNOWN) {
      E_DEBUG(this) << "End of meta";
      break;
    } else {
      if(!m_meta->addToken(token, line)) {
        E_DEBUG(this) << "End of meta data";
        break;
      }
    }
  }

  E_DEBUG(this) << m_meta->getData();

  file.close();

  return m_meta;
}
