#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtDebug>
#include <stdint.h>
#include <CAENVMElib.h>
#include <iostream>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Muon Life Experiment");
    //ui->groupBox->setStyleSheet("background-color : light-red");
    if (CAENVME_Init(cvV1718, 0, 0, &handleChef) == cvSuccess) qDebug() << "Yeah";
    else qDebug() << "Bad";

    readBoardParameters(ui->spinBox_rotary_switches->value());


    lcdNumber_voltages[0] = ui->lcdNumber_channel_0_voltage;
    lcdNumber_voltages[1] = ui->lcdNumber_channel_1_voltage;
    lcdNumber_voltages[2] = ui->lcdNumber_channel_2_voltage;
    lcdNumber_voltages[3] = ui->lcdNumber_channel_3_voltage;
    lcdNumber_voltages[4] = ui->lcdNumber_channel_4_voltage;
    lcdNumber_voltages[5] = ui->lcdNumber_channel_5_voltage;

    lcdNumber_currents[0] = ui->lcdNumber_channel_0_current;
    lcdNumber_currents[1] = ui->lcdNumber_channel_1_current;
    lcdNumber_currents[2] = ui->lcdNumber_channel_2_current;
    lcdNumber_currents[3] = ui->lcdNumber_channel_3_current;
    lcdNumber_currents[4] = ui->lcdNumber_channel_4_current;
    lcdNumber_currents[5] = ui->lcdNumber_channel_5_current;

    label_state_leds[0] = ui->label_channel_0_state_led;
    label_state_leds[1] = ui->label_channel_1_state_led;
    label_state_leds[2] = ui->label_channel_2_state_led;
    label_state_leds[3] = ui->label_channel_3_state_led;
    label_state_leds[4] = ui->label_channel_4_state_led;
    label_state_leds[5] = ui->label_channel_5_state_led;

    label_ramp_up_leds[0] = ui->label_channel_0_ramp_up_led;
    label_ramp_up_leds[1] = ui->label_channel_1_ramp_up_led;
    label_ramp_up_leds[2] = ui->label_channel_2_ramp_up_led;
    label_ramp_up_leds[3] = ui->label_channel_3_ramp_up_led;
    label_ramp_up_leds[4] = ui->label_channel_4_ramp_up_led;
    label_ramp_up_leds[5] = ui->label_channel_5_ramp_up_led;

    label_ramp_down_leds[0] = ui->label_channel_0_ramp_down_led;
    label_ramp_down_leds[1] = ui->label_channel_1_ramp_down_led;
    label_ramp_down_leds[2] = ui->label_channel_2_ramp_down_led;
    label_ramp_down_leds[3] = ui->label_channel_3_ramp_down_led;
    label_ramp_down_leds[4] = ui->label_channel_4_ramp_down_led;
    label_ramp_down_leds[5] = ui->label_channel_5_ramp_down_led;

    label_over_current_leds[0] = ui->label_channel_0_over_current_led;
    label_over_current_leds[1] = ui->label_channel_1_over_current_led;
    label_over_current_leds[2] = ui->label_channel_2_over_current_led;
    label_over_current_leds[3] = ui->label_channel_3_over_current_led;
    label_over_current_leds[4] = ui->label_channel_4_over_current_led;
    label_over_current_leds[5] = ui->label_channel_5_over_current_led;

    label_over_voltage_leds[0] = ui->label_channel_0_over_voltage_led;
    label_over_voltage_leds[1] = ui->label_channel_1_over_voltage_led;
    label_over_voltage_leds[2] = ui->label_channel_2_over_voltage_led;
    label_over_voltage_leds[3] = ui->label_channel_3_over_voltage_led;
    label_over_voltage_leds[4] = ui->label_channel_4_over_voltage_led;
    label_over_voltage_leds[5] = ui->label_channel_5_over_voltage_led;

    label_under_voltage_leds[0] = ui->label_channel_0_under_voltage_led;
    label_under_voltage_leds[1] = ui->label_channel_1_under_voltage_led;
    label_under_voltage_leds[2] = ui->label_channel_2_under_voltage_led;
    label_under_voltage_leds[3] = ui->label_channel_3_under_voltage_led;
    label_under_voltage_leds[4] = ui->label_channel_4_under_voltage_led;
    label_under_voltage_leds[5] = ui->label_channel_5_under_voltage_led;

    label_maxv_leds[0] = ui->label_channel_0_maxv_led;
    label_maxv_leds[1] = ui->label_channel_1_maxv_led;
    label_maxv_leds[2] = ui->label_channel_2_maxv_led;
    label_maxv_leds[3] = ui->label_channel_3_maxv_led;
    label_maxv_leds[4] = ui->label_channel_4_maxv_led;
    label_maxv_leds[5] = ui->label_channel_5_maxv_led;

    label_maxi_leds[0] = ui->label_channel_0_maxi_led;
    label_maxi_leds[1] = ui->label_channel_1_maxi_led;
    label_maxi_leds[2] = ui->label_channel_2_maxi_led;
    label_maxi_leds[3] = ui->label_channel_3_maxi_led;
    label_maxi_leds[4] = ui->label_channel_4_maxi_led;
    label_maxi_leds[5] = ui->label_channel_5_maxi_led;

    label_trip_leds[0] = ui->label_channel_0_trip_led;
    label_trip_leds[1] = ui->label_channel_1_trip_led;
    label_trip_leds[2] = ui->label_channel_2_trip_led;
    label_trip_leds[3] = ui->label_channel_3_trip_led;
    label_trip_leds[4] = ui->label_channel_4_trip_led;
    label_trip_leds[5] = ui->label_channel_5_trip_led;

    label_over_power_leds[0] = ui->label_channel_0_over_power_led;
    label_over_power_leds[1] = ui->label_channel_1_over_power_led;
    label_over_power_leds[2] = ui->label_channel_2_over_power_led;
    label_over_power_leds[3] = ui->label_channel_3_over_power_led;
    label_over_power_leds[4] = ui->label_channel_4_over_power_led;
    label_over_power_leds[5] = ui->label_channel_5_over_power_led;

    label_disabled_leds[0] = ui->label_channel_0_disabled_led;
    label_disabled_leds[1] = ui->label_channel_1_disabled_led;
    label_disabled_leds[2] = ui->label_channel_2_disabled_led;
    label_disabled_leds[3] = ui->label_channel_3_disabled_led;
    label_disabled_leds[4] = ui->label_channel_4_disabled_led;
    label_disabled_leds[5] = ui->label_channel_5_disabled_led;

    label_interlock_leds[0] = ui->label_channel_0_interlock_led;
    label_interlock_leds[1] = ui->label_channel_1_interlock_led;
    label_interlock_leds[2] = ui->label_channel_2_interlock_led;
    label_interlock_leds[3] = ui->label_channel_3_interlock_led;
    label_interlock_leds[4] = ui->label_channel_4_interlock_led;
    label_interlock_leds[5] = ui->label_channel_5_interlock_led;


    // change color of lcd number for board parameters
    ui->lcdNumber_board_vmax->setPalette(Qt::black);
    ui->lcdNumber_board_imax->setPalette(Qt::black);

    // change color of lcd number for channels parameters
    for (int i=0; i<6; ++i) {
        lcdNumber_voltages[i]->setPalette(Qt::red);
        lcdNumber_currents[i]->setPalette(Qt::red);
    }


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readHV()));
    readHV();
    timer->start(1000); //time specified in ms



    maxOfEntries = 1;
    tMin = ui->doubleSpinBox_tmin->value();
    tMax = ui->doubleSpinBox_tmax->value();
    nBins = ui->spinBox_nbins->value();
    for (int i=0; i<nBins; ++i)
    {
      x.push_back( tMin + i * tMax / nBins + 0.5 * (tMax - tMin) / nBins );
      y.push_back(0);
    }


    bars = new QCPBars(ui->widget_qcp->xAxis, ui->widget_qcp->yAxis);
    ui->widget_qcp->addPlottable(bars);
    bars->setWidth(5.0/x.size());
    bars->setData(x, y);
    //bars->setPen(Qt::NoPen);
    //bars->setBrush(QColor(10, 140, 70, 160));

    ui->widget_qcp->rescaleAxes();
    ui->widget_qcp->xAxis->setLabel("Time (µs)");
    ui->widget_qcp->yAxis->setLabel("# entries");
    ui->widget_qcp->xAxis->setRange(tMin*0.99, tMax*1.01);
    ui->widget_qcp->yAxis->setRange(0, 10);

    stopRun = false;
    running = false;

    if (!running) ui->pushButton_stop_run->setEnabled(false);
    ui->widget_bar_config->setEnabled(true);

    this->setCentralWidget(ui->tabWidget);
    ui->tabWidget->setCurrentIndex(0);

    this->setFixedSize(this->size());

}

