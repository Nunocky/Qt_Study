#include <QtGui>
#include <QtWidgets>

#include "finddialog.h"
#include "gotocelldialog.h"
#include "mainwindow.h"
#include "sortdialog.h"
#include "spreadsheet.h"

MainWindow::MainWindow()
{
  spreadSheet = new SpreadSheet;
  setCentralWidget(spreadSheet);

  //setAttribute(Qt::WA_DeleteOnClose);

  createActions();
  createMenus();
  createContextMenu();
  createToolBars();
  createStatusBar();

  readSettings();
  findDialog = 0;

  setWindowIcon(QIcon(":images/icon.png"));
  setCurrentFile("");
}



void 
MainWindow::closeEvent(QCloseEvent *event)
{
  if (okToContinue()) {
    writeSettings();
    event->accept();
  }
  else {
    event->ignore();
  }
}



void 
MainWindow::newFile()
{
//  MainWindow *mainWin = new MainWindow;
//  mainWin->show();

  if (okToContinue()) {
    spreadSheet->clear();
    setCurrentFile("");
  }
}


void 
MainWindow::open()
{
  if (okToContinue()) {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open SpreadSheet"),
                                                    ".",
                                                    tr("SpreadSheet files (*.sp)"));
    if (!fileName.isEmpty()) {
      loadFile(fileName);
    }
  }
}


bool 
MainWindow::save()
{
  if (curFile.isEmpty()) {
    return saveAs();
  }
  else {
    return saveFile(curFile);
  }
}


bool
MainWindow::saveAs()
{
  QString fileName = QFileDialog::getSaveFileName(this,
                                                  tr("Save SpreadSheet"),
                                                  ".",
                                                  tr("SpreadSheet files (*.sp)"));

  if (fileName.isEmpty()) {
    return false;
  }

  return saveFile(fileName);
}


void
MainWindow::find()
{
  if(!findDialog) {
    findDialog = new FindDialog(this);

    connect(findDialog, SIGNAL(findNext(const QString&, Qt::CaseSensitivity)), spreadSheet, SLOT(findNext(const QString&, Qt::CaseSensitivity)));
    connect(findDialog, SIGNAL(findPrev(const QString&, Qt::CaseSensitivity)), spreadSheet, SLOT(findPrev(const QString&, Qt::CaseSensitivity)));
  }

  findDialog->show();
  findDialog->activateWindow();
}


void
MainWindow::goToCell()
{
  GoToCellDialog dialog(this);
  if (dialog.exec()) {
    QString str = dialog.lineEdit->text().toUpper();
    spreadSheet->setCurrentCell(str.mid(1).toInt() - 1,
                                str[0].unicode() - 'A');
  }
}


void
MainWindow::sort()
{
  SortDialog dialog(this);
  QTableWidgetSelectionRange range = spreadSheet->selectedRange();
  dialog.setColumnRange('A' + range.leftColumn(),
                        'A' + range.rightColumn());

  if (dialog.exec()) {
    SpreadSheetCompare compare;
    compare.keys[0] = dialog.primaryColumnCombo->currentIndex();
    compare.keys[1] = dialog.secondaryColumnCombo->currentIndex() - 1;
    compare.keys[2] = dialog.tertiaryColumnCombo->currentIndex() - 1;
    compare.ascending[0] = (dialog.primaryColumnCombo->currentIndex() == 0);
    compare.ascending[1] = (dialog.secondaryColumnCombo->currentIndex() == 0);
    compare.ascending[2] = (dialog.tertiaryColumnCombo->currentIndex() == 0);

    spreadSheet->sort(compare);
  }
}


void
MainWindow::about()
{
    QMessageBox::about(this, 
                       tr("About SpreadSheet"),
                       tr("<h2>SpreadSheet 1.1</h2>"
                          "<p>Copyright &copy; 2006 Software Inc."
                          "<p>SpreadSheet is a small application that "
                          "demonstrates QAction, QMainWindow, QMenuBar, "
                          "QStatusBar, QTableWidget, QToolBar, and many other "
                          "Qt classes."));
}


