#include <iostream>

using namespace std;

//check every character one by one.
//if one doesn't match, use plausibility
//forloops
//fxrlxxp
//1: same
//2: different, so o:x is plausible for silly
//3: same, so plaus.silly doesn't change
//4: same
//5: different, and it's o:x again so it's still plausible
//6: different but it's o:x
//7: same
//8: null, so s is plausible for quiet
//at the end: o:x = silly & s is quiet

//forloops
//frlpz
//1: same
//2: different, so o:r is plaus for silly
//3: different but it's r:l so o:r is not plaus and silly is null and quiet is o
    //initiate a skip to the next array value that makes sense
    //(we decrement every step)
        //we start at 3 for preinput, because:
            //it's the number after where (o) is stored
        //we start at 1 for postinput, because:
        //(3,3) is different
        //(3,2) is SAME
//3,2: same
//4,3: same
//5,4: different

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);


    return 0;
}