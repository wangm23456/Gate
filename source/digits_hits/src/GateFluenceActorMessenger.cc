/*----------------------
   GATE version name: gate_v6

   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See GATE/LICENSE.txt for further details
----------------------*/


#include "GateFluenceActorMessenger.hh"
#include "GateFluenceActor.hh"

//-----------------------------------------------------------------------------
GateFluenceActorMessenger::GateFluenceActorMessenger(GateFluenceActor* sensor)
  :GateImageActorMessenger(sensor),
  pFluenceActor(sensor)
{
  pEnableScatterCmd = 0;
  BuildCommands(baseName+sensor->GetObjectName());
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
GateFluenceActorMessenger::~GateFluenceActorMessenger()
{
  if(pEnableScatterCmd) delete pEnableScatterCmd;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void GateFluenceActorMessenger::BuildCommands(G4String base)
{
  G4String  n = base+"/enableScatter";
  pEnableScatterCmd = new G4UIcmdWithABool(n, this); 
  G4String guid = G4String("Enable computation of scattered particles fluence");
  pEnableScatterCmd->SetGuidance(guid);

  n = base+"/responseDetectorFilename";
  pSetResponseDetectorFileCmd = new G4UIcmdWithAString(n, this);
  guid = G4String( "Response detector curve (weight to each energy)");
  pSetResponseDetectorFileCmd->SetGuidance( guid);

  n = base+"/scatterOrderFilename";
  pSetScatterOrderFilenameCmd = new G4UIcmdWithAString(n,this);
  guid = "Set the file name for the scatter x-rays that hit the detector (printf format with runId as a single parameter).";
  pSetScatterOrderFilenameCmd->SetGuidance(guid);

  n = base+"/scatterProcessFilename";
  pSetScatterProcessFilenameCmd = new G4UIcmdWithAString(n,this);
  guid = "Set the file name for each scatter process x-rays that hit the detector (printf format with runId as a single parameter).";
  pSetScatterProcessFilenameCmd->SetGuidance(guid);
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void GateFluenceActorMessenger::SetNewValue(G4UIcommand* cmd, G4String newValue)
{
  if (cmd == pEnableScatterCmd) 
    pFluenceActor->EnableScatterImage(pEnableScatterCmd->GetNewBoolValue(newValue));

  if( cmd == pSetResponseDetectorFileCmd)
      pFluenceActor->SetResponseDetectorFile(newValue);

  if(cmd == pSetScatterOrderFilenameCmd)
    pFluenceActor->SetScatterOrderFilename(newValue);

  if(cmd == pSetScatterProcessFilenameCmd)
    pFluenceActor->SetScatterProcessFilename(newValue);

  GateImageActorMessenger::SetNewValue( cmd, newValue);
}
//-----------------------------------------------------------------------------