MainWindow::~MainWindow()
{
    qDebug() << "Closing connection with VME crate";
    CAENVME_End(handleChef);
    delete ui;
}

void MainWindow::closing() {
    qDebug() << "About to quit";
    if (running) stopRun = true;
    usleep(100);
    qApp->quit();
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, this->windowTitle(),
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        closing();
        event->accept();
    }
}

void MainWindow::readBoardParameters(int baseAddress)
{
    baseAddressHV = baseAddress << 16;

    uint16_t value16;
    // read board parameters
    QString model;
    CAENVME_ReadCycle(handleChef, baseAddressHV + 0x8116, &value16, cvA32_U_DATA, cvD16);
    model += QString((char) (value16 & 0xff));
    model += QString((char) ((value16 >> 8) & 0xff));
    CAENVME_ReadCycle(handleChef, baseAddressHV + 0x8118, &value16, cvA32_U_DATA, cvD16);
    model += QString((char) (value16 & 0xff));
    model += QString((char) ((value16 >> 8) & 0xff));
    CAENVME_ReadCycle(handleChef, baseAddressHV + 0x811A, &value16, cvA32_U_DATA, cvD16);
    model += QString((char) (value16 & 0xff));
    model += QString((char) ((value16 >> 8) & 0xff));

    if (!model.startsWith("V653")){
        qDebug() << "Wrong board";
        ui->lineEdit_board_model->setText("UNKNOWN");
        HVenabled = false;
        ui->widget_configuration->setEnabled(false);
        ui->lcdNumber_board_vmax->display(888888);
        ui->lcdNumber_board_imax->display(888888);
    }
    else {
        ui->lineEdit_board_model->setText(model);
        HVenabled = true;
        ui->widget_configuration->setEnabled(true);
        CAENVME_ReadCycle(handleChef, baseAddressHV + 0x0050, &value16, cvA32_U_DATA, cvD16);
        ui->lcdNumber_board_vmax->display(value16);
        CAENVME_ReadCycle(handleChef, baseAddressHV + 0x0054, &value16, cvA32_U_DATA, cvD16);
        ui->lcdNumber_board_imax->display(value16);
    }

}

