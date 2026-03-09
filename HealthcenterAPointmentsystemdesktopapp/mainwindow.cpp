#include "mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QHeaderView>
#include <QTime>
#include <QTimer>
#include <QFrame>
#include <QStackedWidget>
#include <QGraphicsDropShadowEffect>
#include <QScrollArea>
#include <QSpacerItem>
#include <QFont>
#include <QFontDatabase>

// ─────────────────────────────────────────────
//  GLOBAL STYLESHEET
// ─────────────────────────────────────────────
void MainWindow::applyGlobalStyles()
{
    setStyleSheet(R"(


        QPushButton#btnQuit {
            background: transparent;
            color: #8b949e;
            border: 1px solid #30363d;
            border-radius: 6px;
            padding: 4px 14px;
            font-size: 12px;
            font-weight: 600;
        }
        QPushButton#btnQuit:hover {
            background: rgba(248,81,73,0.12);
            color: #f85149;
            border-color: rgba(248,81,73,0.4);
        }
        QMainWindow, QWidget#dashboardPage, QWidget#landingPage {
            background-color: #0d1117;
            color: #e6edf3;
            font-family: 'Segoe UI', sans-serif;
        }

        /* ── LANDING ── */
        QWidget#landingPage {
            background: qlineargradient(
                x1:0, y1:0, x2:1, y2:1,
                stop:0 #0d1117,
                stop:0.5 #0f2942,
                stop:1 #0d1117
            );
        }

        QLabel#lblHeroTitle {
            font-size: 42px;
            font-weight: 700;
            color: #58a6ff;
            letter-spacing: 2px;
        }
        QLabel#lblHeroSubtitle {
            font-size: 16px;
            color: #8b949e;
            letter-spacing: 1px;
        }
        QLabel#lblHeroBadge {
            font-size: 11px;
            font-weight: 600;
            color: #3fb950;
            background: rgba(63,185,80,0.12);
            border: 1px solid rgba(63,185,80,0.3);
            border-radius: 12px;
            padding: 4px 14px;
            letter-spacing: 2px;
        }

        QPushButton#btnEnter {
            background: qlineargradient(x1:0,y1:0,x2:1,y2:0,
                stop:0 #1f6feb, stop:1 #388bfd);
            color: #ffffff;
            font-size: 15px;
            font-weight: 600;
            border: none;
            border-radius: 10px;
            padding: 16px 52px;
            letter-spacing: 1px;
        }
        QPushButton#btnEnter:hover {
            background: qlineargradient(x1:0,y1:0,x2:1,y2:0,
                stop:0 #388bfd, stop:1 #58a6ff);
        }
        QPushButton#btnEnter:pressed {
            background: #1f6feb;
        }

        /* ── DASHBOARD HEADER ── */
        QFrame#headerBar {
            background: #161b22;
            border-bottom: 1px solid #21262d;
        }
        QLabel#lblAppName {
            font-size: 18px;
            font-weight: 700;
            color: #58a6ff;
            letter-spacing: 1px;
        }
        QLabel#lblClock {
            font-size: 13px;
            color: #8b949e;
            font-family: 'Courier New', monospace;
        }

        /* ── STAT CARDS ── */
        QFrame#statCard {
            background: #161b22;
            border: 1px solid #21262d;
            border-radius: 12px;
        }
        QLabel#statValue {
            font-size: 32px;
            font-weight: 700;
        }
        QLabel#statTitle {
            font-size: 11px;
            color: #8b949e;
            letter-spacing: 1px;
            font-weight: 600;
        }

        /* ── INPUT PANEL ── */
        QFrame#inputPanel {
            background: #161b22;
            border: 1px solid #21262d;
            border-radius: 12px;
        }
        QLabel#sectionTitle {
            font-size: 13px;
            font-weight: 600;
            color: #8b949e;
            letter-spacing: 2px;
        }
        QLineEdit {
            background: #0d1117;
            color: #e6edf3;
            border: 1px solid #30363d;
            border-radius: 8px;
            padding: 10px 14px;
            font-size: 13px;
            selection-background-color: #1f6feb;
        }
        QLineEdit:focus {
            border: 1px solid #388bfd;
            background: #0d1117;
        }
        QLineEdit::placeholder {
            color: #484f58;
        }
        QSpinBox {
            background: #0d1117;
            color: #e6edf3;
            border: 1px solid #30363d;
            border-radius: 8px;
            padding: 10px 14px;
            font-size: 13px;
        }
        QSpinBox:focus {
            border: 1px solid #388bfd;
        }
        QSpinBox::up-button, QSpinBox::down-button {
            background: #21262d;
            border: none;
            width: 20px;
            border-radius: 4px;
        }
        QSpinBox::up-button:hover, QSpinBox::down-button:hover {
            background: #30363d;
        }

        /* ── ACTION BUTTONS ── */
        QPushButton#btnRegular {
            background: #21262d;
            color: #3fb950;
            border: 1px solid rgba(63,185,80,0.4);
            border-radius: 8px;
            padding: 11px 22px;
            font-size: 13px;
            font-weight: 600;
        }
        QPushButton#btnRegular:hover {
            background: rgba(63,185,80,0.12);
            border-color: #3fb950;
        }

        QPushButton#btnEmergency {
            background: #21262d;
            color: #f85149;
            border: 1px solid rgba(248,81,73,0.4);
            border-radius: 8px;
            padding: 11px 22px;
            font-size: 13px;
            font-weight: 600;
        }
        QPushButton#btnEmergency:hover {
            background: rgba(248,81,73,0.12);
            border-color: #f85149;
        }

        QPushButton#btnServe {
            background: qlineargradient(x1:0,y1:0,x2:1,y2:0,
                stop:0 #1f6feb, stop:1 #388bfd);
            color: #ffffff;
            border: none;
            border-radius: 8px;
            padding: 11px 26px;
            font-size: 13px;
            font-weight: 600;
        }
        QPushButton#btnServe:hover {
            background: qlineargradient(x1:0,y1:0,x2:1,y2:0,
                stop:0 #388bfd, stop:1 #58a6ff);
        }
        QPushButton#btnServe:pressed {
            background: #1f6feb;
        }

        /* ── TABLES ── */
        QFrame#tablePanel {
            background: #161b22;
            border: 1px solid #21262d;
            border-radius: 12px;
        }
        QLabel#tablePanelTitle {
            font-size: 14px;
            font-weight: 700;
            color: #e6edf3;
        }
        QTableWidget {
            background: transparent;
            color: #e6edf3;
            gridline-color: #21262d;
            border: none;
            font-size: 13px;
            selection-background-color: #1f6feb;
            selection-color: #ffffff;
            alternate-background-color: rgba(255,255,255,0.02);
        }
        QTableWidget::item {
            padding: 10px 14px;
            border: none;
        }
        QTableWidget::item:selected {
            background: rgba(31,111,235,0.25);
            color: #58a6ff;
        }
        QHeaderView::section {
            background: #0d1117;
            color: #8b949e;
            font-size: 11px;
            font-weight: 600;
            letter-spacing: 1px;
            padding: 10px 14px;
            border: none;
            border-bottom: 1px solid #21262d;
        }
        QScrollBar:vertical {
            background: #0d1117;
            width: 8px;
            border: none;
        }
        QScrollBar::handle:vertical {
            background: #30363d;
            border-radius: 4px;
            min-height: 20px;
        }
        QScrollBar::handle:vertical:hover {
            background: #484f58;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }

        /* ── STATUS BAR ── */
        QFrame#statusBar {
            background: #161b22;
            border-top: 1px solid #21262d;
        }
        QLabel#statusMsg {
            font-size: 12px;
            color: #8b949e;
        }

        /* ── DIVIDER ── */
        QFrame[frameShape="4"], QFrame[frameShape="5"] {
            color: #21262d;
        }

        /* ── INPUT FIELD LABELS ── */
        QLabel#fieldLabel {
            font-size: 12px;
            font-weight: 600;
            color: #8b949e;
            letter-spacing: 0.5px;
        }
        QLabel#emergencyBadge {
            font-size: 10px;
            font-weight: 700;
            color: #f85149;
            background: rgba(248,81,73,0.12);
            border: 1px solid rgba(248,81,73,0.3);
            border-radius: 10px;
            padding: 2px 10px;
            letter-spacing: 1px;
        }
        QLabel#regularBadge {
            font-size: 10px;
            font-weight: 700;
            color: #3fb950;
            background: rgba(63,185,80,0.12);
            border: 1px solid rgba(63,185,80,0.3);
            border-radius: 10px;
            padding: 2px 10px;
            letter-spacing: 1px;
        }


    )");


}

