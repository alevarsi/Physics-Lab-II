/*
c++ -o leggeOhm leggeOhm.cpp `root-config --glibs --cflags` statistiche_vector.cc
*/

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>

#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFitResult.h"

#include "statistiche_vector.h"

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

int main (int argc, char ** argv) {
    
    vector<double> x;
    vector<double> e_x;
    vector<double> y;
    vector<double> e_y;
    vector<double> z;
    leggi_file( argv[1], x, e_x, y, e_y);
    
    TGraphErrors g( "LeggeOhm.txt" );
    
    TF1 f_fit ( "f_fit", "pol1(0)", 8., 17.1);
    f_fit.SetParameter(0, 0.); //intercetta
    f_fit.SetParameter(1, 0.57); //resistenza in Ohm
	TFitResultPtr fit_result = g.Fit (&f_fit, "S") ;
	if ( fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
	else cout << "Fit fallito" << endl;
    double b = f_fit.GetParameter(0);
	//R misurata con il fit
	double Rm = f_fit.GetParameter(1);
	double e_Rm = f_fit.GetParError(1);
	cout << "Resistenza misurata = " << Rm << " +- " << e_Rm << " MOhm" << endl;
	
    TCanvas c1;
    
    g.GetHistogram()->GetXaxis()->SetTitle("Corrente [uA]");
    g.GetHistogram()->GetYaxis()->SetTitle("Tensione [V]");
    g.GetHistogram()->SetTitle("Tensione vs Corrente");
    g.SetLineColor(kRed + 1);
    g.SetMarkerStyle(4);
    g.SetMarkerColor(kBlack);
    g.Draw ("AP") ;

    c1.Print ("LeggeDiOhm.png", "png") ;

    for( int i = 0; i < x.size(); i++) {
        
        z.push_back( y.at(i) / (b + Rm * x.at(i)) );
        
    }
    TF1 f_orizzontale ( "f_orizzontale", "pol0(0)", 8., 17.1);
    TGraphErrors errori(z.size(), &x[0], &z[0], &e_x[0], &e_y[0]);
    TFitResultPtr fit2_result = errori.Fit (&f_orizzontale, "S") ;
    
    errori.SetMarkerStyle(8);
    errori.SetMarkerColor(kRed);

    errori.Draw("AP");
    c1.Print("errori.png", "png");
    return 0 ;
  }

