#include <QtGui/QApplication>
#include <QtDeclarative>
#include "qmlapplicationviewer.h"
#include "shortcutmaker.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    shortcutMaker sm;
    QDeclarativeContext *ctxt = viewer->rootContext();
    ctxt->setContextProperty("sm", &sm);

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setMainQmlFile(QLatin1String("qml/quickApp/main.qml"));
    viewer->showExpanded();

    return app->exec();
}
