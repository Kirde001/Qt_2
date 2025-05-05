#include "processdialog.h"
#include <algorithm>
#include <QHBoxLayout>

ProcessDialog::ProcessDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Диалог обработки данных");
    setMinimumWidth(650);

    inputField = new QLineEdit(this);
    modeComboBox = new QComboBox(this);

    modeComboBox->addItems({"В нижний регистр", "Обратный порядок", "Удалить пробелы", "Без изменений"});
    processButton = new QPushButton("Обработать в диалоге", this);
    resultLabel = new QLabel("Результат в диалоге: ", this);
    okButton = new QPushButton("Выйти", this);
    cancelButton = new QPushButton("Отмена", this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Введите текст:", this));
    layout->addWidget(inputField);
    layout->addWidget(new QLabel("Выберите режим обработки:", this));
    layout->addWidget(modeComboBox);
    layout->addWidget(processButton);
    layout->addWidget(resultLabel);
    layout->addStretch();

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    layout->addLayout(buttonLayout);

    setLayout(layout);

    connect(processButton, &QPushButton::clicked, this, &ProcessDialog::onProcessDialogButtonClicked);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(this, &QDialog::accepted, [this]() {
        QString result = resultLabel->text();
        result.replace("Результат в диалоге: ", "");
        emit dataProcessedAndReady(result);
    });
}

ProcessDialog::~ProcessDialog()
{
}

void ProcessDialog::onProcessDialogButtonClicked() {
    QString input = inputField->text();
    QString mode = modeComboBox->currentText();
    QString processedResult = processText(input, mode);
    resultLabel->setText("Результат в диалоге: " + processedResult);
}

QString ProcessDialog::processText(const QString &input, const QString &mode) {
    QString processedData;

    if (mode == "В нижний регистр") {
        processedData = input.toLower();
    } else if (mode == "Обратный порядок") {
        processedData = input;
        std::reverse(processedData.begin(), processedData.end());
    } else if (mode == "Удалить пробелы") {
        processedData = input;
        processedData.remove(' ');
    } else { // "Без изменений" или другой режим
        processedData = input;
    }
    return processedData;
}

