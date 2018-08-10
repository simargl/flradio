#include "gui.h"

// Progress bar
void progress_changed() {
    int pos = progress->value();
    AudioPlayer a;
    a.set_position(pos);
}

// Volume
void volume_changed() {
    int vol = volume->value();
    AudioPlayer a;
    a.set_volume(vol);
}

// Pause button
void clicked_pause() {
    AudioPlayer a;
    a.pause_playback();
}

// Play button
void clicked_play() {
    AudioPlayer a;
    a.unpause_playback();
}

// Show about window 
static void cb_bclose(Fl_Button*, void*) {
  about_window->hide();
}

Fl_Double_Window* clicked_about() {
    about_window = new Fl_Double_Window(365, 265, "About Dialog");
    about_window->color((Fl_Color)24);
    bclose = new Fl_Button(300, 240, 60, 20, "Close");
    bclose->box(FL_FLAT_BOX);
    bclose->color(FL_DARK2);
    bclose->selection_color((Fl_Color)43);
    bclose->labelfont(4);
    bclose->labelsize(12);
    bclose->labelcolor(FL_GRAY0);
    bclose->callback((Fl_Callback*)cb_bclose);
    tab = new Fl_Tabs(5, 5, 355, 230);
    tab->color(FL_DARK2);
    g1 = new Fl_Group(5, 35, 355, 200, "About");
    g1->color(FL_DARK2);
    g1->selection_color(FL_DARK2);
    new Fl_Box(5, 40, 355, 195, "FLRadio\n1.0.7\nCross-platform internet radio player\nCopyright \302\251 2015\n<https://github.org/simargl>");
    g1->end();
    g2 = new Fl_Group(5, 40, 355, 195, "Credits");
    g2->color(FL_DARK2);
    g2->selection_color(FL_DARK2);
    g2->hide();
    new Fl_Box(5, 70, 355, 40, "BASS - Audio library (free for non-commercial use)\nhttp://www.un4seen.com/bass.html");
    new Fl_Box(5, 115, 355, 40, "FLTK - Cross-platform C++ GUI toolkit (LGPL v2)\nhttp://www.fltk.org/index.php");
    new Fl_Box(5, 160, 355, 40, "RadioSure - Used stations database\nhttp://www.radiosure.com/stations/");
    g2->end();
    tab->end();
    about_window->set_modal();
    about_window->end();
    about_window->show();
    return about_window;
}

// Radio search function
void radsel_callback() {
    const char *match = radsel->value();
    if (radsel->size() < radsel_length) {
        radsel_all_callback();
    }
    if (radsel->size() == 0) {
        radsel_all_callback();
    }
    for ( int i=1; i<=radio->size(); i++ ) {
        const char *line = radio->text(i);
        std::string m = match;
        std::string l = line;
        transform(m.begin(), m.end(), m.begin(), toupper);
        transform(l.begin(), l.end(), l.begin(), toupper);
        if (l.find(m) == std::string::npos) {
            radio->hide(i);
        }
    }
    radsel_length = radsel->size();
}

// All visible when search text input length is 0
void radsel_all_callback() {
    for ( int i=1; i<=radio->size(); i++ ) {
        radio->show(i);
    }
}

// Shows number of stations in output box
void radio_info_update() {
    int items = radio->size();
    std::stringstream temp_str;
    temp_str<< items;
    std::string str = temp_str.str();
    const char* cstr2 = str.c_str();
    radioinfo->value(cstr2);
}

// Show stations from country
void country_callback() {
    int v = country->value();
    Stations s;
    radio->clear();
    if (v == 0)
        s.add_all(radio);
    if (v == 1)
        s.add_serbia(radio);  
    if (v == 2)
        s.add_bosnia(radio);      
    if (v == 3)
        s.add_croatia(radio);  
    if (v == 4)
        s.add_switzerland(radio);  
    if (v == 5)
        s.add_slovenia(radio);      
    if (v == 6)
        s.add_austria(radio);
    radio_info_update();
}

// Radio browser item clicked
void radio_callback() {
    int index = radio->value();
    if (index == 0) return;
    file = radio->text(index);
    std::string s = file;
    std::string delimiter = "|";
    std::string url = s.substr(s.find(delimiter) + 1, -1);
    std::string title = s.substr(0, s.find(delimiter));
    const char * ru = url.c_str();
    const char * rt = title.c_str();
    AudioPlayer a;
    a.start_playback_url(ru);
    main_window->label(rt);
}

// Update progress bar (this runs on startup)
void update_progress(void*) {
    AudioPlayer a;
    progress->value(a.get_position());
    Fl::repeat_timeout(1, update_progress);
}

// Add all stations (this runs on startup)
void add_stations() {
    Stations s;
    s.add_all(radio);
    radio_info_update();
}

