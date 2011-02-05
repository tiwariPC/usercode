import FWCore.ParameterSet.Config as cms

process = cms.Process("ANA")

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

options.register ('useFlavorHistory',
                  0,
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.int,
                  "Flavor History Mode")

options.register('sampleNameInput',
                 'top',
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.string,
                 "Sample name to give histograms")

options.register ('allSys',
                  1,
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.int,
                  "Run all systematics (1) or just the central one (0)")


options.register('ignoreTrigger',
                 0,
                  VarParsing.multiplicity.singleton,
                  VarParsing.varType.int,
                  "Ignore trigger in selection")

options.register('muTrig',
                 'HLT_Mu9',
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.string,
                 "Muon trigger to run")

options.parseArguments()

print options

import sys

if options.useFlavorHistory > 0 :
    useFlavorHistory = True
else :
    useFlavorHistory = False

inputDoMC=True

inputSampleName = options.sampleNameInput

inputCutsToIgnore = []
if options.ignoreTrigger == 1 :
    inputCutsToIgnore.append( 'Trigger' )

## Source
if len(options.inputFiles) == 0 :
    process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
                                    'dcap:///pnfs/cms/WAX/11/store/user/rappocc/TTJets_TuneD6T_7TeV-madgraph-tauola/shyft_387_v1/806866a699de2045917e2f88bbb597f4/shyft_386_mc_1_1_n47.root'
#                                    'file:/uscms_data/d2/rappocc/analysis/SHyFT/CMSSW_3_8_3_SHyFT/src/Analysis/EDSHyFT/test/syncex_shyft_382_mc.root'
#                                    'dcap:///pnfs/cms/WAX/11/store/user/rappocc/InclusiveMu15/shyft_38xOn35x_v1/91f2fc34c53b68691c104fb43fa3e9f4/shyft_382_mc_1_1_rw3.root'
#                                    'dcap:///pnfs/cms/WAX/11/store/user/rappocc/TTbarJets-madgraph/shyft_38xOn35x_v2/b8014e49c41bd22a9b4664626194b599/shyft_382_mc_1_1_fU1.root'
#                                    'dcap:///pnfs/cms/WAX/11/store/user/rappocc/WJets-madgraph/shyft_38xOn35x_v5/c0e35ba6e48486ab759b591ebe1227c6/shyft_382_mc_100_1_DBn.root',
#                                    'dcap:///pnfs/cms/WAX/11/store/user/rappocc/WJets-madgraph/shyft_38xOn35x_v5/c0e35ba6e48486ab759b591ebe1227c6/shyft_382_mc_101_1_Lpm.root',
#                                    'dcap:///pnfs/cms/WAX/11/store/user/rappocc/WJets-madgraph/shyft_38xOn35x_v5/c0e35ba6e48486ab759b591ebe1227c6/shyft_382_mc_102_1_goD.root',
#                                    'dcap:///pnfs/cms/WAX/11/store/user/rappocc/WJets-madgraph/shyft_38xOn35x_v5/c0e35ba6e48486ab759b591ebe1227c6/shyft_382_mc_103_1_fHI.root',
#                                    'dcap:///pnfs/cms/WAX/11/store/user/rappocc/WJets-madgraph/shyft_38xOn35x_v5/c0e35ba6e48486ab759b591ebe1227c6/shyft_382_mc_104_1_GLp.root',
#                                    'dcap:///pnfs/cms/WAX/11/store/user/rappocc/WJets-madgraph/shyft_38xOn35x_v5/c0e35ba6e48486ab759b591ebe1227c6/shyft_382_mc_10_1_rr9.root',
#                                    'dcap:///pnfs/cms/WAX/11/store/user/rappocc/WJets-madgraph/shyft_38xOn35x_v5/c0e35ba6e48486ab759b591ebe1227c6/shyft_382_mc_11_1_rXZ.root',
#                                    'dcap:///pnfs/cms/WAX/11/store/user/rappocc/WJets-madgraph/shyft_38xOn35x_v5/c0e35ba6e48486ab759b591ebe1227c6/shyft_382_mc_12_1_TUg.root',
#                                    'dcap:///pnfs/cms/WAX/11/store/user/rappocc/WJets-madgraph/shyft_38xOn35x_v5/c0e35ba6e48486ab759b591ebe1227c6/shyft_382_mc_13_1_4GA.root',
#                                    'dcap:///pnfs/cms/WAX/11/store/user/rappocc/WJets-madgraph/shyft_38xOn35x_v5/c0e35ba6e48486ab759b591ebe1227c6/shyft_382_mc_14_1_HVv.root',


                                    )
                                )
else :
    filelist = open( options.inputFiles[0], 'r' )
    process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(
                                    filelist.readlines()
                                    )
                                )

if inputDoMC == False :
    process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange( myList )

## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(3000) )

from Analysis.SHyFT.shyftAnalysis_cfi import shyftAnalysis as inputShyftAnalysis

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("shyftStudies.root")
                                   )

shyftAnalysisParams = inputShyftAnalysis.clone(
                                        muonSrc = cms.InputTag('selectedPatMuonsPFlow'),
                                        electronSrc = cms.InputTag('selectedPatElectronsPFlow'),
                                        metSrc = cms.InputTag('patMETsPFlow'),
                                        jetSrc = cms.InputTag('selectedPatJetsPFlow'),
                                        muTrig = cms.string(options.muTrig),    
                                        jetPtMin = cms.double(25.0),
                                        minJets = cms.int32(3),
                                        metMin = cms.double(20.0),                                        
                                        heavyFlavour = cms.bool( useFlavorHistory ),
                                        doMC = cms.bool( inputDoMC),
                                        sampleName = cms.string(inputSampleName),
                                        identifier = cms.string('PF MC'),
                                        jetAlgo = cms.string("pf"),
                                        simpleSFCalc = cms.bool(False),
                                        reweightBTagEff = cms.bool(False),
                                        useCustomPayload = cms.bool(False),                                            
                                        jetSmear = cms.double(0.1),
                                        cutsToIgnore=cms.vstring(inputCutsToIgnore)
                                       )

process.pfShyftSkim = cms.EDFilter('EDWPlusJetsSelector',
                                   shyftAnalysisParams.clone()
                                   )


process.pfShyftAnaMC = cms.EDAnalyzer('EDSHyFT',
                                    shyftAnalysis = shyftAnalysisParams.clone()                                  
                                    )





process.p = cms.Path(
    process.pfShyftSkim*
    process.pfShyftAnaMC
    )


process.MessageLogger.cerr.FwkReport.reportEvery = 1000
