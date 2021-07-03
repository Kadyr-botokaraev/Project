#include "functions.h"
#include <QDebug>



QString shifr(QString text_tmp,QString key_tmp){
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz ";
    std::string D;
    std::string key = key_tmp.toStdString();
    std::string text = text_tmp.toStdString();

    int* F = new int[text.length()];
    int* G = new int[text.length()];

    int text_length = text.length();
    int key_length = key.length();

    int ind = 0;
    int j = 0;
    while (ind<text_length)
    {
        if (text[ind] != ' ' && text[ind] != '.' && text[ind] != ',' && text[ind] != '!' && text[ind] != '?')
        {
            D += key[j];

            ind++;
            j++;
            j = j % key_length;
        }
        else
        {
            D += text[ind];
            ind++;
        }
    }




    int k;

    int n = 0;


    while (n < text_length) {
        if (text[n] != ' ' && text[n] != '.' && text[n] != ',' && text[n] != '!' && text[n] != '?'){
            if (isupper(text[n])) {
                text[n] = tolower(text[n]);
            }
            k = (text[n]-'a' + D[n]-'a') % 26;
            text[n] = alphabet[k]; // k +'a'


        }

        n++;
    }



    return QString::fromStdString(text);

    delete [] F;
    delete [] G;
}



QString deshifr(QString text_tmp,QString key_tmp){
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz ";
    std::string D;
    std::string key = key_tmp.toStdString();
    std::string text = text_tmp.toStdString();

    int* F = new int[text.length()];
    int* G = new int[text.length()];

    int text_length = text.length();
    int key_length = key.length();

    int ind = 0;
    int j = 0;
    while (ind<text_length)
    {
        if (text[ind] != ' '&& text[ind] != '.' && text[ind] != ',' && text[ind] != '!' && text[ind] != '?')
        {
            D += key[j];

            ind++;
            j++;
            j = j % key_length;
        }
        else
        {
            D += text[ind];
            ind++;
        }
    }




    int k;

    int n = 0;

    while (n < text_length) {
        if (text[n] != ' '&& text[n] != '.' && text[n] != ',' && text[n] != '!' && text[n] != '?'){

            if (isupper(text[n])) {
                text[n] = tolower(text[n]);
             }

            k = (text[n]-'a') - (D[n]-'a');
            if(k < 0) {
                k+=26;
            }

            text[n] = alphabet[k];


        }

        n++;
    }

    return QString::fromStdString(text);

    delete [] F;
    delete [] G;

}












QString parsing(QString mess){
    QString nameOfFunc;
    int pos = mess.indexOf('&');
    nameOfFunc = mess.mid(0, pos);
    if (nameOfFunc == "shifr"){
        QString textAndKey = mess.mid(pos+1,-1);
        QString texForShifr;
        QString key;


        pos = textAndKey.indexOf('&');
        texForShifr = textAndKey.mid(0, pos);
        key = textAndKey.mid(pos+3,-1);

        return shifr(texForShifr,key);

    }

    else if (nameOfFunc == "de_shifr")
    {
        QString textAndKey = mess.mid(pos+1,-1);
        QString texForShifr;
        QString key;


        pos = textAndKey.indexOf('&');
        texForShifr = textAndKey.mid(0, pos);
        key = textAndKey.mid(pos+3,-1);

        return deshifr(texForShifr,key);
    }

    else {

        int p = mess.indexOf('#');

        QString  login = mess.mid(pos+1, p-pos - 1);

        QString pass = mess.mid(p+1, -1);


        //qDebug()<< login << '\n' << pass;



        if (login=="user" && pass=="pass")
            return "auth&ok";
        else
            return "auth&false";
    }


}
