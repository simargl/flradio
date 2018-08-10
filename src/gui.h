#include <cctype>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string.h>
#include "play.h"
#include "stations.h"
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_PNG_Image.H>

Fl_Button *bclose;
Fl_Tabs *tab;
Fl_Group *g1;
Fl_Group *g2;
Fl_Double_Window *main_window;
Fl_Button *button_pause;
Fl_Button *button_play;
Fl_Value_Slider *progress;
Fl_Slider *volume;
Fl_Button *button_about;
Fl_Input *radsel;
Fl_Choice *country;
Fl_Output *radioinfo;
Fl_Browser *radio;
Fl_Double_Window *about_window;

static const char *file; 
static int radsel_length; 

void clicked_pause();
void clicked_play();
void radio_callback();
void progress_changed();
void volume_changed();
void radsel_callback();
void radsel_all_callback();
void add_stations();
void country_callback();
void radio_info_update();
Fl_Double_Window* clicked_about();
