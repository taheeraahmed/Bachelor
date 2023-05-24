#include "utils/utils.h"

const char *modeToString(Mode mode)
{
    switch (mode)
    {
    case NIR_LIGHT:
        return "NIR-lys";
    case PLACEBO:
        return "Placebo";
    case RANDOMIZED:
        return "Randomisert";
    default:
        return "UNKNOWN_MODE";
    }
}

const char *durationToString(Duration duration)
{
    switch (duration)
    {
    case DURATION_20_MIN:
        return "20 min";
    case DURATION_30_MIN:
        return "30 min";
    case DURATION_40_MIN:
        return "40 min";
    default:
        return "UNKNOWN_DURATION";
    }
}

const char *pvmFreqToString(PvmFreq pvmFreq)
{
    switch (pvmFreq)
    {
    case CONTINOUS:
        return "Kontinuerlig";
    case LOW_FREQ:
        return "Lav frekvent";
    case HIGH_FREQ:
        return "Hoy frekvent";
    default:
        return "UNKNOWN_PVM_FREQ";
    }
}

Mode stringToMode(const String &str)
{
    if (str == "NIR-lys")
    {
        return NIR_LIGHT;
    }
    else if (str == "Placebo")
    {
        return PLACEBO;
    }
    else if (str == "Randomisert")
    {
        return RANDOMIZED;
    }
    else {
        return UNKNOWN_MODE;
    }
}

Duration stringToDuration(const String &str)
{
    if (str == "20 min")
    {
        return DURATION_20_MIN;
    }
    else if (str == "30 min")
    {
        return DURATION_30_MIN;
    }
    else if (str == "40 min")
    {
        return DURATION_40_MIN;
    }
    else {
        return UNKNOWN_DURATION;
    }
}

PvmFreq stringToPvmFreq(const String &str)
{
    if (str == "Kontinuerlig")
    {
        return CONTINOUS;
    }
    else if (str == "Lav frekvent")
    {
        return LOW_FREQ;
    }
    else if (str == "Hoy frekvent")
    {
        return HIGH_FREQ;
    }
    else {
        return UNKNOWN_PVM_FREQ;
    }
}
