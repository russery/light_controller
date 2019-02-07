#include "controller_board.X/mcc_generated_files/mcc.h"
#include "hbridge.h"
#include "bsp.h"

void HBridgeSet(HBridge_t bus, HBridgeState_t state){
    switch(state){
        case BridgeOff:
            // P-FET gates high (open).
            BspSetHBridgePin(bus, kFet1, true);
            BspSetHBridgePin(bus, kFet4, true);
            // N-FET gates high (ground outputs).
            BspSetHBridgePin(bus, kFet2, true);
            BspSetHBridgePin(bus, kFet3, true);
            break;
        case BridgeForward:
            // One P-FET open, one N-FET open.
            BspSetHBridgePin(bus, kFet4, true);
            BspSetHBridgePin(bus, kFet2, false);
            // One P-FET closed, one N-FET closed.
            BspSetHBridgePin(bus, kFet3, true);
            BspSetHBridgePin(bus, kFet1, false);
            break;
        case BridgeReverse:
            // One P-FET open, one N-FET open.
            BspSetHBridgePin(bus, kFet1, true);
            BspSetHBridgePin(bus, kFet3, false);
            // One P-FET closed, one N-FET closed.
            BspSetHBridgePin(bus, kFet2, true);
            BspSetHBridgePin(bus, kFet4, false);
            break;
        case BridgeOpen:
            // All FETs open
            BspSetHBridgePin(bus, kFet1, true);
            BspSetHBridgePin(bus, kFet4, true);
            BspSetHBridgePin(bus, kFet2, false);
            BspSetHBridgePin(bus, kFet3, false);
            break;
    }
}
