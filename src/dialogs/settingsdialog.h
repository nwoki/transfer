#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QtWidgets/QDialog>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    void showEvent(QShowEvent *event) Q_DECL_FINAL;

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
