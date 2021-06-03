#ifndef MODELRESULTVALIDATOR_H
#define MODELRESULTVALIDATOR_H

#include <string>
#include <fstream>

class ModelResultMeta;

class ModelResultValidator {
public:
  ModelResultValidator();
  ~ModelResultValidator();

  bool validate(const std::string& filename);
  const ModelResultMeta* getMetaData() const {
    return m_meta;
  }

private:
  static constexpr int MAX_COUNT_OF_SIGNALS = 25;
  ModelResultMeta* m_meta;

  bool readSignalLines(std::ifstream& file, std::string& line);
};

#endif // MODELRESULTVALIDATOR_H
