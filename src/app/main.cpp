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

#include "../gui/commandlineparser.h"
#include "../gui/mainwindow.h"
#include "../model/pluginstorage.h"

#include <QApplication>

int main(int argc, char ** argv) {
    // Load plugins.
    nanospectrum::PluginStorage::instance()->loadDefaultPlugins();

    // Create window.
    QApplication app(argc, argv);

    // NOTE: set app variables which will be used to
    // construct settings path
    app.setOrganizationName(QCoreApplication::translate("main", "SarFSC Inc."));
    app.setOrganizationDomain("sarfsc.ru");
    app.setApplicationName("NanoSpectrum");
    app.setApplicationVersion("0.0.1");

    nanospectrum::CommandLineParser parser(app);
    nanospectrum::CommandLineOptions options {};
    QString errorMessage {};

    nanospectrum::CommandLineParser::CommandLineParseResult parserResult = parser.parseCommandLine(&options, &errorMessage);

    QLocale locale;
    std::unique_ptr<QTranslator> qtTranslator = std::make_unique<QTranslator>();
    qtTranslator->load(locale, "gui", "_", ":/");
    std::unique_ptr<QTranslator> qtTranslator2 = std::make_unique<QTranslator>();
    qtTranslator2->load(QString("qt_").append(QLocale::system().name()),
                        QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QCoreApplication::installTranslator(qtTranslator.get());
    QCoreApplication::installTranslator(qtTranslator2.get());

    switch (parserResult)
    {
    case nanospectrum::CommandLineParser::CommandLineError:
        printf("%s \n", qPrintable(errorMessage));
        parser.showHelp();
        return 1;
    case nanospectrum::CommandLineParser::CommandLineHelpRequested:
        parser.showHelp();
        return 0;
    case nanospectrum::CommandLineParser::CommandLineVersionRequested:
        parser.showVersion();
        return 0;
    case nanospectrum::CommandLineParser::CommandLineOk:
    default:
        break;
    }

    nanospectrum::MainWindow window(options);
    window.show();

    return app.exec();
}