// ─────────────────────────────────────────────
//  CONSTRUCTOR
// ─────────────────────────────────────────────
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    applyGlobalStyles();
    setWindowTitle("Community Health Center — Patient Queue System");
    setMinimumSize(1000, 700);
    resize(1200, 800);

    stackedWidget = new QStackedWidget;
    setCentralWidget(stackedWidget);

    landingPage   = buildLandingPage();
    dashboardPage = buildDashboardPage();

    stackedWidget->addWidget(landingPage);
    stackedWidget->addWidget(dashboardPage);
    stackedWidget->setCurrentIndex(0);

    connect(btnEnterSystem, &QPushButton::clicked, this, &MainWindow::showDashboard);
    connect(btnAddRegular,  &QPushButton::clicked, this, &MainWindow::addRegularPatient);
    connect(btnAddEmergency,&QPushButton::clicked, this, &MainWindow::addEmergencyPatient);
    connect(btnServe,       &QPushButton::clicked, this, &MainWindow::serveNextPatient);
    connect(btnQuit, &QPushButton::clicked, this, &QMainWindow::close);

    clockTimer = new QTimer(this);
    connect(clockTimer, &QTimer::timeout, this, &MainWindow::updateClock);
    clockTimer->start(1000);
    updateClock();
}

// ─────────────────────────────────────────────
//  LANDING PAGE
// ─────────────────────────────────────────────
QWidget* MainWindow::buildLandingPage()
{
    QWidget *page = new QWidget;
    page->setObjectName("landingPage");

    QVBoxLayout *root = new QVBoxLayout(page);
    root->setAlignment(Qt::AlignCenter);
    root->setContentsMargins(60, 60, 60, 60);
    root->setSpacing(0);

    // ── Hero card ──
    QFrame *card = new QFrame;
    card->setObjectName("statCard");
    card->setMaximumWidth(620);
    card->setMinimumWidth(480);

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(52, 52, 52, 52);
    cardLayout->setSpacing(22);
    cardLayout->setAlignment(Qt::AlignCenter);

    // Cross / medical icon (Unicode symbol)
    QLabel *icon = new QLabel("✚");
    icon->setAlignment(Qt::AlignCenter);
    icon->setStyleSheet("font-size: 52px; color: #58a6ff; background: rgba(88,166,255,0.08);"
                        "border-radius: 50px; padding: 18px; border: 1px solid rgba(88,166,255,0.2);");
    icon->setFixedSize(96, 96);

    QLabel *badge = new QLabel("COMMUNITY HEALTH CENTER");
    badge->setObjectName("lblHeroBadge");
    badge->setAlignment(Qt::AlignCenter);

    QLabel *title = new QLabel("Patient Queue\nManagement");
    title->setObjectName("lblHeroTitle");
    title->setAlignment(Qt::AlignCenter);

    QLabel *subtitle = new QLabel(
        "Efficiently triage and manage emergency\n"
        "and regular patient queues in real-time."
        );
    subtitle->setObjectName("lblHeroSubtitle");
    subtitle->setAlignment(Qt::AlignCenter);

    // Feature pills
    QHBoxLayout *pillRow = new QHBoxLayout;
    pillRow->setAlignment(Qt::AlignCenter);
    pillRow->setSpacing(10);

    auto makePill = [](const QString &text, const QString &color) {
        QLabel *p = new QLabel(text);
        p->setStyleSheet(QString(
                             "font-size: 11px; font-weight: 600; color: %1;"
                             "background: transparent; border: 1px solid %1;"
                             "border-radius: 10px; padding: 3px 12px;"
                             ).arg(color));
        return p;
    };
    pillRow->addWidget(makePill("⚡  Priority Triage",   "#f0883e"));
    pillRow->addWidget(makePill("🔴  Emergency Queue",    "#f85149"));
    pillRow->addWidget(makePill("🟢  Regular Queue",      "#3fb950"));

    btnEnterSystem = new QPushButton("Enter System  →");
    btnEnterSystem->setObjectName("btnEnter");
    btnEnterSystem->setCursor(Qt::PointingHandCursor);
    btnEnterSystem->setFixedHeight(52);

    QLabel *versionLabel = new QLabel("v1.0  ·  Queue Management System");
    versionLabel->setAlignment(Qt::AlignCenter);
    versionLabel->setStyleSheet("font-size: 11px; color: #484f58;");

    cardLayout->addWidget(icon,   0, Qt::AlignCenter);
    cardLayout->addSpacing(4);
    cardLayout->addWidget(badge,  0, Qt::AlignCenter);
    cardLayout->addWidget(title,  0, Qt::AlignCenter);
    cardLayout->addWidget(subtitle, 0, Qt::AlignCenter);
    cardLayout->addSpacing(4);
    cardLayout->addLayout(pillRow);
    cardLayout->addSpacing(12);
    cardLayout->addWidget(btnEnterSystem);
    cardLayout->addSpacing(4);
    cardLayout->addWidget(versionLabel, 0, Qt::AlignCenter);

    // Drop shadow on card
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(60);
    shadow->setOffset(0, 12);
    shadow->setColor(QColor(0, 0, 0, 120));
    card->setGraphicsEffect(shadow);

    root->addWidget(card, 0, Qt::AlignCenter);
    return page;
}

