
/*
c++ -o forma forma.cpp `root-config --glibs --cflags`
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

double unoSuR(double * x, double * par) {
    
    return -par[0]*sin(x[0]+par[2]) + par[1]/x[0];
    
}

int main (int argc, char ** argv) {
    
    TCanvas c1;
    c1.SetGrid();
    gStyle->SetOptFit(kTRUE);
    gStyle->SetStatW(0.20);
    gStyle->SetStatH(0.17);
    //gStyle->SetStatY(0.35);
    //gStyle->SetStatX(0.40);


    // --- Modulo V_R ---
    
    TGraphErrors g( "datiForma.txt" );
    
    TF1 f_fit ( "f_fit", unoSuR, 32, 82, 3);
    //f_fit.SetParName(0, "(RC)^2");
    //f_fit.SetParameter(0, 1000);
    TFitResultPtr fit_result = g.Fit (&f_fit, "SQ") ;
    if ( fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;

    g.GetHistogram()->GetXaxis()->SetTitle("R");
    g.GetHistogram()->GetYaxis()->SetTitle("Segnale");
    g.GetHistogram()->SetTitle("Segnale, ipotesi 1/R");
    g.SetLineColor(kRed + 1);
    g.SetMarkerStyle(20);
    g.SetMarkerSize(0.8);
    g.SetMarkerColor(kBlack);
    g.Draw ("AP") ;

    c1.Print ("formaUnoSuR.png", "png") ;
    
    // --- Fase V_R ---
    
    /*TGraphErrors gFaseVr( "datiRCFaseVR.txt" );
    
    TF1 fit_fase_VR ( "fit_fase_VR", VRfase, 30, 3200, 1);
    fit_fase_VR.SetParName(0, "RC");
    fit_fase_VR.SetParameter(0, R*C);
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

    c1.Print ("RCFaseVR_outlier.png", "png") ; */
    

    
    return 0 ;
  }






