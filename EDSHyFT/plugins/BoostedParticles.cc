/////////////////////////////////
// Class to study the semileptonic decay of b' decay:
// It stores the P4 of the decay products
//
////////////////////////////////
#include <memory>
#include "Analysis/EDSHyFT/plugins/BoostedParticles.h"

using namespace std;
using namespace edm;
using namespace reco;

void BoostedParticles::produce(edm::Event& event, const edm::EventSetup& setup)
{

   //leptonic side of b'->tW->tlnu
   std::auto_ptr< LorentzV > Lep1 ( new LorentzV() );
   std::auto_ptr< LorentzV > Nu1  ( new LorentzV() );
   std::auto_ptr< LorentzV > LepT1( new LorentzV() );
   std::auto_ptr< LorentzV > Lep2 ( new LorentzV() );
   std::auto_ptr< LorentzV > Nu2  ( new LorentzV() );
   std::auto_ptr< LorentzV > LepT2( new LorentzV() );

   //P4 of W and b from a t decay: t->Wb->(lnub, qqb)
   std::auto_ptr< LorentzV > LepT1toWtoLep (new LorentzV() );
   std::auto_ptr< LorentzV > LepT1toWtoHad (new LorentzV() );
   std::auto_ptr< LorentzV > LepT1tob      (new LorentzV() );
   std::auto_ptr< LorentzV > LepT2toWtoLep (new LorentzV() );
   std::auto_ptr< LorentzV > LepT2toWtoHad (new LorentzV() );
   std::auto_ptr< LorentzV > LepT2tob      (new LorentzV() );  
   
   //hadronic side of b'->tW->tqq
   std::auto_ptr< LorentzV > WPart1( new LorentzV() );
   std::auto_ptr< LorentzV > WPart2( new LorentzV() );
   std::auto_ptr< LorentzV > HadT1 ( new LorentzV() );
   std::auto_ptr< LorentzV > WPart3( new LorentzV() );
   std::auto_ptr< LorentzV > WPart4( new LorentzV() );
   std::auto_ptr< LorentzV > HadT2 ( new LorentzV() );
   
   //P4 of W and b from a t decay: t->Wb->(lnub, qqb)
   std::auto_ptr< LorentzV > HadT1toWtoLep (new LorentzV() );
   std::auto_ptr< LorentzV > HadT1toWtoHad (new LorentzV() );
   std::auto_ptr< LorentzV > HadT1tob (new LorentzV() );
   std::auto_ptr< LorentzV > HadT2toWtoLep (new LorentzV() );
   std::auto_ptr< LorentzV > HadT2toWtoHad (new LorentzV() );
   std::auto_ptr< LorentzV > HadT2tob (new LorentzV() ); 

   //leptonic side of b'->bZ->bll
   std::auto_ptr< LorentzV > ZLep1 ( new LorentzV() );
   std::auto_ptr< LorentzV > ZLep2 ( new LorentzV() );
   std::auto_ptr< LorentzV > LepB1 ( new LorentzV() );
   std::auto_ptr< LorentzV > ZLep3 ( new LorentzV() );
   std::auto_ptr< LorentzV > ZLep4 ( new LorentzV() );
   std::auto_ptr< LorentzV > LepB2 ( new LorentzV() );

   //hadronic side of b'->bZ->bqq
   std::auto_ptr< LorentzV > ZPart1 ( new LorentzV() );
   std::auto_ptr< LorentzV > ZPart2 ( new LorentzV() );
   std::auto_ptr< LorentzV > HadB1  ( new LorentzV() );
   std::auto_ptr< LorentzV > ZPart3 ( new LorentzV() );
   std::auto_ptr< LorentzV > ZPart4 ( new LorentzV() );
   std::auto_ptr< LorentzV > HadB2  ( new LorentzV() );

   //leptonic side of b'->bH->bll
   std::auto_ptr< LorentzV > HLep1  ( new LorentzV() );
   std::auto_ptr< LorentzV > HLep2  ( new LorentzV() );
   std::auto_ptr< LorentzV > LepBh1 ( new LorentzV() );
   std::auto_ptr< LorentzV > HLep3  ( new LorentzV() );
   std::auto_ptr< LorentzV > HLep4  ( new LorentzV() );
   std::auto_ptr< LorentzV > LepBh2 ( new LorentzV() );

   //hadronic side of b'->bH->bqq
   std::auto_ptr< LorentzV > HPart1  ( new LorentzV() );
   std::auto_ptr< LorentzV > HPart2  ( new LorentzV() );
   std::auto_ptr< LorentzV > HadBh1  ( new LorentzV() );
   std::auto_ptr< LorentzV > HPart3  ( new LorentzV() );
   std::auto_ptr< LorentzV > HPart4  ( new LorentzV() );
   std::auto_ptr< LorentzV > HadBh2  ( new LorentzV() );
    
   //event configuration of b'b'->tWtW
   std::auto_ptr< int >  WtWtTolnutlnut(new int (0));
   std::auto_ptr< int >  WtWtToqqtqqt  (new int (0));
   std::auto_ptr< int >  WtWtToluntqqt (new int (0));
   std::auto_ptr< int >  BBtoWtWt      (new int (0));
   
   //event configuration of b'b'->ZbZb
   std::auto_ptr< int >  ZbZbTollbllb  (new int (0));
   std::auto_ptr< int >  ZbZbToqqbqqb  (new int (0));
   std::auto_ptr< int >  ZbZbTollbqqb  (new int (0));
   std::auto_ptr< int >  BBtoZbZb      (new int (0));
   
   //event configuration of b'b'->tWZb
   std::auto_ptr< int >  WtZbTolnutllb  (new int (0));
   std::auto_ptr< int >  WtZbTolnutqqb  (new int (0));
   std::auto_ptr< int >  WtZbToqqtllb   (new int (0));
   std::auto_ptr< int >  WtZbToqqtqqb   (new int (0));
   std::auto_ptr< int >  BBtoWtZb       (new int (0));

   //event configuration of b'b'->HbHb
   std::auto_ptr< int >  HbHbTollbllb  (new int (0));
   std::auto_ptr< int >  HbHbToqqbqqb  (new int (0));
   std::auto_ptr< int >  HbHbTollbqqb  (new int (0));
   std::auto_ptr< int >  BBtoHbHb      (new int (0));
   
   //event configuration of b'b'->WtHb
   std::auto_ptr< int >  WtHbTolnutllb  (new int (0));
   std::auto_ptr< int >  WtHbTolnutqqb  (new int (0));
   std::auto_ptr< int >  WtHbToqqtllb   (new int (0));
   std::auto_ptr< int >  WtHbToqqtqqb   (new int (0));
   std::auto_ptr< int >  BBtoWtHb       (new int (0));

   //event configuration of b'b'->ZbHb
   std::auto_ptr< int >  ZbHbTollbllb  (new int (0));
   std::auto_ptr< int >  ZbHbTollbqqb  (new int (0));
   std::auto_ptr< int >  ZbHbToqqbllb  (new int (0));
   std::auto_ptr< int >  ZbHbToqqbqqb  (new int (0));
   std::auto_ptr< int >  BBtoZbHb      (new int (0));

   //special hadronic side of b'->bH(bb)
   //===================================
   std::auto_ptr< LorentzV > Htobb1  ( new LorentzV() );
   std::auto_ptr< LorentzV > Htobb2  ( new LorentzV() );
   std::auto_ptr< LorentzV > b1      ( new LorentzV() );
   std::auto_ptr< LorentzV > Htobb3  ( new LorentzV() );
   std::auto_ptr< LorentzV > Htobb4  ( new LorentzV() );
   std::auto_ptr< LorentzV > b2      ( new LorentzV() );
   
   if(!event.isRealData()){
      edm::Handle<std::vector<reco::GenParticle> > h_gen;
      event.getByLabel(edm::InputTag("prunedGenParticles"), h_gen); 
      assert ( h_gen.isValid() );

      int numDa; int id(0); 
      
      std::vector<const reco::Candidate *> LeptW(6); //l1, nu1, t1, l2, nu2, t2
      std::vector<const reco::Candidate *> HadtW(6);
      std::vector<const reco::Candidate *> LepbZ(6);
      std::vector<const reco::Candidate *> HadbZ(6);
      std::vector<const reco::Candidate *> LepbH(6);
      std::vector<const reco::Candidate *> HadbH(6);
      std::vector<const reco::Candidate *> HadbHtobb(6);
    
      std::vector<const reco::Candidate *> LepTtoWtoLep(2);
      std::vector<const reco::Candidate *> LepTtoWtoHad(2);
      std::vector<const reco::Candidate *> HadTtoWtoLep(2);
      std::vector<const reco::Candidate *> HadTtoWtoHad(2);
      std::vector<const reco::Candidate *> LepTtob(2);
      std::vector<const reco::Candidate *> HadTtob(2);
     
      int numLeptW(0), numHadtW(0), numLepbZ(0), numHadbZ(0), numLepbH(0), numHadbH(0),  numHadbHtobb(0);
      
      setPointers(LeptW); setPointers(HadtW); setPointers(LepbZ); setPointers(HadbZ);
      setPointers(LepTtoWtoLep); setPointers(LepTtoWtoHad); setPointers(HadTtoWtoLep); setPointers(HadTtoWtoHad);
      setPointers(LepTtob); setPointers(HadTtob);
     
      for (vector< reco::GenParticle>::const_iterator gpIter = h_gen->begin(); 
           gpIter != h_gen->end(); ++gpIter, ++id){
         
         if( gpIter->status() !=3) continue;
         numDa = gpIter->numberOfDaughters();   
         
         //select a b' b' event
         if(numDa >= 2 && abs(gpIter->daughter(0)->pdgId()) == 7 && abs(gpIter->daughter(1)->pdgId()) == 7 ){
            
            const reco::Candidate* bprimes[2] = { gpIter->daughter(0), gpIter->daughter(1) };
            
            //b'b'->tWtW, tWbZ, bZbZ
            for(int bi=0; bi<2; bi++){
                         
               if(bprimes[bi]->numberOfDaughters()<2){ std::cout << "bprime doesn't decay into 2 particles" << std::endl;  break;}    

               int numDau = bprimes[bi]->numberOfDaughters(); 
               for(int di=0; di<numDau; di++){ 
                  
                  if( bprimes[bi]->daughter(di)->status() != 3 ) continue;           
                  int numTopDau = bprimes[bi]->daughter((di+1)%2)->numberOfDaughters();
                  
                  //b'->t W
                  if(abs(bprimes[bi]->daughter(di)->pdgId()) == 24 && di < 2){
                     if(bprimes[bi]->daughter(di)->numberOfDaughters()!=2) {cout << "W doesn't decay into 2 particles!" << endl; break;}
                    
                     //--------leptonic side--------
                     if(abs(bprimes[bi]->daughter(di)->daughter(0)->pdgId())>10){
                        numLeptW++;
                       
                        if(abs(bprimes[bi]->daughter(di)->daughter(0)->pdgId())%2==1) {//W+ -> l+ nu
                           if(numLeptW == 1){
                              LeptW[0] = bprimes[bi]->daughter(di)->daughter(1);
                              LeptW[1] = bprimes[bi]->daughter(di)->daughter(0);
                           }else{
                              LeptW[3] = bprimes[bi]->daughter(di)->daughter(1);
                              LeptW[4] = bprimes[bi]->daughter(di)->daughter(0);
                           }
                        }
                        else {//W- -> l- nu
                           if(numLeptW == 1){
                              LeptW[0] = bprimes[bi]->daughter(di)->daughter(0);
                              LeptW[1] = bprimes[bi]->daughter(di)->daughter(1);
                           }else{
                              LeptW[3] = bprimes[bi]->daughter(di)->daughter(0);
                              LeptW[4] = bprimes[bi]->daughter(di)->daughter(1);
                           }
                        }                         
      
                        //fill the other leg, t quark
                        if(abs(bprimes[bi]->daughter((di+1)%2)->pdgId())!=6){std::cout << "leptonic side W does not have brother t quark!" << std::endl; break;}
                        if(numLeptW == 1){
                           LeptW[2] = bprimes[bi]->daughter((di+1)%2);
                        }else{
                           LeptW[5] = bprimes[bi]->daughter((di+1)%2);
                        }

                        //fill the top decay
                        if(numLeptW == 1){
                           topDecay( bprimes[bi], numTopDau, di, LepTtoWtoLep[0], LepTtoWtoHad[0], LepTtob[0]);
                        }else{
                           topDecay( bprimes[bi], numTopDau, di, LepTtoWtoLep[1], LepTtoWtoHad[1], LepTtob[1]);
                        }
                        
                     }//-----------hadronic side----------
                     else if(abs(bprimes[bi]->daughter(di)->daughter(0)->pdgId())<=6 && abs(bprimes[bi]->daughter(di)->daughter(1)->pdgId())<=6){ 
                        numHadtW++;
                        if(abs(bprimes[bi]->daughter(di)->daughter(0)->pdgId())%2==1){//W+ -> q q'bar
                          if(numHadtW == 1){
                             HadtW[0] = bprimes[bi]->daughter(di)->daughter(1); 
                             HadtW[1] = bprimes[bi]->daughter(di)->daughter(0);
                          }
                          else{
                             HadtW[3] = bprimes[bi]->daughter(di)->daughter(1); 
                             HadtW[4] = bprimes[bi]->daughter(di)->daughter(0);
                          }
                        }   
                        else{//W- -> q'bar q
                           if(numHadtW == 1){
                              HadtW[0] = bprimes[bi]->daughter(di)->daughter(0); 
                              HadtW[1] = bprimes[bi]->daughter(di)->daughter(1);
                           }
                           else{
                              HadtW[3] = bprimes[bi]->daughter(di)->daughter(0); 
                              HadtW[4] = bprimes[bi]->daughter(di)->daughter(1);
                           }
                        }
                        //fill the hadronic leg, t quark
                        if(abs(bprimes[bi]->daughter((di+1)%2)->pdgId())!=6){std::cout << "hadronic side W does not have associated t quark!" << std::endl; break;}
                        if(numHadtW == 1){
                           HadtW[2] = bprimes[bi]->daughter((di+1)%2);
                        }else{
                           HadtW[5] = bprimes[bi]->daughter((di+1)%2);
                        }
   
                        //fill the top decay
                        if(numHadtW == 1){
                           topDecay( bprimes[bi], numTopDau, di, HadTtoWtoLep[0], HadTtoWtoHad[0], HadTtob[0]);
                        }else{
                           topDecay( bprimes[bi], numTopDau, di, HadTtoWtoLep[1], HadTtoWtoHad[1], HadTtob[1]);
                        }  
                           
                     }
                  }//W //---------b'->bZ---------
                  else if( abs(bprimes[bi]->daughter(di)->pdgId()) == 23 && di < 2){ //look for Z boson(s)
                     if(bprimes[bi]->daughter(di)->numberOfDaughters()!=2) {cout << "Z doesn't decay into 2 particles!" << endl; break;}
                     if(abs(bprimes[bi]->daughter(di)->daughter(0)->pdgId())>10){//Z -> ll
                        numLepbZ++;
                        
                        if(numLepbZ == 1){
                           LepbZ[0] =  bprimes[bi]->daughter(di)->daughter(0);
                           LepbZ[1] =  bprimes[bi]->daughter(di)->daughter(1);
                        }else{
                           LepbZ[3] =  bprimes[bi]->daughter(di)->daughter(0);
                           LepbZ[4] =  bprimes[bi]->daughter(di)->daughter(1);
                        }
                        if(abs(bprimes[bi]->daughter((di+1)%2)->pdgId())!=5){std::cout << "leptonic side Z does not have associated b quark!" << std::endl; break;}
                        if(numLepbZ == 1){
                           LepbZ[2] =  bprimes[bi]->daughter((di+1)%2);
                        }else{
                           LepbZ[5] =  bprimes[bi]->daughter((di+1)%2);
                        }
                     }
                     else if(abs(bprimes[bi]->daughter(di)->daughter(0)->pdgId())<=6 && abs(bprimes[bi]->daughter(di)->daughter(1)->pdgId())<=6){//Z  -> qq
                        numHadbZ++;
                        
                        if(numHadbZ == 1){
                           HadbZ[0] = bprimes[bi]->daughter(di)->daughter(0);
                           HadbZ[1] = bprimes[bi]->daughter(di)->daughter(1);
                        }else{
                           HadbZ[3] = bprimes[bi]->daughter(di)->daughter(0);
                           HadbZ[4] = bprimes[bi]->daughter(di)->daughter(1);
                        }
                        if(abs(bprimes[bi]->daughter((di+1)%2)->pdgId())!=5){std::cout << "hadronic side Z does not have associated b quark!" << std::endl; break;}
                        if(numHadbZ == 1){
                           HadbZ[2] = bprimes[bi]->daughter((di+1)%2);
                        }else{
                           HadbZ[5] = bprimes[bi]->daughter((di+1)%2);
                        } 
                     }//Z->qq
                  }//b'->bZ// //---------b'->bH---------
                  else if( abs(bprimes[bi]->daughter(di)->pdgId()) == 25 && di < 2){ //look for H boson(s)
                     if(bprimes[bi]->daughter(di)->numberOfDaughters()!=2) {cout << "H doesn't decay into 2 particles!" << endl; break;}
                     if(abs(bprimes[bi]->daughter(di)->daughter(0)->pdgId())>10){//H -> ll, gg
                        numLepbH++;

                        if(numLepbH == 1){
                           LepbH[0] =  bprimes[bi]->daughter(di)->daughter(0);
                           LepbH[1] =  bprimes[bi]->daughter(di)->daughter(1);
                        }else{
                           LepbH[3] =  bprimes[bi]->daughter(di)->daughter(0);
                           LepbH[4] =  bprimes[bi]->daughter(di)->daughter(1);
                        }
                        if(abs(bprimes[bi]->daughter((di+1)%2)->pdgId())!=5){std::cout << "leptonic side H does not have associated b quark!" << std::endl; break;}
                        if(numLepbH == 1){
                           LepbH[2] =  bprimes[bi]->daughter((di+1)%2);
                        }else{
                           LepbH[5] =  bprimes[bi]->daughter((di+1)%2);
                        }
                     }
                     else if(abs(bprimes[bi]->daughter(di)->daughter(0)->pdgId())<=6 && abs(bprimes[bi]->daughter(di)->daughter(1)->pdgId())<=6){//H -> qq
                        numHadbH++;
                        
                        if(numHadbH == 1){
                           HadbH[0] = bprimes[bi]->daughter(di)->daughter(0);
                           HadbH[1] = bprimes[bi]->daughter(di)->daughter(1);
                        }else{
                           HadbH[3] = bprimes[bi]->daughter(di)->daughter(0);
                           HadbH[4] = bprimes[bi]->daughter(di)->daughter(1);
                        }
                        if(abs(bprimes[bi]->daughter((di+1)%2)->pdgId())!=5){std::cout << "hadronic side H does not have associated b quark!" << std::endl; break;}
                        if(numHadbH == 1){
                           HadbH[2] = bprimes[bi]->daughter((di+1)%2);
                        }else{
                           HadbH[5] = bprimes[bi]->daughter((di+1)%2);
                        } 
 
                     }//H->qq
                     //-----------------H -> bb ---------------------
                     if(abs(bprimes[bi]->daughter(di)->daughter(0)->pdgId())==5 && abs(bprimes[bi]->daughter(di)->daughter(1)->pdgId())==5){//H -> bb
                        numHadbHtobb++;
                        
                        if(numHadbHtobb == 1){
                           HadbHtobb[0] = bprimes[bi]->daughter(di)->daughter(0);
                           HadbHtobb[1] = bprimes[bi]->daughter(di)->daughter(1);
                        }else{
                           HadbHtobb[3] = bprimes[bi]->daughter(di)->daughter(0);
                           HadbHtobb[4] = bprimes[bi]->daughter(di)->daughter(1);
                        }
                        if(abs(bprimes[bi]->daughter((di+1)%2)->pdgId())!=5){std::cout << "H->bb does not have associated b quark!" << std::endl; break;}
                        if(numHadbHtobb == 1){
                           HadbHtobb[2] = bprimes[bi]->daughter((di+1)%2);
                        }else{
                           HadbHtobb[5] = bprimes[bi]->daughter((di+1)%2);
                        } 
                     }//H->bb
                  }//b'->bH

               }//di 
            }//bi
            break; // if we find one b'b' pair, lets stop the loop
         }// at least 2 daughters       
         
      }//gpIter
    
       //BB->WtWt
       if (numLeptW == 2) *WtWtToqqtqqt = 1;
       if (numHadtW == 2) *WtWtToqqtqqt = 1;
       if (numLeptW == 1 && numHadtW == 1) *WtWtToluntqqt = 1;
       if (*WtWtTolnutlnut == 1 || *WtWtToqqtqqt == 1 || *WtWtToluntqqt == 1) *BBtoWtWt = 1;
      
       //BB->ZbZb
       if (numLepbZ == 2) *ZbZbTollbllb = 1;
       if (numHadbZ == 2) *ZbZbToqqbqqb = 1;
       if (numLepbZ == 1 &&  numHadbZ == 1) *ZbZbTollbqqb = 1;
       if (*ZbZbTollbllb ==1 || *ZbZbToqqbqqb ==1 || *ZbZbTollbqqb == 1) *BBtoZbZb = 1;

       //BB->WtZb
       if (numLeptW == 1 && numLepbZ == 1) *WtZbTolnutllb = 1;
       if (numLeptW == 1 && numHadbZ == 1) *WtZbTolnutqqb = 1;
       if (numHadtW == 1 && numLepbZ == 1) *WtZbToqqtllb  = 1;
       if (numHadtW == 1 && numHadbZ == 1) *WtZbToqqtqqb  = 1;
       if (*WtZbTolnutllb == 1 || *WtZbTolnutqqb == 1 || *WtZbToqqtllb == 1 || *WtZbToqqtqqb == 1) *BBtoWtZb = 1; 

       //BB->HbHb
       if (numLepbH == 2) *HbHbTollbllb = 1;
       if (numHadbH == 2) *HbHbToqqbqqb = 1;
       if (numLepbH == 1 &&  numHadbH == 1) *HbHbTollbqqb = 1;
       if (*HbHbTollbllb ==1 || *HbHbToqqbqqb ==1 || *HbHbTollbqqb == 1) *BBtoHbHb = 1;

       //BB->WtHb
       if (numLeptW == 1 && numLepbH == 1) *WtHbTolnutllb = 1;
       if (numLeptW == 1 && numHadbH == 1) *WtHbTolnutqqb = 1;
       if (numHadtW == 1 && numLepbH == 1) *WtHbToqqtllb  = 1;
       if (numHadtW == 1 && numHadbH == 1) *WtHbToqqtqqb  = 1;
       if (*WtHbTolnutllb == 1 || *WtHbTolnutqqb == 1 || *WtHbToqqtllb == 1 || *WtHbToqqtqqb == 1) *BBtoWtHb = 1; 
  
       //BB->ZbHb
       if (numLepbZ == 1 && numLepbH == 1) *ZbHbTollbllb  = 1;
       if (numLepbZ == 1 && numHadbH == 1) *ZbHbTollbqqb  = 1;
       if (numHadbZ == 1 && numLepbH == 1) *ZbHbToqqbllb  = 1;
       if (numHadbZ == 1 && numHadbH == 1) *ZbHbToqqbqqb  = 1;
       if (*ZbHbTollbllb == 1 || *ZbHbTollbqqb == 1 || *ZbHbToqqbllb == 1 || *ZbHbToqqbqqb == 1) *BBtoZbHb = 1; 

       cout << "BBtoWtHb = " << *BBtoWtHb << ",BBtoHbHb = " << *BBtoHbHb << ",BBtoWtWt = " << *BBtoWtWt << endl;
/*
       if (! (*BBtoWtZb || *BBtoZbZb || *BBtoWtWt)){
          cout << "event---->" << event.id() << endl;
          cout << "*BBtoWtWt = " <<  *BBtoWtWt  << ",WtWtTolnutlnut = " << *WtWtTolnutlnut << ",WtWtToqqtqqt = " << *WtWtToqqtqqt <<",WtWtToluntqqt = " << *WtWtToluntqqt << endl;
          cout << "numHadtW, = " << numHadtW << endl;
       }
*/
       //Fill Leptonic side of b->tW': l1, nu1, t1, l2, nu2, t2
        //----------------------------------------------------
       if(numLeptW == 1) {
          *Lep1 = LeptW[0]->p4(); *Nu1 = LeptW[1]->p4(); *LepT1 = LeptW[2]->p4(); *LepT1tob = LepTtob[0]->p4();
           //fill the top daughters 
          if(LepTtoWtoLep[0] != 0 )  *LepT1toWtoLep = LepTtoWtoLep[0]->p4(); 
          if(LepTtoWtoHad[0] != 0 )  *LepT1toWtoHad = LepTtoWtoHad[0]->p4(); 
       }
        else if(numLeptW == 2) {
           *Lep1 = LeptW[0]->p4(); *Nu1 = LeptW[1]->p4(); *LepT1 = LeptW[2]->p4();
           *Lep2 = LeptW[3]->p4(); *Nu2 = LeptW[4]->p4(); *LepT2 = LeptW[5]->p4();           
           //fill the top daughters 
           if(LepTtoWtoLep[0] != 0 )  *LepT1toWtoLep = LepTtoWtoLep[0]->p4(); 
           if(LepTtoWtoHad[0] != 0 )  *LepT1toWtoHad = LepTtoWtoHad[0]->p4(); 
           if(LepTtoWtoLep[1] != 0 )  *LepT2toWtoLep = LepTtoWtoLep[1]->p4();
           if(LepTtoWtoHad[1] != 0 )  *LepT2toWtoHad = LepTtoWtoHad[1]->p4();
           
           *LepT1tob = LepTtob[0]->p4(); *LepT2tob = LepTtob[1]->p4();
        }
       
        //Fill Hadronic side of b'->tW: q1, q2, t1, q3, q4, t2
        //----------------------------------------------------
       if(numHadtW == 1) {
          *WPart1 = HadtW[0]->p4(); *WPart2 = HadtW[1]->p4(); *HadT1 = HadtW[2]->p4(); *HadT1tob = HadTtob[0]->p4();
          //fill the top daughters 
          if(HadTtoWtoLep[0] != 0 )  *HadT1toWtoLep = HadTtoWtoLep[0]->p4(); 
          if(HadTtoWtoHad[0] != 0 )  *HadT1toWtoHad = HadTtoWtoHad[0]->p4();
       }
        else if(numHadtW == 2) {
           *WPart1 = HadtW[0]->p4(); *WPart2 = HadtW[1]->p4(); *HadT1 = HadtW[2]->p4();
           *WPart3 = HadtW[3]->p4(); *WPart4 = HadtW[4]->p4(); *HadT2 = HadtW[5]->p4();
           //fill the top daughters
           if(HadTtoWtoLep[0] != 0 )  *HadT1toWtoLep = HadTtoWtoLep[0]->p4(); 
           if(HadTtoWtoHad[0] != 0 )  *HadT1toWtoHad = HadTtoWtoHad[0]->p4(); 
           if(HadTtoWtoLep[1] != 0 )  *HadT2toWtoLep = HadTtoWtoLep[1]->p4();
           if(HadTtoWtoHad[1] != 0 )  *HadT2toWtoHad = HadTtoWtoHad[1]->p4();
           
           *HadT1tob = HadTtob[0]->p4(); *HadT2tob = HadTtob[1]->p4();
        }
       
       //Fill the leptonic side of b'->bZ: l1, l2, b1, l3, l4, b2
       //-------------------------------------------------------
       if(numLepbZ == 1) {
          *ZLep1 = LepbZ[0]->p4(); *ZLep2 = LepbZ[1]->p4(); *LepB1 = LepbZ[2]->p4();
       }
       else if(numLepbZ == 2) {
          *ZLep1 = LepbZ[0]->p4(); *ZLep2 = LepbZ[1]->p4(); *LepB1 = LepbZ[2]->p4();
          *ZLep3 = LepbZ[3]->p4(); *ZLep4 = LepbZ[4]->p4(); *LepB2 = LepbZ[5]->p4();
       }
       
       //Fill the hadronic side of b'->bZ: q1, q2, b1, q3, q4, b2
       //--------------------------------------------------------
       if(numHadbZ == 1) {
          *ZPart1 = HadbZ[0]->p4(); *ZPart2 = HadbZ[1]->p4(); *HadB1 = HadbZ[2]->p4();
       }
       else if(numHadbZ == 2) {
          *ZPart1 = HadbZ[0]->p4(); *ZPart2 = HadbZ[1]->p4(); *HadB1 = HadbZ[2]->p4();
          *ZPart3 = HadbZ[3]->p4(); *ZPart4 = HadbZ[4]->p4(); *HadB2 = HadbZ[5]->p4();
       }

       //Fill the leptonic side of b'->bH: l1, l2, b1, l3, l4, b2
       //-------------------------------------------------------
       if(numLepbH == 1) {
          *HLep1 = LepbH[0]->p4(); *HLep2 = LepbH[1]->p4(); *LepBh1 = LepbH[2]->p4();
       }
       else if(numLepbH == 2) {
          *HLep1 = LepbH[0]->p4(); *HLep2 = LepbH[1]->p4(); *LepBh1 = LepbH[2]->p4();
          *HLep3 = LepbH[3]->p4(); *HLep4 = LepbH[4]->p4(); *LepBh2 = LepbH[5]->p4();
       }
       
       //Fill the hadronic side of b'->bH: q1, q2, b1, q3, q4, b2
       //--------------------------------------------------------
       if(numHadbH == 1) {
          *HPart1 = HadbH[0]->p4(); *HPart2 = HadbH[1]->p4(); *HadBh1 = HadbH[2]->p4();
       }
       else if(numHadbH == 2) {
          *HPart1 = HadbH[0]->p4(); *HPart2 = HadbH[1]->p4(); *HadBh1 = HadbH[2]->p4();
          *HPart3 = HadbH[3]->p4(); *HPart4 = HadbH[4]->p4(); *HadBh2 = HadbH[5]->p4();
       }
       

       //Special:Fill the hadronic side of b'->bH(bb): q1, q2, b1, q3, q4, b2
       //=====================================================================
       if(numHadbHtobb == 1) {
          *Htobb1 = HadbHtobb[0]->p4(); *Htobb2 = HadbHtobb[1]->p4(); *b1 = HadbHtobb[2]->p4();
       }
       else if(numHadbHtobb == 2) {
          *Htobb1 = HadbHtobb[0]->p4(); *Htobb2 = HadbHtobb[1]->p4(); *b1 = HadbHtobb[2]->p4();
          *Htobb3 = HadbHtobb[3]->p4(); *Htobb4 = HadbHtobb[4]->p4(); *b2 = HadbHtobb[5]->p4();
       }

/*
       for( unsigned i=0; i<6; ++i){
         
          if(numLeptW > 0 && LeptW[i] != 0){
             cout << "i: " << i << " tW: Lep pt: " << LeptW[i]->p4().pt() <<" pdgId: " << LeptW[i]->pdgId() << endl;

             if(i<2 && LepTtoWtoLep[i]!= 0) cout << "W Pt: b'->tW->Wb(lnu)->lnub(lu): " << LepTtoWtoLep[i]->p4().pt() 
                                                 << " pdgId: "<< LepTtoWtoLep[i]->pdgId() << endl;
             if(i<2 && LepTtoWtoHad[i]!= 0) cout << "W Pt: b'->tW->Wb(lnu)->qqb(lnu): "<< LepTtoWtoHad[i]->p4().pt() 
                                                 << " pdgId: "<< LepTtoWtoHad[i]->pdgId() << endl;
          }
          if(numHadtW > 0 && HadtW[i] != 0 ){
             cout << "i: " << i << " tW: Had pt: " << HadtW[i]->p4().pt() <<" pdgId: " << HadtW[i]->pdgId() << endl;
             
             if(i<2 && HadTtoWtoLep[i]!= 0) cout << "W Pt: b'->tW->Wb(qq)->lnub(qq): " << HadTtoWtoLep[i]->p4().pt() 
                                                 << " pdgId: " << HadTtoWtoLep[i]->pdgId() << endl;
             if(i<2 && HadTtoWtoHad[i]!= 0) cout << "W Pt: b'->tW->Wb(qq)->qqb(qq): "  << HadTtoWtoHad[i]->p4().pt() 
                                                 << " pdgId: " << HadTtoWtoHad[i]->pdgId() << endl;
          }

          if(numLepbZ > 0 && LepbZ[i] != 0){
             cout << "i: " << i << " bZ: Lep pt: " << LepbZ[i]->p4().pt() <<" pdgId: " << LepbZ[i]->pdgId() << endl;
          }
          if(numHadbZ > 0 && HadbZ[i] != 0 ){
             cout << "i: " << i << " bZ: Had pt: " << HadbZ[i]->p4().pt() <<" pdgId: " << HadbZ[i]->pdgId() << endl;
          }

        if(numLepbH > 0 && LepbH[i] != 0){
             cout << "i: " << i << " bH: Lep/glu pt: " << LepbH[i]->p4().pt() <<" pdgId: " << LepbH[i]->pdgId() << endl;
          }
          if(numHadbH > 0 && HadbH[i] != 0 ){
             cout << "i: " << i << " bH: Had pt: " << HadbH[i]->p4().pt() <<" pdgId: " << HadbH[i]->pdgId() << endl;
          }

       }
*/

   }
  
   event.put ( Lep1,  "Lep1");   
   event.put ( Nu1,   "Nu1"); 
   event.put ( LepT1, "LepT1");
   event.put ( Lep2,  "Lep2");   
   event.put ( Nu2,   "Nu2"); 
   event.put ( LepT2, "LepT2");

   event.put ( LepT1toWtoLep,  "LepT1toWtoLep");
   event.put ( LepT1toWtoHad,  "LepT1toWtoHad");   
   event.put ( LepT1tob,       "LepT1tob"); 
   event.put ( LepT2toWtoLep,  "LepT2toWtoLep");
   event.put ( LepT2toWtoHad,  "LepT2toWtoHad");
   event.put ( LepT2tob,       "LepT2tob");

   event.put ( WPart1, "WPart1");
   event.put ( WPart2, "WPart2");
   event.put ( HadT1,  "HadT1");
   event.put ( WPart3, "WPart3");
   event.put ( WPart4, "WPart4");
   event.put ( HadT2,  "HadT2");

   event.put ( HadT1toWtoLep,  "HadT1toWtoLep");
   event.put ( HadT1toWtoHad,  "HadT1toWtoHad");   
   event.put ( HadT1tob,       "HadT1tob"); 
   event.put ( HadT2toWtoLep,  "HadT2toWtoLep");
   event.put ( HadT2toWtoHad,  "HadT2toWtoHad");
   event.put ( HadT2tob,       "HadT2tob");

   event.put ( ZLep1,  "ZLep1");   
   event.put ( ZLep2,  "ZLep2"); 
   event.put ( LepB1,  "LepB1");
   event.put ( ZLep3,  "ZLep3");   
   event.put ( ZLep4,  "ZLep4"); 
   event.put ( LepB2,  "LepB2");

   event.put ( ZPart1, "ZPart1");
   event.put ( ZPart2, "ZPart2");
   event.put ( HadB1,  "HadB1" );
   event.put ( ZPart3, "ZPart3");
   event.put ( ZPart4, "ZPart4");
   event.put ( HadB2,  "HadB2" );

   event.put ( HLep1,  "HLep1");   
   event.put ( HLep2,  "HLep2"); 
   event.put ( LepBh1, "LepBh1");
   event.put ( HLep3,  "HLep3");   
   event.put ( HLep4,  "HLep4"); 
   event.put ( LepBh2, "LepBh2");

   event.put ( HPart1, "HPart1");
   event.put ( HPart2, "HPart2");
   event.put ( HadBh1, "HadBh1");
   event.put ( HPart3, "HPart3");
   event.put ( HPart4, "HPart4");
   event.put ( HadBh2, "HadBh2");

   event.put ( WtWtTolnutlnut, "WtWtTolnutlnut");
   event.put ( WtWtToqqtqqt,   "WtWtToqqtqqt"  );
   event.put ( WtWtToluntqqt,  "WtWtToluntqqt" );
   event.put ( BBtoWtWt,       "BBtoWtWt"      );

   event.put ( ZbZbTollbllb,   "ZbZbTollbllb"  );
   event.put ( ZbZbToqqbqqb,   "ZbZbToqqbqqb"  );
   event.put ( ZbZbTollbqqb,   "ZbZbTollbqqb"  );
   event.put ( BBtoZbZb,       "BBtoZbZb"      );

   event.put ( WtZbTolnutllb,  "WtZbTolnutllb" ); 
   event.put ( WtZbTolnutqqb,  "WtZbTolnutqqb" );
   event.put ( WtZbToqqtllb,   "WtZbToqqtllb"  ); 
   event.put ( WtZbToqqtqqb,   "WtZbToqqtqqb"  );
   event.put ( BBtoWtZb,       "BBtoWtZb"      );
   
   event.put ( HbHbTollbllb,   "HbHbTollbllb"  );
   event.put ( HbHbToqqbqqb,   "HbHbToqqbqqb"  );
   event.put ( HbHbTollbqqb,   "HbHbTollbqqb"  );
   event.put ( BBtoHbHb,       "BBtoHbHb"      );

   event.put ( WtHbTolnutllb,  "WtHbTolnutllb" ); 
   event.put ( WtHbTolnutqqb,  "WtHbTolnutqqb" );
   event.put ( WtHbToqqtllb,   "WtHbToqqtllb"  ); 
   event.put ( WtHbToqqtqqb,   "WtHbToqqtqqb"  );
   event.put ( BBtoWtHb,       "BBtoWtHb"      );
   
   event.put ( ZbHbTollbllb,   "ZbHbTollbllb"  ); 
   event.put ( ZbHbTollbqqb,   "ZbHbTollbqqb"  );
   event.put ( ZbHbToqqbllb,   "ZbHbToqqbllb"  ); 
   event.put ( ZbHbToqqbqqb,   "ZbHbToqqbqqb"  );
   event.put ( BBtoZbHb,       "BBtoZbHb"      );

}

