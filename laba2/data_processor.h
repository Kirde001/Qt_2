#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <QObject>

class DataProcessor : public QObject {
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = nullptr) : QObject(parent) {}
    void processData(const QString &input, const QString &mode);
signals:
    void dataProcessed(const QString &result);
};

#endif // DATA_PROCESSOR_H
