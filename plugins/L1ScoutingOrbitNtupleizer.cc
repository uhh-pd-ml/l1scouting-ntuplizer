#include <vector>
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

  std::vector<int> mu_bx_;
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

  std::vector<int> jet_bx_;
  std::vector<int> jet_hwEt_;
  std::vector<int> jet_hwEta_;
  std::vector<int> jet_hwPhi_;
  std::vector<int> jet_hwQual_;

  std::vector<int> eg_bx_;
  std::vector<int> eg_hwEt_;
  std::vector<int> eg_hwEta_;
  std::vector<int> eg_hwPhi_;
  std::vector<int> eg_hwIso_;

  std::vector<int> tau_bx_;
  std::vector<int> tau_hwEt_;
  std::vector<int> tau_hwEta_;
  std::vector<int> tau_hwPhi_;
  std::vector<int> tau_hwIso_;

  std::vector<int> sum_bx_;
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

  std::vector<int> bmtf_bx_;
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
};

L1ScoutingOrbitNtupleizer::L1ScoutingOrbitNtupleizer(const edm::ParameterSet& cfg)
    : muToken_  (consumes<MuonOrbit>    (cfg.getParameter<edm::InputTag>("muons"))),
      jetToken_ (consumes<JetOrbit>     (cfg.getParameter<edm::InputTag>("jets"))),
      egToken_  (consumes<EGammaOrbit>  (cfg.getParameter<edm::InputTag>("egammas"))),
      tauToken_ (consumes<TauOrbit>     (cfg.getParameter<edm::InputTag>("taus"))),
      sumToken_ (consumes<EtSumOrbit>   (cfg.getParameter<edm::InputTag>("etsums"))),
      bmtfToken_(consumes<BMTFStubOrbit>(cfg.getParameter<edm::InputTag>("bmtfstub"))),
      saveMuons_   (cfg.getParameter<bool>("saveMuons")),
      saveJets_    (cfg.getParameter<bool>("saveJets")),
      saveEGammas_(cfg.getParameter<bool>("saveEGammas")),
      saveTaus_    (cfg.getParameter<bool>("saveTaus")),
      saveEtSums_  (cfg.getParameter<bool>("saveEtSums")),
      saveBmtf_    (cfg.getParameter<bool>("saveBmtf")),
      tree_(nullptr),
      run_(0), lumi_(0), event_(0)
{
  usesResource("TFileService");

  edm::Service<TFileService> fs;
  tree_ = fs->make<TTree>("Events", "L1 scouting orbit ntuple");

  tree_->Branch("run",   &run_,   "run/i");
  tree_->Branch("lumi",  &lumi_,  "lumi/i");
  tree_->Branch("event", &event_, "event/l");

  tree_->Branch("mu_bx",                  &mu_bx_);
  tree_->Branch("mu_hwPt",                &mu_hwPt_);
  tree_->Branch("mu_hwEta",               &mu_hwEta_);
  tree_->Branch("mu_hwPhi",               &mu_hwPhi_);
  tree_->Branch("mu_hwQual",              &mu_hwQual_);
  tree_->Branch("mu_hwCharge",            &mu_hwCharge_);
  tree_->Branch("mu_hwChargeValid",       &mu_hwChargeValid_);
  tree_->Branch("mu_hwIso",               &mu_hwIso_);
  tree_->Branch("mu_hwEtaAtVtx",          &mu_hwEtaAtVtx_);
  tree_->Branch("mu_hwPhiAtVtx",          &mu_hwPhiAtVtx_);
  tree_->Branch("mu_hwPtUnconstrained",   &mu_hwPtUnconstrained_);
  tree_->Branch("mu_hwDXY",               &mu_hwDXY_);

  tree_->Branch("jet_bx",                 &jet_bx_);
  tree_->Branch("jet_hwEt",               &jet_hwEt_);
  tree_->Branch("jet_hwEta",              &jet_hwEta_);
  tree_->Branch("jet_hwPhi",              &jet_hwPhi_);
  tree_->Branch("jet_hwQual",             &jet_hwQual_);

  tree_->Branch("eg_bx",                  &eg_bx_);
  tree_->Branch("eg_hwEt",                &eg_hwEt_);
  tree_->Branch("eg_hwEta",               &eg_hwEta_);
  tree_->Branch("eg_hwPhi",               &eg_hwPhi_);
  tree_->Branch("eg_hwIso",               &eg_hwIso_);

  tree_->Branch("tau_bx",                 &tau_bx_);
  tree_->Branch("tau_hwEt",               &tau_hwEt_);
  tree_->Branch("tau_hwEta",              &tau_hwEta_);
  tree_->Branch("tau_hwPhi",              &tau_hwPhi_);
  tree_->Branch("tau_hwIso",              &tau_hwIso_);

  tree_->Branch("sum_bx",                 &sum_bx_);
  tree_->Branch("sum_hwTotalEt",          &sum_hwTotalEt_);
  tree_->Branch("sum_hwTotalEtEm",        &sum_hwTotalEtEm_);
  tree_->Branch("sum_hwTotalHt",          &sum_hwTotalHt_);
  tree_->Branch("sum_hwMissEt",           &sum_hwMissEt_);
  tree_->Branch("sum_hwMissEtPhi",        &sum_hwMissEtPhi_);
  tree_->Branch("sum_hwMissHt",           &sum_hwMissHt_);
  tree_->Branch("sum_hwMissHtPhi",        &sum_hwMissHtPhi_);
  tree_->Branch("sum_hwMissEtHF",         &sum_hwMissEtHF_);
  tree_->Branch("sum_hwMissEtHFPhi",      &sum_hwMissEtHFPhi_);
  tree_->Branch("sum_hwMissHtHF",         &sum_hwMissHtHF_);
  tree_->Branch("sum_hwMissHtHFPhi",      &sum_hwMissHtHFPhi_);
  tree_->Branch("sum_hwAsymEt",           &sum_hwAsymEt_);
  tree_->Branch("sum_hwAsymHt",           &sum_hwAsymHt_);
  tree_->Branch("sum_hwAsymEtHF",         &sum_hwAsymEtHF_);
  tree_->Branch("sum_hwAsymHtHF",         &sum_hwAsymHtHF_);
  tree_->Branch("sum_minBiasHFP0",        &sum_minBiasHFP0_);
  tree_->Branch("sum_minBiasHFM0",        &sum_minBiasHFM0_);
  tree_->Branch("sum_minBiasHFP1",        &sum_minBiasHFP1_);
  tree_->Branch("sum_minBiasHFM1",        &sum_minBiasHFM1_);
  tree_->Branch("sum_towerCount",         &sum_towerCount_);
  tree_->Branch("sum_centrality",         &sum_centrality_);

  tree_->Branch("bmtf_bx",                &bmtf_bx_);
  tree_->Branch("bmtf_hwPhi",             &bmtf_hwPhi_);
  tree_->Branch("bmtf_hwPhiB",            &bmtf_hwPhiB_);
  tree_->Branch("bmtf_hwQual",            &bmtf_hwQual_);
  tree_->Branch("bmtf_hwEta",             &bmtf_hwEta_);
  tree_->Branch("bmtf_hwQEta",            &bmtf_hwQEta_);
  tree_->Branch("bmtf_station",           &bmtf_station_);
  tree_->Branch("bmtf_wheel",             &bmtf_wheel_);
  tree_->Branch("bmtf_sector",            &bmtf_sector_);
  tree_->Branch("bmtf_tag",               &bmtf_tag_);
}

