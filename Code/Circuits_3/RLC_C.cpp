
/*
c++ -o RLC_C RLC_C.cpp `root-config --glibs --cflags`
*/

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TStyle.h"

using namespace std ;

double VCmodulo(double * x, double * par) {
    
    return par[0] / ( x[0]*sqrt( 1 + pow(x[0]*par[1]-par[0]/x[0], 2) ) );
    
}

double VCfase(double * x, double * par) {
    
    return +3.14159/2 + atan( (x[0]*par[2] - 1. / (x[0]*par[1]))/par[0] );
    
}

int main (int argc, char ** argv) {
    
    TCanvas c1;
    c1.SetGrid();
    gStyle->SetOptFit(kTRUE);
    gStyle->SetStatW(0.20);
    gStyle->SetStatH(0.20);
    gStyle->SetStatY(0.85);
    gStyle->SetStatX(0.50);
    double R = 2660;
    double C = 47e-9;

    // --- Modulo V_C ---
    
    TGraphErrors g( "datiRLCmoduloVC.txt" );
    
    TF1 f_fit ( "f_fit", VCmodulo, 60, 1320000, 2);
    f_fit.SetParName(0, "RC");
    f_fit.SetParName(1, "R/L");
    //f_fit.SetParName(2, "L");
    f_fit.SetParameter(0, 1./(R*C));
    f_fit.SetParameter(1, R*1000./75.);
    //f_fit.SetParameter(2, 0.001);
    
    TFitResultPtr fit_result = g.Fit (&f_fit, "SQ") ;
    if ( fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;

    c1.SetLogx();
    g.GetHistogram()->GetXaxis()->SetTitle("#omega (rad/s)");
    g.GetHistogram()->GetYaxis()->SetTitle("|H(#omega)|");
    g.GetHistogram()->SetTitle("Modulo della funzione di trasferimento per V_C");
    g.SetLineColor(kRed + 1);
    g.SetMarkerStyle(20);
    g.SetMarkerSize(0.8);
    g.SetMarkerColor(kBlack);
    g.Draw ("AP") ;

    c1.Print ("RLCModuloVC.png", "png") ;
    
    // --- Fase V_C ---
    
    /*TGraphErrors gFaseVc( "datiRLCFaseVC.txt" );
    c1.SetLogx();
    TF1 fit_fase_VC ( "fit_fase_VC", VCfase, 60, 880000, 3);
    fit_fase_VC.SetParName(0, "R");
    fit_fase_VC.SetParName(1, "C");
    fit_fase_VC.SetParName(2, "L");
    fit_fase_VC.SetParameter(0, R);
    fit_fase_VC.SetParameter(1, C);
    fit_fase_VC.SetParameter(2, 0.01);
    TFitResultPtr fit_result2 = gFaseVc.Fit (&fit_fase_VC, "SQ") ;
    if ( fit_result2->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;

    
    gFaseVc.GetHistogram()->GetXaxis()->SetTitle("#omega (rad/s)");
    gFaseVc.GetHistogram()->GetYaxis()->SetTitle("#phi (rad)");
    gFaseVc.GetHistogram()->SetTitle("Fase della funzione di trasferimento V_C");
    gFaseVc.SetLineColor(kRed + 1);
    gFaseVc.SetMarkerStyle(20);
    gFaseVc.SetMarkerSize(0.8);
    gFaseVc.SetMarkerColor(kBlack);
    gFaseVc.Draw ("AP") ;

    c1.Print ("RLCFaseVC.png", "png") ; */
    
    return 0 ;
  }







