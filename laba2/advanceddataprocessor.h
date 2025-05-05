#ifndef ADVANCED_DATA_PROCESSOR_H
#define ADVANCED_DATA_PROCESSOR_H

#include <QObject>
#include <QString>

class AdvancedDataProcessor : public QObject {
    Q_OBJECT

public:
    explicit AdvancedDataProcessor(QObject *parent = nullptr);

public slots:
    void step1_ToUpper(const QString &input);
    void step2_Reverse(const QString &input);
    void step3_LogAndFinalize(const QString &input);

signals:
    void step1Complete(const QString &result);
    void step2Complete(const QString &result);
    void processingComplete(const QString &finalResult);
};

#endif // ADVANCED_DATA_PROCESSOR_H

