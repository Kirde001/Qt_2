#include "data_processor.h"
#include <algorithm>
#include <QString>

void DataProcessor::processData(const QString &input, const QString &mode) {
    QString processedData;

    if (mode == "В нижний регистр") {
        processedData = input.toLower();
    }
    else if (mode == "Обратный порядок") {
        processedData = input;
        std::reverse(processedData.begin(), processedData.end());
    } else if (mode == "Удалить пробелы") {
        processedData = input;
        processedData.remove(' ');
    } else {
        processedData = input;
    }

    emit dataProcessed(processedData);
}
