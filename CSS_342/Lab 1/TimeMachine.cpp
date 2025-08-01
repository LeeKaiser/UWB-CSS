#include "TimeSpan.h"

void testTimeSpan();

int main()
{
    testTimeSpan();
    return 0;
}

void testTimeSpan()
{
    /*
    correctNumbers method
    paramiter: higherUnit, lowerUnit

    makes it so that the time unites are scaled properately and rounded.
    */

    // test constructor
    TimeSpan ts0;
    TimeSpan ts1(3, 3, 3);
    TimeSpan ts2(-3, -3, -3);
    TimeSpan ts3(2.3, 5.3, 0.6);
    TimeSpan ts4(-0.6, -123, 5);
    TimeSpan ts5(0, 654.12, 4621);
    TimeSpan ts6(0, -0, 999999999);
    TimeSpan ts7(0, 0, -999999999);

    // constructor test answer
    TimeSpan ta0(0, 0, 0);
    TimeSpan ta1(3, 3, 3);
    TimeSpan ta2(-3, -3, -3);
    TimeSpan ta3(2, 23, 19);
    TimeSpan ta4(-2, -38, -55);
    TimeSpan ta5(12, 11, 8);
    TimeSpan ta6(277777, 46, 39);
    TimeSpan ta7(-277777, -46, -39);

    TimeSpan ta3PTa4(0, -15, -36);
    TimeSpan ta3MTa4(5, 2, 14);

    // print results for various testingtest
    ta0 == ts0 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    ta1 == ts1 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    ta2 == ts2 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    ta3 == ts3 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    ta4 == ts4 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    ta5 == ts5 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    ta6 == ts6 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    ta7 == ts7 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    // test addition overload
    ts1 + ts2 == ta0 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    // test equals and unary negation overload
    ta1 == -ts2 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    ta2 == -ts1 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    -ts6 == ta7 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    // test addition overload (again)
    ta3 + ta4 == ta3PTa4 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    // test not equals overload
    ts1 != ta5 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    ts7 != ta3 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    ts2 != ta1 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    ts7 + ta0 != ta3 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    // test subtraction overload
    ta3 - ta4 == ta3MTa4 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    // test += and -= overload
    ta3 -= ta4; // ta3 = 5,2,14
    ta0 += ta6; // ta0 = 277777,46,39
    ta6 += ta5; // ta6 = 277789,57,47
    ta5 -= ta3; // ta5 = 7,8,54

    TimeSpan ta0PTa6(277777, 46, 39);
    TimeSpan ta6Pta5(277789, 57, 47);
    TimeSpan ta5Mta3(7, 8, 54);

    ta3 == ta3MTa4 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    ta0 == ta0PTa6 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    ta6 == ta6Pta5 ? cout << "PASSED" << endl : cout << "FAILED" << endl;
    ta5 == ta5Mta3 ? cout << "PASSED" << endl : cout << "FAILED" << endl;

    // test  >> overload

    TimeSpan ti0;
    TimeSpan ti1;
    TimeSpan ti2;
    TimeSpan ti3;
    cout << "Testing << operator" << endl;
    cout << "input : 5 hours, 3 mins, 9 secs" << endl; // 5,3,9
    cin >> ti0;
    cout << "input: 3.5 Hours, 843.5 mins, 999.999 secs" << endl; // 17,50,10
    cin >> ti1;
    cout << "input: 9999 Hours, -12 mins, -0 secs" << endl; // 9998,48,0
    cin >> ti2;
    cout << "input: -12 hours, -6543 mins, 14.00001 secs" << endl; // -121,-2,-46
    cin >> ti3;

    TimeSpan tia0(5, 3, 9);
    TimeSpan tia1(17, 50, 10);
    TimeSpan tia2(9998, 48, 0);
    TimeSpan tia3(-121, -2, -46);

    ti0 == tia0 ? cout << "PASSED" << endl : cout << "FAILED" << ti0 << tia0 << endl;
    ti1 == tia1 ? cout << "PASSED" << endl : cout << "FAILED" << ti1 << tia1 << endl;
    ti2 == tia2 ? cout << "PASSED" << endl : cout << "FAILED" << ti2 << tia2 << endl;
    ti3 == tia3 ? cout << "PASSED" << endl : cout << "FAILED" << ti3 << tia3 << endl;
}