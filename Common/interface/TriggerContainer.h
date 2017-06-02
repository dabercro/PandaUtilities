#ifndef TRIGGERCONTAINER_H
#define TRIGGERCONTAINER_H

#include <map>
#include <string>
#include "PandaTree/Objects/interface/Event.h"


class TriggerContainer {
 public:

  TriggerContainer          (panda::Event *event)      { fEvent = event; }
  virtual ~TriggerContainer ()                         {}

  /// Register the location of Panda triggers with this object
  void register_triggers    (const char** trigger_names);

  /// Determine if one trigger was fired or not in the current event
  bool check_trigger        (const char* trigger_name)   { return fEvent->triggerFired(fTriggers[trigger_name]); }

  /// Determine if any of the triggers were fired or not in the current event
  bool check_triggers       (const char** trigger_names);

 private:
  panda::Event *fEvent;
  std::map<const char*, unsigned int> fTriggers;   ///< Maps the trigger to a pointer. Make sure you are using the same pointer throughout

};

void TriggerContainer::register_triggers(const char** trigger_names) {

  int num_triggers = sizeof(trigger_names)/sizeof(trigger_names[0]);

  for (int i_trigger = 0; i_trigger < num_triggers; i_trigger++)
    fTriggers[trigger_names[i_trigger]] = fEvent->registerTrigger(trigger_names[i_trigger]);

}

bool TriggerContainer::check_triggers (const char** trigger_names) {

  int num_triggers = sizeof(trigger_names)/sizeof(trigger_names[0]);

  for (int i_trigger = 0; i_trigger < num_triggers; i_trigger++) {
    if (check_trigger(trigger_names[i_trigger]))
      return true;
  }

  return false;

}

#endif
