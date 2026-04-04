#include "testlib.h"
#include <iostream>
int main(int argc, char* argv[]) {
    registerLemonChecker(argc, argv);
    int out1 = ouf.readInt(), out2 = ouf.readInt(), ans1 = ans.readInt(), ans2 = ans.readInt();
    if (out1 != ans1)
        quitf(_wa, "WA");
    else if (out2 != ans2)
    	quitp(0.4*atoi(argv[4]), "Partially Correct");
    else quitf(_ok, "Accepted");
    return 0;
}