// ─────────────────────────────────────────────
//  STAT CARD HELPER
// ─────────────────────────────────────────────
QFrame* MainWindow::buildStatCard(const QString &title, QLabel *&valueLabel, const QString &color)
{
    QFrame *card = new QFrame;
    card->setObjectName("statCard");
    card->setMinimumHeight(90);

    QVBoxLayout *l = new QVBoxLayout(card);
    l->setContentsMargins(20, 18, 20, 18);
    l->setSpacing(4);

    QLabel *titleLbl = new QLabel(title.toUpper());
    titleLbl->setObjectName("statTitle");

    valueLabel = new QLabel("0");
    valueLabel->setObjectName("statValue");
    valueLabel->setStyleSheet(QString("color: %1;").arg(color));

    l->addWidget(valueLabel);
    l->addWidget(titleLbl);

    return card;
}

// ─────────────────────────────────────────────
//  DASHBOARD PAGE
// ─────────────────────────────────────────────
QWidget* MainWindow::buildDashboardPage()
{
    QWidget *page = new QWidget;
    page->setObjectName("dashboardPage");

    QVBoxLayout *root = new QVBoxLayout(page);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(0);

    // ── HEADER BAR ──
    QFrame *header = new QFrame;
    header->setObjectName("headerBar");
    header->setFixedHeight(58);

    QHBoxLayout *hdrLayout = new QHBoxLayout(header);
    hdrLayout->setContentsMargins(28, 0, 28, 0);

    QLabel *cross = new QLabel("✚");
    cross->setStyleSheet("font-size: 18px; color: #58a6ff;");

    QLabel *appName = new QLabel("Community Health Center");
    appName->setObjectName("lblAppName");

    QFrame *vline = new QFrame;
    vline->setFrameShape(QFrame::VLine);
    vline->setStyleSheet("color: #21262d;");

    QLabel *subName = new QLabel("Patient Queue Management System");
    subName->setStyleSheet("font-size: 12px; color: #8b949e;");

    hdrLayout->addWidget(cross);
    hdrLayout->addSpacing(8);
    hdrLayout->addWidget(appName);
    hdrLayout->addWidget(vline);
    hdrLayout->addWidget(subName);
    hdrLayout->addStretch();

    lblClockDisplay = new QLabel;
    lblClockDisplay->setObjectName("lblClock");
    hdrLayout->addWidget(lblClockDisplay);

    btnQuit = new QPushButton("✕  Quit");
    btnQuit->setObjectName("btnQuit");
    btnQuit->setCursor(Qt::PointingHandCursor);
    btnQuit->setFixedHeight(32);
    hdrLayout->addSpacing(16);
    hdrLayout->addWidget(btnQuit);

    root->addWidget(header);

    // ── SCROLL AREA (main content) ──
    QScrollArea *scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setStyleSheet("background: #0d1117; border: none;");

    QWidget *contentWidget = new QWidget;
    QVBoxLayout *content = new QVBoxLayout(contentWidget);
    content->setContentsMargins(28, 24, 28, 24);
    content->setSpacing(20);

    // ── STAT CARDS ROW ──
    QHBoxLayout *statsRow = new QHBoxLayout;
    statsRow->setSpacing(14);

    statsRow->addWidget(buildStatCard("Emergency Queue",  lblEmergencyCount, "#f85149"));
    statsRow->addWidget(buildStatCard("Regular Queue",    lblRegularCount,   "#3fb950"));
    statsRow->addWidget(buildStatCard("Patients Served",  lblServedCount,    "#58a6ff"));

    content->addLayout(statsRow);

    // ── INPUT PANEL ──
    QFrame *inputPanel = new QFrame;
    inputPanel->setObjectName("inputPanel");

    QVBoxLayout *ipRoot = new QVBoxLayout(inputPanel);
    ipRoot->setContentsMargins(24, 20, 24, 20);
    ipRoot->setSpacing(16);

    QLabel *secTitle = new QLabel("REGISTER PATIENT");
    secTitle->setObjectName("sectionTitle");

    QHBoxLayout *fieldRow = new QHBoxLayout;
    fieldRow->setSpacing(14);

    // Name
    QVBoxLayout *nameCol = new QVBoxLayout;
    QLabel *nameLabel = new QLabel("Patient Name");
    nameLabel->setObjectName("fieldLabel");
    nameEdit = new QLineEdit;
    nameEdit->setPlaceholderText("Patient Name");
    nameEdit->setMinimumHeight(42);
    nameCol->addWidget(nameLabel);
    nameCol->addWidget(nameEdit);

    // Case
    QVBoxLayout *caseCol = new QVBoxLayout;
    QLabel *caseLabel = new QLabel("Emergency Case");
    caseLabel->setObjectName("fieldLabel");
    caseEdit = new QLineEdit;
    caseEdit->setPlaceholderText("e.g. Chest Pain");
    caseEdit->setMinimumHeight(42);
    caseCol->addWidget(caseLabel);
    caseCol->addWidget(caseEdit);

    // Priority
    QVBoxLayout *prioCol = new QVBoxLayout;
    prioCol->setContentsMargins(0,0,0,0);
    QLabel *prioLabel = new QLabel("Priority (1–10)");
    prioLabel->setObjectName("fieldLabel");
    prioritySpin = new QSpinBox;
    prioritySpin->setRange(1, 10);
    prioritySpin->setMinimumHeight(42);
    prioCol->addWidget(prioLabel);
    prioCol->addWidget(prioritySpin);

    fieldRow->addLayout(nameCol, 3);
    fieldRow->addLayout(caseCol, 3);
    fieldRow->addLayout(prioCol, 1);

    // Action buttons
    QHBoxLayout *btnRow = new QHBoxLayout;
    btnRow->setSpacing(12);

    btnAddRegular   = new QPushButton("＋  Add Regular Patient");
    btnAddRegular->setObjectName("btnRegular");
    btnAddRegular->setMinimumHeight(44);
    btnAddRegular->setCursor(Qt::PointingHandCursor);

    btnAddEmergency = new QPushButton("⚠  Add Emergency Patient");
    btnAddEmergency->setObjectName("btnEmergency");
    btnAddEmergency->setMinimumHeight(44);
    btnAddEmergency->setCursor(Qt::PointingHandCursor);

    btnServe        = new QPushButton("▶  Serve Next Patient");
    btnServe->setObjectName("btnServe");
    btnServe->setMinimumHeight(44);
    btnServe->setCursor(Qt::PointingHandCursor);

    btnRow->addWidget(btnAddRegular);
    btnRow->addWidget(btnAddEmergency);
    btnRow->addStretch();
    btnRow->addWidget(btnServe);

    ipRoot->addWidget(secTitle);
    ipRoot->addLayout(fieldRow);
    ipRoot->addLayout(btnRow);

    content->addWidget(inputPanel);

    // ── TABLES ROW ──
    QHBoxLayout *tablesRow = new QHBoxLayout;
    tablesRow->setSpacing(14);

    // ── Emergency table panel ──
    QFrame *emergPanel = new QFrame;
    emergPanel->setObjectName("tablePanel");
    QVBoxLayout *epLayout = new QVBoxLayout(emergPanel);
    epLayout->setContentsMargins(20, 18, 20, 18);
    epLayout->setSpacing(14);

    QHBoxLayout *epHeader = new QHBoxLayout;
    QLabel *epTitle = new QLabel("Emergency Queue");
    epTitle->setObjectName("tablePanelTitle");
    QLabel *epBadge = new QLabel("CRITICAL");
    epBadge->setObjectName("emergencyBadge");
    epHeader->addWidget(epTitle);
    epHeader->addWidget(epBadge);
    epHeader->addStretch();

    tableEmergency = new QTableWidget;
    tableEmergency->setColumnCount(4);
    tableEmergency->setHorizontalHeaderLabels({"Name", "Case", "Priority", "Arrival"});
    tableEmergency->horizontalHeader()->setStretchLastSection(true);
    tableEmergency->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tableEmergency->verticalHeader()->setVisible(false);
    tableEmergency->setAlternatingRowColors(true);
    tableEmergency->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableEmergency->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableEmergency->setShowGrid(false);
    tableEmergency->setFocusPolicy(Qt::NoFocus);
    tableEmergency->setMinimumHeight(260);

    epLayout->addLayout(epHeader);
    epLayout->addWidget(tableEmergency);

    // ── Regular table panel ──
    QFrame *regPanel = new QFrame;
    regPanel->setObjectName("tablePanel");
    QVBoxLayout *rpLayout = new QVBoxLayout(regPanel);
    rpLayout->setContentsMargins(20, 18, 20, 18);
    rpLayout->setSpacing(14);

    QHBoxLayout *rpHeader = new QHBoxLayout;
    QLabel *rpTitle = new QLabel("Regular Queue");
    rpTitle->setObjectName("tablePanelTitle");
    QLabel *rpBadge = new QLabel("STANDARD");
    rpBadge->setObjectName("regularBadge");
    rpHeader->addWidget(rpTitle);
    rpHeader->addWidget(rpBadge);
    rpHeader->addStretch();

    tableRegular = new QTableWidget;
    tableRegular->setColumnCount(2);
    tableRegular->setHorizontalHeaderLabels({"Name", "Arrival"});
    tableRegular->horizontalHeader()->setStretchLastSection(true);
    tableRegular->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tableRegular->verticalHeader()->setVisible(false);
    tableRegular->setAlternatingRowColors(true);
    tableRegular->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableRegular->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableRegular->setShowGrid(false);
    tableRegular->setFocusPolicy(Qt::NoFocus);
    tableRegular->setMinimumHeight(260);

    rpLayout->addLayout(rpHeader);
    rpLayout->addWidget(tableRegular);

    tablesRow->addWidget(emergPanel);
    tablesRow->addWidget(regPanel);

    content->addLayout(tablesRow);
    scroll->setWidget(contentWidget);
    root->addWidget(scroll);

    // ── STATUS BAR ──
    QFrame *statusBarFrame = new QFrame;
    statusBarFrame->setObjectName("statusBar");
    statusBarFrame->setFixedHeight(36);

    QHBoxLayout *sbLayout = new QHBoxLayout(statusBarFrame);
    sbLayout->setContentsMargins(28, 0, 28, 0);

    statusMsgLabel = new QLabel("System ready. Add patients to begin.");
    statusMsgLabel->setObjectName("statusMsg");

    QLabel *footerRight = new QLabel("Community Health Center  ·  Patient Queue Management System");
    footerRight->setStyleSheet("font-size: 11px; color: #30363d;");

    sbLayout->addWidget(statusMsgLabel);
    sbLayout->addStretch();
    sbLayout->addWidget(footerRight);

    root->addWidget(statusBarFrame);

    return page;
}

