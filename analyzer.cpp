#include "analyzer.h"

Analyzer::Analyzer(QWidget *_parent)
{
   parent = _parent;
}



bool Analyzer::analyzeLexic(QString *src,QList<int> *numbers){
    *src = src->toLower();
    QStringList list = src->split(' ',Qt::SkipEmptyParts);
    list = list.join(' ').split(' ',Qt::SkipEmptyParts);
    for (int i=0;i<list.size();i++){
        if(one.contains(list[i])){
            numbers->append(one.value(list[i]));
            continue;
        }
        if(ten.contains(list[i])){
            numbers->append(ten.value(list[i]));
            continue;
        }
        if(teen.contains(list[i])){
            numbers->append(teen.value(list[i]));
            continue;
        }
        if(hund.contains(list[i])){
            numbers->append(hund.value(list[i]));
            continue;
        }
        handleError(i+1,0);
        *src = list[i];
        return false;
    }
    return true;
}

bool Analyzer::analyzeSyntax(QList<int> *numbers, int *output){
    for(int i =0;i<numbers->size()-1;i++){
        switch(QString::number(numbers->at(i)).size()){
        case 1:
            if(QString::number(numbers->at(i+1)).size() == 1){
                handleError(i+2,1); //Единицы рядом друг с другом
                return false;
                break;
            }
            if(QString::number(numbers->at(i+1)).size() == 2){
                handleError(i+2,2); //Десятки после единиц
                return false;
                break;
        }
            if(QString::number(numbers->at(i+1)).size() == 3){
                handleError(i+2,3); //Сотни после единиц
                return false;
                break;
        }
        case 2:
            if (numbers->at(i) > 9 && numbers->at(i) < 20 && QString::number(numbers->at(i+1)).size() == 1){
                handleError(i+2,4); //Единицы после чисел 10-19
                return false;
                break;
            }
            if(QString::number(numbers->at(i+1)).size() == 2){
                handleError(i+2,5); //Десятки рядом друг с другом
                return false;
                break;
        }
            if(QString::number(numbers->at(i+1)).size() == 3){
                handleError(i+2,6); //Сотни после десятков
                return false;
                break;
        }
        case 3:
            if(QString::number(numbers->at(i+1)).size() == 3){
                handleError(i+2,7); //Сотни рядом друг с другом
                return false;
                break;
        }
        }
    }
    for(int i = 0; i < numbers->size();i++){
            *output += numbers->at(i);
        }
    return true;
}


void Analyzer::handleError(int _pos, int _type){
    pos = _pos;
    type = _type;
}

QString Analyzer::getErrorMessage(QString word = ""){
    switch(type){
    case 0:
        return "Слово " + word + " не является числом";
        break;
    case 1:
        return "Числа единичного формата стоят рядом друг с другом";
        break;
    case 2:
        return "Число единичного формата стоит перед числом десятичного формата";
        break;
    case 3:
        return "Число единичного формата стоит перед числом сотенного формата";
        break;
    case 4:
        return "Число единичного формата стоит после числа 10-19";
        break;
    case 5:
        return "Числа десятничного формата стоят рядом друг с другом";
        break;
    case 6:
        return "Число десятичного формата стоит перед числом сотенного формата";
        break;
    case 7:
        return "Числа сотенного стоят рядом друг с другом";
        break;
    }
}

int Analyzer::getErrorPos(){
    return pos;
}

int Analyzer::convert(QString src){
    QList<int> numbers;
    int output = 0;
    if (analyzeLexic(&src,&numbers) == false){
        getErrorMessage();
        return -1;
    }
    if (analyzeSyntax(&numbers,&output) == false){
        getErrorMessage();
        return -1;
    }
    return output;
}
