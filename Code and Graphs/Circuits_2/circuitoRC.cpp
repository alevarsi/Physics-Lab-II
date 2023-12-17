/*
c++ -o circuitoRC circuitoRC.cpp `root-config --glibs --cflags`
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

double f_exp_fissati(double * x, double * par){
    
    double Vg = 1700;
    return Vg * ( 1 -2.*exp(-1.*x[0]/par[0]) );
    
}
int main (int argc, char ** argv) {
    
    vector<double> x;
    vector<double> e_x;
    vector<double> y;
    vector<double> e_y;
    vector<double> z;
    //leggi_file( argv[1], x, e_x, y, e_y);
    
    TGraphErrors g( "VcCircuitoRC.txt" );
    
    TF1 f_fit ( "f_fit", f_exp_fissati, 0, 800, 1);
   // f_fit.SetParName(0, "V0");
    f_fit.SetParName(0, "#tau");
    f_fit.SetParameter(0, 300); //tau in microsecondi
    TFitResultPtr fit_result = g.Fit (&f_fit, "S") ;
    if ( fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;
    double tau = f_fit.GetParameter(0);
    double R = 3.260; //kOhm
    double C = tau / R; //nF
    TCanvas c1;
    c1.SetGrid();
    c1.SetLeftMargin(0.12);
    gStyle->SetOptFit(kTRUE);
    gStyle->SetStatX(0.55);
    gStyle->SetStatY(0.9);
    gStyle->SetStatW(0.2);
    gStyle->SetStatH(0.15);
    
    g.GetHistogram()->GetXaxis()->SetTitle("Tempo [us]");
    g.GetHistogram()->GetYaxis()->SetTitle("Tensione [mV]");
    g.GetHistogram()->SetTitle("Tensione ai capi del condensatore");
    g.SetLineColor(kRed + 1);
    g.SetMarkerStyle(20);
    g.SetMarkerSize(0.8);
    g.SetMarkerColor(kBlack);
    g.Draw ("AP") ;

    c1.Print ("V_C.png", "png") ;

    /*for( int i = 0; i < x.size(); i++) {
        
        z.push_back( y.at(i) / (b + Rm * x.at(i)) );
        
    } */
    
    // --- PROPAGAZIONE ERORRI ---
    
    double e_tau = f_fit.GetParError(0);
    double e_R = 0.001;
    double e_C = 1./(R*R) * sqrt( (R*R)*(e_tau*e_tau) + (tau*tau)*(e_R*e_R) );
    cout << "Capacità = (" << C << " +- " << e_C << ") nF" << endl;
    
    double t = (98. - 97.1) / sqrt(e_C*e_C + 1) ;
    cout << "T  - test = " << t << endl;

    return 0 ;
  }