void
MainWindow::updateCellIndicators()
{
}


void MainWindow::openRecentFile()
{
  if (okToContinue()) {
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
      loadFile(action->data().toString());
  }
}


void
MainWindow::updateStatusBar()
{
}


void
MainWindow::spreadSheetModified()
{
  setWindowModified(true);
  updateStatusBar();
}


void
MainWindow::createActions()
{
  newAction = new QAction(tr("&New"), this);
  newAction->setIcon(QIcon(":/images/new.png"));
  newAction->setShortcut(tr("Ctrl+N"));
  newAction->setStatusTip(tr("Create a new spreadSheet file"));
  connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

  openAction = new QAction(tr("&Open..."), this);
  openAction->setIcon(QIcon(":/images/open.png"));
  openAction->setShortcut(tr("Ctrl+O"));
  openAction->setStatusTip(tr("Open an existing spreadSheet file"));
  connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

  saveAction = new QAction(tr("&Save"), this);
  saveAction->setIcon(QIcon(":/images/save.png"));
  saveAction->setShortcut(tr("Ctrl+S"));
  saveAction->setStatusTip(tr("Save the spreadSheet to disk"));
  connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

  saveAsAction = new QAction(tr("Save &As..."), this);
  saveAsAction->setStatusTip(tr("Save the spreadSheet under a new name"));
  connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));
  
  for(int i=0; i< MaxRecentFiles; ++i) {
    recentFileActions[i] = new QAction(this);
    recentFileActions[i]->setVisible(false);
    connect(recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
  }

//  closeAction = new QAction(tr("&Close"), this);
//  closeAction->setShortcut(tr("Ctrl+W"));
//  closeAction->setStatusTip(tr("Close this window"));
//  connect(closeAction, SIGNAL(triggered()), qApp, SLOT(close()));
  
  exitAction = new QAction(tr("E&xit"), this);
  exitAction->setShortcut(tr("Ctrl+Q"));
  exitAction->setStatusTip(tr("Exit the application"));
  connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
//  connect(exitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

  cutAction = new QAction(tr("Cu&t"), this);
  cutAction->setIcon(QIcon(":/images/cut.png"));
  cutAction->setShortcut(tr("Ctrl+X"));
  cutAction->setStatusTip(tr("Cut the current selection's contents "
                             "to the clipboard"));
  connect(cutAction, SIGNAL(triggered()), spreadSheet, SLOT(cut()));

  copyAction = new QAction(tr("&Copy"), this);
  copyAction->setIcon(QIcon(":/images/copy.png"));
  copyAction->setShortcut(tr("Ctrl+C"));
  copyAction->setStatusTip(tr("Copy the current selection's contents "
                              "to the clipboard"));
  connect(copyAction, SIGNAL(triggered()), spreadSheet, SLOT(copy()));

  pasteAction = new QAction(tr("&Paste"), this);
  pasteAction->setIcon(QIcon(":/images/paste.png"));
  pasteAction->setShortcut(tr("Ctrl+V"));
  pasteAction->setStatusTip(tr("Paste the clipboard's contents into "
                               "the current selection"));
  connect(pasteAction, SIGNAL(triggered()),
          spreadSheet, SLOT(paste()));

  deleteAction = new QAction(tr("&Delete"), this);
  deleteAction->setShortcut(tr("Del"));
  deleteAction->setStatusTip(tr("Delete the current selection's "
                                "contents"));
  connect(deleteAction, SIGNAL(triggered()),
          spreadSheet, SLOT(del()));

  selectRowAction = new QAction(tr("&Row"), this);
  selectRowAction->setStatusTip(tr("Select all the cells in the "
                                   "current row"));
  connect(selectRowAction, SIGNAL(triggered()),
          spreadSheet, SLOT(selectCurrentRow()));

  selectColumnAction = new QAction(tr("&Column"), this);
  selectColumnAction->setStatusTip(tr("Select all the cells in the current column"));
                                      
  connect(selectColumnAction, SIGNAL(triggered()),
          spreadSheet, SLOT(selectCurrentColumn()));

  selectAllAction = new QAction(tr("&All"), this);
  selectAllAction->setShortcut(tr("Ctrl+A"));
  selectAllAction->setStatusTip(tr("Select all the cells in the spreadSheet"));
  connect(selectAllAction, SIGNAL(triggered()), spreadSheet, SLOT(selectAll()));

  findAction = new QAction(tr("&Find..."), this);
  findAction->setIcon(QIcon(":/images/find.png"));
  findAction->setShortcut(tr("Ctrl+F"));
  findAction->setStatusTip(tr("Find a matching cell"));
  connect(findAction, SIGNAL(triggered()), this, SLOT(find()));

  goToCellAction = new QAction(tr("&Go to Cell..."), this);
  goToCellAction->setIcon(QIcon(":/images/gotocell.png"));
  goToCellAction->setShortcut(tr("F5"));
  goToCellAction->setStatusTip(tr("Go to the specified cell"));
  connect(goToCellAction, SIGNAL(triggered()),
          this, SLOT(goToCell()));

  recalculateAction = new QAction(tr("&Recalculate"), this);
  recalculateAction->setShortcut(tr("F9"));
  recalculateAction->setStatusTip(tr("Recalculate all the spreadSheet's formulas"));
                                     
  connect(recalculateAction, SIGNAL(triggered()),
          spreadSheet, SLOT(recalculate()));

  sortAction = new QAction(tr("&Sort..."), this);
  sortAction->setStatusTip(tr("Sort the selected cells or all the cells"));
                              
  connect(sortAction, SIGNAL(triggered()), this, SLOT(sort()));

  showGridAction = new QAction(tr("&Show Grid"), this);
  showGridAction->setCheckable(true);
  showGridAction->setChecked(spreadSheet->showGrid());
  showGridAction->setStatusTip(tr("Show or hide the spreadSheet's grid"));
  connect(showGridAction, SIGNAL(toggled(bool)),
          spreadSheet, SLOT(setShowGrid(bool)));

  autoRecalcAction = new QAction(tr("&Auto-Recalculate"), this);
  autoRecalcAction->setCheckable(true);
  autoRecalcAction->setChecked(spreadSheet->autoRecalculate());
  autoRecalcAction->setStatusTip(tr("Switch auto-recalculation on or off"));
  connect(autoRecalcAction, SIGNAL(toggled(bool)),
          spreadSheet, SLOT(setAutoRecalculate(bool)));

  aboutAction = new QAction(tr("&About"), this);
  aboutAction->setStatusTip(tr("Show the application's About box"));
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

  aboutQtAction = new QAction(tr("About &Qt"), this);
  aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
  connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}


