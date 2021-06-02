#ifndef MODELRESULTVALIDATOR_H
#define MODELRESULTVALIDATOR_H

#include <QObject>
#include <QFile>

class ModelResultMeta;

class ModelResultValidator : public QObject {
  Q_OBJECT
public:
  explicit ModelResultValidator(QObject *parent = nullptr);
  virtual ~ModelResultValidator();

  bool validate(const QString& filename);
  const ModelResultMeta* getMetaData() const {
    return m_meta;
  }

private:
  static constexpr size_t MAX_COUNT_OF_SIGNALS = 25;
  ModelResultMeta* m_meta;

  bool readSignalLines(QFile& file, QByteArray& line);
};

#endif // MODELRESULTVALIDATOR_H
