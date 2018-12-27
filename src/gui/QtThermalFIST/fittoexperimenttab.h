/*
 * Thermal-FIST package
 * 
 * Copyright (c) 2014-2018 Volodymyr Vovchenko
 *
 * GNU General Public License (GPLv3 or later)
 */
#ifndef FITTOEXPERIMENTTAB_H
#define FITTOEXPERIMENTTAB_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QTableWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QRadioButton>
#include <QTextEdit>
#include <QElapsedTimer>
#include <QThread>

#include "BaseStructures.h"
#include "HRGBase/ThermalModelBase.h"
#include "HRGFit/ThermalModelFit.h"

class FitWorker : public QThread
{
    Q_OBJECT

    thermalfist::ThermalModelFit *fTHMFit;

    void run() Q_DECL_OVERRIDE;

public:
    FitWorker(
           thermalfist::ThermalModelFit *THMFit=NULL,
           QObject * parent = 0) :
        QThread(parent), fTHMFit(THMFit)
    {
    }
signals:
    void calculated();
};


class QuantitiesModel;
class QElapsedTimer;

class FitToExperimentTab : public QWidget
{
    Q_OBJECT

    QTableView *tableQuantities;
    QPushButton *buttonAddQuantity, *buttonRemoveQuantity;
    QPushButton *buttonLoadFromFile;
    QTableWidget *tableParameters;
    QLabel *labelHint;

		QRadioButton *radIdeal, *radEVD, *radEVCRS, *radQVDW;
		QRadioButton *radGCE, *radCE, *radSCE;

		QRadioButton *radioBoltz, *radioQuant;
		QCheckBox *CBBoseOnly, *CBPionsOnly;
		QCheckBox *CBQuadratures;

    QPushButton *buttonResults;
    QPushButton *buttonChi2Map;
		QPushButton *buttonChi2Profile;
		QPushButton *labelValid;

    QDoubleSpinBox *spinTemperature, *spinmuB, *spingammaq, *spingammaS, *spinVolumeR;
    QCheckBox *CBTemperature, *CBmuB, *CBgammaq, *CBgammaS, *CBVolumeR;
    QDoubleSpinBox *spinTmin, *spinTmax;
    QDoubleSpinBox *spinmuBmin, *spinmuBmax;
    QDoubleSpinBox *spingqmin, *spingqmax;
    QDoubleSpinBox *spingsmin, *spingsmax;
    QDoubleSpinBox *spinVRmin, *spinVRmax;
    QSpinBox *spinB, *spinS, *spinQ;
    QDoubleSpinBox *spinQBRatio;
    QDoubleSpinBox *spinRadius;

		QCheckBox *checkFixMuQ, *checkFixMuS, *checkFixMuC;

		QComboBox *comboWidth;

    QCheckBox *checkBratio;
	QCheckBox *checkFitRc;

    QCheckBox *checkOMP;

    QRadioButton *radioUniform, *radioBaglike, *radioMesons, *radioCustomEV;
		QString strEVPath;

    QPushButton *buttonCalculate;

    thermalfist::ThermalParticleSystem *TPS;
    thermalfist::ThermalModelBase *model;
    thermalfist::ThermalModelFit *fitcopy;

    ThermalModelConfig lastconfig;

    QTextEdit *teDebug;

    QuantitiesModel *myModel;

    QElapsedTimer timer;
    QTimer *calcTimer;

		QString cpath;

    int getCurrentRow();

    std::vector<thermalfist::FittedQuantity> quantities;

public:
    FitToExperimentTab(QWidget *parent = 0, thermalfist::ThermalModelBase *model = NULL);
    ~FitToExperimentTab();
		ThermalModelConfig getConfig();
    thermalfist::ThermalModelFitParameters getFitParameters();
    thermalfist::ThermalModelFit* Fit() const { return fitcopy; }
    ThermalModelConfig LastUsedConfig() const { return lastconfig; }
signals:

private slots:
    void writetofile();
    void showValidityCheckLog();

public slots:
    void changedRow();
		void performFit(const ThermalModelConfig & config, const thermalfist::ThermalModelFitParameters & params);
    void calculate();
    void quantityDoubleClick(const QModelIndex &);
    void showResults();
    void showChi2Map();
		void showChi2Profile();
    void setModel(thermalfist::ThermalModelBase *model);
    void removeQuantityFromFit();
    void addQuantity();
    void loadFromFile();
		void loadEVFromFile();
		void saveToFile();
    void modelChanged();
    void resetTPS();
    void updateProgress();
    void finalize();
    void updateFontSizes();
};

#endif // FITTOEXPERIMENTTAB_H
