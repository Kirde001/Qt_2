#include "mainwindow.h"
#include "advanceddataprocessor.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QStringList>

#include <cmath>
#include <QDate>
#include <QDateTime>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    inputField = new QLineEdit(this);
    processButton = new QPushButton("Обработать", this);
    outputLabel = new QLabel("Результат: ", this);

    modeComboBox = new QComboBox(this);
    modeComboBox->addItems({"В нижний регистр", "Обратный порядок", "Удалить пробелы"});

    // 2
    variantProcessButton = new QPushButton("Обработка с QVariant, задание 2", this);
    variantOutputLabel = new QLabel("Результат QVariant: ", this);
    // 3
    advancedProcessButton = new QPushButton("Запустить цепочку обработки, задание 3", this);
    intermediateLabel1 = new QLabel("Шаг 1: ", this);
    intermediateLabel2 = new QLabel("Шаг 2: ", this);
    finalAdvancedLabel = new QLabel("Результат цепочки: ", this);
    // 4
    openDialogButton = new QPushButton("Открыть диалог обработки, задание 4", this);
    dialogResultLabel = new QLabel("Результат из диалога: ", this);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(inputField);
    layout->addWidget(modeComboBox);
    layout->addWidget(processButton);
    layout->addWidget(outputLabel);
    // 2
    layout->addWidget(variantProcessButton);
    layout->addWidget(variantOutputLabel);
    // 3
    layout->addWidget(advancedProcessButton);
    layout->addWidget(intermediateLabel1);
    layout->addWidget(intermediateLabel2);
    layout->addWidget(finalAdvancedLabel);
    // 4
    layout->addWidget(openDialogButton);
    layout->addWidget(dialogResultLabel);


    processor = new DataProcessor(this);
    advancedProcessor = new AdvancedDataProcessor(this);

    connect(processor, &DataProcessor::dataProcessed, this, &MainWindow::handleProcessedData);
    connect(processButton, &QPushButton::clicked, this, &MainWindow::onProcessButtonClicked);
    connect(modeComboBox, &QComboBox::currentTextChanged, this, &MainWindow::onModeChanged);
    //2
    connect(variantProcessButton, &QPushButton::clicked, this, &MainWindow::onVariantProcessButtonClicked);
    //3
    connect(advancedProcessButton, &QPushButton::clicked, this, &MainWindow::onAdvancedProcessButtonClicked);
    connect(advancedProcessor, &AdvancedDataProcessor::step1Complete, advancedProcessor, &AdvancedDataProcessor::step2_Reverse);
    connect(advancedProcessor, &AdvancedDataProcessor::step2Complete, advancedProcessor, &AdvancedDataProcessor::step3_LogAndFinalize);
    connect(advancedProcessor, &AdvancedDataProcessor::step1Complete, this, &MainWindow::handleIntermediateResult1);
    connect(advancedProcessor, &AdvancedDataProcessor::step2Complete, this, &MainWindow::handleIntermediateResult2);
    connect(advancedProcessor, &AdvancedDataProcessor::processingComplete, this, &MainWindow::handleFinalAdvancedResult);
    //4
    connect(openDialogButton, &QPushButton::clicked, this, &MainWindow::onOpenDialogButtonClicked);
}

void MainWindow::handleProcessedData(const QString &data) {
    outputLabel->setText("Результат: " + data);
}

void MainWindow::onProcessButtonClicked() {
    QString inputData = inputField->text();
    processor->processData(inputData, modeComboBox->currentText());
}

void MainWindow::onModeChanged(const QString &mode) {
    QString inputData = inputField->text();
    processor->processData(inputData, mode);
}

void MainWindow::onVariantProcessButtonClicked() {
    QString inputText = inputField->text();
    processVariantInput(inputText);
}


void MainWindow::processVariantInput(const QString &text) {
    QVariant variant(text);
    QString resultText = "Результат обработки QVariant: ";
    QString typeName = "";
    QVariant processedValue;

    bool ok;

    // Bool
    if (text.compare("true", Qt::CaseInsensitive) == 0) {
         variant = QVariant(true);
         processedValue = QVariant(!variant.toBool());
         typeName = "Boolean";
    } else if (text.compare("false", Qt::CaseInsensitive) == 0) {
         variant = QVariant(false);
         processedValue = QVariant(!variant.toBool());
         typeName = "Boolean";
    } else {
        // целое
        int intVal = text.toInt(&ok);
        if (ok) {
            variant = QVariant(intVal);
            processedValue = variant;
            typeName = "Integer";
        } else {
            // вещественное
            double doubleVal = text.toDouble(&ok);
            if (ok) {
                variant = QVariant(doubleVal);
                processedValue = QVariant(std::round(variant.toDouble()));
                typeName = "Double";
            } else {
                // дата
                QDate dateVal = QDate::fromString(text, Qt::ISODate);
                if (dateVal.isValid()) {
                    variant = QVariant(dateVal);
                    processedValue = QVariant(variant.toDate().addDays(1));
                    typeName = "Date";
                } else {
                     // дата и время
                     QDateTime dateTimeVal = QDateTime::fromString(text, Qt::ISODate);
                     if (dateTimeVal.isValid()) {
                        variant = QVariant(dateTimeVal);
                        processedValue = QVariant(variant.toDateTime().addSecs(60));
                        typeName = "DateTime";
                     } else {
                        // строка
                        processedValue = variant; // Оставляем как есть
                        typeName = "String";
                     }
                }
            }
        }
    }


    if (!typeName.isEmpty()) {
         resultText += QString("Тип: %1, Обработано: %2").arg(typeName).arg(processedValue.toString());
    } else {
         resultText += QString("Не удалось определить тип или обработать: %1").arg(text);
    }


    variantOutputLabel->setText(resultText);
}


void MainWindow::onAdvancedProcessButtonClicked() {
    QString inputText = inputField->text();
    QMetaObject::invokeMethod(advancedProcessor, "step1_ToUpper", Qt::QueuedConnection,
                              Q_ARG(QString, inputText));
}

void MainWindow::handleIntermediateResult1(const QString &data) {
    intermediateLabel1->setText("Шаг 1: " + data);
}

void MainWindow::handleIntermediateResult2(const QString &data) {
    intermediateLabel2->setText("Шаг 2: " + data);
}

void MainWindow::handleFinalAdvancedResult(const QString &data) {
    finalAdvancedLabel->setText("Результат цепочки: " + data);
}


void MainWindow::onOpenDialogButtonClicked() {
    ProcessDialog *dialog = new ProcessDialog(this);
    connect(dialog, &ProcessDialog::dataProcessedAndReady, this, &MainWindow::handleDialogResult);
    dialog->exec();
}
void MainWindow::handleDialogResult(const QString &result) {
    dialogResultLabel->setText("Результат из диалога: " + result);
}
