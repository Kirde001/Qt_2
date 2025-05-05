#include "advanceddataprocessor.h"
#include <QDebug> // Убедимся, что QDebug включен здесь
#include <algorithm> // Нужно для std::reverse

AdvancedDataProcessor::AdvancedDataProcessor(QObject *parent) : QObject(parent)
{
    qDebug() << "Процесс создан";
}

void AdvancedDataProcessor::step1_ToUpper(const QString &input) {
    QString result = input.toUpper();
    emit step1Complete(result);
}

void AdvancedDataProcessor::step2_Reverse(const QString &input) {
    QString result = input;
    std::reverse(result.begin(), result.end());
    emit step2Complete(result);
}

void AdvancedDataProcessor::step3_LogAndFinalize(const QString &input) {
    qDebug() << "На вход" << input;
    qDebug() << "Результат:" << input;
    QString result = "Результатl: " + input;
    emit processingComplete(result);
}

