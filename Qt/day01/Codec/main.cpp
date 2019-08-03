#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QTextCodec>
int main(int argc,char** argv){
    QApplication app(argc,argv);
    QTextCodec* codec = 
        QTextCodec::codecForName("GBK");
    /*QString str1 = 
        codec->toUnicode("���Ǳ�ǩ");
    QString str2 =
        codec->toUnicode("���ǰ�ť");*/
    QLabel label(
        codec->toUnicode("���Ǳ�ǩ"));
    label.show();
    QPushButton button(
        codec->toUnicode("���ǰ�ť"));
    button.show();
    return app.exec();
}


