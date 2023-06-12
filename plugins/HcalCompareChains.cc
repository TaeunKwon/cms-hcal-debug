// -*- C++ -*-
//
// Package:    HcalCompareLegacyChains
// Class:      HcalCompareLegacyChains
// 
/**\class HcalCompareLegacyChains HcalCompareLegacyChains.cc HcalDebug/CompareChans/src/HcalCompareLegacyChains.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  matthias wolf
//         Created:  Fri Aug 26 11:37:21 CDT 2013
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/ModuleFactory.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "CondFormats/DataRecord/interface/HcalChannelQualityRcd.h"

#include "CalibFormats/CaloTPG/interface/CaloTPGTranscoder.h"
#include "CalibFormats/CaloTPG/interface/CaloTPGRecord.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"

// EDM formats
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalDigi/interface/HcalTriggerPrimitiveDigi.h"
#include "DataFormats/HcalDetId/interface/HcalTrigTowerDetId.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/HcalRecHit/interface/HBHERecHit.h"
#include "DataFormats/HcalRecHit/interface/HFRecHit.h"

#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/HcalTowerAlgo/interface/HcalGeometry.h"
#include "Geometry/HcalCommonData/interface/HcalDDDRecConstants.h"
#include "Geometry/HcalTowerAlgo/interface/HcalTrigTowerGeometry.h"
#include "Geometry/Records/interface/HcalGeometryRecord.h"
#include "Geometry/Records/interface/HcalRecNumberingRecord.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "Geometry/HcalTowerAlgo/interface/HcalFlexiHardcodeGeometryLoader.h"
#include "Geometry/HcalTowerAlgo/interface/HcalHardcodeGeometryLoader.h"

#include "RecoLocalCalo/HcalRecAlgos/interface/HcalSeverityLevelComputer.h"
#include "RecoLocalCalo/HcalRecAlgos/interface/HcalSeverityLevelComputerRcd.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TString.h"
#include "TTree.h"
//
// class declaration
//

class HcalCompareChains : public edm::EDAnalyzer {
   public:
      explicit HcalCompareChains(const edm::ParameterSet&);
      ~HcalCompareChains();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void beginLuminosityBlock(const edm::LuminosityBlock&, const edm::EventSetup&) override;

      double get_cosh(const HcalDetId&, const CaloGeometry &gen_geo);

      // ----------member data ---------------------------
      bool first_;

      std::vector<edm::InputTag> frames_;
      edm::InputTag digis_hw_;
      edm::InputTag digis_emu_;
      std::vector<edm::InputTag> rechits_;

//      edm::ESHandle<CaloGeometry> gen_geo_;

      bool swap_iphi_;

      TH2D *df_multiplicity_;
      TH2D *tp_multiplicity_;

      TTree *tps_;
      TTree *events_;
      TTree *matches_;

      int run_;
      int evt_;
      int ls_;

      int mt_run_;
      int mt_evt_;
      int mt_ls_;

      double tp_energy_hw_;
      int tp_soi_hw_;
      double tp_energy_emu_;
      int tp_soi_emu_;
      int tp_ieta_;
      int tp_iphi_;

      double ev_rh_energy0_;
      double ev_rh_energy2_;
      double ev_rh_energy3_;
      double ev_tp_energy_;
      int ev_rh_unmatched_;
      int ev_tp_unmatched_;
      int ev_nVtx_;

      double mt_rh_energy0_;
      double mt_rh_energy2_;
      double mt_rh_energy3_;
      double mt_tp_energy_;
      double mt_nVtx_;

      int mt_ieta_;
      int mt_iphi_;
      int mt_version_;
      int mt_tp_soi_;

      int max_severity_;

      edm::ESGetToken<HcalChannelQuality, HcalChannelQualityRcd> statusToken_;
      edm::ESGetToken<HcalSeverityLevelComputer, HcalSeverityLevelComputerRcd> compToken_;
      edm::ESGetToken<CaloGeometry, CaloGeometryRecord> gen_geoToken_;
      edm::ESGetToken<HcalTopology, HcalRecNumberingRecord> tok_htopo_;
      edm::ESGetToken<HcalDDDRecConstants, HcalRecNumberingRecord> tok_ddrec_;
      edm::ESGetToken<CaloTPGTranscoder, CaloTPGRecord> caloTPGToken_;
      edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
//      edm::ESGetToken<HcalTrigTowerGeometry, CaloGeometryRecord> tpd_geo_h_Token_;

      unsigned int maxVtx_;

      const HcalChannelQuality* status_;
      const HcalSeverityLevelComputer* comp_;
};

HcalCompareChains::HcalCompareChains(const edm::ParameterSet& config) :
   edm::EDAnalyzer(),
   first_(true),
   frames_(config.getParameter<std::vector<edm::InputTag>>("dataFrames")),
   digis_hw_(config.getParameter<edm::InputTag>("triggerPrimitives_hw")),
   digis_emu_(config.getParameter<edm::InputTag>("triggerPrimitives_emu")),
   rechits_(config.getParameter<std::vector<edm::InputTag>>("recHits")),
   swap_iphi_(config.getParameter<bool>("swapIphi")),
   max_severity_(config.getParameter<int>("maxSeverity")),
   statusToken_(esConsumes<HcalChannelQuality, HcalChannelQualityRcd, edm::Transition::BeginLuminosityBlock>()),
   compToken_(esConsumes<HcalSeverityLevelComputer, HcalSeverityLevelComputerRcd, edm::Transition::BeginLuminosityBlock>()),
   gen_geoToken_(esConsumes<CaloGeometry, CaloGeometryRecord>()),
   tok_htopo_(esConsumes<HcalTopology, HcalRecNumberingRecord>(edm::ESInputTag{})),
   tok_ddrec_(esConsumes<HcalDDDRecConstants, HcalRecNumberingRecord>()),
   caloTPGToken_(esConsumes<CaloTPGTranscoder, CaloTPGRecord>())
//   tpd_geo_h_Token_(esConsumes<HcalTrigTowerGeometry, CaloGeometryRecord>())
{
   consumes<HcalTrigPrimDigiCollection>(digis_hw_);
   consumes<HcalTrigPrimDigiCollection>(digis_emu_);
   consumes<HBHEDigiCollection>(frames_[0]);
   consumes<HFDigiCollection>(frames_[1]);
   consumes<edm::SortedCollection<HBHERecHit>>(rechits_[0]);
   consumes<edm::SortedCollection<HFRecHit>>(rechits_[1]);

   vtxToken_ = consumes<reco::VertexCollection>(
      config.getUntrackedParameter("vtxToken", edm::InputTag("offlinePrimaryVertices")));
   maxVtx_ = config.getParameter<unsigned int>("maxVtx");

   edm::Service<TFileService> fs;

   df_multiplicity_ = fs->make<TH2D>("df_multiplicity", "DataFrame multiplicity;ieta;iphi", 65, -32.5, 32.5, 72, 0.5, 72.5);
   tp_multiplicity_ = fs->make<TH2D>("tp_multiplicity", "TrigPrim multiplicity;ieta;iphi", 65, -32.5, 32.5, 72, 0.5, 72.5);

   tps_ = fs->make<TTree>("tps", "Trigger primitives hardware");
   tps_->Branch("et_hw", &tp_energy_hw_);
   tps_->Branch("soi_hw", &tp_soi_hw_);
   tps_->Branch("et_emu", &tp_energy_emu_);
   tps_->Branch("soi_emu", &tp_soi_emu_);
   tps_->Branch("ieta", &tp_ieta_);
   tps_->Branch("iphi", &tp_iphi_);

   events_ = fs->make<TTree>("events", "Event quantities");
   events_->Branch("run", &run_, "run/I");
   events_->Branch("evt", &evt_, "evt/I");
   events_->Branch("ls", &ls_, "ls/I");
   events_->Branch("RH_energyM0", &ev_rh_energy0_);
   events_->Branch("RH_energyM2", &ev_rh_energy2_);
   events_->Branch("RH_energyM3", &ev_rh_energy3_);
   events_->Branch("TP_energy", &ev_tp_energy_);
   events_->Branch("RH_unmatched", &ev_rh_unmatched_);
   events_->Branch("TP_unmatched", &ev_tp_unmatched_);
   events_->Branch("nVtx", &ev_nVtx_);

   matches_ = fs->make<TTree>("matches", "Matched RH and TP");
   matches_->Branch("RH_energyM0", &mt_rh_energy0_);
   matches_->Branch("RH_energyM2", &mt_rh_energy2_);
   matches_->Branch("RH_energyM3", &mt_rh_energy3_);
   matches_->Branch("TP_energy", &mt_tp_energy_);
   matches_->Branch("nVtx", &mt_nVtx_);
   matches_->Branch("run", &mt_run_, "run/I");
   matches_->Branch("evt", &mt_evt_, "evt/I");
   matches_->Branch("ls", &mt_ls_, "ls/I");
   matches_->Branch("ieta", &mt_ieta_);
   matches_->Branch("iphi", &mt_iphi_);
   matches_->Branch("tp_version", &mt_version_);
   matches_->Branch("tp_soi", &mt_tp_soi_);
}

HcalCompareChains::~HcalCompareChains() {}

double
HcalCompareChains::get_cosh(const HcalDetId& id, const CaloGeometry &gen_geo)
{
   const auto *sub_geo = dynamic_cast<const HcalGeometry*>(gen_geo.getSubdetectorGeometry(id));
   auto eta = sub_geo->getPosition(id).eta();
   return cosh(eta);
}

void
HcalCompareChains::beginLuminosityBlock(const edm::LuminosityBlock& lumi, const edm::EventSetup& setup)
{

   status_ = &setup.getData(statusToken_);
   comp_ = &setup.getData(compToken_);

}

void
HcalCompareChains::analyze(const edm::Event& event, const edm::EventSetup& setup)
{
   using namespace edm;

//   edm::ESHandle<HcalTrigTowerGeometry> tpd_geo_h;
//   setup.get<CaloGeometryRecord>().get(tpd_geo_h);
//   edm::ESHandle<HcalDbService> conditions;
//   setup.get<HcalDbRecord>().get(conditions);
//   const HcalTrigTowerGeometry& tpd_geo = *tpd_geo_h;
   const HcalDDDRecConstants hcons = setup.getData(tok_ddrec_);
   const HcalTopology topology = setup.getData(tok_htopo_);

   HcalTrigTowerGeometry tpd_geo(&topology);

  run_ = event.id().run();
  evt_ = event.id().event();
  ls_ = event.id().luminosityBlock();

//   const HcalTrigTowerGeometry &tpd_geo = HcalTrigTowerGeometryESProducer::produce(setup.get<CaloGeometryRecord>());

   // ==========
   // Dataframes
   // ==========

   // get vertices
   edm::Handle<reco::VertexCollection> vertices;
   event.getByToken(vtxToken_, vertices);

  int nVtx = 0;

  if (vertices.isValid()) {
    for (reco::VertexCollection::const_iterator it = vertices->begin();
         it != vertices->end() && nVtx < (int) maxVtx_;
         ++it) {
      if (!it->isFake()) {
        ++nVtx;
      }
    }
  }

  ev_nVtx_ = nVtx;

   Handle<HBHEDigiCollection> frames;
   Handle<HFDigiCollection> hfframes;
   if (frames_.size() == 2) {
      if (first_ && event.getByLabel(frames_[0], frames) && event.getByLabel(frames_[1], hfframes)) {
         std::set<HcalTrigTowerDetId> ids;

         for (const auto& frame: *(frames.product())) {
            auto mapped = tpd_geo.towerIds(frame.id());

            for (const auto& id: mapped) {
               df_multiplicity_->Fill(id.ieta(), id.iphi());
               ids.insert(id);
            }
         }

         for (const auto& frame: *(hfframes.product())) {
            auto mapped = tpd_geo.towerIds(frame.id());

            for (const auto& id: mapped) {
               df_multiplicity_->Fill(id.ieta(), id.iphi());
               ids.insert(id);
            }
         }

         for (const auto& id: ids) {
            tp_multiplicity_->Fill(id.ieta(), id.iphi());
         }

         first_ = false;
      }
   }

   // ==============
   // Matching stuff
   // ==============

   ev_rh_energy0_ = 0.;
   ev_rh_energy2_ = 0.;
   ev_rh_energy3_ = 0.;
   ev_rh_unmatched_ = 0.;
   ev_tp_energy_ = 0.;
   ev_tp_unmatched_ = 0.;

   std::map<HcalTrigTowerDetId, std::vector<HBHERecHit>> rhits;
   std::map<HcalTrigTowerDetId, std::vector<HFRecHit>> fhits;
   std::map<HcalTrigTowerDetId, std::vector<HcalTriggerPrimitiveDigi>> tpdigis_hw;
   std::map<HcalTrigTowerDetId, std::vector<HcalTriggerPrimitiveDigi>> tpdigis_emu;

   Handle<HcalTrigPrimDigiCollection> digis_hw;
   if (!event.getByLabel(digis_hw_, digis_hw)) {
      LogError("HcalTrigPrimDigiCleaner") <<
         "Can't find hcal trigger primitive digi collection with tag hcalDigis'" <<
         digis_hw_ << "'" << std::endl;
      return;
   }

   Handle<HcalTrigPrimDigiCollection> digis_emu;
   if (!event.getByLabel(digis_emu_, digis_emu)) {
      LogError("HcalTrigPrimDigiCleaner") <<
         "Can't find hcal trigger primitive digi collection with tag hcalDigis'" <<
         digis_emu_ << "'" << std::endl;
      return;
   }

   edm::Handle< edm::SortedCollection<HBHERecHit> > hits;
   if (!event.getByLabel(rechits_[0], hits)) {
      edm::LogError("HcalCompareLegacyChains") <<
         "Can't find rec hit collection with tag '" << rechits_[0] << "'" << std::endl;
      /* return; */
   }

   edm::Handle< edm::SortedCollection<HFRecHit> > hfhits;
   if (!event.getByLabel(rechits_[1], hfhits)) {
      edm::LogError("HcalCompareLegacyChains") <<
         "Can't find rec hit collection with tag '" << rechits_[1] << "'" << std::endl;
      /* return; */
   }

   const CaloGeometry gen_geo = setup.getData(gen_geoToken_);