void
MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);

    separatorAction = fileMenu->addSeparator();

    for (int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);

    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    selectSubMenu = editMenu->addMenu(tr("&Select"));
    selectSubMenu->addAction(selectRowAction);
    selectSubMenu->addAction(selectColumnAction);
    selectSubMenu->addAction(selectAllAction);

    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(goToCellAction);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(recalculateAction);
    toolsMenu->addAction(sortAction);

    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(showGridAction);
    optionsMenu->addAction(autoRecalcAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}


void
MainWindow::createContextMenu()
{
  spreadSheet->addAction(cutAction);
  spreadSheet->addAction(copyAction);
  spreadSheet->addAction(pasteAction);
  spreadSheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}


void
MainWindow::createToolBars()
{
  fileToolBar = addToolBar(tr("&File"));
  fileToolBar->addAction(newAction);
  fileToolBar->addAction(openAction);
  fileToolBar->addAction(saveAction);

  editToolBar = addToolBar(tr("&Edit"));
  editToolBar->addAction(cutAction);
  editToolBar->addAction(copyAction);
  editToolBar->addAction(pasteAction);
  editToolBar->addSeparator();
  editToolBar->addAction(findAction);
  editToolBar->addAction(goToCellAction);
}

void
MainWindow:: createStatusBar()
{
  locationLabel = new QLabel(" W999 ");
  locationLabel->setAlignment(Qt::AlignHCenter);
  locationLabel->setMinimumSize(locationLabel->sizeHint());

  formulaLabel = new QLabel;
  formulaLabel->setIndent(3);

  statusBar()->addWidget(locationLabel);
  statusBar()->addWidget(formulaLabel, 1);

  connect(spreadSheet, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(updateStatusBar()));
  connect(spreadSheet, SIGNAL(modified()), this, SLOT(spreadSheetModified()));

  updateStatusBar();
}


