
/*
c++ -o LeggeCauchy LeggeCauchy.cpp `root-config --glibs --cflags`
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
#include "TMatrixDSym.h"

using namespace std ;

double cauchy(double * x, double * par){
    
    return par[0] + par[1]/( x[0] * x[0] );
    
}

int main (int argc, char ** argv) {
    
    TCanvas c1;
    c1.SetGrid();
    gStyle->SetOptFit(kTRUE);
    gStyle->SetStatW(0.21);
    gStyle->SetStatH(0.18);
    gStyle->SetStatY(0.84);
    gStyle->SetStatX(0.87);

    TGraphErrors g( "DatiCauchy.txt" );
    
    TF1 f_fit ( "f_fit", cauchy, 400, 600, 2);
    f_fit.SetParName(0, "A");
    f_fit.SetParName(1, "B");
    //f_fit.SetParameter(0, 1000);
    TFitResultPtr fit_result = g.Fit (&f_fit, "SQ") ;
    if ( fit_result->IsValid() ) cout << "Fit avvenuto con successo" << endl;
    else cout << "Fit fallito" << endl;

    g.GetHistogram()->GetXaxis()->SetTitle("#lambda [nm]");
    g.GetHistogram()->GetYaxis()->SetTitle("n(#lambda)");
    g.GetHistogram()->SetTitle("Legge di Cauchy");
    g.SetLineColor(kRed + 1);
    g.SetMarkerStyle(20);
    g.SetMarkerSize(0.8);
    g.SetMarkerColor(kBlack);
    g.Draw ("AP") ;

    c1.Print ("LeggeCauchy.png", "png") ;
    
    TMatrixDSym cov = fit_result->GetCovarianceMatrix () ;

    cout << "Covarianza = " << cov(1,0) << "\t" ;


    
    return 0 ;
  }







