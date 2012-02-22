import FWCore.ParameterSet.Config as cms

process = cms.Process("KinFit")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

#input stuff for Run/Lumi selection with the "JSON"-formatted files from the PVT group
import FWCore.PythonUtilities.LumiList as LumiList


## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )


###############################
####### Parameters ############
###############################
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('python')

## options.register ('useFlavorHistory',
##                   0,
##                   VarParsing.multiplicity.singleton,
##                   VarParsing.varType.int,
##                   "Flavor History Mode")

options.register ('doMC',
                  0,
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.int,
                  "Use MC truth")

options.register ('sampleNameInput',
                  'top',
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.string,
                  "Sample name to give histograms")

options.register ('outputRootFile',
                  'shyftStudies.root',
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.string,
                  "Output root file name")

options.register('ignoreTrigger',
                 0,
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.int,
                  "Ignore trigger in selection")

options.register('triggerName',
                 'HLT_Ele27_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v1',
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.string,
                 "Electron trigger to run")

options.register('eleEt',
                  30.,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.float,
                 "electron et threshold")

options.register('runLoose',
                 0,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.int,
                 "Run extra sequence(1) for loose selction or ignore them (0)")

options.parseArguments()

print options

import sys

if options.doMC > 0 :
    inputDoMC = True
else :
    inputDoMC = False
   
inputSampleName = options.sampleNameInput

inputCutsToIgnore = []
if options.ignoreTrigger == 1 :
    inputCutsToIgnore.append( 'Trigger' )

## Source
if len(options.inputFiles) == 0 :
    process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
        '/store/user/lpctlbsm/vasquez/SingleElectron/ttbsm_v9_Run2011A-May10ReReco/f8e845a0332c56398831da6c30999af1/ttbsm_42x_data_1_1_wlr.root'
        )
                                )
payloads = [
    'Jec12_V1_L1FastJet_AK5PFchs.txt',
    'Jec12_V1_L2Relative_AK5PFchs.txt',
    'Jec12_V1_L3Absolute_AK5PFchs.txt',
    'Jec12_V1_L2L3Residual_AK5PFchs.txt',
    'Jec12_V1_Uncertainty_AK5PFchs.txt',    
]    
## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'GR_R_42_V12::All'
process.load("Configuration.StandardSequences.MagneticField_cff")

# run the trigger on the fly
process.load('PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff')


from Analysis.SHyFT.shyftAnalysis_cfi import shyftAnalysis as inputShyftAnalysis


process.pfShyftSkim =  cms.EDFilter('EDWPlusJetsSelector',
                                    inputShyftAnalysis.clone(
    muonSrc = cms.InputTag('selectedPatMuonsPFlow'),
    electronSrc = cms.InputTag('selectedPatElectronsPFlow'),
    metSrc = cms.InputTag('patMETsPFlow'),
    jetSrc = cms.InputTag('goodPatJetsPFlow'),
    pvSrc   = cms.InputTag('goodOfflinePrimaryVertices'),
    ePlusJets = cms.bool( True ),
    muPlusJets = cms.bool( False ),
    eleTrig = cms.string(options.triggerName),      
    usePFIso = cms.bool(True),
    useVBTFDetIso  = cms.bool(False),
    eEtCut = cms.double(options.eleEt),
    jetPtMin = cms.double(35.0),##
    minJets = cms.int32(4),
    metMin = cms.double(0.0),
    reweightPU = cms.bool(False),
    useData = cms.bool( not inputDoMC ),
    doMC = cms.bool( inputDoMC),
    sampleName = cms.string(inputSampleName),
    cutsToIgnore=cms.vstring(inputCutsToIgnore),
    identifier = cms.string('PF'),
    jecPayloads = cms.vstring( payloads )
    )
                                    )

############################
## adding KinFitter stuff
############################

from TopQuarkAnalysis.TopObjectResolutions.stringResolutions_etEtaPhi_cff import *

