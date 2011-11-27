#ifndef SHORTCUTMAKER_H
#define SHORTCUTMAKER_H
#include <QObject>
#include <QDebug>
#include <QtMobility/qmobilityglobal.h>
#include <QtContacts/QContactFetchRequest>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QtDBus/QDBusInterface>

class shortcutMaker : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void cppMethod(const QString &msg) {
        qDebug() << "Called the C++ method with" << msg;
    }
    shortcutMaker();

public slots:
    int toggleShortcut(int number, const QString &name, const QString &url) {
        QString uu = url;
        uu.replace(QString("file://"),QString(""));
        QFile file("/home/user/.local/share/applications/contact" + QString::number(number) + ".desktop");
        if (!file.exists()){
            if ( file.open( QIODevice::WriteOnly ) ) {
                QTextStream stream( &file );
                stream.setCodec("UTF-8");
                stream << "[Desktop Entry]\nVersion=1.0\nType=Application\nName=" << name << "\nComment=Contact\nExec=dbus-send --type=method_call --dest=com.nokia.contacts / com.nokia.maemo.meegotouch.ContactsInterface.openContactCard int32:" << number << "\nIcon=" << uu << endl;
                return 1;
            } else {
                qDebug( "Could not create file" );
            }
        } else {
            if (file.remove()) return 2;
        }
//        QDBusInterface device(QLatin1String("com.nokia.contacts"),
//                              QLatin1String("/"),
//                              QLatin1String("com.nokia.maemo.meegotouch.ContactsInterface"));
//        device.call(QLatin1String("openContactCard"),QVariant::fromValue(number));
//        qDebug() << "Called the C++ slot with" << QVariant::fromValue(number) << name;

    }

    char checkIfExists(int number){
        QFile file("/home/user/.local/share/applications/contact" + QString::number(number) + ".desktop");
        return file.exists();
    }
};

#endif // SHORTCUTMAKER_H
