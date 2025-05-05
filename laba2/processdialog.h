#ifndef PROCESSDIALOG_H
#define PROCESSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class ProcessDialog : public QDialog {
    Q_OBJECT

public:
    explicit ProcessDialog(QWidget *parent = nullptr);
    ~ProcessDialog();

signals:
    void dataProcessedAndReady(const QString &result);

private slots:
    void onProcessDialogButtonClicked();
private:
    QLineEdit *inputField;
    QComboBox *modeComboBox;
    QPushButton *processButton;
    QLabel *resultLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QString processText(const QString &input, const QString &mode);
};

#endif // PROCESSDIALOG_H

