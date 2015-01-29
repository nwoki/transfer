#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QSettings>
#include <QtCore/QStandardPaths>

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>


SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, [this] () {
        QString username = ui->usernameLineEdit->text();
        QString downloadDir = ui->downloadDirectoryLineEdit->text();

        // check data validity
        if (username.isEmpty()) {
            QMessageBox::warning(nullptr, tr("Invalid settings"), tr("The username cannot be blank"));
            return;
        }

        if (downloadDir.isEmpty()) {
            downloadDir = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
        }

        // save new data
        QSettings settings;
        settings.setValue("user/name", username);
        settings.setValue("user/download_dir", downloadDir);
        settings.sync();

        close();
    });

    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, [this] () {
        close();
    });

    connect(ui->downloadDirectoryToolButton, &QAbstractButton::clicked, [this] () {
        QString downloadDir = QFileDialog::getExistingDirectory(nullptr
                                                                , tr("Select download directory")
                                                                , QDir::homePath());

        if (!downloadDir.isEmpty()) {
            ui->downloadDirectoryLineEdit->setText(downloadDir);
        }
    });

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::showEvent(QShowEvent* event)
{
    // load info from settings
    QSettings settings;

    ui->usernameLineEdit->setText(settings.value("user/name").toString());
    ui->downloadDirectoryLineEdit->setText(settings.value("user/download_dir").toString());

    QDialog::showEvent(event);
}
