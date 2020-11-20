/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== gui.xml ==================
static const unsigned char temp_binary_data_0[] =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"
"\r\n"
"<magic>\r\n"
"  <Styles>\r\n"
"    <Style name=\"default\">\r\n"
"      <Nodes/>\r\n"
"      <Classes>\r\n"
"        <plot-view border=\"2\" background-color=\"black\" border-color=\"silver\" display=\"contents\"/>\r\n"
"        <nomargin margin=\"0\" padding=\"0\" border=\"0\"/>\r\n"
"        <group margin=\"5\" padding=\"5\" border=\"2\" flex-direction=\"column\"/>\r\n"
"      </Classes>\r\n"
"      <Types>\r\n"
"        <Slider border=\"0\" slider-textbox=\"textbox-below\"/>\r\n"
"        <ToggleButton border=\"0\" max-height=\"50\" caption-size=\"0\" text=\"Active\"/>\r\n"
"        <TextButton border=\"0\" max-height=\"50\" caption-size=\"0\"/>\r\n"
"        <ComboBox border=\"0\" max-height=\"50\" caption-size=\"0\"/>\r\n"
"        <Plot border=\"0\" margin=\"0\" padding=\"0\" background-color=\"00000000\"\r\n"
"              radius=\"0\"/>\r\n"
"        <XYDragComponent border=\"0\" margin=\"0\" padding=\"0\" background-color=\"00000000\"\r\n"
"                         radius=\"0\"/>\r\n"
"      </Types>\r\n"
"      <Palettes>\r\n"
"        <default/>\r\n"
"      </Palettes>\r\n"
"    </Style>\r\n"
"  </Styles>\r\n"
"  <View id=\"root\" resizable=\"1\" resize-corner=\"1\" background-color=\"FF455060\">\r\n"
"    <View caption=\"HAMMER CONTROLS\" class=\"group\" lookAndFeel=\"FoleysFinest\"\r\n"
"          background-color=\"FF455060\">\r\n"
"      <View background-color=\"FF455060\" min-height=\"0\" max-height=\"60\" flex-direction=\"row-reverse\">\r\n"
"        <View background-color=\"FF455060\" flex-direction=\"row\"/>\r\n"
"        <ToggleButton parameter=\"BANG\" max-width=\"50\" max-height=\"50\" toggle-text=\"play\"\r\n"
"                      text=\"Play\" tab-caption=\"\" background-color=\"FF455060\" lookAndFeel=\"FoleysFinest\"\r\n"
"                      image-placement=\"centred\"/>\r\n"
"        <Label justification=\"centred-left\" editable=\"0\" background-color=\"FF455060\"\r\n"
"               max-height=\"50\" text=\"\" font-size=\"14\"/>\r\n"
"      </View>\r\n"
"      <Slider parameter=\"FOR\" slider-type=\"linear-vertical\" background-color=\"FF455060\"\r\n"
"              lookAndFeel=\"LookAndFeel_V1\" caption=\"External Force\" flex-align-self=\"auto\"\r\n"
"              slider-textbox=\"textbox-below\"/>\r\n"
"      <Slider caption=\"Velocity\" parameter=\"VEL\" lookAndFeel=\"LookAndFeel_V1\"\r\n"
"              image-placement=\"stretch\" background-color=\"FF455060\" slider-type=\"linear-vertical\"/>\r\n"
"      <Slider caption=\"Mass\" parameter=\"MASS\" background-color=\"FF455060\" slider-type=\"linear-vertical\"\r\n"
"              lookAndFeel=\"LookAndFeel_V1\"/>\r\n"
"    </View>\r\n"
"    <View caption=\"RESONATOR CONTROLS\" class=\"group\" background-color=\"FF455060\">\r\n"
"      <Slider caption=\"Frequency0\" parameter=\"FREQ0\" lookAndFeel=\"LookAndFeel_V2\"\r\n"
"              background-color=\"FF455060\"/>\r\n"
"      <Slider caption=\"Frequency1\" parameter=\"FREQ1\" lookAndFeel=\"LookAndFeel_V2\"\r\n"
"              background-color=\"FF455060\"/>\r\n"
"      <Slider caption=\"Frequency2\" parameter=\"FREQ2\" lookAndFeel=\"LookAndFeel_V2\"\r\n"
"              background-color=\"FF455060\"/>\r\n"
"      <Slider caption=\"Decay0\" parameter=\"DEC0\" lookAndFeel=\"LookAndFeel_V2\"\r\n"
"              background-color=\"FF455060\"/>\r\n"
"      <Slider caption=\"Decay1\" parameter=\"DEC1\" lookAndFeel=\"LookAndFeel_V2\"\r\n"
"              background-color=\"FF455060\"/>\r\n"
"      <Slider caption=\"Decay2\" parameter=\"DEC2\" lookAndFeel=\"LookAndFeel_V2\"\r\n"
"              background-color=\"FF455060\"/>\r\n"
"      <Slider caption=\"Gain Pickup1 Mode0\" parameter=\"GAINPICK10\" lookAndFeel=\"LookAndFeel_V2\"\r\n"
"              background-color=\"FF455060\"/>\r\n"
"      <Slider caption=\"Gain Pickup0 Mode1\" parameter=\"GAINPICK11\" lookAndFeel=\"LookAndFeel_V2\"\r\n"
"              background-color=\"FF455060\"/>\r\n"
"      <Slider caption=\"Gain Pickup1 Mode2\" parameter=\"GAINPICK12\" lookAndFeel=\"LookAndFeel_V2\"\r\n"
"              background-color=\"FF455060\"/>\r\n"
"    </View>\r\n"
"    <View flex-direction=\"column\" background-color=\"FF455060\">\r\n"
"      <View caption=\"IMPACT PARAMETERS\" class=\"group\" background-color=\"FF455060\">\r\n"
"        <Slider caption=\"Stiffness\" parameter=\"STIFF\" background-color=\"FF455060\"\r\n"
"                lookAndFeel=\"LookAndFeel_V2\"/>\r\n"
"        <Slider caption=\"Shape\" parameter=\"SH\" background-color=\"FF455060\" lookAndFeel=\"LookAndFeel_V2\"/>\r\n"
"        <Slider caption=\"Dissipation\" parameter=\"DISS\" background-color=\"FF455060\"\r\n"
"                lookAndFeel=\"LookAndFeel_V2\"/>\r\n"
"      </View>\r\n"
"      <View caption=\"\" class=\"group\" background-color=\"FF455060\">\r\n"
"        <Slider caption=\"Volume\" parameter=\"VOL\" background-color=\"FF455060\"\r\n"
"                lookAndFeel=\"Skeuomorphic\" max-width=\"300\" max-height=\"300\" flex-align-self=\"stretch\"\r\n"
"                slider-type=\"rotary\"/>\r\n"
"      </View>\r\n"
"    </View>\r\n"
"  </View>\r\n"
"</magic>\r\n"
"\0";

const char* gui_xml = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x163d7b13:  numBytes = 4481; return gui_xml;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "gui_xml"
};

const char* originalFilenames[] =
{
    "gui.xml"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
    {
        if (namedResourceList[i] == resourceNameUTF8)
            return originalFilenames[i];
    }

    return nullptr;
}

}
