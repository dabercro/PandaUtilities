#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "TLorentzVector.h" 
#include "TMath.h"

#ifndef PI
#define PI 3.141592654
#endif

/** \file NumericalFunctions.h
 * \brief Some numerical functions
 * \author S. Narayanan
 * \author Daniel Abercrombie <dabercro@mit.edu>
 */

//////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Invariant mass of a pair of particles
 */
inline double Mxx(double pt1, double eta1, double phi1, double m1, double pt2, double eta2, double phi2, double m2) {
	TLorentzVector v1,v2;
	v1.SetPtEtaPhiM(pt1,eta1,phi1,m1);
	v2.SetPtEtaPhiM(pt2,eta2,phi2,m2);
	return (v1+v2).M();
}

inline double MT(double pt1, double phi1, double pt2, double phi2)
{
	TLorentzVector v1,v2;
	v1.SetPtEtaPhiM(pt1,0,phi1,0);
	v2.SetPtEtaPhiM(pt2,0,phi2,0);
	return (v1+v2).M();
}

/**
 * \brief Signed delta-phi
 */
inline double SignedDeltaPhi(float phi1, float phi2) {
	double dPhi = phi1-phi2;
	if (dPhi<-PI)
		dPhi = 2*PI+dPhi;
	else if (dPhi>PI)
		dPhi = -2*PI+dPhi;
	return dPhi;
}

/**
 * \brief Unsigned delta-phi
 */
inline double UnsignedDeltaPhi(float phi1, float phi2) {
  return fabs(SignedDeltaPhi(phi1, phi2));
}

/**
 * \brief Calculates the delta-R-squared metric
 */
inline double DeltaR2(float eta1, float phi1, float eta2, float phi2) {
	double dEta2 = (eta1-eta2); dEta2 *= dEta2;
	double dPhi = SignedDeltaPhi(phi1,phi2);
	return dEta2 + dPhi*dPhi;
}

/**
 * \brief Exponential times erf, aka CMSShape
 */
inline double ExpErf(double x, double a, double b, double c) {
	double exp_ = TMath::Exp(c*x);
	double erf_ = TMath::Erf((x-a)/b);
	return exp_*(1+erf_)/2;
}

/**
 * \brief Calculates delta-R
 */
inline double DeltaR(float eta1, float phi1, float eta2, float phi2) {
  return TMath::Sqrt(DeltaR2(eta1, phi1, eta2, phi2));
}

#endif
