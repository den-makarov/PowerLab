#ifndef MODELRESULTVALIDATOR_H
#define MODELRESULTVALIDATOR_H

#include <string>
#include <fstream>
#include <memory>

namespace PowerLab {
namespace ModelResult {

class ModelResultMeta;

class ModelResultValidator {
public:
  ModelResultValidator();

  bool validate(const std::string& filename);
  const ModelResultMeta& getMetaData() const {
    return *m_meta;
  }

private:
  static constexpr int MAX_COUNT_OF_SIGNALS = 25;
  std::unique_ptr<ModelResultMeta> m_meta;

  bool readSignalLines(std::ifstream& file, std::string& line);
};

} // namespace ModelResult
} // namespace PowerLab

#endif // MODELRESULTVALIDATOR_H
