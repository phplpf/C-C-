#include <QApplication>
#include <QPushButton>
#include <QTextCodec>
int main(int argc,char** argv){
    QApplication app(argc,argv);
    
    //1)����GBK�������
    QTextCodec* codec = 
        QTextCodec::codecForName("GBK");
    //2)����ʾ�ַ���ת��Ϊunicode
    QString str = 
        codec->toUnicode("�����е���!");

    QPushButton button(str);
    button.show();

    return app.exec();
}

