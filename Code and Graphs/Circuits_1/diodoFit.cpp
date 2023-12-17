/*
c++ -o diodoFit diodoFit.cpp `root-config --glibs --cflags`
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


int main (int argc, char ** argv) {   
	
    TGraphErrors g( "diodoRetta.txt" );
      
    TF1 f_fit ( "f_fit", "pol1(0)", 0.83, 0.90);
    //f_fit.SetParameter(0); //intercetta
    //f_fit.SetParameter(1); //resistenza in Ohm
	TFitResultPtr fit_result = g.Fit (&f_fit, "S") ;
	if ( fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
	else cout << "Fit fallito" << endl;
    double a = f_fit.GetParameter(1);
    double b = f_fit.GetParameter(0);
    double intercetta = -1. * f_fit.GetParameter(0) / f_fit.GetParameter(1);
    double v_a = fit_result->CovMatrix(1,1);
    double v_b = fit_result->CovMatrix(0,0);
    double v_ab = fit_result->CovMatrix(0,1);
    double v_intercetta = 1./(a*a*a*a) * (b*b*v_a - 2*a*b*v_ab + a*a*v_b);
    cout << "V soglia = " << intercetta << " +- " << v_intercetta << endl;
    TCanvas c1;
    c1.SetGrid();
    gStyle->SetOptFit(kTRUE);
    gStyle->SetStatX(0.5);
    gStyle->SetStatY(0.9);
    gStyle->SetStatW(0.2);
    gStyle->SetStatH(0.15);

    g.GetHistogram()->GetXaxis()->SetTitle("Tensione [V]");
    g.GetHistogram()->GetYaxis()->SetTitle("Corrente [mA]");
    g.GetHistogram()->SetTitle("Caratteristica Diodo");
    g.SetLineColor(kRed + 1);
    g.SetMarkerStyle(20);
    g.SetMarkerSize(0.8);
    g.Draw ("AP") ;

   c1.Print ("GraficoDiodoRetta.png", "png") ;



    return 0 ;
  }

