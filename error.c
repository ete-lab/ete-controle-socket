#include <stdio.h>

char *Error(int value){
    switch (value) {
    case 0:
        return "CAMAC operation successful, gave Q and X\n";
        break;
    case 1:
        return " CAMAC operation return ed X but no Q\n";
        break;
    case 2:
        return " CAMAC operation return ed Q but no X\n";
        break;
    case 3:
        return " CAMAC operation successful, no Q or X\n";
        break;
    case 64:
        return " Crate no. not in range 0..3\n";
        break;
    case 65:
        return " Station no. not in range 1..24\n";
        break;
    case 66:
        return " Sub-address not in range 0..15\n";
        break;
    case 67:
        return " Function code not in range 0..41\n";
        break;
    case 68:
        return " Illegal LAM no.\n";
        break;
    case 69:
        return " Illegal LAM identifier\n";
        break;
    case 70:
        return " LAM already linked\n";
        break;
    case 71:
        return " Illegal repeat count\n";
        break;
    case 72:
        return " 4th element of control block CB illegal\n";
        break;
    case 73:
        return " Illegal mode - bit mode not valid\n";
        break;
    case 74:
        return " Failed to open configuration file config.dat\n";
        break;
    case 99:
        return " 1330 controller error - no CAMAC cycle\n";
        break;
    default:
        return " Erro %d nao catalogado.\n";
    }

}