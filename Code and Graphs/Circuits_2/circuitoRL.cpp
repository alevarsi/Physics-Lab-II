/*
c++ -o circuitoRL circuitoRL.cpp `root-config --glibs --cflags`
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

void leggi_file(char * nomefile, vector<double> & x, vector<double> & e_x, vector<double> & y, vector<double> & e_y) {
    
    ifstream f_input;
    f_input.open(nomefile);
    double dato_x;
    double errore_x;
    double dato_y;
    double errore_y;
    while(true) {
        

        f_input >> dato_x;
        f_input >> dato_y;
        f_input >> errore_x;
        f_input >> errore_y;
        if(f_input.eof()==true) break;
        x.push_back(dato_x);
        e_x.push_back(errore_x);
        y.push_back(dato_y);
        e_y.push_back(errore_y);
        
    }
    
    f_input.close();
    
}

double f_exp(double * x, double * par) {
    
    return par[0]*exp(-1. * x[0]/par[1]);
    
}

double f_exp_fissati(double * x, double * par){
    
    double Vg = 2850;
    return Vg*exp(-1. * x[0]/par[0]);
    
}

int main (int argc, char ** argv) {
    
    //leggi_file( argv[1], x, y, e_x, e_y);
    
    TGraphErrors g( "VrCircuitoRL.txt" );
    
    TF1 f_fit ( "f_fit", f_exp_fissati, 0, 8.25, 1);
    //f_fit.SetParameter(0, 1260); //V_0
    //f_fit.SetParameter(0, -10000);
    f_fit.SetParameter(0, 3); //tau
    //f_fit.SetParName(0, "K");
    f_fit.SetParName(0, "#tau");
    TFitResultPtr fit_result = g.Fit (&f_fit, "SQ") ;
    if ( fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;
    TCanvas c1;
    c1.SetGrid();
    gStyle->SetOptFit(kTRUE);
    gStyle->SetStatX(0.85);
    gStyle->SetStatY(0.85);
    gStyle->SetStatW(0.2);
    gStyle->SetStatH(0.15);
    
    g.GetHistogram()->GetXaxis()->SetTitle("Tempo [us]");
    g.GetHistogram()->GetYaxis()->SetTitle("Tensione [mV]");
    g.GetHistogram()->SetTitle("Tensione ai capi dell'induttanza");
    g.SetLineColor(kRed + 1);
    g.SetMarkerStyle(20);
    g.SetMarkerSize(0.8);
    g.SetMarkerColor(kBlack);
    g.Draw ("AP") ;

    c1.Print ("V_L2.png", "png") ;

    // --- ANALISI DATI ---
    
    double tau = f_fit.GetParameter(0); //microsecondi
    double e_tau = f_fit.GetParError(0);
    
    double R = 3.260; //kOhm
    double e_R = 0.001;
    
    double R_reale = R + 0.0405;
    double e_R_reale = sqrt( pow(0.001, 2) + pow(e_R, 2) );
    
    double L = tau * R; //mH
    double L_reale = tau * R_reale;
    double variazione = (L_reale - L) / L * 100;
    
    double e_L = sqrt( R*R*e_tau*e_tau + tau*tau*e_R_reale*e_R_reale);
    cout << "Induttanza reale = (" << L_reale << " +- " << e_L << ") mH" << endl;
    cout << "Induttanza = " << L << " mH" << endl;
    cout.precision(3);
    cout << "Variazione percentuale = " << variazione << " %" << endl;

    return 0 ;
  }



