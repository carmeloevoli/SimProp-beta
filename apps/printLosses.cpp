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

  const auto gammaAxis = utils::LogAxis<double>(1e8, 1e14, 6 * 32);

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

  const auto gammaAxis = utils::LogAxis<double>(1e8, 1e14, 6 * 32);
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

  const auto zAxis = utils::LinAxis<double>(0, 10, 30);
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

void plot_photopion_losses() {
  auto cosmology = std::make_shared<cosmo::Planck2018>();
  auto adiabatic = losses::AdiabaticContinuousLosses(cosmology);
  std::vector<std::shared_ptr<photonfields::PhotonField> > phFields{
      std::make_shared<photonfields::CMB>(),
      std::make_shared<photonfields::Dominguez2011PhotonField>()};
  auto pionLosses = losses::PhotoPionContinuousLosses(phFields);
  const auto gammaAxis = utils::LogAxis<double>(1e8, 1e16, 8 * 32);

  utils::OutputFile out("test_photopion_losses.txt");
  out << std::scientific;
  for (auto Gamma : gammaAxis) {
    out << Gamma << "\t";
    out << SI::cLight / adiabatic.beta(proton, Gamma) / SI::Mpc << "\t";
    out << SI::cLight / pionLosses.beta(proton, Gamma) / SI::Mpc << "\t";
    out << SI::cLight / pionLosses.beta(O16, Gamma) / SI::Mpc << "\t";
    out << SI::cLight / pionLosses.beta(Fe56, Gamma) / SI::Mpc << "\t";
    out << "\n";
  }
}

void plot_photopion_inelasticity() {
  double eps_th = SI::pionMassC2 + SI::pionMassC2 * SI::pionMassC2 / 2. / SI::protonMassC2;
  utils::OutputFile out("test_photopion_inelasticity.txt");
  out << std::scientific;
  for (double eps = eps_th; eps < 10.0 * SI::GeV; eps += 0.01 * SI::GeV) {
    out << eps / SI::GeV << "\t";
    auto s = pow2(SI::protonMassC2) + 2. * SI::protonMassC2 * eps;
    out << s / SI::GeV2 << "\t";
    out << losses::inelasticity(s) << "\t";
    out << losses::inelasticityPoorApproximation(s, -1.) << "\t";
    out << losses::inelasticityPoorApproximation(s, 0.) << "\n";
  }
}

int main() {
  try {
    utils::startup_information();
    utils::Timer timer("main timer for print losses");

    // plot_pair_on_fields();
    // plot_pair_nuclei();
    // plot_pair_evolution();
    plot_photopion_losses();
    plot_photopion_inelasticity();

  } catch (const std::exception& e) {
    LOGE << "exception caught with message: " << e.what();
  }
  return EXIT_SUCCESS;
}