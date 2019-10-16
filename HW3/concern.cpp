//#include <iostream>
//#include <string>
//using namespace std;
    // delete ^^

class Concern
{
public:
    Concern(string name);
    virtual ~Concern();
    string person() const;
    virtual string description() const = 0;
    virtual bool possibleFelony() const;
private:
    string m_person;
};

Concern::Concern(string name)
: m_person(name)
{
    
}

Concern::~Concern()
{}

string Concern::person() const
{
    return m_person;
}

bool Concern::possibleFelony() const
{
    return false;
}

// ------------------------------------

class EthicsMatter : public Concern
{
public:
    EthicsMatter(string name);
    virtual ~EthicsMatter();
    virtual string description() const;
};

EthicsMatter::EthicsMatter(string name)
: Concern(name)
{
    
}

EthicsMatter::~EthicsMatter()
{
    cout << "Destroying " + person() + "'s ethics matter" << endl;
}

string EthicsMatter::description() const
{
    return "An ethics matter";
}

// ------------------------------------

class HushPayment : public Concern
{
public:
    HushPayment(string name, int amount);
    virtual ~HushPayment();
    virtual string description() const;
private:
    int m_amount;
};

HushPayment::HushPayment(string name, int amount)
: Concern(name), m_amount(amount)
{
    
}

HushPayment::~HushPayment()
{
    cout << "Destroying " + person() + "'s hush payment" << endl;
}

string HushPayment::description() const
{
    return "A $" + to_string(m_amount) + " payment";
}

// ------------------------------------

class Investigation : public Concern
{
public:
    Investigation(string name);
    virtual ~Investigation();
    virtual string description() const;
    virtual bool possibleFelony() const;
};

Investigation::Investigation(string name)
: Concern(name)
{
    
}

Investigation::~Investigation()
{
    cout << "Destroying " + person() + "'s investigation" << endl;
}

string Investigation::description() const
{
    return "An investigation";
}

bool Investigation::possibleFelony() const
{
    return true;
}

// ----------vvv DELETE vvv------------

/*void display(const Concern* c)
{
    cout << c->description() << " involving " << c->person();
    if (c->possibleFelony())
        cout << ", possibly felonious";
    cout << endl;
}

int main()
{
    Concern* concerns[4];
    concerns[0] = new EthicsMatter("Pruitt");
    // Hush payments have a person's name and an amount of money (an int).
    concerns[1] = new HushPayment("Clifford", 130000);
    concerns[2] = new HushPayment("McDougal", 150000);
    concerns[3] = new Investigation("Mueller");
    
    cout << "Here are the concerns:" << endl;
    for (int k = 0; k < 4; k++)
        display(concerns[k]);
    
    // Clean up the concerns before exiting
    cout << "Cleaning up:" << endl;
    for (int k = 0; k < 4; k++)
        delete concerns[k];
}*/

/*Here are the concerns:
An ethics matter involving Pruitt
A $130000 payment involving Clifford
A $150000 payment involving McDougal
An investigation involving Mueller, possibly felonious
Cleaning up:
Destroying Pruitt's ethics matter
Destroying Clifford's hush payment
Destroying McDougal's hush payment
Destroying Mueller's investigation*/
