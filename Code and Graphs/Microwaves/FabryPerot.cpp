/*
c++ -o FabryPerot `root-config --glibs --cflags` FabryPerot.cpp
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>

#include "TH1F.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"

#include "TF1.h"
#include "TFitResult.h"
#include "TStyle.h"

using namespace std;

double parabola(double * x, double * par){

    return par[0]*(x[0]-par[1])*(x[0]-par[1])+par[2];
}

int main(int argc, char const *argv[])
{
    TGraphErrors* v = new TGraphErrors("FabryPerot.txt");
    TCanvas* g = new TCanvas();

    TF1 m1_fit("m1_fit", parabola, 211.,21.42, 3);
    m1_fit.SetParameter(0, -1000);
    m1_fit.SetParameter(1, 21.3);
    m1_fit.SetParameter(2, 900);
    m1_fit.SetParName(0, "b");
    m1_fit.SetParName(1, "d_{max1}");
    m1_fit.SetParName(2, "y_{max1}");
    TFitResultPtr m1_fit_result = v->Fit(&m1_fit, "S", "", 21.1,21.42);
    if ( m1_fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;

    TF1 m2_fit("m2_fit", parabola, 22.3,22.72, 3);
    m2_fit.SetParameter(0, -1000);
    m2_fit.SetParameter(1, 22.5);
    m2_fit.SetParameter(2, 900);
    m2_fit.SetParName(0, "b");
    m2_fit.SetParName(1, "d_{max2}");
    m2_fit.SetParName(2, "y_{max2}");
    TFitResultPtr m2_fit_result = v->Fit(&m2_fit, "S", "", 22.3,22.72);
    if ( m2_fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;

    TF1 m3_fit("m3_fit", parabola, 23.7,24.1, 3);
    m3_fit.SetParameter(0, -1000);
    m3_fit.SetParameter(1, 23.9);
    m3_fit.SetParameter(2, 900);
    m3_fit.SetParName(0, "b");
    m3_fit.SetParName(1, "d_{max3}");
    m3_fit.SetParName(2, "y_{max3}");
    TFitResultPtr m3_fit_result = v->Fit(&m3_fit, "S", "", 23.7,24.1);
    if ( m3_fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;

    gStyle->SetOptFit(kTRUE);
    gStyle->SetStatY(0.32);
    gStyle->SetStatX(0.47);
    gStyle->SetStatH(0.14);

    v->SetMarkerStyle(20);
    v->SetMarkerColor(kAzure +1);
    v->SetMarkerSize(1);
    v->GetHistogram()->GetXaxis()->SetTitle("d (cm)");
    v->GetHistogram()->GetYaxis()->SetTitle("Tensioni (mV)");
    v->GetHistogram()->SetTitle("Ampiezza del segnale");
    v->Draw ("AP");

    g->SetGrid();
    g->Print ("FabryPerot.png", "png"); 

    double m1 = m1_fit.GetParameter(1);
    double sigma1 = m1_fit.GetParError(1);
    double m2 = m2_fit.GetParameter(1);
    double sigma2 = m2_fit.GetParError(1);
    double m3 = m3_fit.GetParameter(1);
    double sigma3 = m3_fit.GetParError(1);


    double lambdah = 2*(m2 - m1);
    double sigmah = sqrt(pow(sigma1, 2)+ pow(sigma2, 2));
    cout << "lambda stimato tra i primi due massimi" << lambdah << "+-" << sigmah << endl;

    double lambdak = (m3 - m1);
    double sigmak = sqrt(pow(sigma1, 2)+ pow(sigma3, 2));
    cout << "lambda stimato tra il primo massimo e il terzo" << lambdak << "+-" << sigmak << endl;

    double lambdat = 2*(m3 - m2);
    double sigmat = sqrt(pow(sigma3, 2)+ pow(sigma2, 2));
    cout << "lambda stimato tra gli ultimi due massimi" << lambdat << "+-" << sigmat << endl;   

    double t_TEST_1 = (2.85-lambdak)/sigmak;
    cout << "t-TEST con 2.85 per tutti i massimi:" << t_TEST_1 << endl;

    double t_TEST_2 = (2.85-lambdat)/sigmat;
    cout << "t-TEST con 2.85 per solo gli ultimi due:" << t_TEST_2 << endl;

    

    delete g;
    delete v;
    return 0;
}
