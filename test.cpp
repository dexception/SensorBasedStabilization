#include "test.h"

void test(string videoName) {
    const int rate = 100;

    ifstream dataFile((videoName + "/TXT_" + videoName + ".txt").c_str());

    int start = 0;
    double tmp, frames;
    dataFile >> frames >> tmp;
    for (int i = 0; i < frames; ++i) {
        dataFile >> tmp;
        if (!start)
            start = tmp;
        dataFile >> tmp;

    }

    //vector<Quaternion> q;
    int i = 0;
    Quaternion p;
    p.identity();


    while (!dataFile.eof()) {
        dataFile >> tmp;
        double x, y, z;
        dataFile >> x >> y >> z;
        EulerAngles eulerAngles(y / rate, x / rate, z / rate);
        Quaternion tq;
        tq.setToRotateInertialToObject(eulerAngles);

        if (i % (100 / rate) == 0)
            p = p * tq;
        i++;
        EulerAngles e;
        e.fromInertialToObjectQuaternion(p);
        cout << tmp - start << " " << e.pitch << " " << e.heading << " " << e.bank << endl;
    }

}
