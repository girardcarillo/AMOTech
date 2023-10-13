#!/bin/bash

restG4 Sim_ID.rml -t 12

restG4 Sim_ID_Water_Iron_Concrete.rml -t 12
restG4 Sim_ID_Iron_Concrete.rml -t 12
restG4 Sim_ID_Concrete.rml -t 12

restG4 Sim_ID_Water_Concrete_Iron.rml -t 12
restG4 Sim_ID_Concrete_Iron.rml -t 12
restG4 Sim_ID_Iron.rml -t 12

restG4 Sim_ID_OV_Water_Iron_Concrete.rml -t 12
restG4 Sim_ID_OV_Water_Concrete_Iron.rml -t 12
