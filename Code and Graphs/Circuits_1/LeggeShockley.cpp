/*
c++ -o leggeShockley leggeShockley.cpp `root-config --glibs --cflags`
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

double Shockley(double * x, double * par) {

    double a = 38.6;
    double y = par[0]*(exp(a*x[0]/par[1])-1.);
    return y;

}

int main (int argc, char ** argv) {   
	
    TGraphErrors g( "DatiDiodo.txt" );
    
    
    TF1 f_fit1 ( "f_fit1", Shockley, 0, 0.8, 2);
    f_fit1.SetParameter(0,pow(10,-5)); //I0
    f_fit1.SetParameter(1,2.); //g
    TFitResultPtr fit_result1 = g.Fit (&f_fit1, "SQ", "", 0, 0.8);
	if ( fit_result1->IsValid() ) cout << "Fit avvenuto con successo" << endl;
	else cout << "Fit fallito" << endl;
    double gPar = f_fit1.GetParameter(1);
    double I0 = f_fit1.GetParameter(0);
    cout << "g = " << gPar << " +- " << f_fit1.GetParError(1) << endl;
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

    c1.Print ("DiodoShockley1.png", "png") ;
    
    TF1 f_fit ( "f_fit", Shockley, 0, 0.89, 2);
    f_fit.SetParameter(0,pow(10,-5)); //I0
    f_fit.SetParameter(1,2.); //g
    TFitResultPtr fit_result = g.Fit (&f_fit, "SQ", "", 0, 0.89);
    if ( fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;
    gPar = f_fit.GetParameter(1);
    I0 = f_fit.GetParameter(0);
    cout << "g = " << gPar << " +- " << f_fit.GetParError(1) << endl;

    g.Draw ("AP") ;

    c1.Print ("DiodoShockleyCompleto.png", "png") ;

    /*TF1 f_retta ( "f_retta", "pol1(0)", 0.82, 0.90);
    f_retta.SetParameter(0, -7800);// intercetta
    f_retta.SetParameter(1, 9758); //coeff angolare
	TFitResultPtr fit_result1 = g.Fit (&f_retta, "S", "", 0.82, 0.90) ;
	if ( fit_result1->IsValid() ) cout << "Fit avvenuto con successo" << endl;
	else cout << "Fit fallito" << endl;
    g.Draw("AP");
    c1.Print("prova2.png");
    double a = f_retta.GetParameter(1);
    double b = f_retta.GetParameter(0);
    double intercetta = -1. * f_retta.GetParameter(0) / f_retta.GetParameter(1);
    double v_a = fit_result1->CovMatrix(1,1);
    double v_b = fit_result1->CovMatrix(0,0);
    double v_ab = fit_result1->CovMatrix(0,1);
    double v_intercetta = 1./(a*a*a*a) * (b*b*v_a - 2*a*b*v_ab + a*a*v_b) *1000;
    cout << "V soglia = " << intercetta << " +- " << sqrt(v_intercetta) << endl; */
    return 0 ;
  }

