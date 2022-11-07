#include "simprop.h"

using namespace simprop;

void plot_pair_on_fields() {
  auto cosmology = std::make_shared<cosmo::Planck2018>();
  auto adiabatic = losses::AdiabaticContinuousLosses(cosmology);

  std::vector<std::shared_ptr<photonfields::PhotonField> > phFields{
      std::make_shared<photonfields::CMB>(),
      std::make_shared<photonfields::Dominguez2011PhotonField>()};
  auto pair_full = losses::PairProductionLosses(phFields);

  auto cmb = std::make_shared<photonfields::CMB>();
  auto pair_cmb = losses::PairProductionLosses(cmb);

  auto ebl = std::make_shared<photonfields::Dominguez2011PhotonField>();
  auto pair_ebl = losses::PairProductionLosses(ebl);

  auto bggLosses = losses::BGG2006ContinuousLosses();

  const auto gammaAxis = utils::LogAxis(1e8, 1e14, 6 * 32);

  utils::OutputFile out("test_pair_losses.txt");
  out << std::scientific;
  for (auto Gamma : gammaAxis) {
    out << Gamma << "\t";
    out << SI::cLight / adiabatic.beta(proton, Gamma) / SI::Mpc << "\t";
    out << SI::cLight / bggLosses.beta(proton, Gamma) / SI::Mpc << "\t";
    out << SI::cLight / pair_cmb.beta(proton, Gamma) / SI::Mpc << "\t";
    out << SI::cLight / pair_ebl.beta(proton, Gamma) / SI::Mpc << "\t";
    out << SI::cLight / pair_full.beta(proton, Gamma) / SI::Mpc << "\t";
    out << "\n";
  }
}

void plot_pair_nuclei() {
  auto cosmology = std::make_shared<cosmo::Planck2018>();
  auto adiabatic = losses::AdiabaticContinuousLosses(cosmology);
  auto bggLosses = losses::BGG2006ContinuousLosses();

  std::vector<std::shared_ptr<photonfields::PhotonField> > phFields{
      std::make_shared<photonfields::CMB>(),
      std::make_shared<photonfields::Dominguez2011PhotonField>()};
  auto pair = losses::PairProductionLosses(phFields);

  const auto gammaAxis = utils::LogAxis(1e8, 1e14, 6 * 32);
  utils::OutputFile out("test_nuclei_pair_losses.txt");

  out << std::scientific;
  for (auto Gamma : gammaAxis) {
    out << Gamma << "\t";
    out << SI::cLight / adiabatic.beta(proton, Gamma) / SI::Mpc << "\t";
    out << SI::cLight / bggLosses.beta(proton, Gamma) / SI::Mpc << "\t";
    out << SI::cLight / bggLosses.beta(O16, Gamma) / SI::Mpc << "\t";
    out << SI::cLight / bggLosses.beta(Fe56, Gamma) / SI::Mpc << "\t";
    out << SI::cLight / pair.beta(proton, Gamma) / SI::Mpc << "\t";
    out << SI::cLight / pair.beta(O16, Gamma) / SI::Mpc << "\t";
    out << SI::cLight / pair.beta(Fe56, Gamma) / SI::Mpc << "\t";
    out << "\n";
  }
}

void plot_pair_evolution() {
  auto cosmology = std::make_shared<cosmo::Planck2018>();
  auto adiabatic = losses::AdiabaticContinuousLosses(cosmology);
  auto bggLosses = losses::BGG2006ContinuousLosses();

  auto cmb = std::make_shared<photonfields::CMB>();
  auto pair_cmb = losses::PairProductionLosses(cmb);

  auto ebl = std::make_shared<photonfields::Dominguez2011PhotonField>();
  auto pair_ebl = losses::PairProductionLosses(ebl);

  const auto zAxis = utils::LinAxis(0, 10, 30);
  utils::OutputFile out("test_evolution_pair_losses.txt");

  out << std::scientific;
  for (auto z : zAxis) {
    out << z << "\t";
    out << SI::cLight / adiabatic.beta(proton, 1e10, z) / SI::Mpc << "\t";
    //
    out << SI::cLight / bggLosses.beta(proton, 1e10, z) / SI::Mpc << "\t";
    out << SI::cLight / bggLosses.beta(proton, 1e12, z) / SI::Mpc << "\t";
    out << SI::cLight / bggLosses.beta(proton, 1e14, z) / SI::Mpc << "\t";
    //
    out << SI::cLight / pair_cmb.beta(proton, 1e10, z) / SI::Mpc << "\t";
    out << SI::cLight / pair_cmb.beta(proton, 1e12, z) / SI::Mpc << "\t";
    out << SI::cLight / pair_cmb.beta(proton, 1e14, z) / SI::Mpc << "\t";
    //
    out << SI::cLight / pair_ebl.beta(proton, 1e10, z) / SI::Mpc << "\t";
    out << SI::cLight / pair_ebl.beta(proton, 1e12, z) / SI::Mpc << "\t";
    out << SI::cLight / pair_ebl.beta(proton, 1e14, z) / SI::Mpc << "\t";
    out << "\n";
  }
}

int main() {
  try {
    utils::startup_information();
    utils::Timer timer("main timer for print losses");

    plot_pair_on_fields();
    plot_pair_nuclei();
    plot_pair_evolution();

    // auto cosmology = std::make_shared<cosmo::Planck2018>();
    // auto adiabatic = losses::AdiabaticContinuousLosses(cosmology);
    // auto bggLosses = losses::BGG2002ContinuousLosses();
    // auto pionLosses = losses::PhotoPionContinuousLosses();

    // const auto gammaAxis = utils::LogAxis(1e8, 1e16, 8 * 32);

    // utils::OutputFile out("test_losses.txt");
    // out << std::scientific;
    // for (auto Gamma : gammaAxis) {
    //   out << Gamma << "\t";
    //   out << SI::cLight / adiabatic.beta(proton, Gamma) / SI::Mpc << "\t";
    //   out << SI::cLight / bggLosses.beta(proton, Gamma) / SI::Mpc << "\t";
    //   out << SI::cLight / pair_cmb.beta(proton, Gamma) / SI::Mpc << "\t";
    //   out << SI::cLight / pair_irb.beta(proton, Gamma) / SI::Mpc << "\t";
    //   out << SI::cLight / pair.beta(proton, Gamma) / SI::Mpc << "\t";
    //   out << SI::cLight / pionLosses.beta(proton, Gamma) / SI::Mpc << "\t";
    //   out << "\n";
    // }
  } catch (const std::exception& e) {
    LOGE << "exception caught with message: " << e.what();
  }
  return EXIT_SUCCESS;
}