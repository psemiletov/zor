/*
ZOR - Zoom, Overlay, Rotate
Public domain program by Peter Semiletov
created 2012.03.28
*/

#include "cmainwindow.h"


bool file_exists (const QString &fileName)
{
  if (fileName.isNull() || fileName.isEmpty())
     return false;

  return QFile::exists (fileName);
}


void CMainWindow::closeEvent (QCloseEvent *event)
{
  event->accept();
}


CMainWindow::CMainWindow (QWidget *parent): QMainWindow (parent)
{
  settings = new QSettings (QSettings::NativeFormat,
                            QSettings::UserScope,
                            "zor",
                            "zor");


  fname_image = settings->value ("fname_image", "none").toString();

  if (fname_image != "none")
      load_image (fname_image);


  setWindowTitle (tr ("ZOR. Press F1 for help"));
  setWindowOpacity (0.5f);


  setWindowFlags (Qt::WindowStaysOnTopHint);


  QAction *quitAction = new QAction (tr ("E&xit"), this);
  quitAction->setShortcut (tr ("Ctrl+Q"));
  connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
  addAction(quitAction);
}

CMainWindow::~CMainWindow()
{
  qDebug() << "~CMainWindow()";

  settings->setValue ("fname_image", fname_image);
  delete settings;
}


void CMainWindow::paintEvent(QPaintEvent *event)
{

  QPainter painter (this);
  painter.drawImage (0, 0, transformed_image);

}


void CMainWindow::resizeEvent(QResizeEvent *event)
{
  if (transform.isRotating())
     {
      QImage tmp = source_image.transformed (transform);
      transformed_image = tmp.scaled (size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
     }
  else
  transformed_image = source_image.scaled (size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

  update();
}


void CMainWindow::load_image (const QString &fname)
{
  if  (! file_exists (fname))
     return;

  source_image.load (fname);
  transformed_image = source_image;

  if (source_image.size().width() > QApplication::desktop()->size().width() ||
      source_image.size().height() > QApplication::desktop()->size().height())
     {
      transformed_image = source_image.scaled (size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
     }

  transform.reset();
  resize (transformed_image.size());
}



void CMainWindow::keyPressEvent ( QKeyEvent * event)
{

  if (event->key() == Qt::Key_F1)
     {
      QLabel *l = new QLabel (tr ("ZOR = Zoom, Overlay, Rotate<br>***<br>F3 - open file <br> Cursor left/right - rotate<br>Cursor up/down - change transparency<br>O - reset to original<br>M - mirror<br>Ctrl-Q - quit"));
      l->show();
     }
  else
  if (event->key() == Qt::Key_F3)
     {
      fname_image = QFileDialog::getOpenFileName (this,
                                                  tr ("Open Image"),
                                                  QDir::homePath (),
                                                  tr ("Image Files (*.png *.jpg *.jpeg *.bmp *.gif)"));

      load_image (fname_image);
      update();
     }
  else
  if (event->key() == Qt::Key_Left)
     {
      transform.rotate (-1);
      transformed_image = source_image.transformed (transform);
      transformed_image = transformed_image .scaled (size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
      update();
     }
  else
  if (event->key() == Qt::Key_Right)
     {
      transform.rotate (1);
      transformed_image = source_image.transformed (transform);
      transformed_image = transformed_image .scaled (size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
      update();
     }
  else
  if (event->key() == Qt::Key_Up)
     {
      setWindowOpacity (windowOpacity() + 0.01);
     }
  else
  if (event->key() == Qt::Key_Down)
     {
      setWindowOpacity (windowOpacity() - 0.01);
     }
  else
  if (event->key() == Qt::Key_Plus)
     {
      resize (size().width() + 1, size().height() + 1);
     }
  else
  if (event->key() == Qt::Key_Minus)
     {
      resize (size().width() - 1, size().height() - 1);
     }
  if (event->key() == Qt::Key_M)
     {
      source_image = source_image.mirrored (true, false);
      transformed_image = source_image.transformed (transform);
      update();
     }
  if (event->key() == Qt::Key_O)
     {
      transformed_image = source_image;
      transform.reset();
      resize (source_image.width(), source_image.height());
      update();
     }

  event->accept();
}
