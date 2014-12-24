// ----------------------------------------------------------------------------
//  $Id: LinkDef.h 9556 2014-01-14 22:24:14Z gomez $
//
//  Author:  <paola.ferrario@ific.uv.es>
//  Created: 14 Feb 2013
//  
//  Copyright (c) 2013 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ namespace irene+;
#pragma link C++ class irene::Track+;
#pragma link C++ class irene::Particle+;
#pragma link C++ class irene::SensorHit+;
#pragma link C++ class irene::Event+;
#pragma link C++ class irene::ParameterInfo+;
#pragma link C++ class std::pair<TLorentzVector,double>+;
#pragma link C++ class std::vector<std::pair<TLorentzVector,double>>+;

#endif
