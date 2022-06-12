/***********************************************************************************************************************
**
** Copyright (C) 2022 Evgeny Sinelnikov. <sin@altlinux.org>
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**
***********************************************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutdialog.h"

#include "commandlineoptions.h"

void registerResources()
{
    Q_INIT_RESOURCE(translations);
}

namespace nanospectrum {

class MainWindowPrivate {
public:
    std::vector<std::unique_ptr<QTranslator>> translators {};
    QString localeName {};

    CommandLineOptions options {};

    MainWindowPrivate()
    {}

private:
    MainWindowPrivate(const MainWindowPrivate&)            = delete;   // copy ctor
    MainWindowPrivate(MainWindowPrivate&&)                 = delete;   // move ctor
    MainWindowPrivate& operator=(const MainWindowPrivate&) = delete;   // copy assignment
    MainWindowPrivate& operator=(MainWindowPrivate&&)      = delete;   // move assignment
};

MainWindow::MainWindow(CommandLineOptions &options, QWidget *parent)
    : QMainWindow(parent)
    , d(new MainWindowPrivate())
    , ui(new Ui::MainWindow())
{
    registerResources();

    d->options = options;

    ui->setupUi(this);

    createLanguageMenu();

    QLocale locale(!d->localeName.trimmed().isEmpty()
                   ? d->localeName.replace("-","_")
                   : QLocale::system().name().replace("-","_"));
    std::unique_ptr<QTranslator> qtTranslator = std::make_unique<QTranslator>();
    qtTranslator->load(locale, "gui", "_", ":/");
    QCoreApplication::installTranslator(qtTranslator.get());
    d->translators.push_back(std::move(qtTranslator));
    d->localeName = locale.name().replace("_","-");
    ui->retranslateUi(this);
}

MainWindow::~MainWindow()
{
    delete d;

    delete ui;
}

void MainWindow::setLanguage(const QString &language)
{
    d->localeName = language;
}

QString MainWindow::getLanguage() const
{
    return d->localeName;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionManual_triggered()
{
    const QUrl manual_url = QUrl("https://github.com/sarfsc/nanospectrum");
    QDesktopServices::openUrl(manual_url);
}

void MainWindow::on_actionAbout_triggered()
{
    auto about = new AboutDialog(this);
    about->show();
}

void MainWindow::onLanguageChanged(QAction *action)
{
    for (const auto& translator : d->translators)
    {
        qApp->removeTranslator(translator.get());
    }
    d->translators.clear();

    QString language = action->data().toString();

    std::unique_ptr<QTranslator> qtTranslator = std::make_unique<QTranslator>();
    bool loadResult = qtTranslator->load("gui_" + language + ".qm", ":/");
    QCoreApplication::installTranslator(qtTranslator.get());
    d->translators.push_back(std::move(qtTranslator));
    qWarning() << "Load language " << language << loadResult;

    QLocale locale(language);

    d->localeName = locale.name().replace("_", "-");

    ui->retranslateUi(this);
}

void MainWindow::createLanguageMenu()
{
    QActionGroup* langGroup = new QActionGroup(this);
    langGroup->setExclusive(true);

    connect(langGroup, &QActionGroup::triggered, this, &MainWindow::onLanguageChanged);

    QString defaultLocale = d->localeName.left(QLocale::system().name().lastIndexOf('_'));
    QDir dir(":/");
    QStringList fileNames = dir.entryList(QStringList("gui_*.qm"));

    QMenu* menu = new QMenu(this);
    ui->actionLanguage->setMenu(menu);

    for (QString locale : fileNames)
    {
        locale.truncate(locale.lastIndexOf('.'));
        locale.remove(0, locale.lastIndexOf('_') + 1);

        QString language = QLocale::languageToString(QLocale(locale).language());

        QAction *action = new QAction(language, this);
        action->setCheckable(true);
        action->setData(locale);

        menu->addAction(action);
        langGroup->addAction(action);

        if (defaultLocale == locale)
        {
            action->setChecked(true);
        }
    }
}

}
