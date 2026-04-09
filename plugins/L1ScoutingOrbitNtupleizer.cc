#include <vector>
#include <set>
#include <cstdint>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TTree.h"

#include "DataFormats/L1Scouting/interface/OrbitCollection.h"
#include "DataFormats/L1Scouting/interface/L1ScoutingMuon.h"
#include "DataFormats/L1Scouting/interface/L1ScoutingCalo.h"
#include "DataFormats/L1Scouting/interface/L1ScoutingBMTFStub.h"

#include "L1TriggerScouting/Utilities/interface/conversion.h"

class L1ScoutingOrbitNtupleizer : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit L1ScoutingOrbitNtupleizer(const edm::ParameterSet&);
  ~L1ScoutingOrbitNtupleizer() override = default;

  void analyze(const edm::Event&, const edm::EventSetup&) override;

private:
  using MuonOrbit     = OrbitCollection<l1ScoutingRun3::Muon>;
  using JetOrbit      = OrbitCollection<l1ScoutingRun3::Jet>;
  using EGammaOrbit   = OrbitCollection<l1ScoutingRun3::EGamma>;
  using TauOrbit      = OrbitCollection<l1ScoutingRun3::Tau>;
  using EtSumOrbit    = OrbitCollection<l1ScoutingRun3::BxSums>;
  using BMTFStubOrbit = OrbitCollection<l1ScoutingRun3::BMTFStub>;

  edm::EDGetTokenT<MuonOrbit>     muToken_;
  edm::EDGetTokenT<JetOrbit>      jetToken_;
  edm::EDGetTokenT<EGammaOrbit>   egToken_;
  edm::EDGetTokenT<TauOrbit>      tauToken_;
  edm::EDGetTokenT<EtSumOrbit>    sumToken_;
  edm::EDGetTokenT<BMTFStubOrbit> bmtfToken_;

  bool saveMuons_;
  bool saveJets_;
  bool saveEGammas_;
  bool saveTaus_;
  bool saveEtSums_;
  bool saveBmtf_;

  TTree* tree_;

  UInt_t run_;
  UInt_t lumi_;
  ULong64_t event_;
  Int_t bx_;

  Int_t n_mu_;
  Int_t n_jet_;
  Int_t n_eg_;
  Int_t n_tau_;
  Int_t n_sum_;
  Int_t n_bmtf_;
  Bool_t has_any_object_;

  // Muons: raw + converted
  std::vector<int> mu_hwPt_;
  std::vector<int> mu_hwEta_;
  std::vector<int> mu_hwPhi_;
  std::vector<int> mu_hwQual_;
  std::vector<int> mu_hwCharge_;
  std::vector<int> mu_hwChargeValid_;
  std::vector<int> mu_hwIso_;
  std::vector<int> mu_hwEtaAtVtx_;
  std::vector<int> mu_hwPhiAtVtx_;
  std::vector<int> mu_hwPtUnconstrained_;
  std::vector<int> mu_hwDXY_;

  std::vector<float> mu_pt_;
  std::vector<float> mu_eta_;
  std::vector<float> mu_phi_;
  std::vector<float> mu_etaAtVtx_;
  std::vector<float> mu_phiAtVtx_;
  std::vector<float> mu_ptUnconstrained_;

  // Jets: raw + converted
  std::vector<int> jet_hwEt_;
  std::vector<int> jet_hwEta_;
  std::vector<int> jet_hwPhi_;
  std::vector<int> jet_hwQual_;

  std::vector<float> jet_et_;
  std::vector<float> jet_eta_;
  std::vector<float> jet_phi_;

  // EGammas: raw + converted
  std::vector<int> eg_hwEt_;
  std::vector<int> eg_hwEta_;
  std::vector<int> eg_hwPhi_;
  std::vector<int> eg_hwIso_;

  std::vector<float> eg_et_;
  std::vector<float> eg_eta_;
  std::vector<float> eg_phi_;

  // Taus: raw + converted
  std::vector<int> tau_hwEt_;
  std::vector<int> tau_hwEta_;
  std::vector<int> tau_hwPhi_;
  std::vector<int> tau_hwIso_;

  std::vector<float> tau_et_;
  std::vector<float> tau_eta_;
  std::vector<float> tau_phi_;

  // Et sums: raw + converted
  std::vector<int> sum_hwTotalEt_;
  std::vector<int> sum_hwTotalEtEm_;
  std::vector<int> sum_hwTotalHt_;
  std::vector<int> sum_hwMissEt_;
  std::vector<int> sum_hwMissEtPhi_;
  std::vector<int> sum_hwMissHt_;
  std::vector<int> sum_hwMissHtPhi_;
  std::vector<int> sum_hwMissEtHF_;
  std::vector<int> sum_hwMissEtHFPhi_;
  std::vector<int> sum_hwMissHtHF_;
  std::vector<int> sum_hwMissHtHFPhi_;
  std::vector<int> sum_hwAsymEt_;
  std::vector<int> sum_hwAsymHt_;
  std::vector<int> sum_hwAsymEtHF_;
  std::vector<int> sum_hwAsymHtHF_;
  std::vector<int> sum_minBiasHFP0_;
  std::vector<int> sum_minBiasHFM0_;
  std::vector<int> sum_minBiasHFP1_;
  std::vector<int> sum_minBiasHFM1_;
  std::vector<int> sum_towerCount_;
  std::vector<int> sum_centrality_;

  std::vector<float> sum_totalEt_;
  std::vector<float> sum_totalEtEm_;
  std::vector<float> sum_totalHt_;
  std::vector<float> sum_missEt_;
  std::vector<float> sum_missEtPhi_;
  std::vector<float> sum_missHt_;
  std::vector<float> sum_missHtPhi_;
  std::vector<float> sum_missEtHF_;
  std::vector<float> sum_missEtHFPhi_;
  std::vector<float> sum_missHtHF_;
  std::vector<float> sum_missHtHFPhi_;

  // BMTF stubs: raw only
  std::vector<int> bmtf_hwPhi_;
  std::vector<int> bmtf_hwPhiB_;
  std::vector<int> bmtf_hwQual_;
  std::vector<int> bmtf_hwEta_;
  std::vector<int> bmtf_hwQEta_;
  std::vector<int> bmtf_station_;
  std::vector<int> bmtf_wheel_;
  std::vector<int> bmtf_sector_;
  std::vector<int> bmtf_tag_;

  void clearVectors();

  template <typename TOrbit>
  void collectBxs(const edm::Handle<TOrbit>& handle, std::set<int>& bxs) const {
    if (!handle.isValid())
      return;
    for (auto bx : handle->getFilledBxs()) {
      bxs.insert(static_cast<int>(bx));
    }
  }
};