void L1ScoutingOrbitNtupleizer::clearVectors() {
  mu_bx_.clear();
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

  jet_bx_.clear();
  jet_hwEt_.clear();
  jet_hwEta_.clear();
  jet_hwPhi_.clear();
  jet_hwQual_.clear();

  eg_bx_.clear();
  eg_hwEt_.clear();
  eg_hwEta_.clear();
  eg_hwPhi_.clear();
  eg_hwIso_.clear();

  tau_bx_.clear();
  tau_hwEt_.clear();
  tau_hwEta_.clear();
  tau_hwPhi_.clear();
  tau_hwIso_.clear();

  sum_bx_.clear();
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

  bmtf_bx_.clear();
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
  run_   = iEvent.id().run();
  lumi_  = iEvent.luminosityBlock();
  event_ = iEvent.id().event();

  clearVectors();

  if (saveMuons_) {
    edm::Handle<MuonOrbit> h;
    iEvent.getByToken(muToken_, h);
    if (h.isValid()) {
      for (unsigned bx : h->getFilledBxs()) {
        for (unsigned i = 0; i < h->getBxSize(bx); ++i) {
          const auto& mu = h->getBxObject(bx, i);
          mu_bx_.push_back(static_cast<int>(bx));
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
        }
      }
    }
  }

  if (saveJets_) {
    edm::Handle<JetOrbit> h;
    iEvent.getByToken(jetToken_, h);
    if (h.isValid()) {
      for (unsigned bx : h->getFilledBxs()) {
        for (unsigned i = 0; i < h->getBxSize(bx); ++i) {
          const auto& jet = h->getBxObject(bx, i);
          jet_bx_.push_back(static_cast<int>(bx));
          jet_hwEt_.push_back(jet.hwEt());
          jet_hwEta_.push_back(jet.hwEta());
          jet_hwPhi_.push_back(jet.hwPhi());
          jet_hwQual_.push_back(jet.hwQual());
        }
      }
    }
  }

  if (saveEGammas_) {
    edm::Handle<EGammaOrbit> h;
    iEvent.getByToken(egToken_, h);
    if (h.isValid()) {
      for (unsigned bx : h->getFilledBxs()) {
        for (unsigned i = 0; i < h->getBxSize(bx); ++i) {
          const auto& eg = h->getBxObject(bx, i);
          eg_bx_.push_back(static_cast<int>(bx));
          eg_hwEt_.push_back(eg.hwEt());
          eg_hwEta_.push_back(eg.hwEta());
          eg_hwPhi_.push_back(eg.hwPhi());
          eg_hwIso_.push_back(eg.hwIso());
        }
      }
    }
  }

  if (saveTaus_) {
    edm::Handle<TauOrbit> h;
    iEvent.getByToken(tauToken_, h);
    if (h.isValid()) {
      for (unsigned bx : h->getFilledBxs()) {
        for (unsigned i = 0; i < h->getBxSize(bx); ++i) {
          const auto& tau = h->getBxObject(bx, i);
          tau_bx_.push_back(static_cast<int>(bx));
          tau_hwEt_.push_back(tau.hwEt());
          tau_hwEta_.push_back(tau.hwEta());
          tau_hwPhi_.push_back(tau.hwPhi());
          tau_hwIso_.push_back(tau.hwIso());
        }
      }
    }
  }

  if (saveEtSums_) {
    edm::Handle<EtSumOrbit> h;
    iEvent.getByToken(sumToken_, h);
    if (h.isValid()) {
      for (unsigned bx : h->getFilledBxs()) {
        for (unsigned i = 0; i < h->getBxSize(bx); ++i) {
          const auto& s = h->getBxObject(bx, i);
          sum_bx_.push_back(static_cast<int>(bx));
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
        }
      }
    }
  }

  if (saveBmtf_) {
    edm::Handle<BMTFStubOrbit> h;
    iEvent.getByToken(bmtfToken_, h);
    if (h.isValid()) {
      for (unsigned bx : h->getFilledBxs()) {
        for (unsigned i = 0; i < h->getBxSize(bx); ++i) {
          const auto& s = h->getBxObject(bx, i);
          bmtf_bx_.push_back(static_cast<int>(bx));
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
      }
    }
  }

  tree_->Fill();
}

DEFINE_FWK_MODULE(L1ScoutingOrbitNtupleizer);