void  BoostedParticles::topDecay(const reco::Candidate* bprimes, int numTopDau, int di,//const reco::Candidate* &TtoW,
                                 const reco::Candidate* &TtoWtoLep, const reco::Candidate* &TtoWtoHad, const reco::Candidate* &Ttob){
   for(int td=0; td<numTopDau; td++){
      //cout << "td: " << td << endl;

      if(bprimes->daughter((di+1)%2)->daughter(td)->status() != 3 ) continue;              
      //t->W b
      if(abs(bprimes->daughter((di+1)%2)->daughter(td)->pdgId()) == 24 && td < 2){// t -> W
         if(bprimes->daughter((di+1)%2)->daughter(td)->numberOfDaughters()!=2) {cout << "W doesn't decay into 2 particles!" << endl; break;}
         
         //find if the given W decays leptonicaly or hadronically
         if(abs(bprimes->daughter((di+1)%2)->daughter(td)->daughter(0)->pdgId())>10){//W -> l nu
            TtoWtoLep = bprimes->daughter((di+1)%2)->daughter(td);
         }
         else if (abs(bprimes->daughter((di+1)%2)->daughter(td)->daughter(0)->pdgId())<6 && 
                  abs(bprimes->daughter((di+1)%2)->daughter(td)->daughter(1)->pdgId())<6) { //W  -> qq
            TtoWtoHad = bprimes->daughter((di+1)%2)->daughter(td);
         }
         //the other b/q quark from top decay
         if(abs(bprimes->daughter((di+1)%2)->daughter((td+1)%2)->pdgId())>5){std::cout << "W LepTtoW does not have associated b,d,s quark!" << std::endl; break;}
         Ttob = bprimes->daughter((di+1)%2)->daughter((td+1)%2);
      }//W
   }//td 
}

void BoostedParticles::setPointers(std::vector<const reco::Candidate *> decayList){
   for(vector<const reco::Candidate *>::iterator iter = decayList.begin(); decayList.end() != iter; ++iter){
      *iter = 0;
   }
}

//define this as a plug-in
DEFINE_FWK_MODULE(BoostedParticles);