void MainWindow::readHV()
{
    uint16_t value16;
    if (!HVenabled) return;
    bool hvOn = false;
    // read channels parameters
    for (int i=0; i<6; ++i) {
        CAENVME_ReadCycle(handleChef, baseAddressHV + 0x80 * i + 0x88, &value16, cvA32_U_DATA, cvD16);
        lcdNumber_voltages[i]->display(value16*0.1);
        CAENVME_ReadCycle(handleChef, baseAddressHV + 0x80 * i + 0x8C, &value16, cvA32_U_DATA, cvD16);
        lcdNumber_currents[i]->display(value16*0.05);
        CAENVME_ReadCycle(handleChef, baseAddressHV + 0x80 * i + 0x94, &value16, cvA32_U_DATA, cvD16);
        label_state_leds[i]->setPixmap(value16 & (0x1 << 0) ? QPixmap(":/green.png") : QPixmap(":/lightgreen.png"));
        hvOn = hvOn || value16;
        label_ramp_up_leds[i]->setPixmap(value16 & (0x1 << 1) ? QPixmap(":/orange.png") : QPixmap(":/lightorange.png"));
        label_ramp_down_leds[i]->setPixmap(value16 & (0x1 << 2) ? QPixmap(":/orange.png") : QPixmap(":/lightorange.png"));
        label_over_current_leds[i]->setPixmap(value16 & (0x1 << 3) ? QPixmap(":/red.png") : QPixmap(":/lightred.png"));
        label_over_voltage_leds[i]->setPixmap(value16 & (0x1 << 4) ? QPixmap(":/red.png") : QPixmap(":/lightred.png"));
        label_under_voltage_leds[i]->setPixmap(value16 & (0x1 << 5) ? QPixmap(":/red.png") : QPixmap(":/lightred.png"));
        label_maxv_leds[i]->setPixmap(value16 & (0x1 << 6) ? QPixmap(":/orange.png") : QPixmap(":/lightorange.png"));
        label_maxi_leds[i]->setPixmap(value16 & (0x1 << 7) ? QPixmap(":/orange.png") : QPixmap(":/lightorange.png"));
        label_trip_leds[i]->setPixmap(value16 & (0x1 << 8) ? QPixmap(":/orange.png") : QPixmap(":/lightorange.png"));
        label_over_power_leds[i]->setPixmap(value16 & (0x1 << 9) ? QPixmap(":/red.png") : QPixmap(":/lightred.png"));
        label_disabled_leds[i]->setPixmap(value16 & (0x1 << 11) ? QPixmap(":/red.png") : QPixmap(":/lightred.png"));
        label_interlock_leds[i]->setPixmap(value16 & (0x1 << 12) ? QPixmap(":/red.png") : QPixmap(":/lightred.png"));
    }

    ui->label_high_voltage->setEnabled(hvOn);
    CAENVME_ReadCycle(handleChef, baseAddressHV + 0x0050, &value16, cvA32_U_DATA, cvD16);
    ui->lcdNumber_board_vmax->display(value16);
    CAENVME_ReadCycle(handleChef, baseAddressHV + 0x0054, &value16, cvA32_U_DATA, cvD16);
    ui->lcdNumber_board_imax->display(value16);
    //CAENVME_ReadCycle(handleChef, 0xAA000090, &value16, cvA32_U_DATA, cvD16);

    //value16 = 1;
    //qDebug() << value16;
    //unsigned int data = 0x0;
    //CVErrorCodes flag = CAENVME_WriteCycle(handleChef, 0xAA000090, &data, cvA32_U_DATA, cvD16);
    //if (flag != cvSuccess) qDebug() << "Couldn't write";

    /*
     * QMessageBox::information(
        this,
        tr("Application Name"),
        tr("Hello") );
    */

}

