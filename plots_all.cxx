#include "eff_all.cxx"
#include "combined_plots.cxx"
#include "fixed_pileup.cxx"

void plots_all() {

  eff_all("pi15",1,1,1,1);
  eff_all("pi50",1,1,1,1);
  eff_all("pi100",1,1,1,1);

  eff_all("mu15",1,1,1,1);
  eff_all("mu50",1,1,1,1);
  eff_all("mu100",1,1,1,1);

  combined_plots("pi15", "mu15", 1, 50, 200);
  combined_plots("pi50", "mu50", 1, 50, 200);
  combined_plots("pi100", "mu100", 1, 50, 200);

  combined_plots("pi15", "mu15", 1, 50, 300);
  combined_plots("pi50", "mu50", 1, 50, 300);
  combined_plots("pi100", "mu100", 1, 50, 300);

  fixed_pileup("pi", 50, 1);
  fixed_pileup("mu", 50, 1);

  fixed_pileup("pi", 200, 1);
  fixed_pileup("mu", 200, 1);

  fixed_pileup("pi", 300, 1);
  fixed_pileup("mu", 300, 1);

}
