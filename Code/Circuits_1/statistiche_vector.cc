#include "statistiche_vector.h"
#include <cmath>
#include <vector>

using namespace std ;

template <typename T> 
T ricercaMin(const vector<T> & data) {

	T min = data.at(0);
	for ( int i = 1; i < data.size(); i++ ) {
	
		if( data.at(i) < min ) min = data.at(i);
	
	}
	return min;

}
template <typename T> 
T ricercaMax(const vector<T> & data) {

	double max = data.at(0);
	for ( int i = 1; i < data.size(); i++ ) {
	
		if( data.at(i) > max ) max = data.at(i);
	
	}
	return max;

}

double calcMedia (const vector<double> & data) {

	double media = 0. ;
	for (int i = 0 ; i < data.size () ; ++i)  media += data.at (i) ;
	
	return media / data.size () ;
}

double calcVarianza (const vector<double> & data) {

	double media = 0. ;
	double mediaSq = 0. ;
	
	for (int i = 0 ; i < data.size () ; ++i) {
		media += data.at (i) ;
		mediaSq += data.at (i) * data.at (i) ;
    }  
    
	media /= data.size () ;  
	return data.size () * (mediaSq / data.size () - media * media) / (data.size () - 1) ;
}

double calcSigma (const vector<double> & data) {

	return sqrt (calcVarianza (data)) ;
}

double calcDevStdMedia (const vector<double> & data) {

	return sqrt (calcVarianza (data)/data.size ()) ;
}

double calcAsimmetria (const vector<double> & data) {

	double media = calcMedia (data) ;
	double sigma = calcSigma (data)  ;
	double asimmetria = 0. ;
	for (int i = 0 ; i < data.size () ; ++i) {
	
      asimmetria += pow ((data.at (i) - media) / sigma, 3) ;
    }  
	asimmetria /= data.size () ;  
	return asimmetria ;
	
}

template <typename T> 
double calcCurtosi (const std::vector<T> & data) {

	double media = calcMedia (data) ;
	double sigma = calcSigma (data)  ;
	double curtosi = 0. ;
	for (int i = 0 ; i < data.size () ; ++i) {
	
      curtosi += pow ((data.at (i) - media) / sigma, 4) ;
    }  
	curtosi /= data.size () - 3.;  
	return curtosi ;

}

template <typename T> 
double calcVarianzaSigmaQuadro (const std::vector<T> & data) {
	
	double var = calcVarianza(data);
	return 2. * var * var / (data.size() - 1);

}