//   setup.get<CaloGeometryRecord>().get(gen_geo_);


/*   auto isValid = [&](const auto& hit) {
      HcalDetId id(hit.id());
      auto s = status_->getValues(id);
      int level = comp_->getSeverityLevel(id, 0, s->getValue());
      return level <= max_severity_;
   };
*/
   if (hits.isValid()) {

      for (auto& hit: *(hits.product())) {

         HcalDetId id(hit.id());

//         if (not isValid(hit))
//            continue;

         ev_rh_energy0_ += hit.eraw() / get_cosh(id, gen_geo);
         ev_rh_energy2_ += hit.energy() / get_cosh(id, gen_geo);
         ev_rh_energy3_ += hit.eaux() / get_cosh(id, gen_geo);
         auto tower_ids = tpd_geo.towerIds(id);
         for (auto& tower_id: tower_ids) {
            tower_id = HcalTrigTowerDetId(tower_id.ieta(), tower_id.iphi(), 1);
            rhits[tower_id].push_back(hit);
         }
      }
   }


   if (hfhits.isValid()) {
      for (auto& hit: *(hfhits.product())) {
         HcalDetId id(hit.id());
//         if (not isValid(hit))
//            continue;
         ev_rh_energy0_ += hit.energy() / get_cosh(id, gen_geo);
         ev_rh_energy2_ += hit.energy() / get_cosh(id, gen_geo);
         ev_rh_energy3_ += hit.energy() / get_cosh(id, gen_geo);

         auto tower_ids = tpd_geo.towerIds(id);
         for (auto& tower_id: tower_ids) {
            tower_id = HcalTrigTowerDetId(tower_id.ieta(), tower_id.iphi(), 1, tower_id.version());
            fhits[tower_id].push_back(hit);
         }
      }
   }

   // ESHandle<L1CaloHcalScale> hcal_scale;
   // setup.get<L1CaloHcalScaleRcd>().get(hcal_scale);
   // const L1CaloHcalScale* h = hcal_scale.product();

   ESHandle<CaloTPGTranscoder> decoder = setup.getHandle(caloTPGToken_);
