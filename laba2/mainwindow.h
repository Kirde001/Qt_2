#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include "data_processor.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private slots:
    void handleProcessedData(const QString &data);
    void onProcessButtonClicked();
    void onModeChanged(const QString &mode);
private:
    QLineEdit *inputField;
    QLabel *outputLabel;
    QPushButton *processButton;
    QComboBox *modeComboBox;
    DataProcessor *processor;
};

#endif // MAINWINDOW_H
