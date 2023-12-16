/*
c++ -o RintVolt ResIntVolt.cpp `root-config --glibs --cflags`  statistiche_vector.cc
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

using namespace std;

void stampa( vector<double> & v) {

	for( int i = 0; i < v.size(); i ++) {
		
		cout << v[i] << endl;
	
	}

}

int main (int argc, char ** argv) {

    if (argc < 2)
      {
        cout << "usage: " << argv[0] << " DatiVoltmetro.txt " << endl ;
        exit (1) ;
      }

   	string nome_file = argv[1];
	
    TGraphErrors g("DatiVoltmetro.txt");
    
    TF1 f_fit ( "f_fit", "pol1(0)", 0.16, 1.3); //p0 = intercetta; p1 = Rm
    f_fit.SetParameter(0, 0.);
    f_fit.SetParameter(1, 0.804); //resistenza in MOhm
	TFitResultPtr fit_result = g.Fit (&f_fit, "S") ;
	if ( fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
	else cout << "Fit fallito" << endl;
	
	//R misurata con il fit
	double Rm = f_fit.GetParameter(1);
	double e_Rm = f_fit.GetParError(1);
	cout << "Resistenza misurata = " << Rm << " +- " << e_Rm << endl;
	
	// Calcolo resistenza R utilizzata
	/*vector<double> Resistenze;
	ifstream f_dati;
	f_dati.open("RVolt.txt");
	while(true) {
	
   		double x_temp;
   		f_dati >> x_temp;   		
   		if(f_dati.eof() == true ) break;
   		Resistenze.push_back(x_temp);
   		  	
	
	}
	double R = calcMedia(Resistenze);
	double e_R = calcDevStdMedia(Resistenze);
	double Rvolt = R * Rm / (R - Rm);
	cout << "Risultato = " << Rvolt << endl;
	cout << "R calcolata da noi = " << R << endl; */
    double Rv = (Rm * 0.89) / (0.89 - Rm);
    cout << "Resistenza Voltmetro = " << Rv << "" << endl;
    
    TCanvas c1;
    c1.SetGrid();
	gStyle->SetOptFit(kTRUE);
    gStyle->SetStatX(0.5);
    gStyle->SetStatY(0.9);
    gStyle->SetStatW(0.2);
    gStyle->SetStatH(0.15);
    g.GetHistogram()->GetXaxis()->SetTitle("Corrente [uA]");
    g.GetHistogram()->GetYaxis()->SetTitle("Tensione [V]");
    g.GetHistogram()->SetTitle("Resistenza interna del voltmetro");
    g.SetMarkerStyle(20);
    g.SetMarkerSize(0.8);
    g.SetLineColor(kRed + 1);
    g.Draw ("AP") ;

   c1.Print ("GraficoRintVolt.png", "png") ;

    return 0 ;
  }