L1ScoutingOrbitNtupleizer::L1ScoutingOrbitNtupleizer(const edm::ParameterSet& cfg)
    : muToken_(consumes<MuonOrbit>(cfg.getParameter<edm::InputTag>("muons"))),
      jetToken_(consumes<JetOrbit>(cfg.getParameter<edm::InputTag>("jets"))),
      egToken_(consumes<EGammaOrbit>(cfg.getParameter<edm::InputTag>("egammas"))),
      tauToken_(consumes<TauOrbit>(cfg.getParameter<edm::InputTag>("taus"))),
      sumToken_(consumes<EtSumOrbit>(cfg.getParameter<edm::InputTag>("etsums"))),
      bmtfToken_(consumes<BMTFStubOrbit>(cfg.getParameter<edm::InputTag>("bmtfstub"))),
      saveMuons_(cfg.getParameter<bool>("saveMuons")),
      saveJets_(cfg.getParameter<bool>("saveJets")),
      saveEGammas_(cfg.getParameter<bool>("saveEGammas")),
      saveTaus_(cfg.getParameter<bool>("saveTaus")),
      saveEtSums_(cfg.getParameter<bool>("saveEtSums")),
      saveBmtf_(cfg.getParameter<bool>("saveBmtf")),
      tree_(nullptr),
      run_(0),
      lumi_(0),
      event_(0),
      bx_(0),
      n_mu_(0),
      n_jet_(0),
      n_eg_(0),
      n_tau_(0),
      n_sum_(0),
      n_bmtf_(0),
      has_any_object_(false) {
  usesResource("TFileService");

  edm::Service<TFileService> fs;
  tree_ = fs->make<TTree>("Events", "L1 scouting BX ntuple");

  tree_->Branch("run", &run_, "run/i");
  tree_->Branch("lumi", &lumi_, "lumi/i");
  tree_->Branch("event", &event_, "event/l");
  tree_->Branch("bx", &bx_, "bx/I");

  tree_->Branch("n_mu", &n_mu_, "n_mu/I");
  tree_->Branch("n_jet", &n_jet_, "n_jet/I");
  tree_->Branch("n_eg", &n_eg_, "n_eg/I");
  tree_->Branch("n_tau", &n_tau_, "n_tau/I");
  tree_->Branch("n_sum", &n_sum_, "n_sum/I");
  tree_->Branch("n_bmtf", &n_bmtf_, "n_bmtf/I");
  tree_->Branch("has_any_object", &has_any_object_, "has_any_object/O");

  tree_->Branch("mu_hwPt", &mu_hwPt_);
  tree_->Branch("mu_hwEta", &mu_hwEta_);
  tree_->Branch("mu_hwPhi", &mu_hwPhi_);
  tree_->Branch("mu_hwQual", &mu_hwQual_);
  tree_->Branch("mu_hwCharge", &mu_hwCharge_);
  tree_->Branch("mu_hwChargeValid", &mu_hwChargeValid_);
  tree_->Branch("mu_hwIso", &mu_hwIso_);
  tree_->Branch("mu_hwEtaAtVtx", &mu_hwEtaAtVtx_);
  tree_->Branch("mu_hwPhiAtVtx", &mu_hwPhiAtVtx_);
  tree_->Branch("mu_hwPtUnconstrained", &mu_hwPtUnconstrained_);
  tree_->Branch("mu_hwDXY", &mu_hwDXY_);
  tree_->Branch("mu_pt", &mu_pt_);
  tree_->Branch("mu_eta", &mu_eta_);
  tree_->Branch("mu_phi", &mu_phi_);
  tree_->Branch("mu_etaAtVtx", &mu_etaAtVtx_);
  tree_->Branch("mu_phiAtVtx", &mu_phiAtVtx_);
  tree_->Branch("mu_ptUnconstrained", &mu_ptUnconstrained_);

  tree_->Branch("jet_hwEt", &jet_hwEt_);
  tree_->Branch("jet_hwEta", &jet_hwEta_);
  tree_->Branch("jet_hwPhi", &jet_hwPhi_);
  tree_->Branch("jet_hwQual", &jet_hwQual_);
  tree_->Branch("jet_et", &jet_et_);
  tree_->Branch("jet_eta", &jet_eta_);
  tree_->Branch("jet_phi", &jet_phi_);

  tree_->Branch("eg_hwEt", &eg_hwEt_);
  tree_->Branch("eg_hwEta", &eg_hwEta_);
  tree_->Branch("eg_hwPhi", &eg_hwPhi_);
  tree_->Branch("eg_hwIso", &eg_hwIso_);
  tree_->Branch("eg_et", &eg_et_);
  tree_->Branch("eg_eta", &eg_eta_);
  tree_->Branch("eg_phi", &eg_phi_);

  tree_->Branch("tau_hwEt", &tau_hwEt_);
  tree_->Branch("tau_hwEta", &tau_hwEta_);
  tree_->Branch("tau_hwPhi", &tau_hwPhi_);
  tree_->Branch("tau_hwIso", &tau_hwIso_);
  tree_->Branch("tau_et", &tau_et_);
  tree_->Branch("tau_eta", &tau_eta_);
  tree_->Branch("tau_phi", &tau_phi_);

  tree_->Branch("sum_hwTotalEt", &sum_hwTotalEt_);
  tree_->Branch("sum_hwTotalEtEm", &sum_hwTotalEtEm_);
  tree_->Branch("sum_hwTotalHt", &sum_hwTotalHt_);
  tree_->Branch("sum_hwMissEt", &sum_hwMissEt_);
  tree_->Branch("sum_hwMissEtPhi", &sum_hwMissEtPhi_);
  tree_->Branch("sum_hwMissHt", &sum_hwMissHt_);
  tree_->Branch("sum_hwMissHtPhi", &sum_hwMissHtPhi_);
  tree_->Branch("sum_hwMissEtHF", &sum_hwMissEtHF_);
  tree_->Branch("sum_hwMissEtHFPhi", &sum_hwMissEtHFPhi_);
  tree_->Branch("sum_hwMissHtHF", &sum_hwMissHtHF_);
  tree_->Branch("sum_hwMissHtHFPhi", &sum_hwMissHtHFPhi_);
  tree_->Branch("sum_hwAsymEt", &sum_hwAsymEt_);
  tree_->Branch("sum_hwAsymHt", &sum_hwAsymHt_);
  tree_->Branch("sum_hwAsymEtHF", &sum_hwAsymEtHF_);
  tree_->Branch("sum_hwAsymHtHF", &sum_hwAsymHtHF_);
  tree_->Branch("sum_minBiasHFP0", &sum_minBiasHFP0_);
  tree_->Branch("sum_minBiasHFM0", &sum_minBiasHFM0_);
  tree_->Branch("sum_minBiasHFP1", &sum_minBiasHFP1_);
  tree_->Branch("sum_minBiasHFM1", &sum_minBiasHFM1_);
  tree_->Branch("sum_towerCount", &sum_towerCount_);
  tree_->Branch("sum_centrality", &sum_centrality_);
  tree_->Branch("sum_totalEt", &sum_totalEt_);
  tree_->Branch("sum_totalEtEm", &sum_totalEtEm_);
  tree_->Branch("sum_totalHt", &sum_totalHt_);
  tree_->Branch("sum_missEt", &sum_missEt_);
  tree_->Branch("sum_missEtPhi", &sum_missEtPhi_);
  tree_->Branch("sum_missHt", &sum_missHt_);
  tree_->Branch("sum_missHtPhi", &sum_missHtPhi_);
  tree_->Branch("sum_missEtHF", &sum_missEtHF_);
  tree_->Branch("sum_missEtHFPhi", &sum_missEtHFPhi_);
  tree_->Branch("sum_missHtHF", &sum_missHtHF_);
  tree_->Branch("sum_missHtHFPhi", &sum_missHtHFPhi_);

  tree_->Branch("bmtf_hwPhi", &bmtf_hwPhi_);
  tree_->Branch("bmtf_hwPhiB", &bmtf_hwPhiB_);
  tree_->Branch("bmtf_hwQual", &bmtf_hwQual_);
  tree_->Branch("bmtf_hwEta", &bmtf_hwEta_);
  tree_->Branch("bmtf_hwQEta", &bmtf_hwQEta_);
  tree_->Branch("bmtf_station", &bmtf_station_);
  tree_->Branch("bmtf_wheel", &bmtf_wheel_);
  tree_->Branch("bmtf_sector", &bmtf_sector_);
  tree_->Branch("bmtf_tag", &bmtf_tag_);
}

