#include "capturedialog.h"
#include "ui_Capturedialog.h"

CaptureDialog::CaptureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CaptureDialog)
{
    ui->setupUi(this);
    initial_parameter_display();

    this->update();
}

void CaptureDialog::initial_parameter_display(void)
{
    dvb_config_get( &m_cfg );
    switch(m_cfg.cap_format.video_format)
    {
    case CAP_PAL:
        ui->radioButtonPal720x576->setChecked(true);
        break;
    case CAP_NTSC:
        ui->radioButtonNtsc720x480->setChecked(true);
        break;
    case CAP_AUTO:
    default:
        ui->radioButtonAuto->setChecked(true);
        break;
    }
}

void CaptureDialog::on_buttonBox_accepted()
{
    if(ui->radioButtonPal720x576->isChecked() == true ) m_cfg.cap_format.video_format = CAP_PAL;
    if(ui->radioButtonNtsc720x480->isChecked() == true ) m_cfg.cap_format.video_format = CAP_NTSC;
    if(ui->radioButtonAuto->isChecked()    == true ) m_cfg.cap_format.video_format = CAP_AUTO;
    dvb_config_save( &m_cfg );
}
