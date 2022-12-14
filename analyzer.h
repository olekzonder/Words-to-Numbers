#ifndef ANALYZER_H
#define ANALYZER_H
#include <QString>
#include <QMap>
#include <QList>
#include <QMessageBox>
#include <QDebug>
class Analyzer
{
    QWidget *parent;
    int type = -1;
    int pos = 0;
    QMap<QString,int> one = {

        {"один",1},
        {"два", 2},
        {"три",3},
        {"четыре", 4},
        {"пять",5},
        {"шесть", 6},
        {"семь",7},
        {"восемь", 8},
        {"девять",9}
    };
    QMap<QString,int> ten = {

        {"десять",10},
        {"двадцать", 20},
        {"тридцать",30},
        {"сорок", 40},
        {"пятьдесят",50},
        {"шестьдесят", 60},
        {"семьдесят",70},
        {"восемьдесят", 80},
        {"девяносто",90}
    };
    QMap<QString,int> teen = {

        {"одиннадцать",11},
        {"двенадцать", 12},
        {"тринадцать",13},
        {"четырнадцать", 14},
        {"пятнадцать",15},
        {"шестнадцать", 16},
        {"семнадцать",17},
        {"восемнадцать", 18},
        {"девятнадцать",19}
    };
    QMap<QString,int> hund = {

        {"сто",100},
        {"двести", 200},
        {"триста",300},
        {"четыреста", 400},
        {"пятьсот",500},
        {"шестьсот", 600},
        {"семьсот",700},
        {"восемьсот", 800},
        {"девятьсот",900}
    };
    void handleError(int pos, int type);
    bool analyzeSyntax(QList<int> *numbers, int *output);
    bool analyzeLexic(QString *src,QList<int> *numbers);
public:
    Analyzer(QWidget *parent);
    QString getErrorMessage(QString word);
    int getErrorPos();
    int convert(QString src);
};

#endif // ANALYZER_H
