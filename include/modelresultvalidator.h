#ifndef MODELRESULTVALIDATOR_H
#define MODELRESULTVALIDATOR_H

#include <QObject>

class ModelResultMeta;

class ModelResultValidator : public QObject {
  Q_OBJECT
public:
  explicit ModelResultValidator(const QString& filename, QObject *parent = nullptr);
  const ModelResultMeta* validate();


private:
  QString m_filename;
  ModelResultMeta* m_meta = nullptr;
};

#endif // MODELRESULTVALIDATOR_H
