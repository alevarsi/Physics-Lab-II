/*
c++ -o circuitoRLC circuitoRLC.cpp `root-config --glibs --cflags`
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

double f_sovra(double * x, double * par) {
    
    return par[0]*exp(-1. * x[0]*par[1]/1000.) * ( exp(par[2]/1000.*x[0]) - exp(-1.*par[2]/1000.*x[0]));
    
}

double f_sotto(double * x, double * par) {
    
    return par[0]*exp(-1. * par[1]/1000. * x[0])*sin(par[2]/1000.*x[0]);
    
}

double f_critico(double * x, double * par) {
    
    return par[0]*x[0]*exp(-1. * par[1]*x[0]);
    
}

int main (int argc, char ** argv) {
    
   // --- SOVRASMORZATO ---
    
    /*TGraphErrors g( "SmorzCritico.txt" );
    
    TF1 f_fit ( "f_fit", f_sovra, 24, 272, 3);
    f_fit.SetParName(0, "Amp");
    f_fit.SetParName(1, "#gamma");
    f_fit.SetParName(2, "#beta");
    f_fit.SetParameter(0, 8); //R*I_0
    f_fit.SetParameter(1, 50.2); //gamma
    f_fit.SetParameter(2, 46);
    TFitResultPtr fit_result = g.Fit (&f_fit, "SQ") ;
    if ( fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;
    TCanvas c1;
    c1.SetGrid();
    gStyle->SetOptFit(kTRUE);
    gStyle->SetStatW(0.2);
    gStyle->SetStatH(0.15);
    gStyle->SetStatY(0.9);
    gStyle->SetStatX(0.9);
    
    g.GetHistogram()->GetXaxis()->SetTitle("Tempo [us]");
    g.GetHistogram()->GetYaxis()->SetTitle("Tensione [V]");
    g.GetHistogram()->SetTitle("Tensione ai capi della resistenza");
    g.SetLineColor(kRed + 1);
    g.SetMarkerStyle(20);
    g.SetMarkerSize(0.8);
    g.SetMarkerColor(kBlack);
    g.Draw ("AP") ;

    c1.Print ("V_R_SovraCritico.png", "png") ;
    
    // --- ANALISI DATI ---
    
    double L = 11.94e-3;
    double R = 790;
    
    double gamma = f_fit.GetParameter(1) * 1000;
    double e_gamma = f_fit.GetParError(1) * 1000;
    
    double e_gamma_atteso = sqrt( (1./(4*L*L)) * (1*1 + (R*R*0.03e-3*0.03e-3)/(L*L)) );
    double gamma_atteso = R / (2*L);
    
    cout << "Gamma atteso = " << gamma_atteso << " +- " << e_gamma_atteso << endl;
    cout << "Gamma fit = " << gamma << " +- " << e_gamma << endl;
    
    double t = (gamma_atteso - gamma) / sqrt(e_gamma*e_gamma + e_gamma_atteso*e_gamma_atteso);
    
    cout << "T - test: " << t << endl; */

    // --- SOTTOSMORZATO ---
    TCanvas c1;
    c1.SetGrid();
    gStyle->SetOptFit(kTRUE);
    gStyle->SetStatW(0.2);
    gStyle->SetStatH(0.15);
    gStyle->SetStatY(0.9);
    gStyle->SetStatX(0.9);
    
    TGraphErrors sotto ("VrSottosmorzato.txt");
    TF1 fit_sotto ( "fit_sotto", f_sotto, 0, 1200, 3);
    fit_sotto.SetParName(0, "Amp");
    fit_sotto.SetParName(1, "#gamma");
    fit_sotto.SetParName(2, "#beta");
    
    fit_sotto.SetParameter(0, 80); //ampiezza
    fit_sotto.SetParameter(2, 35);
    fit_sotto.SetParameter(1, 01); //gamma
    TFitResultPtr fit_result1 = sotto.Fit (&fit_sotto, "SQ") ;
    if ( fit_result1->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;
    //double gamma = f_fit.GetParameter(1); //
    sotto.GetHistogram()->GetXaxis()->SetTitle("Tempo [#mus]");
    sotto.GetHistogram()->GetYaxis()->SetTitle("Tensione [mV]");
    //sotto.GetHistogram()->SetTitle("Tensione ai capi della resistenza (regime sottosmorzato)");
    sotto.SetLineColor(kRed + 1);
    sotto.SetMarkerStyle(20);
    sotto.SetMarkerSize(0.7);
    sotto.SetMarkerColor(kBlack);
    sotto.Draw("AP");
    c1.Print("SottoNoMassimi.png", "png");
    
    double gamma = fit_sotto.GetParameter(1); //in
    
    // --- SMORZAMENTO CRITICO  ---

    /*TGraphErrors critico ("SmorzCritico.txt");
    TF1 fit_critico ( "fit_critico", f_sovra, 0, 271, 3);
    fit_critico.SetParName(0, "Amp");
    fit_critico.SetParName(1, "#gamma");
    fit_critico.SetParameter(0, 10); //ampiezza
    fit_critico.SetParameter(1, 35); //gamma
    fit_critico.SetParameter(2, 17);
    TFitResultPtr fit_result2 = critico.Fit (&fit_critico, "SQ") ;
    if ( fit_result2->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;
    //double gamma = f_fit.GetParameter(1); //
    critico.GetHistogram()->GetXaxis()->SetTitle("Tempo [#mus]");
    critico.GetHistogram()->GetYaxis()->SetTitle("Tensione [V]");
    critico.GetHistogram()->SetTitle("Tensione ai capi della resistenza (smorzamento critico)");
    critico.SetLineColor(kRed + 1);
    critico.SetMarkerStyle(20);
    critico.SetMarkerSize(0.7);
    critico.SetMarkerColor(kBlack);
    critico.Draw("AP");
    c1.Print("V_R_Critico.png", "png"); */
    
    return 0 ;
  }