// ─────────────────────────────────────────────
//  HELPERS
// ─────────────────────────────────────────────
int MainWindow::getCurrentTimeInMinutes()
{
    QTime t = QTime::currentTime();
    return t.hour() * 60 + t.minute();
}

QString MainWindow::convertTime(int total)
{
    int h = total / 60;
    int m = total % 60;
    return QString("%1:%2")
        .arg(h, 2, 10, QChar('0'))
        .arg(m, 2, 10, QChar('0'));
}

void MainWindow::showStatusMessage(const QString &msg, const QString &type)
{
    QString color = "#8b949e";
    if (type == "success") color = "#3fb950";
    else if (type == "error")   color = "#f85149";
    else if (type == "warning") color = "#f0883e";
    else if (type == "info")    color = "#58a6ff";

    statusMsgLabel->setStyleSheet(
        QString("font-size: 12px; color: %1;").arg(color));
    statusMsgLabel->setText("● " + msg);
}

void MainWindow::updateStats()
{
    lblEmergencyCount->setText(QString::number(emergency.size()));
    lblRegularCount->setText(QString::number(consultation.size()));
    lblServedCount->setText(QString::number(servedCount));
}

void MainWindow::updateClock()
{
    lblClockDisplay->setText(QTime::currentTime().toString("hh:mm:ss  AP"));
}