int main(int argc, char **argv) {
    main_window = new Fl_Double_Window(830, 545, "FLRadio");
    main_window->color((Fl_Color)24);
    main_window->align(Fl_Align(FL_ALIGN_TEXT_OVER_IMAGE));
    Fl_Group* g1 = new Fl_Group(5, 5, 820, 45);
    g1->color((Fl_Color)24);
    
    progress = new Fl_Value_Slider(5, 5, 540, 20);
    progress->type(1);
    progress->box(FL_FLAT_BOX);
    progress->color(FL_DARK2);
    progress->selection_color((Fl_Color)61);
    progress->labelsize(12);
    progress->labelcolor(FL_GRAY0);
    progress->minimum(-1);
    progress->maximum(300);
    progress->step(1);
    progress->value(-1);
    progress->textsize(12);
    progress->textcolor(FL_GRAY0);
    progress->callback((Fl_Callback*)progress_changed);
    progress->type(FL_HOR_FILL_SLIDER);
    
    volume = new Fl_Slider(550, 5, 80, 20);
    volume->type(1);
    volume->box(FL_FLAT_BOX);
    volume->color(FL_DARK2);
    volume->selection_color((Fl_Color)61);
    volume->labelsize(12);
    volume->labelcolor(FL_GRAY0);
    volume->maximum(100);
    volume->step(1);
    volume->value(100);
    volume->callback((Fl_Callback*)volume_changed);
    volume->type(FL_HOR_FILL_SLIDER);

    button_pause = new Fl_Button(635, 5, 60, 20, "pause");
    button_pause->box(FL_FLAT_BOX);
    button_pause->selection_color((Fl_Color)43);
    button_pause->labelfont(4);
    button_pause->labelsize(12);
    button_pause->labelcolor(FL_GRAY0);
    button_pause->callback((Fl_Callback*)clicked_pause);
    
    button_play = new Fl_Button(700, 5, 60, 20, "play");
    button_play->box(FL_FLAT_BOX);
    button_play->selection_color((Fl_Color)43);
    button_play->labelfont(4);
    button_play->labelsize(12);
    button_play->labelcolor(FL_GRAY0);
    button_play->callback((Fl_Callback*)clicked_play);
    
    button_about = new Fl_Button(765, 5, 60, 20, "about");
    button_about->box(FL_FLAT_BOX);
    button_about->selection_color((Fl_Color)43);
    button_about->labelfont(4);
    button_about->labelsize(12);
    button_about->labelcolor(FL_GRAY0);
    button_about->callback((Fl_Callback*)clicked_about);
      
    radsel = new Fl_Input(5, 30, 540, 20);
    radsel->box(FL_FLAT_BOX);
    radsel->color(FL_DARK2);
    radsel->selection_color((Fl_Color)61);
    radsel->labelfont(4);
    radsel->labelcolor(FL_GRAY0);
    radsel->textfont(5);
    radsel->textsize(12);
    radsel->textcolor(FL_GRAY0);
    radsel->callback((Fl_Callback*)radsel_callback);
    radsel->align(Fl_Align(FL_ALIGN_TEXT_OVER_IMAGE));
    radsel->when(FL_WHEN_CHANGED);
      
    country = new Fl_Choice(635, 30, 190, 20);
    country->down_box(FL_BORDER_BOX);
    country->selection_color((Fl_Color)43);
    country->textfont(4);
    country->textsize(12);
    country->callback((Fl_Callback*)country_callback);
    country->add("All");country->add("Serbia");country->add("Bosnia");country->add("Croatia");country->add("Switzerland");country->add("Slovenia");country->add("Austria");
    country->value(0);
      
    radioinfo = new Fl_Output(550, 30, 80, 20);
    radioinfo->box(FL_FLAT_BOX);
    radioinfo->color((Fl_Color)53);
    radioinfo->selection_color((Fl_Color)61);
    radioinfo->textfont(4);
    radioinfo->textsize(12);
    g1->end();
    
    radio = new Fl_Browser(5, 55, 820, 485);
    radio->box(FL_FLAT_BOX);
    radio->color(FL_GRAY0);
    radio->selection_color(FL_DARK_BLUE);
    radio->labelfont(4);
    radio->textfont(4);
    radio->textsize(15);
    radio->textcolor((Fl_Color)61);
    radio->callback((Fl_Callback*)radio_callback);
    radio->type(FL_MULTI_BROWSER);
    int widths[] = { 420,420,420 };
    radio->column_widths(widths);
    radio->column_char('|');
    
    main_window->size_range(500, 300);
    main_window->end();
    add_stations();

    const char *name = "flradio.png"; 
    Fl_PNG_Image *img = new Fl_PNG_Image(name);
    main_window->icon(img);
    
    Fl::add_timeout(1.0, update_progress);
    Fl::focus(radsel);
    
    main_window->resizable(radio);
    main_window->show(argc, argv);
    return Fl::run();
}
