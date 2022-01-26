#ifndef SWITCHES_H
#define SWITCHES_H

// All switches are on port D
#define SW_0_POS (0)
#define SW_1_POS (1)
#define SW_2_POS (2)
#define SW_3_POS (3)

// Macro to read switches returns state switches, active low
#define READ_SWITCHES  (PTE->PDIR)  

// Function prototypes
extern void Init_4way_Switch(void);

#endif
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
