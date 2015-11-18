#include "eff_reco.cxx"
#include <string>

void eff_reco_all(string sample) {

  string sample_radix = "./" + sample + "/hist-" + sample + "pu";

  eff((sample_radix + "50.root").c_str());
  eff((sample_radix + "100.root").c_str());
  eff((sample_radix + "140.root").c_str());
  eff((sample_radix + "200.root").c_str());
  eff((sample_radix + "300.root").c_str());

}