void MainWindow::on_radioButton_on_off_clicked()
{
    if (ui->radioButton_on_off->isChecked()) {
        ui->radioButton_on_off->setText("ON");
        ui->label_state_led->setPixmap(QPixmap(":/green.png"));
    }
    else {
        ui->radioButton_on_off->setText("OFF");
        ui->label_state_led->setPixmap(QPixmap(":/grey.png"));
    }
}

void MainWindow::on_pushButton_set_clicked()
{

    int channel, state, voltage, current, tripTime, vMax, rampDown, rampUp;
    channel = ui->spinBox_channel->value();
    state = ui->radioButton_on_off->isChecked();
    voltage = ui->spinBox_voltage->value();
    current = ui->spinBox_current->value();
    tripTime = ui->spinBox_trip_time->value();
    vMax = ui->spinBox_vmax->value();
    rampDown = ui->spinBox_ramp_down->value();
    rampUp = ui->spinBox_ramp_up->value();


    if (channel == -1) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to set all the channels ?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
    }

    if (channel < -1 || channel > 5) {
         qDebug() << "Impossible channel";
    }
    else {
        int start = channel;
        int end = channel+1;
        if (channel == -1) {
            start = 0;
            end = 6;
        }
        for (int i=start; i<end; ++i) {
            uint16_t value16;
            value16 = state ? 0x1 : 0x0;
            CAENVME_WriteCycle(handleChef, baseAddressHV + 0x80 * i + 0x90, &value16, cvA32_U_DATA, cvD16);

            value16 = voltage * 10;
            CAENVME_WriteCycle(handleChef, baseAddressHV + 0x80 * i + 0x80, &value16, cvA32_U_DATA, cvD16);

            value16 = current * 20;
            CAENVME_WriteCycle(handleChef, baseAddressHV + 0x80 * i + 0x84, &value16, cvA32_U_DATA, cvD16);

            value16 = tripTime * 10;
            CAENVME_WriteCycle(handleChef, baseAddressHV + 0x80 * i + 0x98, &value16, cvA32_U_DATA, cvD16);

            value16 = vMax * 10;
            CAENVME_WriteCycle(handleChef, baseAddressHV + 0x80 * i + 0x9C, &value16, cvA32_U_DATA, cvD16);

            value16 = rampDown;
            CAENVME_WriteCycle(handleChef, baseAddressHV + 0x80 * i + 0xA0, &value16, cvA32_U_DATA, cvD16);

            value16 = rampUp;
            CAENVME_WriteCycle(handleChef, baseAddressHV + 0x80 * i + 0xA4, &value16, cvA32_U_DATA, cvD16);
        }
    }

}

