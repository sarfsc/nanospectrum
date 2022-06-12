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

#ifndef NANOSPECTRUM_MAINWINDOW_H
#define NANOSPECTRUM_MAINWINDOW_H

#include "gui.h"

#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace nanospectrum {
    class CommandLineOptions;
    class MainWindowPrivate;

    class NANOSPECTRUM_GUI_EXPORT MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        // construction and destruction
        MainWindow(CommandLineOptions& options, QWidget *parent = 0);
        ~MainWindow();

        void setLanguage(const QString& language);
        QString getLanguage() const;

    protected:
        void closeEvent(QCloseEvent *event) override;

    private slots:
        void on_actionManual_triggered();

    private:

        MainWindowPrivate* const d;

        Ui::MainWindow *ui;

    private slots:
        void on_actionExit_triggered();
        void on_actionAbout_triggered();

        void onLanguageChanged(QAction *action);

    private:
        void createLanguageMenu();

    private:
        MainWindow(const MainWindow&)            = delete;   // copy ctor
        MainWindow(MainWindow&&)                 = delete;   // move ctor
        MainWindow& operator=(const MainWindow&) = delete;   // copy assignment
        MainWindow& operator=(MainWindow&&)      = delete;   // move assignment
    };
}

#endif // NANOSPECTRUM_MAINWINDOW_H
