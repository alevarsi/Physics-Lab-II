/*
c++ -o doppiaFenditura `root-config --glibs --cflags` doppiaFenditura.cpp
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

    return par[1]*pow(sin(par[0]*x[0])/(par[0]*x[0]) ,2);
}

int main(int argc, char const *argv[])
{
    TGraphErrors* v = new TGraphErrors("Young.txt");
    TCanvas* g = new TCanvas();
    
    TF1 m1_fit("m1_fit", parabola, -3.,3., 2);
    m1_fit.SetParameter(1, 450);
    m1_fit.SetParameter(0, 10);
    m1_fit.SetParName(0, "k");
    TFitResultPtr m1_fit_result = v->Fit(&m1_fit, "S");
    if ( m1_fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;


    gStyle->SetOptFit(kTRUE);
    /*gStyle->SetStatY(0.7);
    gStyle->SetStatX(0.47);
    gStyle->SetStatH(0.14);
*/
    v->SetMarkerStyle(20);
    v->SetMarkerColor(kAzure +1);
    v->SetMarkerSize(1);
    v->GetHistogram()->GetXaxis()->SetTitle("Angolo");
    v->GetHistogram()->GetYaxis()->SetTitle("Segnale");
    v->GetHistogram()->SetTitle("Ampiezza del segnale");
    v->Draw ("AP");

    g->SetGrid();
    g->Print ("doppiaFenditura.png", "png");

    delete g;
    delete v;
    return 0;
}