void MainWindow::on_spinBox_channel_valueChanged(int arg1)
{
    //QMessageBox msgBox;
    //msgBox.setText("The channel " + QString::number(arg1) + "must be read.");
    //msgBox.exec();
    qDebug() << QString::number(arg1);
}

void MainWindow::on_spinBox_rotary_switches_valueChanged(int baseAddress)
{
    readBoardParameters(baseAddress);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    //qDebug() << QString::number(index);
    if (index == 1) {
        timer->stop();
    }
    else if (index == 0) {
        timer->start(1000);
    }
}

void MainWindow::on_pushButton_start_run_clicked()
{
    if (running) return;


    //get current date
    QDate date = QDate::currentDate();
    QString dateString = date.toString();
    qDebug() << dateString.replace(" ", "_");
    //get current time
    QTime time = QTime::currentTime();
    QString timeString = time.toString();
    qDebug() << timeString.replace(":", "_");

    QString fileName = "/home/aleonard/Desktop/MuonLifeExpData/Muon_Life_Data_";
    fileName += dateString;
    fileName += "_at_";
    fileName += timeString;
    fileName += ".txt";

    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        qDebug() << "Problem opening or creating the file";
    }
    else {
        QTextStream stream(&file);


        ui->widget_bar_config->setEnabled(false);
        ui->pushButton_start_run->setEnabled(false);
        ui->pushButton_stop_run->setEnabled(true);
        uint16_t value16;
        uint32_t value32;
        uint32_t prevStart = 0;
        uint32_t currentStop = 0;
        std::vector<uint32_t> differences(100);
        qDebug() << "Reading Output Buffer Register";
        running = true;
        stopRun = false;
        int nStop = 0;
        do {
            QCoreApplication::processEvents();
            //std::cout << "Reading Status Register" << std::endl;
            CAENVME_ReadCycle(handleChef, 0xDD000000 + 0x1002, &value16, cvA32_U_DATA, cvD16);
            //std::cout << "Any Data Stored: " << (value16 & 0x1) << std::endl;
            //std::cout << "Almost full ? : " << ((value16 >> 1) & 0x1) << std::endl;

            if (value16 & 0x1) {
                //std::cout << "Reading Output Buffer Register" << std::endl;
                CAENVME_ReadCycle(handleChef, 0xDD000000 + 0x0000, &value32, cvA32_U_DATA, cvD32);
                //std::cout << "Data: 0x" << std::hex << ((value32 >> 27) & 0x1F) << std::endl;
                //std::cout << "Trailing ?: 0x" << std::hex << ((value32 >> 26) & 0x1) << std::endl;
                //std::cout << "Channel: 0x" << std::hex << ((value32 >> 21) & 0x1F) << std::endl;
                //std::cout << "TDC Meas: " << std::dec << (value32 & 0x1FFFFF) << std::endl;
                int channel = ((value32 >> 21) & 0x1F);
                if (channel == 0) prevStart = (value32 & 0x1FFFFF);
                else if (channel == 1) {
                    nStop++;
                    currentStop = (value32 & 0x1FFFFF);
                    double difference = (currentStop - prevStart)*0.000025;
                    differences.push_back(difference);
                    qDebug() << "event " << QString::number(nStop) << "  " << QString::number(difference);
                    if (difference <= tMax && difference >= tMin) updatePlot(difference);
                    stream << QString::number(difference) + "\n";

                }
            }
            usleep(1);
        } while (!stopRun);
        qDebug() << "Run has been stoped";
        file.close();
        ui->widget_bar_config->setEnabled(true);

        stopRun = false;
        running = false;
        ui->pushButton_start_run->setEnabled(true);
        ui->pushButton_stop_run->setEnabled(false);
    }
}

