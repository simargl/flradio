#include <iostream>
#include <unistd.h>
#include <FL/Fl_Browser.H>

class Stations
{
    public:
        void add_serbia(Fl_Browser *r);
        void add_bosnia(Fl_Browser *r);
        void add_croatia(Fl_Browser *r);
        void add_switzerland(Fl_Browser *r);
        void add_slovenia(Fl_Browser *r);
        void add_austria(Fl_Browser *r);
        void add_all(Fl_Browser *r);
};
