// Copyright (C) 2023-2024 Stdware Collections (https://www.github.com/stdware)
// Copyright (C) 2021-2023 wangwenx190 (Yuhang Zhao)
// SPDX-License-Identifier: Apache-2.0

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QQuickWidget>

#include "codeeditor.h"
#include "frame.h"
#include "CusConfig.h"

namespace QWK {
    class WidgetWindowAgent;
    class StyleAgent;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    enum Theme {
        Dark,
        Light,
    };
    Q_ENUM(Theme)

Q_SIGNALS:
    void themeChanged();

public slots:
    void displayNCFunc(QPoint pt);

protected:
    bool event(QEvent *event) override;

    void closeEvent(QCloseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

private:
    void installWindowAgent();
    void loadStyleSheet(Theme theme);

    Theme currentTheme{};

    QWK::WidgetWindowAgent *windowAgent;

    CodeEditor *pedit{nullptr};
    QGridLayout *rootLayout{nullptr};
    QQuickWidget *contentQuick{nullptr};
    QQuickWidget *topQuick{nullptr};
    QQuickWidget *rightQuick{nullptr};
    QQuickWidget *bottomQuick{nullptr};
    CusConfig *gconf{nullptr};
    QString qgconf{"gconf"};
    QString qrootMain{ "rootMain" };

    QFrame* popFrame{ nullptr };
};

#endif // MAINWINDOW_H
