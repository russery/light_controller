
#ifndef HBRIDGE_H
#define	HBRIDGE_H

#include "bsp.h"

typedef enum HBridgeState {BridgeOff, BridgeForward,
        BridgeReverse, BridgeOpen} HBridgeState_t;
void HBridgeSet(HBridge_t bus, HBridgeState_t state);

#endif	/* HBRIDGE_H */

