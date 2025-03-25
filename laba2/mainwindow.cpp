#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    inputField = new QLineEdit(this);
    processButton = new QPushButton("Обработать", this);
    outputLabel = new QLabel("Результат: ", this);

    modeComboBox = new QComboBox(this);
    modeComboBox->addItems({"В нижний регистр", "Обратный порядок", "Удалить пробелы"});

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(inputField);
    layout->addWidget(modeComboBox);
    layout->addWidget(processButton);
    layout->addWidget(outputLabel);

    processor = new DataProcessor(this);

    connect(processor, &DataProcessor::dataProcessed, this, &MainWindow::handleProcessedData);
    connect(processButton, &QPushButton::clicked, this, &MainWindow::onProcessButtonClicked);
    connect(modeComboBox, &QComboBox::currentTextChanged, this, &MainWindow::onModeChanged); // Связываем изменение режима с обработкой
}

void MainWindow::handleProcessedData(const QString &data) {
    outputLabel->setText("Результат: " + data);
}

void MainWindow::onProcessButtonClicked() {
    QString inputData = inputField->text();
    processor->processData(inputData, modeComboBox->currentText()); // Передаем режим обработки
}

void MainWindow::onModeChanged(const QString &mode) {
    // Обновляем результат в реальном времени
    QString inputData = inputField->text();
    processor->processData(inputData, mode);
}
