import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing("analysis")
options.outputFile = "l1scouting_ntuple.root"
options.maxEvents = -1
options.parseArguments()

process = cms.Process("NTUPLE")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

process.source = cms.Source(
    "PoolSource",
    fileNames = cms.untracked.vstring(options.inputFiles)
)

process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string(options.outputFile)
)

process.l1ntuplizer = cms.EDAnalyzer(
    "L1ScoutingOrbitNtupleizer",

    muons    = cms.InputTag("l1ScGmtUnpacker",  "Muon",     "SCHLP"),
    jets     = cms.InputTag("l1ScCaloUnpacker", "Jet",      "SCHLP"),
    egammas  = cms.InputTag("l1ScCaloUnpacker", "EGamma",   "SCHLP"),
    taus     = cms.InputTag("l1ScCaloUnpacker", "Tau",      "SCHLP"),
    etsums   = cms.InputTag("l1ScCaloUnpacker", "EtSum",    "SCHLP"),
    bmtfstub = cms.InputTag("l1ScBMTFUnpacker", "BMTFStub", "SCHLP"),

    saveMuons   = cms.bool(True),
    saveJets    = cms.bool(True),
    saveEGammas = cms.bool(True),
    saveTaus    = cms.bool(True),
    saveEtSums  = cms.bool(True),
    saveBmtf    = cms.bool(True),
)

process.p = cms.Path(process.l1ntuplizer)