// ─────────────────────────────────────────────
//  SLOTS
// ─────────────────────────────────────────────
void MainWindow::showDashboard()
{
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::addRegularPatient()
{
    QString name = nameEdit->text().trimmed();
    if (name.isEmpty()) {
        showStatusMessage("Please enter a patient name.", "warning");
        return;
    }

    int time = getCurrentTimeInMinutes();
    consultation.push({name.toStdString(), "Regular", 0, time});
    nameEdit->clear();

    showStatusMessage("Regular patient '" + name + "' added to queue.", "success");
    updateTables();
    updateStats();
}

void MainWindow::addEmergencyPatient()
{
    QString name   = nameEdit->text().trimmed();
    QString ecase  = caseEdit->text().trimmed();
    int priority   = prioritySpin->value();

    if (name.isEmpty()) {
        showStatusMessage("Please enter a patient name.", "warning");
        return;
    }
    if (ecase.isEmpty()) {
        showStatusMessage("Please enter the emergency case description.", "warning");
        return;
    }

    int time = getCurrentTimeInMinutes();
    emergency.push({
        name.toStdString(),
        ecase.toStdString(),
        priority,
        time
    });

    nameEdit->clear();
    caseEdit->clear();
    prioritySpin->setValue(1);

    showStatusMessage(
        "Emergency patient '" + name + "' added (Priority " + QString::number(priority) + ").",
        "error"
        );
    updateTables();
    updateStats();
}

void MainWindow::serveNextPatient()
{
    if (!emergency.empty()) {
        patient p = emergency.top();
        emergency.pop();
        servedCount++;
        showStatusMessage(
            "Serving emergency patient: " + QString::fromStdString(p.name) +
                " — " + QString::fromStdString(p.ecase),
            "info"
            );
    } else if (!consultation.empty()) {
        patient p = consultation.front();
        consultation.pop();
        servedCount++;
        showStatusMessage(
            "Serving regular patient: " + QString::fromStdString(p.name),
            "info"
            );
    } else {
        showStatusMessage("No patients in queue.", "warning");
        return;
    }

    updateTables();
    updateStats();
}

void MainWindow::updateTables()
{
    // ── Emergency table ──
    tableEmergency->setRowCount(0);
    priority_queue<patient> tempE = emergency;
    int row = 0;
    while (!tempE.empty()) {
        patient p = tempE.top();
        tempE.pop();

        tableEmergency->insertRow(row);

        auto setItem = [&](int col, const QString &text, const QString &color = "") {
            QTableWidgetItem *item = new QTableWidgetItem(text);
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
            if (!color.isEmpty())
                item->setForeground(QColor(color));
            tableEmergency->setItem(row, col, item);
        };

        setItem(0, QString::fromStdString(p.name));
        setItem(1, QString::fromStdString(p.ecase));

        // Color-code priority
        QString prioColor = "#3fb950";
        if (p.priority >= 8)      prioColor = "#f85149";
        else if (p.priority >= 5) prioColor = "#f0883e";

        setItem(2, QString::number(p.priority), prioColor);
        setItem(3, convertTime(p.arrival_total));

        tableEmergency->setRowHeight(row, 44);
        row++;
    }

    // ── Regular table ──
    tableRegular->setRowCount(0);
    queue<patient> tempR = consultation;
    row = 0;
    while (!tempR.empty()) {
        patient p = tempR.front();
        tempR.pop();

        tableRegular->insertRow(row);

        auto setItem = [&](int col, const QString &text) {
            QTableWidgetItem *item = new QTableWidgetItem(text);
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
            tableRegular->setItem(row, col, item);
        };

        setItem(0, QString::fromStdString(p.name));
        setItem(1, convertTime(p.arrival_total));

        tableRegular->setRowHeight(row, 44);
        row++;
    }
}
