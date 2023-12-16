#ifndef statistiche_vector_h
#define statistiche_vector_h

#include <vector>

template <typename T> T ricercaMin(const std::vector<T> & data);
template <typename T> T ricercaMax(const std::vector<T> & data);
double calcMedia (const std::vector<double> & data);
double calcVarianza (const std::vector<double> & data);
double calcSigma (const std::vector<double> & data);
double calcDevStdMedia (const std::vector<double> & data);
double calcAsimmetria (const std::vector<double> & data);
template <typename T> double calcCurtosi (const std::vector<T> & data);
template <typename T> double calcVarianzaSigmaQuadro (const std::vector<T> & data);

#endif
