/*
c++ -o RintAmp ResIntAmp.cpp `root-config --glibs --cflags`
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
#include "TStyle.h"


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

    if (argc < 2)
      {
        cout << "usage: " << argv[0] << " DatiAmperometro.txt " << endl ;
        exit (1) ;
      }
	
   	vector<double> V; //Volt
   	vector<double> I; //mA
	vector<double> V_err;
   	vector<double> I_err;
	leggi_file(argv[1], V, I, V_err, I_err);
	
    TGraphErrors g( "DatiAmperometro.txt" );
    
    
    TF1 f_fit ( "f_fit", "pol1(0)", 0.2, 1.3);
    f_fit.SetParameter(0, 0.); //intercetta
    f_fit.SetParameter(1, 13); //resistenza in Ohm
	TFitResultPtr fit_result = g.Fit (&f_fit, "S") ;
	if ( fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
	else cout << "Fit fallito" << endl;

	//R misurata con il fit
	double Rm = f_fit.GetParameter(1) * 1000;
	double e_Rm = f_fit.GetParError(1) * 1000;
	cout << "Resistenza misurata = " << Rm << " +- " << e_Rm << endl;
    double errore = sqrt(e_Rm * e_Rm + 0.05 *0.05* 11. *11.);
	double Ramp = Rm - 11.;
	cout << "Resistenza interna amperometro: " << Ramp << " +- " << errore << endl;

    TCanvas c1;
    c1.SetGrid();
    //g.GetHistogram()->SetMinimum(-0.1);
    gStyle->SetOptFit(kTRUE);
    gStyle->SetStatX(0.5);
    gStyle->SetStatY(0.9);
    gStyle->SetStatW(0.2);
    gStyle->SetStatH(0.15);
    g.GetHistogram()->GetXaxis()->SetTitle("Corrente [mA]");
    g.GetHistogram()->GetYaxis()->SetTitle("Tensione [V]");
    g.GetHistogram()->SetTitle("Resistenza interna amperometro");
    g.SetLineColor(kRed + 1);
    g.SetMarkerStyle(20);
    g.SetMarkerSize(0.8);
    g.Draw ("AP") ;

   c1.Print ("GraficoRintAmp.png", "png") ;
    
    vector<double> z;

    return 0 ;
  }