//   setup.get<CaloTPGRecord>().get(decoder);

//   const CaloTPGTranscoder *decoder = &setup.getData(caloTPGToken_);

   for (const auto& digi: *digis_hw) {
      HcalTrigTowerDetId id = digi.id();
      id = HcalTrigTowerDetId(id.ieta(), id.iphi(), 1, id.version());

      tp_energy_emu_ = 0;
      tp_soi_emu_ = 0;

      for (const auto& digi_emu: *digis_emu) {
        HcalTrigTowerDetId id_emu = digi_emu.id();
        id_emu = HcalTrigTowerDetId(id_emu.ieta(), id_emu.iphi(), 1, id_emu.version());

        if (id == id_emu){
          tp_energy_emu_ = decoder->hcaletValue(id, digi_emu.t0());
          tp_soi_emu_ = digi_emu.SOI_compressedEt(); 
          tpdigis_emu[id].push_back(digi_emu);
          break;
        }
      }
//      if (tp_energy_emu_ != 0) std::cout<<"PFA1' & PFA2 matched!"<<std::endl;

      ev_tp_energy_ += decoder->hcaletValue(id, digi.t0());

      tpdigis_hw[id].push_back(digi);

      tp_energy_hw_ = decoder->hcaletValue(id, digi.t0());
      tp_soi_hw_ = digi.SOI_compressedEt();

      tp_ieta_ = id.ieta();
      tp_iphi_ = id.iphi();


      tps_->Fill();
   }

   for (const auto& pair: tpdigis_hw) {
      auto id = pair.first;

      auto new_id(id);
      if (swap_iphi_ and id.version() == 1 and id.ieta() > 28 and id.ieta() < 40) {
         if (id.iphi() % 4 == 1)
            new_id = HcalTrigTowerDetId(id.ieta(), (id.iphi() + 70) % 72, id.depth(), id.version());
         else
            new_id = HcalTrigTowerDetId(id.ieta(), (id.iphi() + 2) % 72 , id.depth(), id.version());
      }

      auto rh = rhits.find(new_id);
      auto fh = fhits.find(new_id);

      if (rh != rhits.end() and fh != fhits.end()) {
         assert(0);
      }

      mt_ieta_ = new_id.ieta();
      mt_iphi_ = new_id.iphi();
      mt_version_ = new_id.version();
      mt_tp_energy_ = 0;
      mt_tp_soi_ = 0;

      for (const auto& tp: pair.second) {
         mt_tp_energy_ += decoder->hcaletValue(new_id, tp.t0());
         mt_tp_soi_ = tp.SOI_compressedEt();
      }
      mt_rh_energy0_ = 0.;
      mt_rh_energy2_ = 0.;
      mt_rh_energy3_ = 0.;
      mt_nVtx_ = 0;
      mt_run_ = -1;
      mt_evt_ = -1;
      mt_ls_ = -1;

      if (rh != rhits.end()) {
         for (const auto& hit: rh->second) {
            HcalDetId id(hit.id());

            if (abs(hit.id().ieta()) == 16 && hit.id().depth() == 4) continue;
            auto tower_ids = tpd_geo.towerIds(id);
            auto count = std::count_if(std::begin(tower_ids), std::end(tower_ids),
                  [&](const auto& t) { return t.version() == new_id.version(); });
            mt_rh_energy0_ += hit.eraw() / get_cosh(id, gen_geo) / count;
            mt_rh_energy2_ += hit.energy() / get_cosh(id, gen_geo) / count;
            mt_rh_energy3_ += hit.eaux() / get_cosh(id, gen_geo) / count;
         }
         mt_nVtx_ = nVtx;
         mt_run_ = run_;
         mt_evt_ = evt_;
         mt_ls_ = ls_;

         matches_->Fill();
         rhits.erase(rh);
      } else if (fh != fhits.end()) {
         for (const auto& hit: fh->second) {
            HcalDetId id(hit.id());

            if (abs(hit.id().ieta()) == 16 && hit.id().depth() == 4) continue;
            auto tower_ids = tpd_geo.towerIds(id);
            auto count = std::count_if(std::begin(tower_ids), std::end(tower_ids),
                  [&](const auto& t) { return t.version() == new_id.version(); });
            mt_rh_energy0_ += hit.energy() / get_cosh(id, gen_geo) / count;
            mt_rh_energy2_ += hit.energy() / get_cosh(id, gen_geo) / count;
            mt_rh_energy3_ += hit.energy() / get_cosh(id, gen_geo) / count;
         }
         mt_nVtx_ = nVtx;
         mt_run_ = run_;
         mt_evt_ = evt_;
         mt_ls_ = ls_;

         matches_->Fill();
         fhits.erase(fh);
      } else {
         ++ev_tp_unmatched_;
      }
   }

   for (const auto& pair: rhits) {
      ev_rh_unmatched_ += pair.second.size();
   }

   events_->Fill();
}

void
HcalCompareChains::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HcalCompareChains);