void
MainWindow::readSettings()
{
  QSettings settings("Software Inc.", "SpreadSheet");

  QRect rect = settings.value("geometry", QRect(200, 200, 400, 400)).toRect();

  move(rect.topLeft());
  resize(rect.size());

  recentFiles = settings.value("recentFiles").toStringList();
  updateRecentFileActions();

  bool showGrid = settings.value("showGrid", true).toBool();
  showGridAction->setChecked(showGrid);

  bool autoRecalc = settings.value("autoRecalc", true).toBool();
  autoRecalcAction->setChecked(autoRecalc);

}

void
MainWindow::writeSettings()
{
  QSettings settings("Software Inc.", "SpreadSheet");

  settings.setValue("geometry",    geometry());
  settings.setValue("recentFiles", recentFiles);
  settings.setValue("showGrid",    showGridAction->isChecked());
  settings.setValue("autoRecalc",  autoRecalcAction->isChecked());
}

bool
MainWindow::okToContinue()
{
  if (isWindowModified()) {
    int ret = QMessageBox::warning(this, 
                                   tr("SpreadSheet"),
                                   tr("The document has been modified.\nDo you want to save your changes?"),
                                   QMessageBox::Yes | QMessageBox::Default,
                                   QMessageBox::No,
                                   QMessageBox::Cancel | QMessageBox::Escape);

    if (ret == QMessageBox::Yes) {
      return save();
    }
    else if (ret == QMessageBox::Cancel) {
      return false;
    }
  }

  return true;
}

bool
MainWindow::loadFile(const QString &fileName)
{
  if (!spreadSheet->readFile(fileName)) {
    statusBar()->showMessage(tr("Loading canceled"), 2000);
    return false;
  }

  setCurrentFile(fileName);
  statusBar()->showMessage(tr("File loaded"), 2000);
  return true;
}

bool
MainWindow::saveFile(const QString &fileName)
{
  if (!spreadSheet->writeFile(fileName)) {
    statusBar()->showMessage(tr("Saving canceled"), 2000);
    return false;
  }

  setCurrentFile(fileName);
  statusBar()->showMessage(tr("File saved"), 2000);
  return true;  
}

void
MainWindow::setCurrentFile(const QString &fileName)
{
  curFile = fileName;
  setWindowModified(false);

  QString shownName = "Untitled";
  if (!curFile.isEmpty()) {
    shownName = strippedName(curFile);
    recentFiles.removeAll(curFile);
    recentFiles.prepend(curFile);
    updateRecentFileActions();
  }

  setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("SpreadSheet")));
}

void
MainWindow::updateRecentFileActions()
{
  QMutableStringListIterator i(recentFiles);
  while(i.hasNext()) {
    if (!QFile::exists(i.next())) {
      i.remove();
    }
  }

  for (int j=0; j < MaxRecentFiles; j++) {
    if (j < recentFiles.count()) {
      QString text = tr("&%1 %2").arg(j+1).arg(strippedName(recentFiles[j]));
      recentFileActions[j]->setText(text);
      recentFileActions[j]->setData(recentFiles[j]);
      recentFileActions[j]->setVisible(true);
    }
    else {
      recentFileActions[j]->setVisible(false);
    }
  }

  separatorAction->setVisible(!recentFiles.isEmpty());
}

QString
MainWindow::strippedName(const QString &fullFileName)
{
  return QFileInfo(fullFileName).fileName();
}


