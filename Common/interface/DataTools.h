
#ifndef DATAUTILITIES_H
#define DATAUTILITIES_H

#include "Common.h"
#include "TString.h"

/** \file DataTools.h
 * \brief Tools used to deal with CMS detector metadata
 * \author S. Narayanan
 *
 */


//////////////////////////////////////////////////////////////////////////////////

class EraHandler {
  public:
    /**
     * \param year year of data-taking
     * \brief constructor
     */
    EraHandler(int year=2016) 
    {
      switch (year) 
      {
        case 2016: 
        {
          runBounds = {272007,
                       275657,
                       276315,
                       276831,
                       277772,
                       278820,
                       280919,
                       284044};
          eraNames = {"B","C","D","E","F","G","H"};
          bins = new Binner(runBounds);
          break;
        }
        default :
        {
          PError("PandaUtilities::EraHandler",TString::Format("Year %i is not known",year));
        }
      }
    }
    ~EraHandler() { delete bins; }
    TString getEra(int runNumber) 
    {
      if (runNumber<runBounds[0]) {
        PError("PandaUtilities::EraHandler",
            TString::Format("Run number (%i) is less than first run (%i)",runNumber,(int)runBounds[0]));
        return "";
      }
      if (runNumber>runBounds.back()) {
        PError("PandaUtilities::EraHandler",
            TString::Format("Run number (%i) is greater than last run (%i)",runNumber,(int)runBounds.back()));
        return "";
      }
      unsigned int eraIdx = bins->bin(runNumber);
      return eraNames[eraIdx];
    }
  private:
    std::vector<double> runBounds;
    std::vector<TString> eraNames;
    Binner *bins=0;
};

#endif
