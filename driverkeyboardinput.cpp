/*
This Source Code Form is subject to the
terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not
distributed with this file, You can
obtain one at
http://mozilla.org/MPL/2.0/.
*/

#include "stdafx.h"
#include "driverkeyboardinput.h"

bool
driverkeyboard_input::init() {

    default_bindings();
    recall_bindings();
    bind();
    m_bindingsetups.clear();

    return true;
}

void
driverkeyboard_input::default_bindings() {

    m_bindingsetups = {
        { user_command::aidriverenable, GLFW_KEY_Q | keymodifier::shift },
        { user_command::aidriverdisable, GLFW_KEY_Q },
        // jointcontrollerset,
        { user_command::mastercontrollerincrease, GLFW_KEY_KP_ADD },
        { user_command::mastercontrollerincreasefast, GLFW_KEY_KP_ADD | keymodifier::shift },
        { user_command::mastercontrollerdecrease, GLFW_KEY_KP_SUBTRACT },
        { user_command::mastercontrollerdecreasefast, GLFW_KEY_KP_SUBTRACT | keymodifier::shift },
        // mastercontrollerset,
        { user_command::secondcontrollerincrease, GLFW_KEY_KP_DIVIDE },
        { user_command::secondcontrollerincreasefast, GLFW_KEY_KP_DIVIDE | keymodifier::shift },
        { user_command::secondcontrollerdecrease, GLFW_KEY_KP_MULTIPLY },
        { user_command::secondcontrollerdecreasefast, GLFW_KEY_KP_MULTIPLY | keymodifier::shift },
        // secondcontrollerset,
        { user_command::mucurrentindicatorothersourceactivate, GLFW_KEY_Z | keymodifier::shift },
        { user_command::independentbrakeincrease, GLFW_KEY_KP_1 },
        { user_command::independentbrakeincreasefast, GLFW_KEY_KP_1 | keymodifier::shift },
        { user_command::independentbrakedecrease, GLFW_KEY_KP_7 },
        { user_command::independentbrakedecreasefast, GLFW_KEY_KP_7 | keymodifier::shift },
        // independentbrakeset,
        { user_command::independentbrakebailoff, GLFW_KEY_KP_4 },
        // universalbrakebutton1,
        // universalbrakebutton2,
        // universalbrakebutton3,
        { user_command::trainbrakeincrease, GLFW_KEY_KP_3 },
        { user_command::trainbrakedecrease, GLFW_KEY_KP_9 },
        // trainbrakeset,
        { user_command::trainbrakecharging, GLFW_KEY_KP_DECIMAL },
        { user_command::trainbrakerelease, GLFW_KEY_KP_6 },
        { user_command::trainbrakefirstservice, GLFW_KEY_KP_8 },
        { user_command::trainbrakeservice, GLFW_KEY_KP_5 },
        { user_command::trainbrakefullservice, GLFW_KEY_KP_2 },
        { user_command::trainbrakehandleoff, GLFW_KEY_KP_5 | keymodifier::control },
        { user_command::trainbrakeemergency, GLFW_KEY_KP_0 },
        { user_command::trainbrakebasepressureincrease, GLFW_KEY_KP_3 | keymodifier::control },
        { user_command::trainbrakebasepressuredecrease, GLFW_KEY_KP_9 | keymodifier::control },
        { user_command::trainbrakebasepressurereset, GLFW_KEY_KP_6 | keymodifier::control },
        { user_command::trainbrakeoperationtoggle, GLFW_KEY_KP_4 | keymodifier::control },
        { user_command::manualbrakeincrease, GLFW_KEY_KP_1 | keymodifier::control },
        { user_command::manualbrakedecrease, GLFW_KEY_KP_7 | keymodifier::control },
        { user_command::alarmchaintoggle, GLFW_KEY_B | keymodifier::shift | keymodifier::control },
        { user_command::wheelspinbrakeactivate, GLFW_KEY_KP_ENTER },
        { user_command::sandboxactivate, GLFW_KEY_S | keymodifier::shift },
        // autosandboxtoggle,
        // autosandboxactivate,
        // autosandboxdeactivate,
        { user_command::reverserincrease, GLFW_KEY_D },
        { user_command::reverserdecrease, GLFW_KEY_R },
        // reverserforwardhigh,
        // reverserforward,
        // reverserneutral,
        // reverserbackward,
        { user_command::waterpumpbreakertoggle, GLFW_KEY_W | keymodifier::control },
        // waterpumpbreakerclose,
        // waterpumpbreakeropen,
        { user_command::waterpumptoggle, GLFW_KEY_W },
        // waterpumpenable,
        // waterpumpdisable,
        { user_command::waterheaterbreakertoggle, GLFW_KEY_W | keymodifier::control | keymodifier::shift },
        // waterheaterbreakerclose,
        // waterheaterbreakeropen,
        { user_command::waterheatertoggle, GLFW_KEY_W | keymodifier::shift },
        // waterheaterenable,
        // waterheaterdisable,
        { user_command::watercircuitslinktoggle, GLFW_KEY_H | keymodifier::shift },
        // watercircuitslinkenable,
        // watercircuitslinkdisable,
        { user_command::fuelpumptoggle, GLFW_KEY_F },
        // fuelpumpenable,
        // fuelpumpdisable,
        { user_command::oilpumptoggle, GLFW_KEY_F | keymodifier::shift },
        // oilpumpenable,
        // oilpumpdisable,
        { user_command::linebreakertoggle, GLFW_KEY_M },
        // linebreakeropen,
        // linebreakerclose,
        { user_command::convertertoggle, GLFW_KEY_X },
        // converterenable,
        // converterdisable,
        { user_command::convertertogglelocal, GLFW_KEY_X | keymodifier::shift },
        { user_command::converteroverloadrelayreset, GLFW_KEY_N | keymodifier::control },
        { user_command::compressortoggle, GLFW_KEY_C },
        // compressorenable,
        // compressordisable,
        { user_command::compressortogglelocal, GLFW_KEY_C | keymodifier::shift },
        // compressorpresetactivatenext,
        // compressorpresetactivateprevious,
        // compressorpresetactivatedefault,
        { user_command::motoroverloadrelaythresholdtoggle, GLFW_KEY_F | keymodifier::control },
        // motoroverloadrelaythresholdsetlow,
        // motoroverloadrelaythresholdsethigh,
        { user_command::motoroverloadrelayreset, GLFW_KEY_N },
        // universalrelayreset1,
        // universalrelayreset2,
        // universalrelayreset3,
        { user_command::notchingrelaytoggle, GLFW_KEY_G },
        { user_command::epbrakecontroltoggle, GLFW_KEY_Z | keymodifier::control },
        { user_command::trainbrakeoperationmodeincrease, GLFW_KEY_KP_2 | keymodifier::control },
        { user_command::trainbrakeoperationmodedecrease, GLFW_KEY_KP_8 | keymodifier::control },
        { user_command::brakeactingspeedincrease, GLFW_KEY_B | keymodifier::shift },
        { user_command::brakeactingspeeddecrease, GLFW_KEY_B },
        // brakeactingspeedsetcargo,
        // brakeactingspeedsetpassenger,
        // brakeactingspeedsetrapid,
        { user_command::brakeloadcompensationincrease, GLFW_KEY_H | keymodifier::shift | keymodifier::control },
        { user_command::brakeloadcompensationdecrease, GLFW_KEY_H | keymodifier::control },
        { user_command::mubrakingindicatortoggle, GLFW_KEY_L | keymodifier::shift },
        { user_command::alerteracknowledge, GLFW_KEY_SPACE },
        { user_command::hornlowactivate, GLFW_KEY_A },
        { user_command::hornhighactivate, GLFW_KEY_S },
        { user_command::whistleactivate, GLFW_KEY_Z },
        { user_command::radiotoggle, GLFW_KEY_R | keymodifier::control },
        { user_command::radiochannelincrease, GLFW_KEY_R | keymodifier::shift },
        { user_command::radiochanneldecrease, GLFW_KEY_R },
        { user_command::radiostopsend, GLFW_KEY_PAUSE | keymodifier::shift | keymodifier::control },
        { user_command::radiostoptest, GLFW_KEY_R | keymodifier::shift | keymodifier::control },
        { user_command::radiocall3send, GLFW_KEY_BACKSPACE },
        // radiovolumeincrease,
        // radiovolumedecrease,
        { user_command::cabchangeforward, GLFW_KEY_HOME },
        { user_command::cabchangebackward, GLFW_KEY_END },
        // viewturn,
        // movehorizontal,
        // movehorizontalfast,
        // movevertical,
        // moveverticalfast,
        { user_command::moveleft, GLFW_KEY_LEFT },
        { user_command::moveright, GLFW_KEY_RIGHT },
        { user_command::moveforward, GLFW_KEY_UP },
        { user_command::moveback, GLFW_KEY_DOWN },
        { user_command::moveup, GLFW_KEY_PAGE_UP },
        { user_command::movedown, GLFW_KEY_PAGE_DOWN },
        { user_command::nearestcarcouplingincrease, GLFW_KEY_INSERT },
        { user_command::nearestcarcouplingdisconnect, GLFW_KEY_DELETE },
        { user_command::nearestcarcoupleradapterattach, GLFW_KEY_INSERT | keymodifier::control },
        { user_command::nearestcarcoupleradapterremove, GLFW_KEY_DELETE | keymodifier::control },
        { user_command::occupiedcarcouplingdisconnect, GLFW_KEY_DELETE | keymodifier::shift },
        { user_command::doortoggleleft, GLFW_KEY_COMMA },
        { user_command::doortoggleright, GLFW_KEY_PERIOD },
        { user_command::doorpermitleft, GLFW_KEY_COMMA | keymodifier::shift },
        { user_command::doorpermitright, GLFW_KEY_PERIOD | keymodifier::shift },
        { user_command::doorpermitpresetactivatenext, GLFW_KEY_PERIOD | keymodifier::shift | keymodifier::control },
        { user_command::doorpermitpresetactivateprevious, GLFW_KEY_COMMA | keymodifier::shift | keymodifier::control },
        // dooropenleft,
        // dooropenright,
        { user_command::dooropenall, GLFW_KEY_SLASH | keymodifier::shift },
        // doorcloseleft,
        // doorcloseright,
        { user_command::doorcloseall, GLFW_KEY_SLASH | keymodifier::control },
        // doorsteptoggle,
        { user_command::doormodetoggle, GLFW_KEY_SLASH | keymodifier::shift | keymodifier::control },
        { user_command::departureannounce, GLFW_KEY_SLASH },
        { user_command::doorlocktoggle, GLFW_KEY_S | keymodifier::control },
        { user_command::pantographcompressorvalvetoggle, GLFW_KEY_V | keymodifier::control },
        // pantographcompressorvalveenable,
        // pantographcompressorvalvedisable,
        { user_command::pantographcompressoractivate, GLFW_KEY_V | keymodifier::shift },
        { user_command::pantographtogglefront, GLFW_KEY_P },
        { user_command::pantographtogglerear, GLFW_KEY_O },
        // pantographraisefront,
        // pantographraiserear,
        // pantographlowerfront,
        // pantographlowerrear,
        { user_command::pantographlowerall, GLFW_KEY_P | keymodifier::control },
        { user_command::pantographselectnext, GLFW_KEY_P | keymodifier::shift },
        { user_command::pantographselectprevious, GLFW_KEY_O | keymodifier::shift },
        { user_command::pantographtoggleselected, GLFW_KEY_O | keymodifier::shift | keymodifier::control },
        // pantographraiseselected,
        // pantographlowerselected,
        { user_command::heatingtoggle, GLFW_KEY_H },
        // heatingenable,
        // heatingdisable,
        { user_command::lightspresetactivatenext, GLFW_KEY_T | keymodifier::shift },
        { user_command::lightspresetactivateprevious, GLFW_KEY_T },
        { user_command::headlighttoggleleft, GLFW_KEY_Y },
        // headlightenableleft,
        // headlightdisableleft,
        { user_command::headlighttoggleright, GLFW_KEY_I },
        // headlightenableright,
        // headlightdisableright,
        { user_command::headlighttoggleupper, GLFW_KEY_U },
        // headlightenableupper,
        // headlightdisableupper,
        { user_command::redmarkertoggleleft, GLFW_KEY_Y | keymodifier::shift },
        // redmarkerenableleft,
        // redmarkerdisableleft,
        { user_command::redmarkertoggleright, GLFW_KEY_I | keymodifier::shift },
        // redmarkerenableright,
        // redmarkerdisableright,
        { user_command::headlighttogglerearleft, GLFW_KEY_Y | keymodifier::control },
        { user_command::headlighttogglerearright, GLFW_KEY_I | keymodifier::control },
        { user_command::headlighttogglerearupper, GLFW_KEY_U | keymodifier::control },
        { user_command::redmarkertogglerearleft, GLFW_KEY_Y | keymodifier::control | keymodifier::shift },
        { user_command::redmarkertogglerearright, GLFW_KEY_I | keymodifier::control | keymodifier::shift },
        { user_command::redmarkerstoggle, GLFW_KEY_E | keymodifier::shift },
        { user_command::endsignalstoggle, GLFW_KEY_E },
        { user_command::headlightsdimtoggle, GLFW_KEY_L | keymodifier::control },
        // headlightsdimenable,
        // headlightsdimdisable,
        { user_command::motorconnectorsopen, GLFW_KEY_L },
        // motorconnectorsclose,
        { user_command::motordisconnect, GLFW_KEY_E | keymodifier::control },
        { user_command::interiorlighttoggle, GLFW_KEY_APOSTROPHE },
        // interiorlightenable,
        // interiorlightdisable,
        { user_command::interiorlightdimtoggle, GLFW_KEY_APOSTROPHE | keymodifier::control },
        // interiorlightdimenable,
        // interiorlightdimdisable,
        // compartmentlightstoggle,
        // compartmentlightsenable,
        // compartmentlightsdisable,
        { user_command::instrumentlighttoggle, GLFW_KEY_SEMICOLON },
        // instrumentlightenable,
        // instrumentlightdisable,
        { user_command::dashboardlighttoggle, GLFW_KEY_SEMICOLON | keymodifier::shift },
        { user_command::timetablelighttoggle, GLFW_KEY_APOSTROPHE | keymodifier::shift },
        { user_command::generictoggle0, GLFW_KEY_0 },
        { user_command::generictoggle1, GLFW_KEY_1 },
        { user_command::generictoggle2, GLFW_KEY_2 },
        { user_command::generictoggle3, GLFW_KEY_3 },
        { user_command::generictoggle4, GLFW_KEY_4 },
        { user_command::generictoggle5, GLFW_KEY_5 },
        { user_command::generictoggle6, GLFW_KEY_6 },
        { user_command::generictoggle7, GLFW_KEY_7 },
        { user_command::generictoggle8, GLFW_KEY_8 },
        { user_command::generictoggle9, GLFW_KEY_9 },
        { user_command::batterytoggle, GLFW_KEY_J },
        // batteryenable,
        // batterydisable,
        { user_command::motorblowerstogglefront, GLFW_KEY_N | keymodifier::shift },
        { user_command::motorblowerstogglerear, GLFW_KEY_M | keymodifier::shift },
        { user_command::motorblowersdisableall, GLFW_KEY_M | keymodifier::control },
        // coolingfanstoggle,
        // tempomattoggle,
        // springbraketoggle,
        // springbrakeenable,
        // springbrakedisable,
        // springbrakeshutofftoggle,
        // springbrakeshutoffenable,
        // springbrakeshutoffdisable,
        // springbrakerelease,
        // distancecounteractivate,
	    // speedcontrolincrease,
	    // speedcontroldecrease,
	    // speedcontrolpowerincrease,
	    // speedcontrolpowerdecrease,
	    // speedcontrolbutton0,
	    // speedcontrolbutton1,
	    // speedcontrolbutton2,
	    // speedcontrolbutton3,
	    // speedcontrolbutton4,
	    // speedcontrolbutton5,
	    // speedcontrolbutton6,
	    // speedcontrolbutton7,
	    // speedcontrolbutton8,
	    // speedcontrolbutton9,
	    // admin_timejump,
	    { user_command::timejumplarge, GLFW_KEY_F1 | keymodifier::control },
	    { user_command::timejumpsmall, GLFW_KEY_F1 | keymodifier::shift },
	    // admin_vehiclemove,
	    { user_command::vehiclemoveforwards, GLFW_KEY_LEFT_BRACKET | keymodifier::control },
	    { user_command::vehiclemovebackwards, GLFW_KEY_RIGHT_BRACKET | keymodifier::control },
	    { user_command::vehicleboost, GLFW_KEY_TAB | keymodifier::control },
	    { user_command::debugtoggle, GLFW_KEY_F12 | keymodifier::control | keymodifier::shift },
	    { user_command::pausetoggle, GLFW_KEY_ESCAPE }
    };
}

//---------------------------------------------------------------------------