void L1ScoutingOrbitNtupleizer::clearVectors() {
  n_mu_ = 0;
  n_jet_ = 0;
  n_eg_ = 0;
  n_tau_ = 0;
  n_sum_ = 0;
  n_bmtf_ = 0;
  has_any_object_ = false;

  mu_hwPt_.clear();
  mu_hwEta_.clear();
  mu_hwPhi_.clear();
  mu_hwQual_.clear();
  mu_hwCharge_.clear();
  mu_hwChargeValid_.clear();
  mu_hwIso_.clear();
  mu_hwEtaAtVtx_.clear();
  mu_hwPhiAtVtx_.clear();
  mu_hwPtUnconstrained_.clear();
  mu_hwDXY_.clear();
  mu_pt_.clear();
  mu_eta_.clear();
  mu_phi_.clear();
  mu_etaAtVtx_.clear();
  mu_phiAtVtx_.clear();
  mu_ptUnconstrained_.clear();

  jet_hwEt_.clear();
  jet_hwEta_.clear();
  jet_hwPhi_.clear();
  jet_hwQual_.clear();
  jet_et_.clear();
  jet_eta_.clear();
  jet_phi_.clear();

  eg_hwEt_.clear();
  eg_hwEta_.clear();
  eg_hwPhi_.clear();
  eg_hwIso_.clear();
  eg_et_.clear();
  eg_eta_.clear();
  eg_phi_.clear();

  tau_hwEt_.clear();
  tau_hwEta_.clear();
  tau_hwPhi_.clear();
  tau_hwIso_.clear();
  tau_et_.clear();
  tau_eta_.clear();
  tau_phi_.clear();

  sum_hwTotalEt_.clear();
  sum_hwTotalEtEm_.clear();
  sum_hwTotalHt_.clear();
  sum_hwMissEt_.clear();
  sum_hwMissEtPhi_.clear();
  sum_hwMissHt_.clear();
  sum_hwMissHtPhi_.clear();
  sum_hwMissEtHF_.clear();
  sum_hwMissEtHFPhi_.clear();
  sum_hwMissHtHF_.clear();
  sum_hwMissHtHFPhi_.clear();
  sum_hwAsymEt_.clear();
  sum_hwAsymHt_.clear();
  sum_hwAsymEtHF_.clear();
  sum_hwAsymHtHF_.clear();
  sum_minBiasHFP0_.clear();
  sum_minBiasHFM0_.clear();
  sum_minBiasHFP1_.clear();
  sum_minBiasHFM1_.clear();
  sum_towerCount_.clear();
  sum_centrality_.clear();
  sum_totalEt_.clear();
  sum_totalEtEm_.clear();
  sum_totalHt_.clear();
  sum_missEt_.clear();
  sum_missEtPhi_.clear();
  sum_missHt_.clear();
  sum_missHtPhi_.clear();
  sum_missEtHF_.clear();
  sum_missEtHFPhi_.clear();
  sum_missHtHF_.clear();
  sum_missHtHFPhi_.clear();

  bmtf_hwPhi_.clear();
  bmtf_hwPhiB_.clear();
  bmtf_hwQual_.clear();
  bmtf_hwEta_.clear();
  bmtf_hwQEta_.clear();
  bmtf_station_.clear();
  bmtf_wheel_.clear();
  bmtf_sector_.clear();
  bmtf_tag_.clear();
}