# original version /TopQuarkAnalysis/TopKinFitter/python/TtSemiLepKinFitProducer_Electrons_cfi.py
process.kinFitTtSemiLepEventTCHEM = cms.EDProducer("TtSemiLepKinFitProducerElectron",
    jets = cms.InputTag("pfShyftSkim:jets"),
    leps = cms.InputTag("pfShyftSkim:electrons"),
    mets = cms.InputTag("pfShyftSkim:met"),

    # ------------------------------------------------
    # maximum number of jets to be considered in the
    # jet combinatorics (has to be >= 4, can be set to
    # -1 if you want to take all)
    # ------------------------------------------------
    maxNJets = cms.int32(5),

    #-------------------------------------------------
    # maximum number of jet combinations finally
    # written into the event, starting from the "best"
    # (has to be >= 1, can be set to -1 if you want to 
    # take all)
    #-------------------------------------------------
    maxNComb = cms.int32(2),

    # ------------------------------------------------
    # option to take only a given jet combination
    # instead of going through the full combinatorics
    # ------------------------------------------------
    match = cms.InputTag(""),
    useOnlyMatch = cms.bool(False),

    # ------------------------------------------------
    # option to use b-tagging
    # ------------------------------------------------
    bTagAlgo          = cms.string("trackCountingHighEffBJetTags"),
    minBDiscBJets     = cms.double(3.3),
    maxBDiscLightJets = cms.double(3.3),
    useBTagging       = cms.bool(True),

    # ------------------------------------------------
    # settings for the KinFitter
    # ------------------------------------------------    
    maxNrIter = cms.uint32(500),
    maxDeltaS = cms.double(5e-05),
    maxF      = cms.double(0.0001),                                        
    # ------------------------------------------------
    # select parametrisation
    # 0: EMom, 1: EtEtaPhi, 2: EtThetaPhi
    # ------------------------------------------------
    jetParametrisation = cms.uint32(1),
    lepParametrisation = cms.uint32(1),
    metParametrisation = cms.uint32(1),

    jetEnergyResolutionSmearFactor = cms.double(1.0),
    # ------------------------------------------------
    # set constraints
    # 1: Whad-mass, 2: Wlep-mass, 3: thad-mass,
    # 4: tlep-mass, 5: nu-mass, 6: equal t-masses,
    # by default: Px conservation and Py conservation
    # ------------------------------------------------                                   
    constraints = cms.vuint32(1, 2, 6),

    # ------------------------------------------------
    # set mass values used in the constraints
    # ------------------------------------------------    
    mW   = cms.double(80.4),
    mTop = cms.double(173.),

    # using new object resolutions
    udscResolutions             = udscResolutionPF.functions,
    bResolutions                = bjetResolutionPF.functions,
    lepResolutions              = elecResolution.functions,
    metResolutions              = metResolutionPF.functions,
                                                   )

process.tprimeNtupleDumperTCHEM = cms.EDProducer("TprimeNtupleDumper",
    do_MC = cms.bool(False),
    resonanceId = cms.int32(6),                                              
    kinFitterLabel = cms.string("kinFitTtSemiLepEventTCHEM"),
    selectorLabel  = cms.string("pfShyftSkim"),
                                            )
# add pure min Chi2 and TCHE b-taggers for comparison
process.kinFitTtSemiLepEventCHI2 = process.kinFitTtSemiLepEventTCHEM.clone()
process.kinFitTtSemiLepEventCHI2.useBTagging = False

process.tprimeNtupleDumperCHI2 = process.tprimeNtupleDumperTCHEM.clone()
process.tprimeNtupleDumperCHI2.kinFitterLabel = cms.string("kinFitTtSemiLepEventCHI2")

process.kinFitTtSemiLepEventCSVM = process.kinFitTtSemiLepEventTCHEM.clone()
process.kinFitTtSemiLepEventCSVM.useBTagging = True
process.kinFitTtSemiLepEventCSVM.bTagAlgo = "combinedSecondaryVertexBJetTags"
process.kinFitTtSemiLepEventCSVM.minBDiscBJets = 0.679
process.kinFitTtSemiLepEventCSVM.maxBDiscLightJets = 0.679

process.tprimeNtupleDumperCSVM = process.tprimeNtupleDumperTCHEM.clone()
process.tprimeNtupleDumperCSVM.kinFitterLabel = cms.string("kinFitTtSemiLepEventCSVM")

## process.kinFitTtSemiLepEventSSVHEM = process.kinFitTtSemiLepEventTCHEM.clone()
## process.kinFitTtSemiLepEventSSVHEM.useBTagging = True
## process.kinFitTtSemiLepEventSSVHEM.bTagAlgo = "simpleSecondaryVertexHighEffBJetTags"
## process.kinFitTtSemiLepEventSSVHEM.minBDiscBJets = 1.74
## process.kinFitTtSemiLepEventSSVHEM.maxBDiscLightJets = 1.74

## process.tprimeNtupleDumperSSVHEM = process.tprimeNtupleDumperTCHEM.clone()
## process.tprimeNtupleDumperSSVHEM.kinFitterLabel = cms.string("kinFitTtSemiLepEventSSVHEM")


process.p = cms.Path(
    process.patTriggerDefaultSequence*
    process.pfShyftSkim*
    (process.kinFitTtSemiLepEventCHI2 * process.tprimeNtupleDumperCHI2 +
     process.kinFitTtSemiLepEventTCHEM * process.tprimeNtupleDumperTCHEM +
     process.kinFitTtSemiLepEventCSVM * process.tprimeNtupleDumperCSVM)
#    process.kinFitTtSemiLepEventSSVHEM * process.tprimeNtupleDumperSSVHEM)
    )

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    SelectEvents   = cms.untracked.PSet(SelectEvents = cms.vstring('p') ),                               
    fileName = cms.untracked.string('ttTest.root'),
    outputCommands = cms.untracked.vstring('drop *')
)
process.out.outputCommands += ['keep *_kinFitTtSemiLepEvent*_*_*',
                               'keep *_pfShyftSkim*_*_*',
                               'keep *_tprimeNtupleDumper*_*_*',
                               'keep PileupSummaryInfos_*_*_*',
                               'keep *_goodOfflinePrimaryVertices_*_*',
                               'keep *_patTriggerEvent_*_*',
                               'keep *_patTrigger_*_*'
                               ]

## output path
process.outpath = cms.EndPath(process.out)

#suppress the L1 trigger error messages
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.suppressWarning.append('patTrigger')
process.MessageLogger.cerr.FwkJob.limit=1
process.MessageLogger.cerr.ERROR = cms.untracked.PSet( limit =
cms.untracked.int32(0) )
