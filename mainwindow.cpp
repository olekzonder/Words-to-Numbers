#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    analyzer = new Analyzer(this);
    this->setWindowTitle("Перевод трёхзначного числа");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_translateButton_clicked()
{
    QString source = ui->inputTextEdit->toPlainText();
    QStringList list = source.split('\n',Qt::SkipEmptyParts);
    int res;
    QString outputText = "<html>";
    QStringList tempOut;
    QString inputText = "<html>";
    QStringList tempIn;
    for (int i=0;i<list.size();i++){
        res = analyzer->convert(list[i]);
        if (res != -1){
            tempOut.append(QString::number(res));
            tempIn.append(list[i]);
        }
        else{
            int pos = analyzer->getErrorPos()-1;
            QStringList splitText = list[i].split(' ', Qt::SkipEmptyParts);
            QStringList errInput;
            QString errWord;
            for (int j = 0;j<splitText.size();j++){
                if (j == pos){
                    errWord = splitText[j];
                    errInput.append("<span style=\"text-decoration-style: wavy;text-decoration: underline;text-decoration-color:red\">"+splitText[j]+"</span>");
                }
                else errInput.append(splitText[j]);
            }
            tempIn.append(errInput.join(" "));
            tempOut.append("<b> Ошибка: </b>" + analyzer->getErrorMessage(errWord));
        }
    }
    QString tempOutString = tempOut.join("<br>");
    QString tempInString = tempIn.join("<br>");
    outputText.append(tempOutString);
    outputText.append("</html>");
    inputText.append(tempInString);
    inputText.append("</html>");
    ui->inputTextEdit->setText(inputText);
    ui->outputTextEdit->setText(outputText);
}