void L1ScoutingOrbitNtupleizer::analyze(const edm::Event& iEvent, const edm::EventSetup&) {
  run_ = iEvent.id().run();
  lumi_ = iEvent.luminosityBlock();
  event_ = iEvent.id().event();

  edm::Handle<MuonOrbit> hMu;
  edm::Handle<JetOrbit> hJet;
  edm::Handle<EGammaOrbit> hEg;
  edm::Handle<TauOrbit> hTau;
  edm::Handle<EtSumOrbit> hSum;
  edm::Handle<BMTFStubOrbit> hBmtf;

  iEvent.getByToken(muToken_, hMu);
  iEvent.getByToken(jetToken_, hJet);
  iEvent.getByToken(egToken_, hEg);
  iEvent.getByToken(tauToken_, hTau);
  iEvent.getByToken(sumToken_, hSum);
  iEvent.getByToken(bmtfToken_, hBmtf);

  std::set<int> allBxs;
  if (saveMuons_)
    collectBxs(hMu, allBxs);
  if (saveJets_)
    collectBxs(hJet, allBxs);
  if (saveEGammas_)
    collectBxs(hEg, allBxs);
  if (saveTaus_)
    collectBxs(hTau, allBxs);
  if (saveEtSums_)
    collectBxs(hSum, allBxs);
  if (saveBmtf_)
    collectBxs(hBmtf, allBxs);

  for (int bx : allBxs) {
    bx_ = bx;
    clearVectors();

    if (saveMuons_ && hMu.isValid()) {
      const auto bxu = static_cast<unsigned>(bx);
      const auto n = hMu->getBxSize(bxu);
      for (unsigned i = 0; i < n; ++i) {
        const auto& mu = hMu->getBxObject(bxu, i);
        mu_hwPt_.push_back(mu.hwPt());
        mu_hwEta_.push_back(mu.hwEta());
        mu_hwPhi_.push_back(mu.hwPhi());
        mu_hwQual_.push_back(mu.hwQual());
        mu_hwCharge_.push_back(mu.hwCharge());
        mu_hwChargeValid_.push_back(mu.hwChargeValid());
        mu_hwIso_.push_back(mu.hwIso());
        mu_hwEtaAtVtx_.push_back(mu.hwEtaAtVtx());
        mu_hwPhiAtVtx_.push_back(mu.hwPhiAtVtx());
        mu_hwPtUnconstrained_.push_back(mu.hwPtUnconstrained());
        mu_hwDXY_.push_back(mu.hwDXY());

        mu_pt_.push_back(l1ScoutingRun3::ugmt::fPt(mu.hwPt()));
        mu_eta_.push_back(l1ScoutingRun3::ugmt::fEta(mu.hwEta()));
        mu_phi_.push_back(l1ScoutingRun3::ugmt::fPhi(mu.hwPhi()));
        mu_etaAtVtx_.push_back(l1ScoutingRun3::ugmt::fEtaAtVtx(mu.hwEtaAtVtx()));
        mu_phiAtVtx_.push_back(l1ScoutingRun3::ugmt::fPhiAtVtx(mu.hwPhiAtVtx()));
        mu_ptUnconstrained_.push_back(l1ScoutingRun3::ugmt::fPtUnconstrained(mu.hwPtUnconstrained()));
      }
      n_mu_ = static_cast<Int_t>(n);
    }

    if (saveJets_ && hJet.isValid()) {
      const auto bxu = static_cast<unsigned>(bx);
      const auto n = hJet->getBxSize(bxu);
      for (unsigned i = 0; i < n; ++i) {
        const auto& jet = hJet->getBxObject(bxu, i);
        jet_hwEt_.push_back(jet.hwEt());
        jet_hwEta_.push_back(jet.hwEta());
        jet_hwPhi_.push_back(jet.hwPhi());
        jet_hwQual_.push_back(jet.hwQual());

        jet_et_.push_back(l1ScoutingRun3::demux::fEt(jet.hwEt()));
        jet_eta_.push_back(l1ScoutingRun3::demux::fEta(jet.hwEta()));
        jet_phi_.push_back(l1ScoutingRun3::demux::fPhi(jet.hwPhi()));
      }
      n_jet_ = static_cast<Int_t>(n);
    }

    if (saveEGammas_ && hEg.isValid()) {
      const auto bxu = static_cast<unsigned>(bx);
      const auto n = hEg->getBxSize(bxu);
      for (unsigned i = 0; i < n; ++i) {
        const auto& eg = hEg->getBxObject(bxu, i);
        eg_hwEt_.push_back(eg.hwEt());
        eg_hwEta_.push_back(eg.hwEta());
        eg_hwPhi_.push_back(eg.hwPhi());
        eg_hwIso_.push_back(eg.hwIso());

        eg_et_.push_back(l1ScoutingRun3::demux::fEt(eg.hwEt()));
        eg_eta_.push_back(l1ScoutingRun3::demux::fEta(eg.hwEta()));
        eg_phi_.push_back(l1ScoutingRun3::demux::fPhi(eg.hwPhi()));
      }
      n_eg_ = static_cast<Int_t>(n);
    }

    if (saveTaus_ && hTau.isValid()) {
      const auto bxu = static_cast<unsigned>(bx);
      const auto n = hTau->getBxSize(bxu);
      for (unsigned i = 0; i < n; ++i) {
        const auto& tau = hTau->getBxObject(bxu, i);
        tau_hwEt_.push_back(tau.hwEt());
        tau_hwEta_.push_back(tau.hwEta());
        tau_hwPhi_.push_back(tau.hwPhi());
        tau_hwIso_.push_back(tau.hwIso());

        tau_et_.push_back(l1ScoutingRun3::demux::fEt(tau.hwEt()));
        tau_eta_.push_back(l1ScoutingRun3::demux::fEta(tau.hwEta()));
        tau_phi_.push_back(l1ScoutingRun3::demux::fPhi(tau.hwPhi()));
      }
      n_tau_ = static_cast<Int_t>(n);
    }

    if (saveEtSums_ && hSum.isValid()) {
      const auto bxu = static_cast<unsigned>(bx);
      const auto n = hSum->getBxSize(bxu);
      for (unsigned i = 0; i < n; ++i) {
        const auto& s = hSum->getBxObject(bxu, i);

        sum_hwTotalEt_.push_back(s.hwTotalEt());
        sum_hwTotalEtEm_.push_back(s.hwTotalEtEm());
        sum_hwTotalHt_.push_back(s.hwTotalHt());
        sum_hwMissEt_.push_back(s.hwMissEt());
        sum_hwMissEtPhi_.push_back(s.hwMissEtPhi());
        sum_hwMissHt_.push_back(s.hwMissHt());
        sum_hwMissHtPhi_.push_back(s.hwMissHtPhi());
        sum_hwMissEtHF_.push_back(s.hwMissEtHF());
        sum_hwMissEtHFPhi_.push_back(s.hwMissEtHFPhi());
        sum_hwMissHtHF_.push_back(s.hwMissHtHF());
        sum_hwMissHtHFPhi_.push_back(s.hwMissHtHFPhi());
        sum_hwAsymEt_.push_back(s.hwAsymEt());
        sum_hwAsymHt_.push_back(s.hwAsymHt());
        sum_hwAsymEtHF_.push_back(s.hwAsymEtHF());
        sum_hwAsymHtHF_.push_back(s.hwAsymHtHF());
        sum_minBiasHFP0_.push_back(s.minBiasHFP0());
        sum_minBiasHFM0_.push_back(s.minBiasHFM0());
        sum_minBiasHFP1_.push_back(s.minBiasHFP1());
        sum_minBiasHFM1_.push_back(s.minBiasHFM1());
        sum_towerCount_.push_back(s.towerCount());
        sum_centrality_.push_back(s.centrality());

        sum_totalEt_.push_back(l1ScoutingRun3::demux::fEt(s.hwTotalEt()));
        sum_totalEtEm_.push_back(l1ScoutingRun3::demux::fEt(s.hwTotalEtEm()));
        sum_totalHt_.push_back(l1ScoutingRun3::demux::fEt(s.hwTotalHt()));
        sum_missEt_.push_back(l1ScoutingRun3::demux::fEt(s.hwMissEt()));
        sum_missEtPhi_.push_back(l1ScoutingRun3::demux::fPhi(s.hwMissEtPhi()));
        sum_missHt_.push_back(l1ScoutingRun3::demux::fEt(s.hwMissHt()));
        sum_missHtPhi_.push_back(l1ScoutingRun3::demux::fPhi(s.hwMissHtPhi()));
        sum_missEtHF_.push_back(l1ScoutingRun3::demux::fEt(s.hwMissEtHF()));
        sum_missEtHFPhi_.push_back(l1ScoutingRun3::demux::fPhi(s.hwMissEtHFPhi()));
        sum_missHtHF_.push_back(l1ScoutingRun3::demux::fEt(s.hwMissHtHF()));
        sum_missHtHFPhi_.push_back(l1ScoutingRun3::demux::fPhi(s.hwMissHtHFPhi()));
      }
      n_sum_ = static_cast<Int_t>(n);
    }

    if (saveBmtf_ && hBmtf.isValid()) {
      const auto bxu = static_cast<unsigned>(bx);
      const auto n = hBmtf->getBxSize(bxu);
      for (unsigned i = 0; i < n; ++i) {
        const auto& s = hBmtf->getBxObject(bxu, i);
        bmtf_hwPhi_.push_back(s.hwPhi());
        bmtf_hwPhiB_.push_back(s.hwPhiB());
        bmtf_hwQual_.push_back(s.hwQual());
        bmtf_hwEta_.push_back(s.hwEta());
        bmtf_hwQEta_.push_back(s.hwQEta());
        bmtf_station_.push_back(s.station());
        bmtf_wheel_.push_back(s.wheel());
        bmtf_sector_.push_back(s.sector());
        bmtf_tag_.push_back(s.tag());
      }
      n_bmtf_ = static_cast<Int_t>(n);
    }

    has_any_object_ = (n_mu_ + n_jet_ + n_eg_ + n_tau_ + n_sum_ + n_bmtf_) > 0;
    tree_->Fill();
  }
}

DEFINE_FWK_MODULE(L1ScoutingOrbitNtupleizer);