void MainWindow::on_spinBox_nbins_valueChanged(int arg1)
{
    nBins = arg1;
    x.clear();
    y.clear();
    for (int i=0; i<nBins; ++i) {
        x.push_back(0);
        y.push_back(0);
    }
    adjustPlot();
}

void MainWindow::on_doubleSpinBox_tmax_valueChanged(double arg1)
{
    if (arg1 <= tMin) return;
    tMax = arg1;
    adjustPlot();
}

void MainWindow::on_doubleSpinBox_tmin_valueChanged(double arg1)
{
    if (arg1 >= tMax) return;
    tMin = arg1;
    adjustPlot();
}

void MainWindow::adjustPlot()
{
    for (int i=0; i<nBins; ++i) {
        x[i] = tMin + i * tMax / nBins + 0.5 * (tMax - tMin) / nBins;
        y[i] = 0;
    }
    maxOfEntries = 1;
    bars->clearData();
    bars->setData(x, y);
    ui->widget_qcp->rescaleAxes();
    ui->widget_qcp->xAxis->setRange(tMin*0.99, tMax*1.01);
    ui->widget_qcp->yAxis->setRange(0, 10);
    ui->widget_qcp->replot();
}

void MainWindow::updatePlot(double value)
{
    int index = value * nBins / (tMax - tMin);
    qDebug() << QString::number(value) << "  index: " << QString::number(index);
    if (index >= nBins || index < 0) return;

    y[index]++;
    if (y[index] > maxOfEntries) maxOfEntries = y[index];
    bars->clearData();
    bars->setData(x, y);
    ui->widget_qcp->yAxis->setRange(0, 10 + 1.3*maxOfEntries);
    ui->widget_qcp->replot();
}

void MainWindow::on_pushButton_stop_run_clicked()
{
    if (running) stopRun = true;
    else stopRun = false;
}

void MainWindow::on_pushButton_clear_bars_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Clear data", "Are you sure you want to clear the data ?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        adjustPlot();
    }
    else {
        qDebug() << "Yes was *not* clicked";
        return;
    }
}

