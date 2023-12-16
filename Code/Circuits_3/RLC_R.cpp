
/*
c++ -o RLC_R RLC_R.cpp `root-config --glibs --cflags`
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

double VRmodulo(double * x, double * par) {
    
    return 1. / ( sqrt( 1 + 1/(par[0]*par[0]) * pow((x[0]*par[2] - 1. / (x[0]*par[1])),2) ));
    
}

double VRfase(double * x, double * par) {
    
    return atan( (x[0]*par[2] - 1. / (x[0]*par[1]))/par[0] );
    
}

int main (int argc, char ** argv) {
    
    TCanvas c1;
    c1.SetGrid();
    /*gStyle->SetOptFit(kTRUE);
    gStyle->SetStatW(0.19);
    gStyle->SetStatH(0.18);
    gStyle->SetStatY(0.86);
    gStyle->SetStatX(0.475); */
    double R = 2660;
    double C = 47e-9;

    // --- Modulo V_R ---
    
    TGraphErrors g( "datiRLCmoduloVR.txt" );
    
    TF1 f_fit ( "f_fit", VRmodulo, 60, 1320000, 3);
    f_fit.SetParName(0, "R");
    f_fit.SetParName(1, "C");
    f_fit.SetParName(2, "L");
    f_fit.SetParameter(0, R);
    f_fit.SetParameter(1, C);
    f_fit.SetParameter(2, 0.001);
    
    TFitResultPtr fit_result = g.Fit (&f_fit, "SQ") ;
    if ( fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;

    c1.SetLogx();
    g.GetHistogram()->GetXaxis()->SetTitle("#omega (rad/s)");
    g.GetHistogram()->GetYaxis()->SetTitle("|H(#omega)|");
    g.GetHistogram()->SetTitle("Modulo della funzione di trasferimento per V_R");
    g.SetLineColor(kRed + 1);
    g.SetMarkerStyle(20);
    g.SetMarkerSize(0.8);
    g.SetMarkerColor(kBlack);
    g.Draw ("AP") ;

    c1.Print ("RLCModuloVRnoBox.png", "png") ;
    
    // --- Fase V_R ---
    
    /*TGraphErrors gFaseVr( "datiRLCFaseVR.txt" );
    c1.SetLogx();
    TF1 fit_fase_VR ( "fit_fase_VR", VRfase, 60, 880000, 3);
    fit_fase_VR.SetParName(0, "R");
    fit_fase_VR.SetParName(1, "C");
    fit_fase_VR.SetParName(2, "L");
    fit_fase_VR.SetParameter(0, R);
    fit_fase_VR.SetParameter(1, C);
    fit_fase_VR.SetParameter(2, 0.01);
    TFitResultPtr fit_result2 = gFaseVr.Fit (&fit_fase_VR, "SQ") ;
    if ( fit_result2->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;

    
    gFaseVr.GetHistogram()->GetXaxis()->SetTitle("#omega (rad/s)");
    gFaseVr.GetHistogram()->GetYaxis()->SetTitle("#phi (rad)");
    gFaseVr.GetHistogram()->SetTitle("Fase della funzione di trasferimento");
    gFaseVr.SetLineColor(kRed + 1);
    gFaseVr.SetMarkerStyle(20);
    gFaseVr.SetMarkerSize(0.8);
    gFaseVr.SetMarkerColor(kBlack);
    gFaseVr.Draw ("AP") ;

    c1.Print ("RLCFaseVR.png", "png") ; */
    
    // --- Fase V_C ---
    
    /*TGraphErrors gFaseVc( "datiRCFaseVC.txt" );
    
    TF1 fit_fase_VC ( "fit_fase_VC", VCfase, 30, 3200, 1);
    fit_fase_VC.SetParName(0, "RC");
    fit_fase_VC.SetParameter(0, R*C);
    TFitResultPtr fit_result3 = gFaseVc.Fit (&fit_fase_VC, "SQ") ;
    if ( fit_result3->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;

    
    gFaseVc.GetHistogram()->GetXaxis()->SetTitle("Frequenza (#omega)");
    gFaseVc.GetHistogram()->GetYaxis()->SetTitle("#Delta #phi");
    gFaseVc.GetHistogram()->SetTitle("Fase della funzione di trasferimento di V_C");
    gFaseVc.SetLineColor(kRed + 1);
    gFaseVc.SetMarkerStyle(20);
    gFaseVc.SetMarkerSize(0.8);
    gFaseVc.SetMarkerColor(kBlack);
    gFaseVc.Draw ("AP") ;
    
    gStyle->SetStatY(0.8);
    gStyle->SetStatX(0.85);

    c1.Print ("RCFaseVC.png", "png") ; */
    
    // --- Modulo V_C ---
    
    /*TGraphErrors gC( "VCmoduloRC.txt");
    
    TF1 fit_VC ("fit_VC", VCmodulo, 30, 3200, 1);
    fit_VC.SetParName(0, "(RC)^2");
    fit_VC.SetParameter(0, R*R*C*C);
    TFitResultPtr fit_result1 = gC.Fit (&fit_VC, "SQ") ;
    if ( fit_result1->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;

    c1.SetLogx();
    gStyle->SetStatW(0.22);
    gStyle->SetStatH(0.20);
    gStyle->SetStatY(0.35);
    gStyle->SetStatX(0.55);
    gC.GetHistogram()->GetXaxis()->SetTitle("#omega (rad/s)");
    gC.GetHistogram()->GetYaxis()->SetTitle("|H(#omega)|");
    gC.GetHistogram()->SetTitle("Modulo della funzione di trasferimento (V_C)");
    gC.SetLineColor(kRed + 1);
    gC.SetMarkerStyle(20);
    gC.SetMarkerSize(0.8);
    gC.SetMarkerColor(kBlack);
    gC.Draw ("AP") ;

    c1.Print ("RCModuloVC.png", "png") ; */
    
    // --- ANALISI DATI ---
    
    /*double R = 67100;
    
    
    double e_gamma_atteso = sqrt( (1./(4*L*L)) * (1*1 + (R*R*0.03e-3*0.03e-3)/(L*L)) );
    double gamma_atteso = R / (2*L);
    
    cout << "Gamma atteso = " << gamma_atteso << " +- " << e_gamma_atteso << endl;
    cout << "Gamma fit = " << gamma << " +- " << e_gamma << endl;
    
    double t = (gamma_atteso - gamma) / sqrt(e_gamma*e_gamma + e_gamma_atteso*e_gamma_atteso);
    
    cout << "T - test: " << t << endl;

    fit_result->PrintCovMatrix (cout) ; */

    
    return 0 ;
  }






