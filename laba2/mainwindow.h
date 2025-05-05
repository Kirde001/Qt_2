#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QVariant>
#include "data_processor.h"
#include "advanceddataprocessor.h"
#include "processdialog.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private slots:
    void handleProcessedData(const QString &data);
    void onProcessButtonClicked();
    void onModeChanged(const QString &mode);

    void onVariantProcessButtonClicked(); //2

    void onAdvancedProcessButtonClicked(); // 3
    void handleIntermediateResult1(const QString &data); // шаг 1
    void handleIntermediateResult2(const QString &data); // 2
    void handleFinalAdvancedResult(const QString &data); // 3

    // 4
    void onOpenDialogButtonClicked();
    void handleDialogResult(const QString &result);


private:
    QLineEdit *inputField;
    QLabel *outputLabel;
    QPushButton *processButton;
    QComboBox *modeComboBox;
    DataProcessor *processor;

    QPushButton *variantProcessButton;
    QLabel *variantOutputLabel;

    QPushButton *advancedProcessButton;
    QLabel *intermediateLabel1;
    QLabel *intermediateLabel2;
    QLabel *finalAdvancedLabel;
    AdvancedDataProcessor *advancedProcessor;

    QPushButton *openDialogButton;
    QLabel *dialogResultLabel;


    void processVariantInput(const QString &text);
};

#endif // MAINWINDOW_H
