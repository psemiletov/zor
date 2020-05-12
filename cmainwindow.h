#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QtGui>

class CMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

  QString fname_image;

  QImage source_image;
  QImage transformed_image;

  QTransform transform;

  QSettings *settings;

  CMainWindow(QWidget *parent = 0);
  ~CMainWindow();


  void load_image (const QString &fname);

  void paintEvent (QPaintEvent *event);
  void resizeEvent (QResizeEvent *event);
  void keyPressEvent ( QKeyEvent * event);

  void closeEvent (QCloseEvent *event);

};

#endif // CMAINWINDOW_H
