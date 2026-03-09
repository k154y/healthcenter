#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QWidget>
#include <QStackedWidget>
#include <QFrame>
#include <QTimer>
#include <queue>
#include <string>
using namespace std;

struct patient {
    string name;
    string ecase;
    int priority;
    int arrival_total;

    bool operator<(const patient &o) const {
        return priority < o.priority;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void addRegularPatient();
    void addEmergencyPatient();
    void serveNextPatient();
    void showDashboard();
    void updateClock();

private:
    // Pages
    QStackedWidget  *stackedWidget;
    QWidget         *landingPage;
    QWidget         *dashboardPage;

    // Landing page widgets
    QPushButton     *btnEnterSystem;
    QPushButton     *btnQuit;

    // Dashboard - Input
    QLineEdit       *nameEdit;
    QLineEdit       *caseEdit;
    QSpinBox        *prioritySpin;

    // Dashboard - Buttons
    QPushButton     *btnAddRegular;
    QPushButton     *btnAddEmergency;
    QPushButton     *btnServe;

    // Dashboard - Tables
    QTableWidget    *tableEmergency;
    QTableWidget    *tableRegular;

    // Dashboard - Stats
    QLabel          *lblEmergencyCount;
    QLabel          *lblRegularCount;
    QLabel          *lblClockDisplay;
    QLabel          *lblServedCount;

    // Status bar label
    QLabel          *statusMsgLabel;

    // Clock timer
    QTimer          *clockTimer;

    // Counters
    int servedCount = 0;

    // Data
    priority_queue<patient> emergency;
    queue<patient>          consultation;

    // Helpers
    int     getCurrentTimeInMinutes();
    QString convertTime(int total);
    void    updateTables();
    void    updateStats();
    void    showStatusMessage(const QString &msg, const QString &type = "info");
    void    applyGlobalStyles();

    QWidget* buildLandingPage();
    QWidget* buildDashboardPage();
    QFrame*  buildStatCard(const QString &title, QLabel *&valueLabel, const QString &color);
};

#endif // MAINWINDOW_H
