#ifndef EDEE_H_
#define EDEE_H_

class Edee {
public:
    Edee();

    void init();
    void run();
    void cleanup();

    void setState(int s);
    int getState() const;
private:
    int state;
};

#endif // EDEE_H_
